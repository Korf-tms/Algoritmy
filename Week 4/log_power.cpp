#include <iostream>

using std::cout, std::endl;

// computes x^y
int power_recursive(int x, int y) {
    if (y == 1) {
        return x;
    }
    if (y % 2 == 1) {
        return x*power_recursive(x, y/2)*power_recursive(x, y/2);
    }
    else {
        return power_recursive(x, y/2)*power_recursive(x, y/2);
    }

}

// compute x^y 
int power_iter(int x, int y) {
    int res = 1;
    while (y > 0){
        if (y % 2 == 1) {
            res *= x;
            y -= 1; // in fact not needed
        }
        x = x*x;
        y /= 2;
    }
    return -1;
}

int main() {
    int base = 3;
    int power = 3;
    int res = power_recursive(base, power);
    cout << res << endl;
    return 0;
}
