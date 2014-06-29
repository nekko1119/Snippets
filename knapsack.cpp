#include <array>
#include <iomanip>
#include <iostream>

struct good {
  int size;
  int value;
};

std::array<good const, 5> const goods = {{
  {2, 2},
  {3, 4},
  {5, 7},
  {6, 10},
  {9, 16}
}};

int main()
{
  constexpr int knap_max_size = 16;
  std::array<int, knap_max_size + 1> knapsack = {{}};
  std::cout << "ナップザックの大きさ:\t";
  for (int i = 1; i < knap_max_size + 1; ++i)
  {
    std::cout << std::setw(2) << i << " ";
  }
  std::cout << "\n\n";
  // 使う品物の数
  for (int i = 0; i < static_cast<int>(goods.size()); ++i) {
    // ナップザックの大きさ
    for (int knap_size = goods[i].size;  knap_size < knap_max_size + 1; ++knap_size) {
      int new_value = knapsack[knap_size - goods[i].size] + goods[i].value;
      if (knapsack[knap_size] < new_value) {
        knapsack[knap_size] = new_value;
      }
    }
    std::cout << "品物" << i + 1 << "まで使う:\t\t";
    for (int i = 1; i < knap_max_size + 1; ++i) {
      std::cout << std::setw(2) << knapsack[i] << " ";
    }
    std::cout << "\n";
  }
}