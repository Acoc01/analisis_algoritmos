#include "hs.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

void kmers(std::vector<std::string> &v1, std::string seg, int k);

int main() {
  std::srand(time(NULL));

  std::cout << "Ingrese nombre del archivo: " << std::endl;

  std::string filename, line;
  std::cin >> filename;
  // Cardinalidad del conjunto de Genomas
  int S = 0, x = 15;
  std::ifstream newFile(filename);
  std::vector<std::string> k1;

  // Cuenta cuantas lineas tiene el archivo de genomas
  if (newFile.is_open()) {
    while (newFile.peek() != EOF) {
      getline(newFile, line);
      if (line.size() >= x)
        x = line.size();
      kmers(k1, line, 15);
      S++;
    }
    newFile.close();
  }

  // Para prueba 1 hacer m = n.
  int n = S * (x - 15 + 1);
  // Numero de buckets
  int m = n;
  std::cout << "El tamanio de k-mers en el archivo es: " << n << std::endl;
  std::cout << "El tamanio de cada linea de genoma es: " << x << std::endl;
  std::cout << "El arreglo k1 tiene: " << k1.size() << " kmers" << std::endl;

  // pHash newTable(m, 1137551);
  //   Sacamos el hashing de todos los k-mers

  return 0;
}

void kmers(std::vector<std::string> &v1, std::string seg, int k) {
  int size = seg.size();
  int kmer_size = size - k + 1;
  for (int i = 0; i < kmer_size; ++i) {
    v1.push_back(seg.substr(i, i + k - 1));
  }
}
