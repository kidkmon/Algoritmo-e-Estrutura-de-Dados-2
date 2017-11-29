#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

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

template<typename T>
class Lista{
private:
    No<T>* prim;
    No<T>* ult;
public:
    Lista ();
    ~Lista(){}
    No<T>* getPrim();
    No<T>* busca(T);
    void insere(T);
    void remove(T);
    void print();
};

class Grafo{
private:
    float **matriz;
    float ordem, tamanho;
    void inicializador();
public:
    Grafo(int);
    void inserirAresta(int,int,float);
    void print();
};

int main() {

    Grafo g(5);

    g.inserirAresta(1,2,2);
    g.inserirAresta(2,3,2);
    g.inserirAresta(3,4,3);
    g.inserirAresta(4,5,4);
    g.inserirAresta(5,1,5);

    g.print();

    return 0;
}

//Início do Nó
template<typename T>
No<T>::No(T valor) {
    this->valor = valor;
    this->prox = NULL;
}

template<typename T>
void No<T>::setValor(T valor) { this->valor = valor; }

template<typename T>
void No<T>::setProx(No* prox) { this->prox = prox; }

template<typename T>
T No<T>::getValor() { return valor; }

template<typename T>
No<T>* No<T>::getProx() { return prox; }

// Início da Lista
template <typename T>
Lista<T>::Lista(){
    prim = new No<T>;
    prim->setProx(NULL);
    ult = prim;
}

template<typename T>
No<T>* Lista<T>::getPrim(){
    return prim;
}

template<typename T>
No<T>* Lista<T>::busca(T elemento){
    No<T>* p = prim->getProx();
    while(p != NULL && p->getValor() != elemento){
        p = p->getProx();
    }
    return p;
}

template<typename T>
void Lista<T>::insere(T elemento){
    ult->setProx(new No<T>);
    ult = ult->getProx();
    ult->setProx(NULL);
    ult->setValor(elemento);
}

template<typename T>
void Lista<T>::print(){
    No<T>* p = prim->getProx();
    while(p != NULL){
        cout << p->getValor() << " ";
        p = p->getProx();
    }
    cout << endl;
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
