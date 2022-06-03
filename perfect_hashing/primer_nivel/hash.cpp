#include "hs.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <set>
#include <vector>

void kmers(std::vector<std::string> &v1, std::string seg, int k);

int main() {

  std::cout << "Ingrese nombre del archivo: " << std::endl;

  std::string filename, line;
  std::cin >> filename;
  // Cardinalidad del conjunto de Genomas
  int S = 0, x = 15;
  std::ifstream newFile(filename);
  std::vector<std::string> k1;
  std::set<std::string> set1;

  std::cout << "[+] Calculando tamaño del archivo y generando k-mers..."
            << std::endl;
  // Cuenta cuantas lineas tiene el archivo de genomas
  if (newFile.is_open()) {
    while (newFile.peek() != EOF) {
      getline(newFile, line);
      if (line.size() >= x)
        x = line.size();
      if (line != "")
        kmers(k1, line, 15);
      S++;
    }
    newFile.close();
  }
  std::cout << "[+] Acomodando elementos repetidos..." << std::endl;
  for (int i = 0; i < k1.size(); ++i) {
    set1.insert(k1[i]);
  }
  std::cout << "[+] Tamanio de claves sin repetir: " << set1.size()
            << std::endl;
  // Para prueba 1 hacer m = n.
  int n = set1.size();
  // Numero de buckets
  int m = n;
  std::set<std::string>::iterator itr;
  pHash newTable(m, 7342117);
  //   Sacamos el hashing de todos los k-mers
  long long int sum;
  int cont = 1;
  double aux = n * ((double)5 / 2);
  long long int prop1 = 4 * n;
  std::srand(time(NULL));
  newTable.modAB();
  std::cout << "[+] Calculando posicion de cada kmer..." << std::endl;
  for (itr = set1.begin(); itr != set1.end(); ++itr) {
    newTable.clusterBi(*itr);
  }
  std::cout << "[+] Calculando variables a_i e b_i para el primer nivel..."
            << std::endl;
  sum = newTable.cCount();
  if (sum <= prop1) {
    std::pair<int, int> p = newTable.getAB();
    int ai = p.first, bi = p.second;
    std::cout
        << "[+] La cantidad de veces que se repitio el hashing hasta cumplir "
           "prop 1 es: "
        << cont;
    std::cout << std::endl;
    std::cout << "[+] Sumatoria: " << sum << std::endl;
    std::cout << "[+] Maximo permitido: " << prop1 << std::endl;
    std::cout << "[+] Para constante a_i e b_i: " << ai << " " << bi
              << std::endl;
    std::cout << "[+] Colisiones de cada Bucket: " << std::endl;
  } else {
    while (sum > prop1) {
      std::cout << "[-] La funcion no es optima." << std::endl;
      std::cout << "[+] Calculando nueva funcion..." << std::endl;
      newTable.modAB();
      for (itr = set1.begin(); itr != set1.end(); ++itr) {
        newTable.clusterBi(*itr);
      }
      sum = newTable.cCount();
      cont++;
      std::cout << "Sumatoria = " << sum << std::endl;
      std::cout << "2n = " << prop1 << std::endl;
      if (sum <= prop1) {
        std::cout
            << "[+] La cantidad de veces repetidas hasta que ci*ci < 2*n: "
            << cont << std::endl;
        std::cout << "[+] Sumatoria: " << sum << std::endl;
        std::cout << "[+] Maximo permitido: " << prop1 << std::endl;
        std::pair<int, int> p2 = newTable.getAB();
        int a_i2 = p2.first, b_i2 = p2.second;
        std::cout << "[+] Para constante a_i e b_i: " << a_i2 << " " << b_i2
                  << std::endl;
        std::cout << "[+] Colisiones de cada Bucket: " << std::endl;
        break;
      }
    }
  }
  return 0;
}

void kmers(std::vector<std::string> &v1, std::string seg, int k) {
  int size = seg.size();
  int kmer_size = size - k + 1;
  for (int i = 0; i < kmer_size; ++i) {
    int posi = i, posf = i + k;
    if (posf <= size)
      v1.push_back(seg.substr(posi, k));
  }
}
