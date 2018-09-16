#include <iostream>


int main() {
    int l;
    int r;
    std::cin >> l;
    std::cin >> r;
    int max = 0;
    for (int i = l; i <= r; ++i) {
        for (int j = i; j <= r; ++j) {
            int value = i ^ j;
            if (value > max) {
                max = value;
            }
        }
    }
    std::cout << max;
    return 0;
}
