#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

struct mini_list {
  int m;
  int a;
  int b;
  std::vector<std::string> buck;
};
struct bucket_t {
  int c;
  mini_list list_i;
};

int hashFun(std::string gen);
int randInt(int p);
void createMiniL(int num);

int main() {
  std::vector<bucket_t> table(10);
  for (int i = 0; i < 10; ++i) {
    table[i].c = i;
    mini_list listaux;
    table[i].list_i = listaux;
    table[i].list_i.m = i + 1;
    table[i].list_i.a = (i + 2) * 10;
    table[i].list_i.b = (i + 3) * 10;
  }
  for (int i = 0; i < 10; ++i) {
    std::cout << "c" << i << ": " << table[i].c << std::endl;
    std::cout << "m0: " << table[i].list_i.m << std::endl;
    std::cout << "a0: " << table[i].list_i.a << std::endl;
    std::cout << "b0: " << table[i].list_i.b << std::endl;
  }

  return 0;
}
