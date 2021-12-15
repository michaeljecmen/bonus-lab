#include <iostream>
#include <memory>
#include <vector>

using namespace std;

struct Item {
    Item(int x_) : x(x_) { cout << "item " << x << " created" << endl; }
    ~Item() { cout << "item " << x << " destroyed" << endl; }
    int x;
};

vector<shared_ptr<Item>> items;

shared_ptr<Item> process_item() {
    auto temp = items.back();
    items.pop_back();
    return temp;
}

int main() {
    shared_ptr<Item> local = shared_ptr<Item>(new Item(0));
    items.push_back(local);
    for (int i = 1; i < 4; ++i) {
        items.push_back(shared_ptr<Item>(new Item(i)));
    }
    cout << endl;

    for (int i = 3; i >= 0; --i) {
        cout << "processing item " << i << endl;
        auto returned = process_item();
        cout << "item " << returned->x << " still alive" << endl;
    }
    cout << "done processing" << endl
         << endl;

    cout << "local item value: " << local->x << endl;
}
