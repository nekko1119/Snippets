#include <algorithm>
#include <iterator>
#include <functional>
#include <utility>

template <typename Iterator, typename Compare>
void comb_sort(Iterator first, Iterator last, Compare comp)
{
  auto gap = std::distance(first, last);
  for (auto i = first; i != last; ++i) {
    gap = gap * 10 / 13;
    if (gap == 0) {
      gap = 1;
    }
    bool is_sorted = true;
    for (auto j = first; j != std::prev(last, gap); ++j) {
      if (!comp(*j, *std::next(j, gap))) {
        std::iter_swap(j, std::next(j, gap));
        is_sorted = false;
      }
    }
    if (is_sorted && gap == 1) {
      break;
    }
  }
}

template <typename Iterator>
void comb_sort(Iterator first, Iterator last)
{
  using type = typename std::iterator_traits<Iterator>::value_type;
  comb_sort(first, last, std::less<type>{});
}

template <typename Iterator, typename OStream, typename Compare>
void debug_comb_sort(Iterator first, Iterator last, OStream&& out, Compare comp)
{
  auto gap = std::distance(first, last);
  for (auto i = first; i != last; ++i) {
    gap = gap * 10 / 13;
    if (gap == 0) {
      gap = 1;
    }
    bool is_sorted = true;
    for (auto j = first; j != std::prev(last, gap); ++j) {
      using type = typename std::iterator_traits<Iterator>::value_type;
      std::copy(first, last, std::ostream_iterator<type>(out, ","));
      out << "\n";
      if (!comp(*j, *std::next(j, gap))) {
        std::iter_swap(j, std::next(j, gap));
        is_sorted = false;
      }
    }
    if (is_sorted && gap == 1) {
      break;
    }
  }
}

template <typename Iterator, typename OStream>
void debug_comb_sort(Iterator first, Iterator last, OStream&& out)
{
  using type = typename std::iterator_traits<Iterator>::value_type;
  debug_comb_sort(first, last, std::forward<OStream>(out), std::less<type>{});
}

#include <cassert>
#include <iostream>
#include <list>

int main() {
  std::list<int> v = {5, 4, 3, 2, 1};
  debug_comb_sort(std::begin(v), std::end(v), std::cout);

  std::cout << "\n";
  std::copy(std::begin(v), std::end(v), std::ostream_iterator<int>(std::cout, ","));
  assert(std::is_sorted(std::begin(v), std::end(v)));
}
/*
5,4,3,2,1,
2,4,3,5,1,
2,1,3,5,4,
2,1,3,5,4,
2,1,3,5,4,
2,1,3,5,4,
1,2,3,5,4,
1,2,3,5,4,
1,2,3,5,4,
1,2,3,4,5,
1,2,3,4,5,
1,2,3,4,5,
1,2,3,4,5,

1,2,3,4,5,[Finished in 0.1s]
*/