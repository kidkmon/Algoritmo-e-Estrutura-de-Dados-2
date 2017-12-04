#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
#include <algorithm>

using namespace std;

class Grafo{
private:
    float **matriz;
    int ordem, tamanho;
    void inicializador();
public:
    Grafo(){}
    Grafo(int);
    void setOrdem(int);
    int getOrdem();
    float** getMatriz();
    void inserirAresta(int,int,float);
    void print();
};

class FilaPrioridade{
private:
    vector<pair<int,float>> fila;
    int pai(int);
    int esq(int);
    int dir(int);
    void trocarValorPosicao(int,int);
public:
    FilaPrioridade(){}
    pair<int,float> getHeapMinimo();
    pair<int,float> remover();
    bool vazia();
    void construirHeap();
    void heapficar(int);
    void diminuirChaveHeap(pair<int,float>);
    void inserir(pair<int,float>);
    void print();
};

class Dijkstra{
private:
    FilaPrioridade filaPrioridade;
    float *vetorDistancia;
    int *vetorPredecessor,ordem;
    float somaPeso;
public:
    Dijkstra(){ }
    void inicializador(Grafo&,int);
    void relaxar(int,int,float);
    int* getVetorPredecessor();
    float metodoDijkstra(Grafo&,int,int);

};

class UnionFind{
private:
    int *vetorVertice, tamanho;
public:
    UnionFind(){}
    UnionFind(int);
    int getTamanho();
    bool conectado(int,int);
    int find(int);
    void algoritmoUnion(int,int);
};

class HeapSort{
private:
    int pai(int);
    int esq(int);
    int dir(int);
    void heapficar(vector<pair<pair<int,int>,float>>&,int,int);
    void construirHeap(vector<pair<pair<int,int>,float>>&,int&);
public:
    HeapSort(){}
    void heapSort(vector<pair<pair<int,int>,float>>&);
    void print(vector<pair<pair<int,int>,float>>);
};

class Kruskal{
private:
    UnionFind *unionFind = new UnionFind(100);
    HeapSort algoritmoHeapSort;
    vector<pair<pair<int,int>,float>> vetorArestas;
public:
    Kruskal(){ vetorArestas.push_back(make_pair(make_pair(-1,-1),-1)); }
    float mstKruskal(Grafo&,int,int);
};

int main() {

    int vertices,arestas;
    int vertice1,vertice2;
    int entrada,saida;
    float peso;

    cin >> vertices >> arestas;

    Grafo grafo(vertices);
    Dijkstra dijkstra;

    for(int i = 0; i < arestas; i++){
        cin >> vertice1 >> vertice2 >> peso;
        grafo.inserirAresta(vertice1,vertice2,peso);
    }

    cin >> entrada >> saida;
    
    float a = dijkstra.metodoDijkstra(grafo,entrada,saida);

    cout << a << endl;
    return 0;
}

//Início do Grafo
Grafo::Grafo(int ordem){
    this->ordem = ordem;
    matriz = new float*[ordem+1];
    for(int i = 1; i <= ordem; i++){ matriz[i] = new float[ordem+1]; }
    inicializador();
}

void Grafo::inicializador(){
    for(int i = 1;i <= ordem; i++){
        for(int j = 1; j <= ordem; j++){
            matriz[i][j] = 0;
        }
    }
}

void Grafo::inserirAresta(int u, int v, float peso){
    matriz[u][v] = peso;
    matriz[v][u] = peso;
    tamanho++;
}

void Grafo::setOrdem(int ordem){ 
    this->ordem = ordem; 
    matriz = new float*[ordem+1];
    for(int i = 0; i <= ordem; i++){ matriz[i] = new float[ordem+1]; }
    inicializador();
}

int Grafo::getOrdem(){ return ordem; }

float** Grafo::getMatriz(){ return matriz; }

void Grafo::print(){
    int k = 3;
    cout << " ";
    for(int j = 1; j <= ordem; j++){ cout << setw(k) << j; }
    cout << endl;
    for(int j = 1; j <= ordem*k + 3; j++){ cout << "-"; }
    cout << endl;
    for(int i = 1; i <= ordem; i++){
        cout << setw(1) << i; cout << " |";
        for(int j = 1; j <= ordem; j++){
            cout << setw(k) << matriz[i][j];
        }
        cout << endl;
    }
}

//Início da Fila de Prioridade
int FilaPrioridade::pai(int posicao) {
    if(posicao%2 == 0){
        return (posicao/2) - 1;
    }
    else{
        return posicao/2;
    }
}

int FilaPrioridade::esq(int posicao){ return 2*posicao; }

int FilaPrioridade::dir(int posicao){ return (2*posicao) + 1; }

void FilaPrioridade::trocarValorPosicao(int posicaoFilho, int posicaoPai){
    pair<int,float> tmp = fila[posicaoFilho];
    fila[posicaoFilho] = fila[posicaoPai];
    fila[posicaoPai] = tmp;
}

void FilaPrioridade::construirHeap(){
    for(int i = pai(fila.size()); i >= 1; i--){
        heapficar(i);
    }
}

void FilaPrioridade::heapficar(int posicao){
    int esquerda = esq(posicao), direita = dir(posicao), tamanho = fila.size(),menor;

    if(esquerda < tamanho && fila[esquerda].second < fila[posicao].second){
        menor = esquerda;
    }
    else{
        menor = posicao;
    }
    if(direita < tamanho && fila[direita].second < fila[menor].second){
        menor = direita;
    }
    if(menor != posicao){
        trocarValorPosicao(menor,posicao);
        heapficar(menor);
    }
}

void FilaPrioridade::diminuirChaveHeap(pair<int,float> posicao){
    fila[posicao.first].second = posicao.second;
    int tamanho = fila.size() - 1;
    int posicaoPai = pai(tamanho);

    while(fila[tamanho] < fila[posicaoPai] && tamanho >= 0 && posicaoPai >= 0){
        trocarValorPosicao(tamanho,posicaoPai);
        tamanho = posicaoPai;
        posicaoPai = pai(tamanho);
    }
}

void FilaPrioridade::inserir(pair<int,float> posicao){
    fila.push_back(make_pair(posicao.first,posicao.second));
    diminuirChaveHeap(posicao);
}

pair<int,float> FilaPrioridade::remover(){
    int tamanhoFila = fila.size() - 1;
    trocarValorPosicao(tamanhoFila, 0);
    pair<int,float> menorPar = fila.back();
    fila.pop_back();
    heapficar(0);
    return menorPar;
}

pair<int,float> FilaPrioridade::getHeapMinimo(){
    return fila[0];
}

bool FilaPrioridade::vazia(){
    if(fila.size() == 0) { return true;}
    else { return false; }
}

void FilaPrioridade::print(){
    while(fila.size() > 0){
        pair<int,float> p = remover();
        cout << p.first << " " << p.second << endl;
    }
    cout << endl;
}

//Início de Dijkstra
void Dijkstra::inicializador(Grafo &grafo,int origem){
    this->ordem = grafo.getOrdem();
    vetorDistancia = new float[ordem+1];
    vetorPredecessor = new int[ordem+1];

    for(int i = 0; i <= ordem;i++){
        vetorDistancia[i] = numeric_limits<float>::max();
        vetorPredecessor[i] = -1;
    }
    vetorDistancia[origem] = 0;
    filaPrioridade.inserir(make_pair(origem,vetorDistancia[origem]));
}

void Dijkstra::relaxar(int u, int v, float w){
    if(vetorDistancia[v] > vetorDistancia[u] + w){
        vetorDistancia[v] = vetorDistancia[u] + w;
        vetorPredecessor[v] = u;
        filaPrioridade.inserir(make_pair(v,vetorDistancia[v]));
    }
}

int* Dijkstra::getVetorPredecessor(){ return vetorPredecessor; }

float Dijkstra::metodoDijkstra(Grafo &grafo,int origem, int destino){
    inicializador(grafo,origem);
    
    while(!filaPrioridade.vazia()){
        pair<int,float> menorPar = filaPrioridade.getHeapMinimo();
        filaPrioridade.remover();
        for(int i = 1; i <= grafo.getOrdem();i++){
            int verticeAdjacente;
            if(grafo.getMatriz()[menorPar.first][i] > 0.0f){
                verticeAdjacente = i;
                float peso = grafo.getMatriz()[menorPar.first][i];
                relaxar(menorPar.first,verticeAdjacente,peso);
            }

        }
    }
    return vetorDistancia[destino];
}

//Início do Union Find
UnionFind::UnionFind(int tamanho){
    this->tamanho = tamanho;
    vetorVertice = new int[tamanho];
    for(int i = 0; i < tamanho;i++){
        vetorVertice[i] = i;
    }
}

int UnionFind::getTamanho() {
    return tamanho;
}

bool UnionFind::conectado(int vertice1, int vertice2) {
    return find(vertice1) == find(vertice2);
}

int UnionFind::find(int vertice) {
    if(vetorVertice[vertice] == vertice){
        return vertice;
    }
    return find(vetorVertice[vertice]);
}

void UnionFind::algoritmoUnion(int vertice1, int vertice2) {
    int valorVertice1 = find(vertice1);
    int valorVertice2 = find(vertice2);

    vetorVertice[valorVertice1] = valorVertice2;
}

//Início do Heap Sort
int HeapSort::pai(int posicao) { return posicao/2; }

int HeapSort::esq(int posicao){ return 2*posicao; }

int HeapSort::dir(int posicao){ return (2*posicao)+1; }

void HeapSort::heapficar(vector<pair<pair<int,int>,float>> &vetor, int posicao, int heapSize){
    int esquerda = esq(posicao), direita = dir(posicao), menor;

    if(esquerda <= heapSize && vetor[esquerda].second > vetor[posicao].second){
        menor = esquerda;
    }
    else{
        menor = posicao;
    }

    if(direita <= heapSize && vetor[direita].second > vetor[menor].second){
        menor = direita;
    }

    if(menor != posicao){
        swap(vetor[posicao],vetor[menor]);
        heapficar(vetor,menor,heapSize);
    }
}

void HeapSort::construirHeap(vector<pair<pair<int,int>,float>> &vetor, int &heapSize){
    heapSize = vetor.size() - 1;
    for(int i = pai(heapSize); i >= 1; i--){
        heapficar(vetor,i,heapSize);
    }
}

void HeapSort::heapSort(vector<pair<pair<int,int>,float>> &vetor){
    int heapSize = 0;
    construirHeap(vetor, heapSize);
    for(int i = vetor.size()-1; i >= 2;i--){
        swap(vetor[1],vetor[i]);
        heapSize--;
        heapficar(vetor,1,heapSize);
    }
}

void HeapSort::print(vector<pair<pair<int,int>,float>> vetor){
    for(unsigned int i = 1; i < vetor.size();i++){
        cout << vetor[i].second << " ";
    }
    cout << endl;
}

//Início do Kruskal
float Kruskal::mstKruskal(Grafo &grafo, int tamanhoAresta,int tamanhoVertice){    
    int mstArestas = 0, contadorAresta = 0;
    float mstPeso = 0;

    for(int i = 1; i <= grafo.getOrdem();i++){
        for(int j = 1; j <= grafo.getOrdem();j++){
            if (grafo.getMatriz()[i][j] > 0) {
                vetorArestas.push_back(make_pair(make_pair(i,j),grafo.getMatriz()[i][j])); 
            }
        }
    }   

    algoritmoHeapSort.heapSort(vetorArestas);

    while((mstArestas < tamanhoVertice-1) || (contadorAresta < tamanhoAresta)){
        int vertice1 = vetorArestas[contadorAresta].first.first;
        int vertice2 = vetorArestas[contadorAresta].first.second;
        float peso = vetorArestas[contadorAresta].second;

        if(unionFind->find(vertice1) != unionFind->find(vertice2)){
            unionFind->algoritmoUnion(vertice1,vertice2);
            mstPeso += peso;
            mstArestas++;
        }
        contadorAresta++;
    }
    return mstPeso;
}