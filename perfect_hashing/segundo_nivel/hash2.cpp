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
  std::srand(time(NULL));
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
  // Para prueba 1 hacer m = n.
  int n = S * (x - 15 + 1);
  // Numero de buckets
  int m = n;
  std::set<std::string>::iterator itr;

  pHash newTable(m, 7342117);
  //   Sacamos el hashing de todos los k-mers
  newTable.modAB();
  newTable.setAB(6273927, 6617981);
  std::cout << "[+] Calculando posicion de cada kmer..." << std::endl;
  for (itr = set1.begin(); itr != set1.end(); ++itr) {
    newTable.clusterBi(*itr);
  }
  // Ahora debemos crear las tablas para cada bucket.
  // Las tablas estan con un a y b aleatorio desde el inicio
  std::cout << "[+] Creando listas para cada Bucket..." << std::endl;
  newTable.makeList();
  // Una vez creada cada lista hay que escoger los a y b para cada
  // lista que no genera colisiones.
  std::cout << "[+] Calculando a_j y b_j para cada lista..." << std::endl;
  for (itr = set1.begin(); itr != set1.end(); ++itr) {
    newTable.clusterBj(*itr);
  }
  int cont = 0;
  for (int i = 0; i < m; ++i) {
    if (newTable.cCounti(i) == 0) {
      // std::cout << "[+] No hay colisiones, las variables a_j y b_j son: ";
      std::pair<int, int> p = newTable.getAB(i);
      std::cout << p.first << " " << p.second << std::endl;
      cont++;
    }
  }
  if (cont == m) {
    std::cout << "[+] No hay colisiones en ninguna lista." << std::endl;
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
