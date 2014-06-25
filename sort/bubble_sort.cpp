#include <algorithm>
#include <iterator>
#include <functional>
#include <utility>

template <typename Iterator, typename Compare>
void bubble_sort(Iterator first, Iterator last, Compare comp)
{
  for (auto i = first; i != last; ++i) {
    bool is_sorted = true;
    for (auto j = first; j != std::prev(last, 1 + std::distance(first, i)); ++j) {
      if (!comp(*j, *std::next(j))) {
        std::iter_swap(j, std::next(j));
        is_sorted = false;
      }
    }
    if (is_sorted) {
      break;
    }
  }
}

template <typename Iterator>
void bubble_sort(Iterator first, Iterator last)
{
  using type = typename std::iterator_traits<Iterator>::value_type;
  bubble_sort(first, last, std::less<type>{});
}

template <typename Iterator, typename OStream, typename Compare>
void debug_bubble_sort(Iterator first, Iterator last, OStream&& out, Compare comp)
{
  for (auto i = first; i != last; ++i) {
    bool is_sorted = true;
    for (auto j = first; j != std::prev(last, 1 + std::distance(first, i)); ++j) {
      using type = typename std::iterator_traits<Iterator>::value_type;
      std::copy(first, last, std::ostream_iterator<type>(out, ","));
      out << "\n";
      if (!comp(*j, *std::next(j))) {
        std::iter_swap(j, std::next(j));
        is_sorted = false;
      }
    }
    if (is_sorted) {
      break;
    }
  }
}

template <typename Iterator, typename OStream>
void debug_bubble_sort(Iterator first, Iterator last, OStream&& out)
{
  using type = typename std::iterator_traits<Iterator>::value_type;
  debug_bubble_sort(first, last, std::forward<OStream>(out), std::less<type>{});
}

#include <cassert>
#include <iostream>
#include <list>

int main() {
  std::list<int> v = {5, 1, 4, 2, 3};
  debug_bubble_sort(std::begin(v), std::end(v), std::cout);

  std::cout << "\n";
  std::copy(std::begin(v), std::end(v), std::ostream_iterator<int>(std::cout, ","));
  assert(std::is_sorted(std::begin(v), std::end(v)));
}
/*
5,1,4,2,3,
1,5,4,2,3,
1,4,5,2,3,
1,4,2,5,3,
1,4,2,3,5,
1,4,2,3,5,
1,2,4,3,5,
1,2,3,4,5,
1,2,3,4,5,

1,2,3,4,5,[Finished in 1.1s]
*/