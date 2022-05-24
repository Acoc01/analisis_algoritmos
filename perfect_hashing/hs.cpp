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
    table[i].c = 0;
  }
  this->table = table;
}

int pHash::hashFun(std::string gen, int p, int M) {
  int k = this->stringValue(gen);
  this->a = randInt(p), this->b = randInt(p);
  return ((this->a * k + this->b) % p) % M;
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

void pHash::pushElem(std::string kmer) {
  int pos = this->hashFun(kmer, this->prm, this->tam_bucket);
  if (!table[pos].list_i.buck.empty()) {
    table[pos].list_i.buck.push_back(kmer);
    table[pos].list_i.mi = std::pow(table[pos].list_i.buck.size(), 2);
  }
}

int pHash::cCount(std::string kmer) {
  int sum = 0;
  for (int i = 0; i < this->table.size(); ++i) {
    sum += this->table[i].c;
  }
  return sum;
}
