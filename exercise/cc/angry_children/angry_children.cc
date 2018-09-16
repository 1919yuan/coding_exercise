#include <algorithm>
#include <vector>
#include <iostream>

int main() {
  int n;
  std::cin >> n;
  int k;
  std::cin >> k;
  std::vector<int> v;
  v.resize(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> v[i];
  }
  std::sort(v.begin(), v.end());
  int min = 1000000000;
  for (int i = k - 1; i < n; ++i) {
    int diff = v[i] - v[i - k + 1];
    if (diff < min) {
      min = diff;
    }
  }
  std::cout << min << std::endl;
  return 0;
}
