#include <iostream>
#include <vector>

using namespace std;

typedef int Vertice;

class Lista{
private:
    vector<int> lista;
public:
    Lista (){}
    void insere(int);
    int busca(int);
    void remove(int);
    void print();
    void destroy();
};

template<typename T>
class No{
private:
    T valor;
    No<T>* prox;
public:
    No(){prox = NULL;}
    No(T);
    void setValor(T);
    void setProx(No<T>*);
    T getValor();
    No<T>* getProx();
};

class Fila{
private:
    No<int>* frente;
    No<int>* tras;
public:
    Fila();
    void enfileira(int);
    void desenfileira(int);
};

class Grafo{

private:
    Lista *adjacentes;
    int ordem;
    int tamanho;
    void destroy();
public:
    Grafo(int);
    void inicializar(int);
    void insereAresta(Vertice, Vertice);
    void removeAresta(Vertice, Vertice);
    void print();
    void algoritmoBFS(Vertice);
};


int main(){
 
    

    return 0;
}

// Início da Lista
void Lista::destroy(){
    vector<int>().swap(lista);
}

void Lista::insere(int posicao){
    lista.push_back(posicao);
}

int Lista::busca(int posicao){
    bool verificaPosicaoEncontrada = false;
    int posicaoEncontrada, i = 0;
    
    while(i < lista.size() || verificaPosicaoEncontrada == false){
        if(posicao == lista[i]){
            posicaoEncontrada = i;
            verificaPosicaoEncontrada = true;
        }
        i++;
    }

    if(verificaPosicaoEncontrada){
        return posicaoEncontrada;
    }
    else{
        return -1;
    }
}

void Lista::remove(int posicao){
    int buscaPosicao = busca(posicao);
    if(buscaPosicao == -1){
        cout << "Lista vazia ou posicao invalida" << endl;
    }
    else{
        lista.erase(lista.begin()+ buscaPosicao);
    }
}

void Lista::print(){
    for(int i = 0; i < lista.size();i++){
        cout << lista[i] << " ";
    }
    cout << endl;
}

//Inicia Nó
template<typename T>
No<T>::No(T valor) {
    this->valor = valor;
    this->prox = NULL;
}

template<typename T>
void No<T>::setValor(T valor) {
    this->valor = valor;
}

template<typename T>
void No<T>::setProx(No* prox) {
    this->prox = prox;
}

template<typename T>
T No<T>::getValor() {
    return valor;
}

template<typename T>
No<T>* No<T>::getProx() {
    return prox;
}

//Inicio Fila
Fila::Fila(){
    frente = new No<int>;
    frente->setProx(NULL);
    tras = frente;
}

void Fila::enfileira(int item){
    tras->setProx(new No<int>);
    tras = tras->getProx();
    tras->setValor(item);
    tras->setProx(NULL);
}

void Fila::desenfileira(int item){
    No<int>* aux = frente;
    frente = frente->getProx();
    item = frente->getValor();
    delete aux;
}

// Início Grafo
Grafo::Grafo(int ordem){
    inicializar(ordem);
}

void Grafo::inicializar(int ordem){
    if(this->ordem != 0){
        destroy();
    }
    this->ordem = ordem;
    adjacentes = new Lista[ordem + 1];
}

void Grafo::insereAresta(Vertice u, Vertice v){
    int chave = v;
    adjacentes[u].insere(chave);
    chave = u;
    adjacentes[v].insere(chave);
    tamanho++;
}

void Grafo::print(){
    for(int i = 0;i < ordem;i++){
        cout << "v[" << i << "] = ";
        adjacentes[i].print();
    }
}

void Grafo::destroy(){
    for(int i = 0; i < ordem;i++){
        adjacentes[i].destroy();
    }
    delete(adjacentes);
    ordem = tamanho = 0;
}

void Grafo::algoritmoBFS(Vertice origem){
    
}
