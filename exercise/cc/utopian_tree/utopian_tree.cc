#include <iostream>


int main() {
  int t;
  std::cin >> t;
  while (t--) {
    int n;
    std::cin >> n;
    std::cout << (1 << ((n + 3) / 2)) - 1 - (n % 2) << std::endl;
  }
  return 0;
}
