#include <iostream>
#include <utility>
using std::cout;
using std::endl;

// NOTE: the example will not work if you hit "Run" above due to constructor elision
// need to go to the shell tab on the right and compile with:
// make quiz
// use make quiz-elide to see how the compiler would automatically optimize this

class MyIntVector {
    static int next_id;  // used for printing
   public:
    MyIntVector();
    ~MyIntVector();
    MyIntVector(const MyIntVector& other);
    MyIntVector& operator=(const MyIntVector& other);
    MyIntVector(MyIntVector&& other);
    MyIntVector& operator=(MyIntVector&& other);
    void swap(MyIntVector& first, MyIntVector& second);
    void push_back(int val);
    void print();

   private:
    size_t size;
    size_t capacity;
    int* data;
    int id;
};

// creates a big vector with nums [0, n)
MyIntVector create_big_vector(int n) {
    MyIntVector big_vec;
    for (int i = 0; i < n; ++i) {
        big_vec.push_back(i);
    }
    return big_vec;
}

void foo(MyIntVector&& v) {
    cout << "foo with rvalue reference" << endl;
}
void foo(const MyIntVector& v) {
    cout << "foo with const lvalue reference" << endl;
}

template <typename VEC>
void bar(const VEC& vec) {
    foo(vec);
}

template <typename VEC>
void baz(VEC&& vec) {
    foo(std::forward<VEC>(vec));
}

template <typename VEC>
void bax(VEC&& vec) {
    foo(vec);
}

void bay(MyIntVector&& vec) {
    foo(vec);
}

int main() {
    MyIntVector v;
    // bar(v);
    // baz(v);
    // bax(v);
    // bay(v);

    // bar(std::move(v));
    // baz(std::move(v));
    // bax(std::move(v));
    // bay(std::move(v));

    // bar(MyIntVector());
    // baz(MyIntVector());
    // bax(MyIntVector());
    // bay(MyIntVector());
}

// bonus question:
// inside of the functions bar, baz, bax, and bay, is vec an lvalue or an rvalue?

// implementations
int MyIntVector::next_id = 1;
MyIntVector::MyIntVector() : size(0), capacity(4), data(new int[4]), id(next_id++) {
    cout << "constructing " << id << endl;
}

// destructor
MyIntVector::~MyIntVector() {
    cout << "destructing " << id << endl;
    delete[] data;
}

// copy constructor (deep copy)
MyIntVector::MyIntVector(const MyIntVector& other)
    : size(other.size), capacity(other.capacity), data(new int[other.capacity]), id(next_id++) {
    cout << "copy constructing " << id << " from " << other.id << endl;
    for (int i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}
// copy assignment operator (deep copy)
MyIntVector& MyIntVector::operator=(const MyIntVector& other) {
    cout << "copy assigning " << id << " from " << other.id << endl;
    MyIntVector temp(other);
    swap(*this, temp);
    return *this;
}

// move constructor (stealing)
MyIntVector::MyIntVector(MyIntVector&& other) : MyIntVector() {
    cout << "move constructing " << id << " from " << other.id << endl;
    // default construct ourself then swap with the other object
    swap(*this, other);
    // note: need to allow the other object to "safely" destruct
}

// move assignment operator (stealing)
MyIntVector& MyIntVector::operator=(MyIntVector&& other) {
    cout << "move assigning " << id << " from " << other.id << endl;
    swap(*this, other);
    return *this;
    // let the other object handle the destruction our data
}

void MyIntVector::swap(MyIntVector& first, MyIntVector& second) {
    std::swap(first.size, second.size);
    std::swap(first.capacity, second.capacity);
    std::swap(first.data, second.data);
}
void MyIntVector::print() {
    cout << "----------------------------------------------------" << endl;
    cout << "printing MyIntVector " << id << ":" << endl;
    cout << "size=" << size << " capacity=" << capacity << " data=[";
    for (int i = 0; i < size; i++) {
        if (i != size - 1) {
            cout << data[i] << ",";
        } else {
            cout << data[i];
        }
    }
    cout << "]" << endl;
    cout << "----------------------------------------------------" << endl;
}
void MyIntVector::push_back(int val) {
    if (size == capacity) {
        // double our array
        int* new_data = new int[capacity * 2];
        for (int i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }

        // now replace data ptr with newly allocated array
        delete[] data;
        data = new_data;
        capacity *= 2;
    }

    // actually do the push_back
    data[size++] = val;
}