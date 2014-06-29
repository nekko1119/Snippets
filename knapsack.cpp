#include <array>
#include <iomanip>
#include <iostream>

// 品物
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
  for (int i = 1; i < knap_max_size + 1; ++i) {
    std::cout << std::setw(2) << i << " ";
  }
  std::cout << "\n\n";
  // 使う品物の数
  for (int i = 0; i < static_cast<int>(goods.size()); ++i) {
    // ナップザックの大きさ
    for (int knap_size = goods[i].size;  knap_size < knap_max_size + 1; ++knap_size) {
      // 今までの価値から現在の品物を入れるために品物分のサイズを引いた価値に、
      // 実際に追加してみて、価値が更新したら本当に代入する
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
/*
ナップザックの大きさ:  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 

品物1まで使う:     0  2  2  4  4  6  6  8  8 10 10 12 12 14 14 16 
品物2まで使う:     0  2  4  4  6  8  8 10 12 12 14 16 16 18 20 20 
品物3まで使う:     0  2  4  4  7  8  9 11 12 14 15 16 18 19 21 22 
品物4まで使う:     0  2  4  4  7 10 10 12 14 14 17 20 20 22 24 24 
品物5まで使う:     0  2  4  4  7 10 10 12 16 16 18 20 20 23 26 26 
[Finished in 0.1s]
*/