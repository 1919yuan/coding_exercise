#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

/*
 * Complete the function below.
 */
typedef struct Rod {
  int parent;
  int index;
  int set_size;
} Rod;

int find(int index, const vector<Rod>& rods) {
  int cur = index;
  int root = rods[cur].parent;
  while (root != cur) {
    cur = root;
    root = rods[cur].parent;
  }
  return root;
}

void merge(int index_1, int index_2, vector<Rod>* rods) {
  int root_1 = find(index_1, *rods);
  int root_2 = find(index_2, *rods);
  if (root_1 != root_2) {
    if ((*rods)[root_1].set_size > (*rods)[root_2].set_size) {
      (*rods)[root_2].parent = root_1;
    (*rods)[root_1].set_size += (*rods)[root_2].set_size;
    } else {
      (*rods)[root_1].parent = root_2;
      (*rods)[root_2].set_size += (*rods)[root_1].set_size;
    }
  }
}

int minimalCost(int n, vector < string > pairs) {
  vector<Rod> rods;
  rods.resize(n);
  for (int i = 0; i < n; ++i) {
    rods[i].index = i;
    rods[i].parent = i;
    rods[i].set_size = 1;
  }
  for (const auto& pair : pairs) {
    stringstream ss(pair);
    int rod_1, rod_2;
    ss >> rod_1 >> rod_2;
    rod_1--;
    rod_2--;
    // assert(0 <= rod_1 && rod_1 < n);
    // assert(0 <= rod_2 && rod_2 < n);
    if (rod_1 != rod_2) {
      merge(rod_1, rod_2, &rods);
    }
  }
  vector<bool> visited(n, false);
  int cost = 0;
  for (int i = 0; i < n; ++i) {
    cout << "rod: " << i << std::endl;
    if (!visited[i]) {
      int root = find(i, rods);
      if (!visited[root]) {
        cout << "root: " << root << std::endl;
        cost += ceil(sqrt(double(rods[root].set_size)));
        cout << "cost: " << cost << std::endl;
      }
      visited[root] = true;
    }
  }
  return cost;
}

int main() {
  // ofstream fout(getenv("OUTPUT_PATH"));
  int res;
  int _n;
  cin >> _n;
  cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');


  int _pairs_size = 0;
  cin >> _pairs_size;
  cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
  vector<string> _pairs;
  string _pairs_item;
  for(int _pairs_i=0; _pairs_i<_pairs_size; _pairs_i++) {
    getline(cin, _pairs_item);
    _pairs.push_back(_pairs_item);
  }

  res = minimalCost(_n, _pairs);
  cout << res << endl;

  // fout.close();
  return 0;
}
