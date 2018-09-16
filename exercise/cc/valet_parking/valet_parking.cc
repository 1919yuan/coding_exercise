#include <iostream>
#include <vector>

const int kUninitialized = -2;
const int kEmpty = -1;

int main(int argc, char **argv) {
  std::vector<int> cars;
  std::vector<int> positions;
  int n;
  std::cin >> n;
  cars.resize(n);
  positions.resize(n, kUninitialized);
  for (int i = 0; i < n; ++i) {
    std::cin >> cars[i];
    if (cars[i] >= n) {
      return 1;
    }
    if (positions[cars[i]] == kUninitialized) {
      positions[cars[i]] = i;
    } else {
      return 1;
    }
  }
  int car_in_empty_spot = kEmpty;
  int position = 0;
  int empty_position = kEmpty;
  while (position < n) {
    if (cars[position] != position) {
      if (car_in_empty_spot == position) {
        if (cars[position] != kEmpty) {
          std::cout << "Move car #" << cars[position] << " from spot "
                    << position << " to spot " << empty_position
                    << "." << std::endl;
          positions[cars[position]] = empty_position;
          cars[empty_position] = cars[position];
          cars[position] = kEmpty;
          empty_position = kEmpty;
        }
        std::cout << "Move car #" << position << " from empty spot to spot "
                  << position << "." << std::endl;
        car_in_empty_spot = kEmpty;
        cars[position] = position;
        positions[position] = position;
      } else if (car_in_empty_spot == kEmpty) {
        std::cout << "Move car #" << cars[position] << " from spot "
                  << position << " to empty spot." << std::endl;
        car_in_empty_spot = cars[position];
        positions[cars[position]] = kEmpty;
        cars[position] = kEmpty;
        std::cout << "Move car #" << position << " from spot "
                  << positions[position] << " to spot " << position
                  << "." << std::endl;
        empty_position = positions[position];
        cars[positions[position]] = kEmpty;
        cars[position] = position;
        positions[position] = position;
      }
    }
    ++position;
  }
  std::cout << "cars:";
  for (int i = 0; i < n; ++i) std::cout << " " << cars[i];
  std::cout << std::endl << "positions: ";
  for (int i = 0; i < n; ++i) std::cout << " " << positions[i];
  std::cout << std::endl;
  return 0;
}
