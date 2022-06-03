#include "hs.h"
#include <iostream>
#include <random>
#include <vector>
/*Constructor que inicializa las variables
y a parte inicializa los M buckets*/
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

/*Funcion hash.*/
int pHash::hashFun(std::string gen, int p, int M, int a, int b) {
  int k = this->stringValue(gen);
  int pos = abs(((a * k + b) % p) % M);
  return pos;
}
/*Codifica el kmer a un entero para usarlo en hash*/
int pHash::stringValue(std::string gen) {
  int sum = 0;
  for (int i = 0; i < gen.size(); ++i) {
    char aux = gen[i];
    sum = (sum << 2) | ((aux >> 1) & 3);
  }
  return sum;
}

/*Entero aleatorio*/
int pHash::randInt(int p) { return rand() % p; }

/*Inicializa los valores de las listas, se usa solo en el
constructor*/
void pHash::createMiniL(struct mini_list *ls) {
  ls->ai = 0;
  ls->bi = 0;
  ls->mi = 0;
  ls->ci = 0;
}
/*Funcion para debuguear que se uso para formar los buckets*/
void pHash::printBucket() {
  int size = this->table.size();
  for (int i = 0; i < size; ++i) {
    std::cout << "Bucket #" << i << ": ";
    std::cout << std::endl;
    std::cout << "C #" << i << ": " << this->table[i].c;
    std::cout << std::endl;
    std::cout << "M #" << i << ": " << this->table[i].list_i.mi;
    std::cout << std::endl;
  }
}

/*Funcion que modifica la tabla, se encarga de debuguear*/
void pHash::modifyTable() {
  for (int i = 0; i < this->table.size(); ++i) {
    this->table[i].list_i.ai = i * 10;
    this->table[i].list_i.bi = (i + 5) * 10;
    this->table[i].list_i.mi = (i + 10) * 10;
  }
}

// Genera una nueva lista de tamanio ci^2.
void pHash::makeList() {
  for (int pos = 0; pos < this->tam_bucket; pos++) {
    this->table[pos].list_i.ai = 0;
    this->table[pos].list_i.bi = 0;
    this->table[pos].list_i.ci = 0;
    if (this->table[pos].c > 0) {
      this->table[pos].list_i.buck.clear();
      int tam = pow((double)this->table[pos].c, 2);
      this->table[pos].list_i.mi = tam;
      std::vector<std::string> nwv(tam);
      this->table[pos].list_i.buck = nwv;
      this->modAB(pos);
    }
  }
}
// Hace push de un elemento en el bucket para ver cuantas
// Colisiones se crean en el bucket i
void pHash::clusterBi(std::string kmer) {
  // Tentativa posicion dada por hash
  int pos = hashFun(kmer, this->prm, this->tam_bucket, this->a, this->b);
  this->table[pos].si.push_back(kmer);
  this->table[pos].c++;
}
/*Para usar esta funcion se tiene que obtener primero la posicion
del bucket al que corresponde el kmer. Luego de eso se llama a esta
funcion que calcula la posicion del kmer dentro de la lista de ese
bucket. Si encuentra colisiones le suma a una variable que cuenta
el numero de colisiones de la lista de ese bucket.
La idea es repetir este proceso llamando a modAB(pos) antes de calcular
todos los clusters de todas las listas hasta que esos cluster sean 0.*/

// Funcion modificada, antes recibia kmer ahora nada.
void pHash::clusterBj() {
  /*int pos = hashFun(kmer, this->prm, this->tam_bucket, this->a, this->b);
  int tam = this->table[pos].list_i.mi;
  int ai = this->table[pos].list_i.ai;
  int bi = this->table[pos].list_i.bi;
  int i = hashFun(kmer, this->prm, tam, ai, bi);
  if (this->table[pos].c > 1) {
    if (this->table[pos].list_i.buck[i] != "") {
      this->table[pos].list_i.ci++;
    } else {
      this->table[pos].list_i.buck[i] = "1";
    }
  }*/
  // Recorro cada bucket.
  int listas_sin_colision = 0;
  for (int i = 0; i < this->tam_bucket; ++i) {
    // Si hay mas de un elemento calculamos Aj Bj
    if (this->table[i].c > 1) {
      modAB(i);                     // Calculamos Aj y Bj
      this->table[i].list_i.ci = 0; // Iniciamos contador de colision en 0
      // Iniciamos el tamanio del bucket como ci^2
      this->table[i].list_i.mi = pow(this->table[i].c, 2);
      // Guardamos el tamanio
      int mi = this->table[i].list_i.mi;
      // Creamos un arreglo de tamanio mi
      std::vector<std::string> aux(mi);
      this->table[i].list_i.buck = aux;
      // Creamos contador de veces que se busca Aj y Bj
      int cont = 1;
      // Guardamos variables ai, bi para escribir menos
      int ai = this->table[i].list_i.ai;
      int bi = this->table[i].list_i.bi;
      // Recorremos cada conjunto Si e insertamos contando colisiones.
      for (int j = 0; j < this->table[i].si.size(); ++j) {
        // Calculamos la posicion del elemento Si.
        int pos = hashFun(this->table[i].si[j], this->prm, mi, ai, bi);
        // Si la posicion no estaba vacia entonces hay colision
        if (this->table[i].list_i.buck[pos] != "") {
          this->table[i].list_i.ci++;
          // Si la posicion estaba vacia se ingresa el kmer.
        } else {
          this->table[i].list_i.buck[pos] = this->table[i].si[j];
        }
      }
      // Si no hay colisiones en esta lista se imprimen las variables
      // Y la cantidad de veces. Luego se pasa al siguiente bucket
      if (this->table[i].list_i.ci == 0) {
        std::cout << ai << " " << bi << " #" << i << " Tardo: " << cont
                  << " veces." << std::endl;
        listas_sin_colision++;
      } else {
        // En caso contrario se repite el ciclo anterior hasta que no hayan
        // colisiones
        while (this->table[i].list_i.ci != 0) {
          // Se modifica Aj y Bj
          modAB(i);
          // El contador de colisiones se hace 0
          this->table[i].list_i.ci = 0;
          // Se limpia el bucket y se crea de nuevo
          this->table[i].list_i.buck.clear();
          std::vector<std::string> aux(mi);
          this->table[i].list_i.buck = aux;
          // El contador de veces aumenta en 1
          cont++;
          // Se actualizan las variables para escribir menos
          ai = this->table[i].list_i.ai;
          bi = this->table[i].list_i.bi;
          // Se vuelven a recorrer los elementos del bucket Si
          for (int j = 0; j < this->table[i].si.size(); ++j) {
            // Se hace hash con las nuevas variables
            int pos = hashFun(this->table[i].si[j], this->prm, mi, ai, bi);
            // Si la posicion no esta vacia se suma una colision
            if (this->table[i].list_i.buck[pos] != "") {
              this->table[i].list_i.ci++;
              // Si la posicion esta vacia se guarda el kmer
            } else {
              this->table[i].list_i.buck[pos] = this->table[i].si[j];
            }
          }
        }
        std::cout << ai << " " << bi << " #" << i << " Tardo: " << cont
                  << " veces." << std::endl;
        listas_sin_colision++;
      }
    }
  }
  std::cout << "Listas sin colisiones: " << listas_sin_colision << std::endl;
}
// Cuenta cuantas colisiones hay en total en el la tabla
long long int pHash::cCount() {
  long long int sum = 0;
  for (int i = 0; i < this->table.size(); ++i) {
    // Se considera colision si cae mas de un elemento en i.
    if (this->table[i].c >= 1)
      sum += pow(this->table[i].c, 2);
    std::cout << "c#" << i << ": " << this->table[i].c << std::endl;
  }
  for (int i = 0; i < this->table.size(); ++i) {
    this->table[i].si.clear();
    this->table[i].c = 0;
  }
  return sum;
}

long long int pHash::cCounti(int pos) { return this->table[pos].list_i.ci; }

/*Modifica a y b de forma aleatoria*/
void pHash::modAB() {
  this->a = randInt(this->prm);
  this->b = randInt(this->prm);
}

void pHash::modAB(int pos) {
  if (this->table[pos].c > 1) {
    this->table[pos].list_i.ai = randInt(this->prm);
    this->table[pos].list_i.bi = randInt(this->prm);
  }
}
/*Destructor*/
void pHash::clear() {
  for (int i = 0; i < this->table.size(); ++i) {
    this->table[i].list_i.buck.clear();
  }
  this->table.clear();
}
std::pair<int, int> pHash::getAB() { return std::make_pair(this->a, this->b); }
std::pair<int, int> pHash::getAB(int pos) {
  int aj = this->table[pos].list_i.ai;
  int bj = this->table[pos].list_i.bi;
  return std::make_pair(aj, bj);
}

void pHash::setAB(int a, int b) {
  this->a = a;
  this->b = b;
}

void pHash::setAB(int a, int b, int pos) {
  this->table[pos].list_i.ai = a;
  this->table[pos].list_i.bi = b;
}
