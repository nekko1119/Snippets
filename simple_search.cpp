
#include <iostream>
#include <boost/lexical_cast.hpp>

template <typename Iterator>
Iterator simple_search(Iterator first, Iterator last, Iterator pattern_first, Iterator pattern_end) {
  for (; first != last; ++first) {
    auto i = pattern_first;
    for (auto j = first; i != pattern_end; ++i, ++j) {
      if (*i != *j) {
        break;
      }
    }
    if (i == pattern_end) {
      return first;
    }
  }
  return first;
}

template <typename Iterator, typename Output>
Iterator debug_simple_search(Iterator first, Iterator last, Iterator pattern_first, Iterator pattern_end, Output&& out) {
  int count = 0;
  auto first_ = first;
  for (; first_ != last; ++first_) {
    for (auto i = first; i != last; ++i) {
      out << *i << ",";
    }
    out << "\n";
    for (auto i = 0; i < count; ++i) {
      out << " ";
    }
    count += boost::lexical_cast<std::string>(*first_).length() + 1;
    for (auto i = pattern_first; i != pattern_end; ++i) {
      out << *i << ",";
    }
    out << "\n";
    auto i = pattern_first;
    for (auto j = first_; i != pattern_end; ++i, ++j) {
      if (*i != *j) {
        break;
      }
    }
    if (i == pattern_end) {
      return first_;
    }
  }
  return first_;
}

#include <string>

int main() {
  std::string const text = "aaabaaaab";
  std::string const pattern = "aaaab";
  auto const position = debug_simple_search(text.begin(), text.end(), pattern.begin(), pattern.end(), std::cout);
  if (position != text.end()) {
    std::cout << "found\n";
  } else {
    std::cout << "not found\n";
  }
  int a[] = {123, 456, 789, 123, 456};
  int b[] = {789, 123};
  debug_simple_search(a, a + 5, b, b + 2, std::cout);
}

/*
a,a,a,b,a,a,a,a,b,
a,a,a,a,b,
a,a,a,b,a,a,a,a,b,
  a,a,a,a,b,
a,a,a,b,a,a,a,a,b,
    a,a,a,a,b,
a,a,a,b,a,a,a,a,b,
      a,a,a,a,b,
a,a,a,b,a,a,a,a,b,
        a,a,a,a,b,
found
123,456,789,123,456,
789,123,
123,456,789,123,456,
    789,123,
123,456,789,123,456,
        789,123,
[Finished in 0.1s]
*/