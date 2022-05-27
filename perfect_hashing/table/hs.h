#ifndef PHASH_H
#define PHASH_H
#include <iostream>
#include <vector>

// Estructura de la lista
struct mini_list {
  int mi;
  int ai;
  int bi;
  std::vector<std::string> buck;
};

// Estructura del bucket
struct bucket_t {
  int c;
  mini_list list_i;
};

class pHash {
private:
  // Tabla hash.
  int tam_bucket;
  int prm;
  int a, b;
  std::vector<bucket_t> table;

public:
  // Inicia la tabla Hash.
  pHash(int M, int p);

  // Funcion Hash
  int hashFun(std::string gen, int p, int M, int a, int b);
  // Pasa un string a un entero basando en ASCII
  int stringValue(std::string gen);
  // Numero aleatorio desde 0 hasta p-1
  int randInt(int p);
  // Crea las mini_list para cada bucket
  void createMiniL(struct mini_list *l);
  // Imprime los buckets para debuguear
  void printBucket();
  // Funcion que puede ser modificada para
  // debuguear la tabla
  void modifyTable();
  // Funcion que verifica cuantas colisiones hay
  // En el bucket i
  void clusterBi(std::string kmer);
  // Funcion que verifica numeros de colisiones en la tabla.
  long long int cCount();
  // Funcion que define el todos los kmers.
  void clear();
  // Funcion que setea un a y b aleatorio
  void modAB();
  void modAB(int pos);
  // Funcion que devuelve a y b correspondiente
  std::pair<int, int> getAB();        // Para a_i e b_i
  std::pair<int, int> getAB(int pos); // Para a_j y b_j
};
#endif