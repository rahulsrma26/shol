#include "shol/math/mod.hpp"
#include <iostream>

int main() {
    using namespace std;
    using namespace shol;

    constexpr int mod = 7;
    Modular<int, mod> x = 4, y = 5;
    cout << "x = " << x << " (mod " << mod << ")" << endl;
    cout << "y = " << y << " (mod " << mod << ")" << endl;
    cout << "x + y = " << x + y << " (mod " << mod << ")" << endl;
    cout << "x - y = " << x - y << " (mod " << mod << ")" << endl;
    cout << "x * y = " << x * y << " (mod " << mod << ")" << endl;
    cout << "x / y = " << x / y << " (mod " << mod << ")" << endl;
    cout << "pow(x, 3) = " << pow(x, 3) << " (mod " << mod << ")" << endl;
    cout << "inv(x) = " << inv(x) << " (mod " << mod << ")" << endl;
    cout << "inv(y) = " << inv(y) << " (mod " << mod << ")" << endl;
}

/*
Expected Output:
===============
x = 4 (mod 7)
y = 5 (mod 7)
x + y = 2 (mod 7)
x - y = 6 (mod 7)
x * y = 6 (mod 7)
x / y = 5 (mod 7)
pow(x, 3) = 1 (mod 7)
inv(x) = 2 (mod 7)
inv(y) = 3 (mod 7)
*/
