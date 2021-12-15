#include <iostream>
using namespace std;

template <typename T>
void print(T last) {
    cout << last << endl;
}

template <typename T, typename... Args>
void print(T first, Args... args) {
    cout << first << " ";
    print(args...);
}

int main() {
    print("a", 5, 1 + 2, "apple");
}