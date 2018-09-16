#include <iostream>
#include <cmath>
#include <string>

int main() {
  int t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    int count = 0;
    if (s.size() > 0) {
      for (auto i = s.begin(), j = std::prev(s.end()); i < j; ++i, --j) {
        count += std::abs(*i - *j);
      }
      std::cout << count << std::endl;
    } else {
      std::cout << 0 << std::endl;
    }
  }
  return 0;
}
