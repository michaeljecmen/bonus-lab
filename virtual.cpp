#include <iostream>
using std::cout;
using std::endl;

struct Base {
    virtual void foo() {
        cout << "base foo" << endl;
    }
    void bar() {
        cout << "base bar" << endl;
    }
};

struct Derived : public Base {
    void foo() {
        cout << "derived foo" << endl;
    }
    void bar() {
        cout << "derived bar" << endl;
    }
};

int main() {
    Base b;
    Derived d;
    Base* b_ptr = &d;
    Derived* d_ptr = &d;

    d.foo();
    d_ptr->foo();
    b_ptr->foo();
    d.Base::foo();
    d_ptr->Base::foo();
    d.bar();
    b.bar();
    d_ptr->bar();
    b_ptr->bar();
}