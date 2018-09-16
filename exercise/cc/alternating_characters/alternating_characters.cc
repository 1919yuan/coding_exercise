#include <iostream>
#include <string>

int main () {
    int n;
    std::cin >> n;
    while (n--) {
        int delete_count = 0;
        std::string s;
        std::cin >> s;
        char prev = 0;
        for (auto &c : s) {
            if (prev && c == prev) {
                ++delete_count;
            } else {
                prev = c;
            }
        }
        std::cout << delete_count << std::endl;
    }
    return 0;
}
