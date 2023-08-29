#include <iostream>
#include "Vector.h"

int main() {
    Vector<int> a(4);
    Vector<int> a1;
    a1 = std::move(a);
    std::cout << a1.repr();
    return 0;
}
