#include <iostream>
using std::cout;
using std::endl;

// NOTE: the example will not work if you hit "Run" above due to constructor elision
// need to go to the shell tab on the right and compile with:
// make copy
// use make copy-elide to see how the compiler would automatically optimize this

class MyIntVector {
    static int next_id;  // used for printing
   public:
    // constructor
    MyIntVector() : size(0), capacity(4), data(new int[4]), id(next_id++) {
        cout << "constructing " << id << endl;
    }

    // destructor
    ~MyIntVector() {
        cout << "destructing " << id << endl;
        delete[] data;
    }

    // copy constructor (deep copy)
    MyIntVector(const MyIntVector& other)
        : size(other.size), capacity(other.capacity), data(new int[other.capacity]), id(next_id++) {
        cout << "copy constructing " << id << " from " << other.id << endl;
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
    // copy assignment operator (deep copy)
    MyIntVector& operator=(const MyIntVector& other) {
        cout << "copy assigning " << id << " from " << other.id << endl;
        MyIntVector temp(other);
        swap(*this, temp);
        return *this;
    }
    void swap(MyIntVector& first, MyIntVector& second) {
        std::swap(first.size, second.size);
        std::swap(first.capacity, second.capacity);
        std::swap(first.data, second.data);
    }

    // as seen in lecture, nothing crazy. impls below
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

int main() {
    MyIntVector vec1;
    vec1.push_back(1);
    vec1.push_back(2);
    vec1.push_back(3);
    vec1.push_back(4);
    vec1.push_back(5);
    vec1.print();

    // MyIntVector vec2(vec1);
    // vec2.push_back(6);
    // vec2.print();
    // vec1.print();

    // MyIntVector vec3;
    // vec3 = vec1;
    // vec3.print();

    // what will the output be?
    // MyIntVector vec = create_big_vector(10);
    // vec.print();

    // brief lvalue rvalue example with ++ operator
    // int x = 4;
    // cout << ++x << endl;
    // cout << x << endl;
    // ++x = 3;
}

// implementations
int MyIntVector::next_id = 1;
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