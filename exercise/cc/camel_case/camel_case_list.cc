// #include "camelcase.h"
// #include "trie.h"

class Trie {
 public:
  void insert(const string &prefix, const string &value);
  const std::set<string> &find(const string &prefix);
};

class CamelCaseList {
 public:
  void Insert(const string &value) {
    std::vector<string> all_prefixes;
    get_all_prefixes(value, &all_prefixes);
    for (const auto &prefix : all_prefixes) {
      trie_.insert(prefix, value);
    }
  }
  bool CamelCaseMatch(const string &pattern) {
    const std::set<string> &values = trie_.find(pattern);
    if (values.size() > 0) return true;
    else return false;
  }
 private:
  Trie trie_;
  void get_all_prefixes(const string &value, std::vector<string> *all_prefixes);
};
