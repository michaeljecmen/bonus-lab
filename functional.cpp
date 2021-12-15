#include <functional>
#include <iostream>
using namespace std;

void foo(int x, int y) {
    cout << x << " " << y << endl;
}

function<void()> func1;
void f1(int a, int b) {
    // bind all args
    func1 = bind(foo, a, b);
}

function<void(int)> func2;
void f2(int a) {
    // bind some args -- must use placeholders
    using namespace placeholders;
    func2 = bind(foo, a, _1);
}

void bar(int& x, int y) {
    x = y;
}

int main() {
    f1(10, 9);
    func1();

    f2(5);
    func2(4);

    int local = 0;
    auto barfunc = bind(bar, local, 5);
    barfunc();
    cout << local << endl;
    // does not modify
    auto barfunc2 = bind(bar, ref(local), 5);
    barfunc2();
    cout << local << endl;
}