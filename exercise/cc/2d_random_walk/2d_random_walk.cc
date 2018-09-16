#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>

double recursive_prob(int N, int R, int x, int y) {
  if (N == 0) {
    if (x * x + y * y <= R * R) {
      return 1.0;
    } else {
      return 0.0;
    }
  } else {
    double prob = 0;
    prob += recursive_prob(N - 1, R, x - 1, y);
    prob += recursive_prob(N - 1, R, x + 1, y);
    prob += recursive_prob(N - 1, R, x, y + 1);
    prob += recursive_prob(N - 1, R, x, y - 1);
    return prob / 4.0;
  }
}

int main(int argc, char **argv) {
  assert(argc == 3);
  int N = atoi(argv[1]);
  int R = atoi(argv[2]);
  assert(N >= 0);
  assert(R >= 0);
  if (N == 0) std::cout << "1" << std::endl;
  int x_low = 0 - R;
  int x_high = R;
  double total_prob = 0;
  for (int x = x_low; x <= x_high; ++x) {
    int y_high = floor(sqrt(R * R - x * x));
    std::cout << "x: " << x << " y_high: " << y_high << std::endl;
    int y_low = 0 - y_high;
    for (int y = y_low; y <= y_high; ++y) {
      int absx = abs(x);
      int absy = abs(y);
      if ((N - absx + absy) % 2 != 0) continue;
      for (int k = absx; k <= N - absy; ++k) {
        if ((k + absx) % 2 != 0) continue;
        std::cout << "k: " << k << std::endl;
        double prob = 1;
        int first_block = (k + absx) / 2;
        int second_block = (k - absx) / 2;
        int third_block = (N - k + absy) / 2;
        int fourth_block = (N - k - absy) / 2;
        int first = first_block;
        int second = first + second_block;
        int third = second + third_block;
        int fourth = third + fourth_block;
        assert(fourth == N);
        for (int i = 0; i < N; ++i) {
          prob *= (i + 1) / 4.0;
          if (i < first) {
            prob /= (first - i);
          } else if (i < second) {
            prob /= (second - i);
          } else if (i < third) {
            prob /= (third - i);
          } else {
            prob /= (fourth - i);
          }
        }
        total_prob += prob;
      }
    }
  }
  std::cout << "Prob: " << total_prob << std::endl;
  std::cout << "Recursive prob: " << recursive_prob(N, R, 0, 0) << std::endl;
}
