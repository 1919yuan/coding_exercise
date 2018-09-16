#include <iostream>
#include <vector>

void find_two_sum(const std::vector<int> &array, int target,
                  int *index_0, int *index_1) {
  for (int i = 0; i < array.size() - 1; ++i) {
    for (int j = i + 1; j < array.size(); ++j) {
      if (array[i] + array[j] == target) {
        *index_0 = i;
        *index_1 = j;
        return;
      }
    }
  }
  *index_0 = -1;
  *index_1 = -1;
}

int main(int argc, char **argv) {
  std::vector<int> a;
  int k, target;
  std::cin >> target;
  std::cin >> k;
  for (int i = 0; i < k; ++i) {
    int a_k;
    std::cin >> a_k;
    a.push_back(a_k);
  }
  int index_0, index_1;
  find_two_sum(a, target, &index_0, &index_1);
  std::cout << "[" << index_0 << ", " << index_1 << "]" << std::endl;
  return 0;
}
