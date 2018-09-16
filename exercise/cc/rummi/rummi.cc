#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

struct Card {
  int number_;
  enum Color {
    Black = 0,
    Red = 1,
    Green = 2,
    Blue = 3,
    NumberOfColors = 4
  };
  Color color_;
  static const int kCardsInOneColor = 13;
  int index() const {
    return static_cast<int>(color) * kCardsInOneColor + number; }
  Card(int number, string color) {
    assert(number >= 0);
    assert(number < kCardsInOneColor);
    if (color == "r" || color == "red") {
      color_ = Red;
    } else if (color == "g" || color == "green") {
      color_ = Green;
    } else if (color == "b" || color == "blue") {
      color_ = Blue;
    } else if (color == "k" || color == "black") {
      color_ = Black;
    } else {
      std::cout << "Wrong color input: " << color << std::endl;
      exit(1);
    }
  }
};

void AllPossibleSequences(const std::vector<Card>& cards) {
  std::vector<int> cards_in_one_color[Card::NumberOfColors];
  std::vector<int> cards_in_one_number[Card::kCardsInOneColor];
  const std::vector<string> color_names = { "Black", "Red", "Green", "Blue" };
  for (int i = 0; i < cards.size(); ++i) {
    cards_in_one_color[static_cast<int>(cards[i].color_)].push_back(i);
    cards_in_one_number[cards[i].number_].push_back(i);
  }
  for (int i = 0; i < Card::NumberOfColors; ++i) {
    // sort cards_in_one_color by cards[k].number_.
    std::sort(cards_in_one_color[i],
              cards_in_one_color[i].begin(),
              cards_in_one_color[i].end(),
              [&cards] (int j, int k) {
                return cards[j].number_ < cards[k].number_;
              });
    std::vector<int> numbers;
    for (int j = 0; j < cards_in_one_color[i].size(); ++j) {
      numbers.push_back(cards[cards_in_one_color[i][j]].number_);
    }
    PrintAllSequences(numbers, 3, nullptr, -1, Card::Color(i));
  }
  for (int i = 0; i < Card::kCardsInOneColor; ++i) {
    // sort cards_in_one_number by cards[k].color_.
    std::sort(cards_in_one_number[i],
              cards_in_one_number[i].begin(),
              cards_in_one_number[i].end(),
              [&cards] (int j, int k) {
                return static_cast<int>(cards[j].color_) <
                  static_cast<int>(cards[k].color_);
              });
    std::vector<int> colors;
    for (int j = 0; j < cards_in_one_number[i].size(); ++j) {
      colors.push_back(
          static_cast<int>(cards[cards_in_one_number[i][j]].color_));
    }
    PrintAllSequnces(colors, 3, &color_names, i, Card::NumberOfColors);
  }
}

void PrintAllSequences(const std::vector<int>& array, int min_length,
                       const std::vector<string>* names,
                       const int card_number,
                       const Card::Color card_color) {
  
}

int main(int argc, char **argv) {
  int n = 0;
  std::vector<Card> cards;
  for (int i = 0; i < n; ++i) {
    int number = 0;
    string color;
    std::cin >> number;
    std::cin >> color;
    cards.emplace_back(Card(number, color));
  }

  AllPossibleSequences(cards);
}
