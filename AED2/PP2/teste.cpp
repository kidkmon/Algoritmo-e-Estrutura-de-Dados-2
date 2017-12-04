#include <iostream>
#include <iomanip>
#include <vector>
#include <climits>
#include <cstdlib>

using namespace std;

class Aresta {
private:
  int verticeU, verticeV;
  float peso;
public:
  Aresta(int verticeU, int verticeV, float peso) ;
  int getVerticeU();
  int getVerticeV();
  float getPeso();
};

class Grafo {
private:
  float **grafo, ordem, tamanho;
  vector<Aresta> arestas;
  void inicializa();
public:
  Grafo(int ordem);
  void inserirVertice(int verticeU, int verticeV, float peso);
  void mostrar();
  vector<Aresta> getArestas();
  void mostrar_arestas();
  float getPeso(int verticeU, int verticeV);
  int getOrdem();
  int particao(int primeiro, int ultimo);
  void quicksort(int primeiro, int ultimo);
};

class Fila_Prioridade {
private:
  vector< pair<int,float> > fila_prioridade;
  int tamanho_fila;

  int pai(int posicao);
  int direita(int posicao);
  int esquerda(int posicao);

  void heapfica_minimo(int posicao);
  void reduzir_chave_heap(int posicao, float chave);
  void constroi_heap_minimo();
  pair<int,float> heap_minimo();
public:
  Fila_Prioridade();
  void mostrar_heap();
  pair<int,float> extrair_heap_minimo();
  void inserir_heap_minimo(int vertice, float chave);
  void atualizar_peso(int vertice, float peso);
  bool nao_vazia();
};

class AlgoritmoDijkstra {
private:
  int *predecessores, ordem;
  float *distancias;
  Fila_Prioridade fila_prioridade;
  void inicializa(Grafo *grafo, int vertice_inicial);
  void relaxa(Grafo *grafo, int verticeU, int verticeV);
public:
  AlgoritmoDijkstra() {}
  void Dijkstra(Grafo *grafo, int vertice_inicial);
  int retornar_predecessor(int vertice);
  void mostrar_resultado();
};

class Union_Find {
private:
  int *ranked, *parents;
public:
  Union_Find(int ordem);
  void make_set(int vertice);
  void uniun(int verticeU, int verticeV);
  void link(int verticeU, int verticeV);
  int find_set(int vertice);
};

class AlgoritmoKruskal {
private:
  vector<Aresta> arvore_geradora;
  Union_Find *union_find;
public:
  AlgoritmoKruskal() {}
  void kruskal(Grafo grafo);
  void mostrar_resultado();
  float retornar_peso();
};

class Cerebro {
private:
  int vertice_entrada, vertice_saida;
  Grafo *neuronios;
  vector<Grafo> blocos_neuronios;
  vector<vector<int>> doentes;
  AlgoritmoDijkstra caminho_minimo;
  float custo;
  void inicializa();
  void calcular_custo();
  void calcular_caminho_minimo();
  void mostrar_custo();

public:
  Cerebro();
  void montar_cerebro();
  void injetar_robo();
};

int main() {

  Cerebro cerebro;
  cerebro.montar_cerebro();
  cerebro.injetar_robo();

  return 0;
}

/*  ----- Métodos da Classe Aresta -----  */

Aresta::Aresta(int verticeU, int verticeV, float peso) {
  this->verticeU = verticeU;
  this->verticeV = verticeV;
  this->peso = peso;
}

int Aresta::getVerticeU() {
  return verticeU;
}

int Aresta::getVerticeV() {
  return verticeV;
}

float Aresta::getPeso() {
  return peso;
}

/*  ----- Métodos da Classe Grafo ----- */

void Grafo::inicializa() {
  for(int i = 1; i <= ordem; i++) {
    for(int j = 1; j <= ordem; j++) {
      grafo[i][j] = 0;
    }
  }
}

Grafo::Grafo(int ordem) {
  this->ordem = ordem;
  this->tamanho = 0;
  grafo = new float*[ordem+1];
  for(int i = 1; i <= ordem; i++) {
    grafo[i] = new float[ordem+1];
  }
  inicializa();
}

void Grafo::inserirVertice(int verticeU, int verticeV, float peso) {
  grafo[verticeU][verticeV] = peso;
  grafo[verticeV][verticeU] = peso;
  tamanho++;
  Aresta aux(verticeU, verticeV, peso);
  arestas.push_back(aux);
}
void Grafo::mostrar() {
  int k = 3;
  cout << " ";
  for(int i = 1; i <= ordem; i++) {
    cout << setw(k) << i;
  }
  cout << endl;
  for(int i = 1; i <= ((ordem*k)+3); i++) {
    cout << "-";
  }
  cout << endl;
  for(int i = 1; i <= ordem; i++) {
    cout << setw(1) << i;cout << " |";
    for(int j = 1; j <= ordem; j++) {
      cout << setw(k) << grafo[i][j];
    }
    cout << endl;
  }
}

vector<Aresta> Grafo::getArestas() {
  quicksort(0, arestas.size()-1);
  return arestas;
}

void Grafo::mostrar_arestas() {
  for(unsigned int i = 0; (int) i < (int) arestas.size(); i ++) {
    cout << arestas[i].getVerticeU() << " " << arestas[i].getVerticeV() << " " << arestas[i].getPeso() << endl;
  }
}

float Grafo::getPeso(int verticeU, int verticeV) {
  return grafo[verticeU][verticeV];
}

int Grafo::getOrdem() {
  return this->ordem;
}

int Grafo::particao(int primeiro, int ultimo) {
  Aresta aux = arestas[primeiro];
  Aresta tmp = arestas[ultimo+1];
  arestas[ultimo+1] = aux;
  int i = primeiro, j = ultimo + 1;

  while(true) {
    do {  i++;  } while(arestas[i].getPeso() < aux.getPeso());
    do {  j--;  } while(arestas[j].getPeso() > aux.getPeso());
    if(i < j) {
      Aresta tmp2 = arestas[i];
      arestas[i] = arestas[j];
      arestas[j] = tmp2;
    } else {
      Aresta tmp2 = arestas[primeiro];
      arestas[primeiro] = arestas[j];
      arestas[j] = tmp2;
      arestas[ultimo+1] = tmp;
      return j;
    }
  }
}

void Grafo::quicksort(int primeiro, int ultimo) {
  if(primeiro < ultimo) {
    int part = particao(primeiro, ultimo);
    quicksort(primeiro, part-1);
    quicksort(part+1, ultimo);
  }
}

/*  ----- Métodos da Classe Fila_Prioridade ----- */

int Fila_Prioridade::pai(int posicao) {  return posicao/2; }
int Fila_Prioridade::direita(int posicao) {  return 2*posicao; }
int Fila_Prioridade::esquerda(int posicao) { return ((2*posicao)+1); }

void Fila_Prioridade::heapfica_minimo(int posicao) {
  int d = direita(posicao), e = esquerda(posicao), menor = INT_MAX;
  if(e <= tamanho_fila && fila_prioridade[e].second < fila_prioridade[posicao].second) {
    menor = e;
  } else {
    menor = posicao;
  }
  if(d <= tamanho_fila && fila_prioridade[d].second < fila_prioridade[menor].second) {
    menor = d;
  }
  if(menor != posicao) {
    pair<int, float> aux = fila_prioridade[posicao];
    fila_prioridade[posicao] = fila_prioridade[menor];
    fila_prioridade[menor] = aux;
  }
}

void Fila_Prioridade::reduzir_chave_heap(int posicao, float chave) {
  if(chave > fila_prioridade[posicao].second) {
    cout << "A chave informada é maior que a atual" << endl;
  } else {
    fila_prioridade[posicao].second = chave;
    while(posicao > 0 && fila_prioridade[pai(posicao)].second > fila_prioridade[posicao].second) {
      pair<int,float> temp = fila_prioridade[posicao];
      fila_prioridade[posicao] = fila_prioridade[pai(posicao)];
      fila_prioridade[pai(posicao)] = temp;
      posicao = pai(posicao);
    }
  }
}

void Fila_Prioridade::constroi_heap_minimo() {
  for(int i = (tamanho_fila/2); i > 0; i --) {
    heapfica_minimo(i);
  }
}

pair<int,float> Fila_Prioridade::heap_minimo() {
  return fila_prioridade[1];
}

Fila_Prioridade::Fila_Prioridade() {
  this->tamanho_fila = 0;
  fila_prioridade.push_back(make_pair(-1,-1));
}

void Fila_Prioridade::mostrar_heap() {
  for(int i = 1; i <= tamanho_fila; i ++) {
    cout <<  "(" << fila_prioridade.at(i).first << "-" << fila_prioridade.at(i).second << ") ";
  }
  cout << endl;
}

pair<int,float> Fila_Prioridade::extrair_heap_minimo() {
  if(tamanho_fila < 1) {
    return make_pair(-1,-1);
  } else {
    pair<int,float> minimo = heap_minimo();
    fila_prioridade[1] = fila_prioridade[tamanho_fila];
    tamanho_fila --;
    // constroi_heap_minimo();
    heapfica_minimo(1);
    return minimo;
  }
}

void Fila_Prioridade::inserir_heap_minimo(int vertice, float chave) {
  tamanho_fila ++;
  fila_prioridade.push_back(make_pair(vertice, INT_MAX));
  reduzir_chave_heap(tamanho_fila, chave);
}

void Fila_Prioridade::atualizar_peso(int vertice, float peso) {
  int aux = 1;
  for(int i = 1; i <= tamanho_fila; i ++) {
    if(fila_prioridade[i].first == vertice) {
      aux = i;
      break;
    }
  }
  fila_prioridade[aux].second = peso;
  constroi_heap_minimo();
}

bool Fila_Prioridade::nao_vazia() {
  if(tamanho_fila < 0) {
    return false;
  } else {
    return true;
  }
}

/*  ----- Métodos da Classe AlgoritmoDijkstra ----- */

void AlgoritmoDijkstra::inicializa(Grafo *grafo, int vertice_inicial) {
  this->ordem = grafo->getOrdem();
  predecessores = new int[ordem + 1];
  distancias = new float[ordem + 1];
  for(int i = 1; i <= ordem; i ++) {
    distancias[i] = INT_MAX;
    predecessores[i] = -1;
    fila_prioridade.inserir_heap_minimo(i, distancias[i]);
  }
  fila_prioridade.atualizar_peso(vertice_inicial, 0);
  distancias[vertice_inicial] = 0;
}

void AlgoritmoDijkstra::relaxa(Grafo *grafo, int verticeU, int verticeV) {
  float aux = grafo->getPeso(verticeU, verticeV);
  if(distancias[verticeV] > (distancias[verticeU] + aux)) {
    predecessores[verticeV] = verticeU;
    distancias[verticeV] = (distancias[verticeU] + aux);
    fila_prioridade.atualizar_peso(verticeV, distancias[verticeV]);
  }
}

void AlgoritmoDijkstra::Dijkstra(Grafo *grafo, int vertice_inicial) {
  inicializa(grafo, vertice_inicial);
  while(fila_prioridade.nao_vazia()) {
    pair<int, float> aux = fila_prioridade.extrair_heap_minimo();
    if(aux.first == -1) { break;  }
    for(int i = 1; i <= ordem; i ++) {
      if(grafo->getPeso(aux.first, i) != 0) {
        relaxa(grafo, aux.first, i);
      }
    }
  }
}

int AlgoritmoDijkstra::retornar_predecessor(int vertice) {
  return predecessores[vertice];
}

void AlgoritmoDijkstra::mostrar_resultado() {
  cout << "Vértice   -   Predecessor   -   Distancia" << endl;
  for(int i = 1; i <= ordem; i ++) {
    cout << "    " << i << "\t\t" << predecessores[i] << "\t\t" << distancias[i] << endl;
  }
}

/*  ----- Métodos da Class Union_Find ----- */

Union_Find::Union_Find(int ordem) {
  this->parents = new int[ordem+1];
  this->ranked = new int[ordem+1];
}

void Union_Find::make_set(int vertice) {
  parents[vertice] = vertice;
  ranked[vertice] = 0;
}

void Union_Find::uniun(int verticeU, int verticeV) {
  link(find_set(verticeU),find_set(verticeV));
}

void Union_Find::link(int verticeU, int verticeV) {
  if(ranked[verticeU] > ranked[verticeV]) {
    parents[verticeV] = verticeU;
  } else {
    parents[verticeU] = verticeV;
    if(ranked[verticeU] == ranked[verticeV]) {
      ranked[verticeU] = ranked[verticeU] + 1;
    }
  }
}

int Union_Find::find_set(int vertice) {
  if(vertice != parents[vertice]) {
    parents[vertice] = find_set(parents[vertice]);
  }
  return parents[vertice];
}

/*  ----- Métodos da Class AlgoritmoKruskal ----- */

void AlgoritmoKruskal::kruskal(Grafo grafo) {
  int ordem_grafo = grafo.getOrdem();
  this->union_find = new Union_Find(ordem_grafo);
  for(unsigned int i = 1; (int) i <= ordem_grafo; i ++) {
    union_find->make_set(i);
  }
  vector<Aresta> aux = grafo.getArestas();
  for(unsigned int i = 0; (int) i < (int) aux.size(); i ++) {
    if(union_find->find_set(aux[i].getVerticeU()) != union_find->find_set(aux[i].getVerticeV())) {
      arvore_geradora.push_back(aux[i]);
      union_find->uniun(aux[i].getVerticeU(),aux[i].getVerticeV());
    }
  }
}

void AlgoritmoKruskal::mostrar_resultado() {
  for(unsigned int i = 0; (int) i < (int) arvore_geradora.size(); i ++) {
    cout << arvore_geradora[i].getVerticeU() << " " << arvore_geradora[i].getVerticeV() << endl;
  }
}

float AlgoritmoKruskal::retornar_peso() {
  float aux = 0;
  for(unsigned int i = 0; (int) i < (int) arvore_geradora.size(); i ++) {
    aux += arvore_geradora.at(i).getPeso();
  }
  return aux;
}

/*  ----- Métodos da Classe Cérebro ----- */

void Cerebro::inicializa() {
  this->custo = 0;
  int ordem, tamanho;
  cin >> ordem >> tamanho;

  this->neuronios = new Grafo(ordem);

  for(int i = 0; i < tamanho; i ++) {
    int verticeU, verticeV;
    float peso;
    cin >> verticeU >> verticeV >> peso;
    neuronios->inserirVertice(verticeU, verticeV, peso);
  }

  cin >> this->vertice_entrada >> this->vertice_saida;

  for(int i = 0; i < ordem; i ++) {
    doentes.push_back({});
    int qtd_doentes, tamanho_b, ordem_b;
    cin >> ordem_b >> tamanho_b;
    cin >> qtd_doentes;
    Grafo tmp(ordem_b);
    blocos_neuronios.push_back(tmp);
    for(int j = 0; j < qtd_doentes; j ++) {
      int neuronio_doente;
      cin >> neuronio_doente;
      doentes.at(i).push_back(neuronio_doente);
    }
    for(int j = 0; j < tamanho_b; j ++) {
      int verticeU, verticeV;
      float peso;
      cin >> verticeU >> verticeV >> peso;
      blocos_neuronios.at(i).inserirVertice(verticeU, verticeV, peso);
    }
  }
}

void Cerebro::calcular_custo() {
  int aux = vertice_saida;
  do {
    if(doentes.at(aux-1).size() > 0) {
      AlgoritmoKruskal AK;
      AK.kruskal(blocos_neuronios.at(aux-1));
      custo += AK.retornar_peso();
    }
    aux = caminho_minimo.retornar_predecessor(aux);
  } while(aux != -1);
}

void Cerebro::calcular_caminho_minimo() {
    caminho_minimo.Dijkstra(neuronios, vertice_entrada);
}

void Cerebro::mostrar_custo() {
  cout << custo << endl;
}

Cerebro::Cerebro() {}

void Cerebro::montar_cerebro() {
  inicializa();
}

void Cerebro::injetar_robo() {
  calcular_caminho_minimo();
  calcular_custo();
  mostrar_custo();
}