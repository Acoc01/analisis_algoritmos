#include "hs.h"
#include <random>
#include <vector>

pHash::pHash(int M, int p) {
  this->a = 0;
  this->b = 0;
  this->prm = p;
  this->tam_bucket = M;
  std::vector<bucket_t> table(M);
  for (int i = 0; i < M; ++i) {
    createMiniL(&table[i].list_i);
    table[i].c = -1;
  }
  this->table = table;
}

int pHash::hashFun(std::string gen, int p, int M, int a, int b) {
  int k = this->stringValue(gen);
  return ((a * k + b) % p) % M;
}

int pHash::stringValue(std::string gen) {
  int sum = 0;
  for (int i = 0; i < gen.size(); ++i) {
    sum += (int)gen[i];
  }
  return sum;
}

int pHash::randInt(int p) { return rand() % p; }

void pHash::createMiniL(struct mini_list *ls) {
  ls->ai = 0;
  ls->bi = 0;
  ls->mi = 0;
}

void pHash::printBucket() {
  int size = this->table.size();
  for (int i = 0; i < size; ++i) {
    std::cout << "Bucket #" << i << ": ";
    std::cout << std::endl;
    std::cout << "A #" << i << ": " << this->table[i].list_i.ai;
    std::cout << std::endl;
    std::cout << "B #" << i << ": " << this->table[i].list_i.bi;
    std::cout << std::endl;
    std::cout << "M #" << i << ": " << this->table[i].list_i.mi;
    std::cout << std::endl;
  }
}

void pHash::modifyTable() {
  for (int i = 0; i < this->table.size(); ++i) {
    this->table[i].list_i.ai = i * 10;
    this->table[i].list_i.bi = (i + 5) * 10;
    this->table[i].list_i.mi = (i + 10) * 10;
  }
}
// Hace push de un elemento en el bucket para ver cuantas
// Colisiones se crean en el bucket i
void pHash::clusterBi(std::string kmer) {
  int pos = hashFun(kmer, this->prm, this->tam_bucket, this->a, this->b);
  this->table[pos].c++;
}
// Cuenta cuantas colisiones hay en total en el la tabla
int pHash::cCount() {
  int sum = 0;
  for (int i = 0; i < this->table.size(); ++i) {
    sum += this->table[i].c;
  }
  return sum;
}
