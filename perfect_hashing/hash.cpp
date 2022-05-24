#include "hs.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

int main() {
  std::srand(time(NULL));

  std::cout << "Ingrese nombre del archivo: " << std::endl;

  std::string filename, line;
  // Cardinalidad del conjunto de Genomas
  int S;
  std::ifstream newFile(filename);

  // Cuenta cuantas lineas tiene el archivo de genomas
  if (newFile.is_open()) {
    while (newFile.peek() != EOF) {
      getline(newFile, line);
      S++;
    }
    newFile.close();
  }

  // Para prueba 1 hacer m = n.
  int n = S * (abs(4 - 15 + 1));
  // Numero de buckets
  int m = n;

  pHash newTable(10, m);
  // Sacamos el hashing de todos los k-mers
  //
  if (newFile.is_open()) {
    while (newFile.peek() != EOF) {
      getline(newFile, line);
      S++;
    }
    newFile.close();
  }

  return 0;
}
