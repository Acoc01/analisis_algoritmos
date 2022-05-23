#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits.h>
#include <stdio.h>
#include <vector>
// Funcion para imprimir buckets (prueba)
void print_vec(std::vector<std::vector<int>> v1) {
  for (int i = 0; i < v1.size(); ++i) {
    for (int j = 0; j < v1[i].size(); ++j) {
      std::cout << v1[i][j] << " ";
    }
    std::cout << std::endl;
  }
}
void bucket(std::vector<int> &arr, int k);

int main() {
  int n;
  std::cin >> n;
  std::vector<int> v1;
  for (int i = 0; i < n; ++i) {
    int num;
    std::cin >> num;
    v1.push_back(num);
  }

  for (int i = 0; i < n; ++i) {
    std::cout << v1[i] << " ";
  }
  std::cout << std::endl;

  bucket(v1, n);

  for (int i = 0; i < n; ++i) {
    std::cout << v1[i] << " ";
  }
  std::cout << std::endl;

  return 0;
}

void bucket(std::vector<int> &arr, int k) {
  int mg, mch;
  // Busca el mayor elemento
  mg = *std::max_element(arr.begin(), arr.end());
  // Busca el menor elemento
  mch = *std::min_element(arr.begin(), arr.end());
  int buckets = std::ceil(mg / 10) + 1;
  std::vector<std::vector<int>> aux(buckets);
  for (int i = 0; i < buckets; ++i) {
    for (int j = 0; j < k; ++j) {
      if (arr[j] > i * 10 - 1 && arr[j] <= (i + 1) * 10 - 1) {
        aux[i].push_back(arr[j]);
      }
    }
  }
  print_vec(aux);
  for (int i = 0; i < buckets; ++i) {
    std::sort(aux[i].begin(), aux[i].end());
  }
  int idx = 0;
  for (int i = 0; i < buckets; ++i) {
    for (int j = 0; j < aux[i].size(); ++j) {
      arr[idx++] = aux[i][j];
    }
  }
}
/*
void bucket(std::vector<int> &arr, int k) {
  int max, size = 10;

  if (k > 0)
    max = arr[0];
  else
    return;

  std::vector<std::vector<int>> buckets(size);
  for (int i = 0; i < k; ++i) {
    if (arr[i] > max)
      max = arr[i];
  }

  for (int i = 0; i < k; ++i) {
    int pos = (size * arr[i]) / max;
    buckets[pos].push_back(arr[i]);
  }

  print_vec(buckets);

  for (int i = 0; i < size; ++i) {
    std::sort(buckets[i].begin(), buckets[i].end());
  }

  int idx = 0;

  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < buckets[i].size(); ++j) {
      arr[idx++] = buckets[i][j];
    }
  }
}*/
