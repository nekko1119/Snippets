#include <algorithm>
#include <iterator>
#include <functional>
#include <utility>

template <typename Iterator, typename Compare>
void insert_sort(Iterator first, Iterator last, Compare comp)
{
  auto min = std::min_element(first, last, comp);
  std::iter_swap(first, min);
  while (++first != last) {
    for (auto j = first; comp(*j, *(std::prev(j))); --j) {
      std::iter_swap(std::prev(j), j);
    }
  }
}

template <typename Iterator>
void insert_sort(Iterator first, Iterator last)
{
  using type = typename std::iterator_traits<Iterator>::value_type;
  insert_sort(first, last, std::less<type>{});
}

template <typename Iterator, typename OStream, typename Compare>
void debug_insert_sort(Iterator first, Iterator last, OStream&& out, Compare comp)
{
  using type = typename std::iterator_traits<Iterator>::value_type;
  std::copy(first, last, std::ostream_iterator<type>(out, ","));
  out << "\n";
  auto min = std::min_element(first, last, comp);
  std::iter_swap(first, min);
  auto i = first;
  while (++i != last) {
    for (auto j = i; comp(*j, *(std::prev(j))); --j) {
      std::iter_swap(std::prev(j), j);
    }
    std::copy(first, last, std::ostream_iterator<type>(out, ","));
    out << "\n";
  }
}

template <typename Iterator, typename OStream> 
void debug_insert_sort(Iterator first, Iterator last, OStream&& out)
{
  using type = typename std::iterator_traits<Iterator>::value_type;
  debug_insert_sort(first, last, std::forward<OStream>(out), std::less<type>{});
}

#include <cassert>
#include <iostream>
#include <list>

int main() {
  std::list<int> v = {5, 1, 4, 3, 2};
  debug_insert_sort(std::begin(v), std::end(v), std::cout);

  std::cout << "\n";
  std::copy(std::begin(v), std::end(v), std::ostream_iterator<int>(std::cout, ","));
  assert(std::is_sorted(std::begin(v), std::end(v)));
}

/*
5,1,4,2,3,
1,5,4,2,3,
1,4,5,2,3,
1,2,4,5,3,
1,2,3,4,5,

1,2,3,4,5,[Finished in 0.0s]
*/