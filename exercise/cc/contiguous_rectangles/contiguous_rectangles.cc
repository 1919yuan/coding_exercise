#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <vector>

struct Rectangle {
  Rectangle(int top, int left, int bottom, int right) :
    top_(top), left_(left), bottom_(bottom), right_(right) {}

  bool intersect(const Rectangle &other) const {
    // Left border intersect
    bool left = (other.left_ < right_ && other.left_ >= left_);
    bool right = (other.right_ <= right_ && other.right_ > left_);
    bool top = (other.top_ <= top_ && other.top_ > bottom_);
    bool bottom = (other.bottom_ < top_ && other.bottom_ >= bottom_);
    return (left && top) ||
      (left && bottom) ||
      (right && top) ||
      (right && bottom);
  }

  long area() const {
    return (long(top_) - bottom_) * (long(right_) - left_);
  }

  int left() const {
    return left_;
  }

  int right() const {
    return right_;
  }

  int top() const {
    return top_;
  }

  int bottom() const {
    return bottom_;
  }

  int top_;
  int left_;
  int bottom_;
  int right_;
};

int main(int argc, char **argv) {
  std::istream_iterator<int> eof;
  std::vector<Rectangle> rectangles;

  std::cout << "Please input integer boundaries for a rectangle: "
            << "top, left, bottom, right. Ctrl+d to discontinue."
            << std::endl;

  std::istream_iterator<int> iit(std::cin);

  do {
    assert(iit != eof);
    int top = *iit++;
    assert(iit != eof);
    int left = *iit++;
    assert(iit != eof);
    int bottom = *iit++;
    assert(iit != eof);
    int right = *iit;
    rectangles.emplace_back(Rectangle(top, left, bottom, right));
    std::cout << "Please input integer boundaries for a rectangle: "
              << "top, left, bottom, right. Ctrl+d to discontinue."
              << std::endl;
    iit++;
  } while (iit != eof);

  int top_most =
    std::max_element(rectangles.begin(), rectangles.end(),
                     [](Rectangle& rect1,
                        Rectangle& rect2) {
                       return rect1.top() < rect2.top(); })->top();
  int right_most =
    std::max_element(rectangles.begin(), rectangles.end(),
                     [](Rectangle& rect1,
                        Rectangle& rect2) {
                       return rect1.right() < rect2.right(); })->right();
  int left_most =
    std::min_element(rectangles.begin(), rectangles.end(),
                     [](Rectangle& rect1,
                        Rectangle& rect2) {
                       return rect1.left() < rect2.left(); })->left();
  int bottom_most =
    std::min_element(rectangles.begin(), rectangles.end(),
                     [](Rectangle& rect1,
                        Rectangle& rect2) {
                       return rect1.bottom() < rect2.bottom(); })->bottom();

  long total_relevant_area =
    (long(top_most) - bottom_most) *
    (long(right_most) - left_most);

  long total_area = 0;
  std::for_each(rectangles.begin(), rectangles.end(),
                [&total_area](const Rectangle& rect) {
                  total_area = total_area + rect.area(); });
  if (total_relevant_area != total_area) {
    std::cout << "False!" << std::endl;
  } else {
    bool exact_cover = true;
    for (auto it1 = rectangles.begin(); it1 != rectangles.end(); ++it1) {
      for (auto it2 = std::next(it1); it2 != rectangles.end(); ++it2) {
        if (it1->intersect(*it2)) {
          exact_cover = false;
          break;
        }
      }
      if (!exact_cover) break;
    }
    if (!exact_cover) {
      std::cout << "False!" << std::endl;
    } else {
      std::cout << "True!" << std::endl;
    }
  }
  return 0;
}
