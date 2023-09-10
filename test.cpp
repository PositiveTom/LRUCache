#include <iostream>
#include <list>
#include "lru.h"
using namespace std;


int main() {
    LRUCache<int, int> a(2);
    a.put(1, 2);
    a.put(1, 3);
    a.put(2, 3);
    a.put(3, 5);

    cout << a.get(1) << endl;
    return 0;
}