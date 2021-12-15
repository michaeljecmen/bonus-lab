#include <iostream>
#include <memory>
#include <vector>

using namespace std;

struct Item {
    Item(int x_) : x(x_) { cout << "item " << x << " created" << endl; }
    ~Item() { cout << "item " << x << " destroyed" << endl; }
    int x;
};

vector<unique_ptr<Item>> items;

void add_items(int n) {
    for (int i = 0; i < n; ++i) {
        items.push_back(unique_ptr<Item>(new Item(i)));
    }
    cout << endl;
}

void process_item() {
    items.pop_back();
}

int main() {
    add_items(10);
    for (int i = 0; i < 5; ++i) {
        cout << "processing item" << endl;
        process_item();
    }
    cout << "done processing" << endl
         << endl;
}