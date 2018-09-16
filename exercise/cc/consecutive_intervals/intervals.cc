/* Given a list of intervals [a_1, b_1), [a_2, b_2), ... [a_n, b_n)
   all with integer end points, write a function that returns whether the list
   of intervals cover a consecutive area on the line. */

/* The solution is O(n log n). */

/* This question can be changed to online: O(m * lg n), where m is the number
   of overlapping intervals given a new added interval.

   That online version solution requires maintaining an interval tree of
   intervals, and keep adding to it. Seperately, maintain a disjoint-set of the
   intervals, and each iteration, adding to interval tree is O(lg n), querying
   interval tree for overlap is O(lg n + m), merging the disjoint-set is
   O(m * lg n), maintaining the number of disjoint sets is the number of
   consecutive intervals covered by the intervals. */

#include <assert.h>
#include <iostream>
#include <limits>
#include <map>
#include <unordered_map>
#include <vector>


typedef struct Interval {
  int a;
  int b;
  Interval(int a, int b) : a(a), b(b) {}
} Interval;

bool IsConsecutiveInterval(const std::vector<Interval> &intervals,
                           int *a,
                           int *b) {
  int min = std::numeric_limits<int>::max();
  int max = std::numeric_limits<int>::min();
  // int length = 0;
  std::map<int, std::vector<const Interval*>> points;
  for (const auto &interval : intervals) {
    if (interval.a < min) {
      min = interval.a;
    }
    if (interval.b > max) {
      max = interval. b;
    }

    if (points.find(interval.a) != points.end()) {
      points[interval.a].emplace_back(&interval);
    } else {
      points[interval.a] = std::vector<const Interval*>({&interval});
    }

    if (points.find(interval.b) != points.end()) {
      points[interval.b].emplace_back(&interval);
    } else {
      points[interval.b] = std::vector<const Interval*>({&interval});
    }
  }

  int effective_intervals = 0;
  for (const auto &point : points) {
    // ordered iterator.
    for (const auto &interval : point.second) {
      if (point.first == interval->a) {
        effective_intervals++;
      } else {
        effective_intervals--;
      }
    }
    if (effective_intervals == 0 && point.first != max) {
      std::cerr << "Gap starting here: " << point.first << std::endl;
      return false;
    }
  }

  *a = min;
  *b = max;
  return true;
}

int main(int argc, char **argv) {
  int n;
  std::cin >> n;
  std::vector<Interval> intervals;
  for (int i = 0; i < n; ++i) {
    int a, b;
    std::cin >> a;
    std::cin >> b;
    assert(b >= a);
    intervals.emplace_back(Interval(a, b));
  }
  int a, b;
  bool consecutive = IsConsecutiveInterval(intervals, &a, &b);
  if (consecutive) {
    std::cout << "A consecutive interval: [" << a << ", " << b
              << ")." << std::endl;
  } else {
    std::cout << "The input intervals are not consecutive." << std::endl;
  }
  return 0;
}
