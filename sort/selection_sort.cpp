#include <algorithm>
#include <iterator>
#include <functional>
#include <utility>

template <typename Iterator, typename Compare>
void selection_sort(Iterator first, Iterator last, Compare comp)
{
  for (auto i = first; i != last; ++i) {
    bool is_sorted = true;
    auto min = std::min_element(i, last, comp);
    if (min != i) {
      is_sorted = false;
    }
    std::iter_swap(i, min);
    if (is_sorted) {
      break;
    }
  }
}

template <typename Iterator>
void selection_sort(Iterator first, Iterator last)
{
  using type = typename std::iterator_traits<Iterator>::value_type;
  selection_sort(first, last, std::less<type>{});
}

template <typename Iterator, typename OStream, typename Compare>
void debug_selection_sort(Iterator first, Iterator last, OStream&& out, Compare comp)
{
  for (auto i = first; i != last; ++i) {
    bool is_sorted = true;
    using type = typename std::iterator_traits<Iterator>::value_type;
    std::copy(first, last, std::ostream_iterator<type>(out, ","));
    out << "\n";
    auto min = std::min_element(i, last, comp);
    if (min != i) {
      is_sorted = false;
    }
    std::iter_swap(i, min);
    if (is_sorted) {
      break;
    }
  }
}

template <typename Iterator, typename OStream>
void debug_selection_sort(Iterator first, Iterator last, OStream&& out)
{
  using type = typename std::iterator_traits<Iterator>::value_type;
  debug_selection_sort(first, last, std::forward<OStream>(out), std::less<type>{});
}

#include <cassert>
#include <iostream>
#include <list>

int main() {
  std::list<int> v = {5, 1, 4, 3, 2};
  debug_selection_sort(std::begin(v), std::end(v), std::cout);

  std::cout << "\n";
  std::copy(std::begin(v), std::end(v), std::ostream_iterator<int>(std::cout, ","));
  assert(std::is_sorted(std::begin(v), std::end(v)));
}

/*
5,1,4,3,2,
1,5,4,3,2,
1,2,4,3,5,
1,2,3,4,5,

1,2,3,4,5,[Finished in 0.1s]
*/