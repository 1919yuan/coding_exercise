#include <bitset>
#include <iostream>
#include <vector>

int main(int argc, char **argv) {
  int n;
  std::cin >> n;
  std::vector<int> a;
  a.resize(n);
  const int kN = 101;
  std::bitset<kN> b;
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
    b.flip(a[i]);
  }
  int j = 0;
  for (; j < kN && !b.test(j); ++j);
  std::cout << j << std::endl;
  return 0;
}
