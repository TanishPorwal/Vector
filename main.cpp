#include <iostream>
#include "timer.h"
#include "vector.h"

int main() {
    Timer timer;
    vector v = {1,2,3,4,5};
    for(auto& i : v) // iterator
        std::cout << i << " ";
    std::cout << "\n";
    int x = v[1] + v[2]; // or v.at(1) + v.at(2)
    for(auto i = v.rbegin(); i != v.rend(); i++) // reverse iterator
        std::cout << *i << " ";
    std::cout << "\n";
    return 0;
}
