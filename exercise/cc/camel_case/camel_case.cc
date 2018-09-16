#include <cassert>
#include <iostream>
#include <string>


using std::string;

bool CamelCaseMatch(const string &input, const string &pattern) {
  auto input_iter = input.begin();
  auto pattern_iter = pattern.begin();
  assert(*pattern_iter >= 'A' && *pattern_iter <= 'Z');
  bool can_eat = false;
  while (input_iter != input.end()) {
    if (pattern_iter != pattern.end() && *pattern_iter == *input_iter) {
      ++pattern_iter;
      can_eat = (pattern_iter != pattern.begin() &&
                 (*pattern_iter >= 'A' && *pattern_iter <= 'Z'));
      ++input_iter;
      continue;
    } else {
      if (*input_iter >= 'A' && *input_iter <= 'Z') {
        return false;
      } else if (can_eat || pattern_iter == pattern.end()) {
        ++input_iter;
        continue;
      } else {
        return false;
      }
    }
  }
  if (pattern_iter == pattern.end() && input_iter == input.end()) return true;
  else return false;
}xs

int main(int argc, char **argv) {
  string pattern, input;
  std::cout << "Please input pattern: " << std::endl;
  std::cin >> pattern;
  std::cout << "Please input test string: " << std::endl;
  std::cin >> input;
  if (CamelCaseMatch(input, pattern)) {
    std::cout << "Match!" << std::endl;
  } else {
    std::cout << "No match!" << std::endl;
  }
}
