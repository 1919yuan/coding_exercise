#include <assert.h>

#include <iostream>
#include <vector>


typedef struct Node {
  bool occupied;
  int parent;
  int index;
  explicit Node(int index) : index(index), parent(index), occupied(false) {};
} Node;

class Board {
 public:
  Board(int x_size, int y_size) : x_size_(x_size), y_size_(y_size),
                                  islands_(0) {
    array_.reserve(x_size_ * y_size_);
    for (int i = 0; i < x_size_; ++i) {
      for (int j = 0; j < y_size_; ++j) {
        array_.emplace_back(Node(index_(i, j)));
      }
    }
  };

 private:
  int x_size_;
  int y_size_;
  std::vector<Node> array_;
  int islands_;

  // bool at(int i, int j) {
  //   return array_[index(i, j)].occupied;
  // };

  bool at(int index) {
    return array_[index].occupied;
  };

  // int parent_(int i, int j) {
  //   return array_[index(i, j)].parent;
  // };

  int index_(int i, int j) {
    assert(0 <= i && i < x_size_);
    assert(0 <= j && j < y_size_);
    return i * y_size_ + j;
  };

  int left_(int i, int j) {
    if (i < 0 || i >= x_size_ || j < 1 || j >= y_size_)
      return -1;
    return index_(i, j - 1);
  };

  int right_(int i, int j) {
    if (i < 0 || i >= x_size_ || j < 0 || j >= y_size_ - 1)
      return -1;
    return index_(i, j + 1);
  };

  int up_(int i, int j) {
    if (i < 1 || i >= x_size_ || j < 0 || j >= y_size_)
      return -1;
    return index_(i - 1, j);
  };

  int down_(int i, int j) {
    if (i < 0 || i >= x_size_ - 1 || j < 0 || j >= y_size_)
      return -1;
    return index_(i + 1, j);
  };

  int find(int index) {
    assert(index >= 0);
    int iter = index;
    while (array_[iter].parent != iter) {
      iter = array_[iter].parent;
    }
    return iter;
  };

  int merge(int index1, int index2) {
    int root1 = find(index1);
    int root2 = find(index2);
    if (root1 != root2) {
      array_[root2].parent = root1;
      return root1;
    } else return -1;
  };

 public:
  void Add(int i, int j) {
    assert(i >= 0 && j >= 0 && i < x_size_ && j < y_size_);
    int index = index_(i, j);

    if (!array_[index].occupied) {
      islands_++;
      array_[index].occupied = true;
    } else {
      return;
    }

    int left = left_(i, j);
    int right = right_(i, j);
    int up = up_(i, j);
    int down = down_(i, j);

    if (left != -1 && at(left)) {
      int new_root = merge(index, left);
      if (new_root != -1) {
        islands_--;
      }
    }
    if (right != -1 && at(right)) {
      int new_root = merge(index, right);
      if (new_root != -1) {
        islands_--;
      }
    }
    if (up != -1 && at(up)) {
      int new_root = merge(index, up);
      if (new_root != -1) {
        islands_--;
      }
    }
    if (down != -1 && at(down)) {
      int new_root = merge(index, down);
      if (new_root != -1) {
        islands_--;
      }
    }
  };

  int NumberOfIslands() {
    return islands_;
  }
};

int main(int argc, char **argv) {
  int x_size, y_size;
  std::cout << "Please input board x_size:" << std::endl;
  std::cin >> x_size;
  if (x_size <= 0) {
    std::cout << "Please input a positive integer." << std::endl;
    return 1;
  }
  std::cout << "Please input board y_size:" << std::endl;
  std::cin >> y_size;
  if (y_size <= 0) {
    std::cout << "Please input a positive integer." << std::endl;
    return 1;
  }
  Board board(x_size, y_size);
  while (true) {
    int x, y;
    std::cout << "Please add a piece: \"x[space]y\". -1 to exit." << std::endl;
    std::cin >> x;
    std::cin >> y;
    if (x == -1 || y == -1) break;
    if (x < 0 || x >= x_size) {
      std::cout << "x out of range!" << std::endl;
      continue;
    }
    if (y < 0 || y >= y_size) {
      std::cout << "y out of range!" << std::endl;
      continue;
    }
    board.Add(x, y);
    std::cout << "Number of islands: " << board.NumberOfIslands() << std::endl;
  }
  return 0;
}
