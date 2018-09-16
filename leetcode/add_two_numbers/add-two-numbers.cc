#include <cstddef>
#include <iostream>
#include <memory>
#include <ostream>
#include <stack>
#include <vector>

struct LinkedList {
  int number;
  LinkedList *next;
  LinkedList(int num, LinkedList *next_ptr = nullptr) :
    number(num), next(next_ptr){ };
};

std::ostream &operator<<(std::ostream &output,
                         const LinkedList *head) {
  const LinkedList *iter = head;
  std::stack<int> numbers;
  while (iter) {
    numbers.push(iter->number);
    iter = iter->next;
  }
  while (!numbers.empty()) {
    output << numbers.top();
    numbers.pop();
  }
  return output;
}

void add_two_numbers(const LinkedList *number1,
                     const LinkedList *number2,
                     LinkedList **result,
                     std::vector<std::unique_ptr<LinkedList>> *gc) {
  const LinkedList *iter1 = number1;
  const LinkedList *iter2 = number2;
  LinkedList *head = nullptr;
  LinkedList *last = nullptr;
  int carry = 0;
  while (iter1 && iter2) {
    int number = iter1->number + iter2->number + carry;
    carry = 0;
    if (number > 9) {
      carry = 1;
      number = number - 10;
    }
    std::unique_ptr<LinkedList> node(new LinkedList(number));
    if (!head) {
      head = node.get();
      last = head;
    }
    else {
      last->next = node.get();
      last = node.get();
    }
    gc->push_back(std::move(node));
    iter1 = iter1->next;
    iter2 = iter2->next;
  }
  const LinkedList *cont = iter1 ? iter1 : iter2;
  while (cont) {
    int number = cont->number + carry;
    carry = 0;
    std::unique_ptr<LinkedList> node(new LinkedList(number));
    if (!head) {
      head = node.get();
      last = head;
    } else {
      last->next = node.get();
      last = node.get();
    }
    gc->push_back(std::move(node));
    cont = cont->next;
  }
  *result = head;
}

int main(int argc, char **argv) {
  LinkedList *head1 = nullptr, *head2 = nullptr;
  int n,m;
  std::vector<std::unique_ptr<LinkedList>> gc;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    int number;
    std::cin >> number;
    std::unique_ptr<LinkedList> node(new LinkedList(number, head1));
    head1 = node.get();
    gc.push_back(std::move(node));
  }
  std::cin >> m;
  for (int i = 0; i < m; ++i) {
    int number;
    std::cin >> number;
    std::unique_ptr<LinkedList> node(new LinkedList(number, head2));
    head2 = node.get();
    gc.push_back(std::move(node));
  }
  LinkedList *result;
  add_two_numbers(head1, head2, &result, &gc);
  std::cout << head1 << " + " << head2 << " = ";
  std::cout << result << std::endl;
  return 0;
}
