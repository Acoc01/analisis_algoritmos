#ifndef PHASH_H
#define PHASH_H
#include <iostream>
#include <vector>

// Estructura de la lista
struct mini_list {
  int mi;
  int ai;
  int bi;
  int ci;
  std::vector<std::string> buck;
};

// Estructura del bucket
struct bucket_t {
  int c;
  std::vector<std::string> si;
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
  // Funcion que crea la Lista para cada Bucket
  void makeList(int a, int b, int m, int pos);
  // Funcion que verifica cuantas colisiones hay
  // En el bucket i
  void clusterBi(std::string kmer);
  // Funcion que verifica cuantas colisiones hay
  // En cada lista Bj
  // Funcion modificada, antes recibia kmer.
  void clusterBj();
  // Funcion que verifica numeros de colisiones en la tabla.
  long long int cCount();
  // Funcion que verifica numeros de colisiones en la lista_i.
  long long int cCounti(int pos);
  // Funcion que inserta los elementos de S_i en el Bucket_i
  void insertInto(std::string kmer);
  // Funcion que define el todos los kmers.
  void clear();
  // Funcion que setea un a y b aleatorio
  void modAB();
  void modAB(int pos);
  // Funcion que devuelve a y b correspondiente
  std::pair<int, int> getAB();        // Para a_i e b_i
  std::pair<int, int> getAB(int pos); // Para a_j y b_j
  // Funcion que setea a y b correspondiente
  void setAB(int a, int b);
  void setAB(int a, int b, int pos);
  // Funcion para buscar elemento
  bool searchElem(std::string kmer);
};
#endif
