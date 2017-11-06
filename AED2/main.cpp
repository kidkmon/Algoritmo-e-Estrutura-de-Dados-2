//Eduardo Maia Freire - 1615310003
//Kid Mendes de Oliveira Neto - 1615310011
//Lorene da Silva Marques - 1615310013

#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>

#define BRANCO 0
#define CINZA 1
#define PRETO 2

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

template<typename T>
class Fila{
private:
    No<T>* frente;
    No<T>* tras;
public:
    Fila();
    T getFrente();
    bool vazia();
    void enfileira(T);
    void desenfileira(T);
    void print();
};

template<typename T1,typename T2>
class Movimento{
private:
    pair<T1,T2> posicao;
    vector<pair<T1,T2>> movimentos;
public:
    Movimento() {}
    Movimento(pair<T1,T2>);
    void insereMovimentos(pair<T1,T2>,T2,T2);
    void verificaMovimentos();
    void listarMovimentos();
    int converterPosicaoParaInteiro(pair<T1,T2>);
    pair<T1,T2> converterPosicaoParaPar(T2);
    vector<T2> converterListaPosicaoParaInteiro();
    void print();
};

template<typename T>
class Grafo{
private:
    Lista<T> *posicoes;
    int ordem = 0;
    int tamanho;
public:
    Grafo(T);
    void inicializar(T);
    void insereAresta(T, T);
    T BFS(T,T);
    void print();
};

template<typename T1,typename T2>
class Chess{
private:
    Grafo<T2> *grafo = new Grafo<T2>(64);
    pair<T1,T2> rei, cavalo1, cavalo2, cavalo3, cavalo4;
public:
    Chess(pair<T1,T2>,pair<T1,T2>,pair<T1,T2>,pair<T1,T2>,pair<T1,T2>);
    int maiorNumero(vector<T2>);
    vector<T2> countingSort(vector<T2>,vector<T2>,int);
    vector<T2> inserirAdjacentes();
    void minimoMovimento();
};

int main(){

    string entrada,numeroEntrada;

    getline(cin, numeroEntrada);
    
    for(int i = 0; i < atoi(&numeroEntrada[0]);i++){
        getline(cin, entrada);
    
        pair<char,int> rei,cavalo1,cavalo2,cavalo3,cavalo4;

        cavalo1 = make_pair(entrada[0],atoi(&entrada[1]));
        cavalo2 = make_pair(entrada[3],atoi(&entrada[4]));
        cavalo3 = make_pair(entrada[6],atoi(&entrada[7]));
        cavalo4 = make_pair(entrada[9],atoi(&entrada[10]));
        rei = make_pair(entrada[12],atoi(&entrada[13]));

        Chess<char,int> jogar(rei,cavalo1,cavalo2,cavalo3,cavalo4);

        jogar.minimoMovimento();
    }
   
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

//Inicio Fila
template<typename T>
Fila<T>::Fila(){
    frente = new No<T>;
    frente->setProx(NULL);
    tras = frente;
}

template<typename T>
bool Fila<T>::vazia(){ return tras == frente; }

template<typename T>
T Fila<T>::getFrente(){ return frente->getProx()->getValor(); }

template<typename T>
void Fila<T>::enfileira(T elemento){
    tras->setProx(new No<T>);
    tras = tras->getProx();
    tras->setValor(elemento);
    tras->setProx(NULL);
}

template<typename T>
void Fila<T>::desenfileira(T elemento){
    No<T>* aux = frente;
    frente = frente->getProx();
    elemento = frente->getValor();
    delete aux;
}

template<typename T>
void Fila<T>::print(){
    frente = frente->getProx();
    while(frente != NULL){
        cout << frente->getValor() << endl;
        frente = frente->getProx();
    }
}

//Inicio Movimento
template<typename T1,typename T2>
Movimento<T1,T2>::Movimento(pair<T1,T2> posicao){ this->posicao = posicao; }

template<typename T1,typename T2>
void Movimento<T1,T2>::insereMovimentos(pair<T1,T2> posicao, T2 x, T2 y){
    pair<T1,T2> chave;

    chave.first = posicao.first + x;
    chave.second = posicao.second + y;

    movimentos.push_back(chave);
}

template<typename T1,typename T2>
void Movimento<T1,T2>::verificaMovimentos(){
    vector<pair<T1,T2>> removerPosicao;

    for(unsigned int i = 0; i < movimentos.size();i++){
        if(movimentos[i].first >= 'a' && movimentos[i].first <= 'h' && movimentos[i].second > 0 && movimentos[i].second < 9 ){}
        else{ 
            removerPosicao.push_back(movimentos[i]);
        }
    }

    for(unsigned int i = 0; i < removerPosicao.size();i++){
        int posicao = -1;
        for(unsigned int j = 0; j < movimentos.size();j++){
            if(movimentos[j] == removerPosicao[i]){
                posicao = j;
                j = movimentos.size();
            }
        }
        movimentos.erase(movimentos.begin() + posicao);
    }
}

template<typename T1,typename T2>
void Movimento<T1,T2>::listarMovimentos(){

    insereMovimentos(posicao,2,-1);
    insereMovimentos(posicao,2,1);
    insereMovimentos(posicao,-2,-1);
    insereMovimentos(posicao,-2,1);
    insereMovimentos(posicao,1,-2);
    insereMovimentos(posicao,1,2);
    insereMovimentos(posicao,-1,-2);
    insereMovimentos(posicao,-1,2);

    verificaMovimentos();
}

template<typename T1,typename T2>
int Movimento<T1,T2>::converterPosicaoParaInteiro(pair<T1,T2> posicao){
    int soma;

    if(posicao.first == 'a'){ soma = posicao.second; }
    else if(posicao.first == 'b'){ soma = 8 + posicao.second; }
    else if(posicao.first == 'c'){ soma = 16 + posicao.second; }
    else if(posicao.first == 'd'){ soma = 24 + posicao.second; }
    else if(posicao.first == 'e'){ soma = 32 + posicao.second; }
    else if(posicao.first == 'f'){ soma = 40 + posicao.second; }
    else if(posicao.first == 'g'){ soma = 48 + posicao.second; }
    else if(posicao.first == 'h'){ soma = 56 + posicao.second; }
    
    return soma;
}

template<typename T1,typename T2>
pair<T1,T2> Movimento<T1,T2>::converterPosicaoParaPar(T2 posicao){
    pair<T1,T2> posicaoPar;

    if(posicao < 9){ 
        posicaoPar.first = 'a';
        posicaoPar.second = posicao;
    }
    else if(posicao > 8 && posicao < 17){ 
        posicaoPar.first = 'b';
        posicaoPar.second = posicao - 8;
    }
    else if(posicao > 16 && posicao < 25){ 
        posicaoPar.first = 'c';
        posicaoPar.second = posicao - 16;
    }
    else if(posicao > 24 && posicao < 33){ 
        posicaoPar.first = 'd';
        posicaoPar.second = posicao - 24;
    }
    else if(posicao > 32 && posicao < 41){ 
        posicaoPar.first = 'e';
        posicaoPar.second = posicao - 32;
    }
    else if(posicao > 40 && posicao < 49){ 
        posicaoPar.first = 'f';
        posicaoPar.second = posicao - 40;
    }
    else if(posicao > 48 && posicao < 57){ 
        posicaoPar.first = 'g';
        posicaoPar.second = posicao - 48;
    }
    else if(posicao > 56 && posicao < 65){ 
        posicaoPar.first = 'h';
        posicaoPar.second = posicao - 56;
    }

    return posicaoPar;
}

template<typename T1,typename T2>
vector<T2> Movimento<T1,T2>::converterListaPosicaoParaInteiro(){
    vector<T2> listaConvertida;
    int soma; 

    for(unsigned int i = 0;i < movimentos.size();i++){
        soma = converterPosicaoParaInteiro(movimentos[i]);
        listaConvertida.push_back(soma);        
    }

    return listaConvertida;
}

template<typename T1,typename T2>
void Movimento<T1,T2>::print(){
    for(unsigned int i = 0;i < movimentos.size();i++){
        cout << movimentos[i].first << movimentos[i].second << endl;
    }
}

// Início Grafo
template<typename T>
Grafo<T>::Grafo(T ordem){ inicializar(ordem); }

template<typename T>
void Grafo<T>::inicializar(T ordem){
    this->ordem = ordem;
    posicoes = new Lista<T>[ordem + 1];
}

template<typename T>
void Grafo<T>::insereAresta(T vertice1, T vertice2){
    posicoes[vertice1].insere(vertice2);
    posicoes[vertice2].insere(vertice1);
    tamanho++;
}

template<typename T>
T Grafo<T>::BFS (T inicioVertice, T fimVertice){
    T vertice = inicioVertice;
    bool found = false;
    vector<int> cor(ordem + 1);
    vector<int> distancia(ordem + 1);
    vector<T> predecessor(ordem + 1);
    
    for(int i = 0; i < ordem + 1; i++){
        cor[i] = BRANCO;
        distancia[i] = numeric_limits<int>::max();
        predecessor[i] = -1; 
    }

    cor[vertice] = CINZA;
    distancia[vertice] = -1;
    predecessor[vertice] = -1;

    Fila<T> fila;
    fila.enfileira(vertice);
    
    while(!fila.vazia() && !found){
        vertice = fila.getFrente();
        fila.desenfileira(vertice); 
        No<T>* posicao = posicoes[vertice].getPrim()->getProx();

        while(posicao != NULL){
            if(cor[posicao->getValor()] == BRANCO){
                cor[posicao->getValor()] = CINZA;
                distancia[posicao->getValor()] = distancia[vertice] + 1;
                predecessor[posicao->getValor()] = vertice;
                fila.enfileira(posicao->getValor());
            }

            if(posicao->getValor() == fimVertice){
                found = true;
            }

            posicao = posicao->getProx();
        }
        cor[vertice] = PRETO;
    }
    
    return distancia[fimVertice];
}

template<typename T>
void Grafo<T>::print(){
    for(int i = 0;i < ordem+1;i++){
        cout << "v[" << i << "] = ";
        posicoes[i].print();
    }
}

//Inicio Chess
template<typename T1,typename T2>
Chess<T1,T2>::Chess(pair<T1,T2> rei, pair<T1,T2> cavalo1, pair<T1,T2> cavalo2, pair<T1,T2> cavalo3, pair<T1,T2> cavalo4){
    this->rei = rei;
    this->cavalo1 = cavalo1;
    this->cavalo2 = cavalo2;    
    this->cavalo3 = cavalo3;
    this->cavalo4 = cavalo4;
}

template<typename T1,typename T2>
int Chess<T1,T2>::maiorNumero(vector<T2> vetor) {
  int maior = vetor[0];
  for(unsigned int i = 1; i < vetor.size(); i++) {
    if (vetor[i] > maior) {
      maior = vetor[i];
    }
  }
  return maior;
}

template<typename T1,typename T2>
vector<T2> Chess<T1,T2>::countingSort(vector<T2> A,vector<T2> B, int k){
    vector<T2> C(k);

    for(int i = 0; i < k; i++){
        C[i] = 0;
    }

    for(unsigned int j = 0; j < A.size();j++){
        C[A[j]] = C[A[j]] + 1;
    }

    for(int i = 1;i < k;i++){
        C[i] = C[i] + C[i - 1];
    }

    for(int j = A.size()-1; j >= 0;j--){
        B[C[A[j]]] = A[j];
        C[A[j]] = C[A[j]] - 1;
    }

    return B;
}

template<typename T1,typename T2>
vector<T2> Chess<T1,T2>::inserirAdjacentes(){
    Movimento<T1,T2> *movimento = new Movimento<T1,T2>(rei);
    int posicaoRei = movimento->converterPosicaoParaInteiro(rei);
    int posicaoCavalo1 = movimento->converterPosicaoParaInteiro(cavalo1);
    int posicaoCavalo2 = movimento->converterPosicaoParaInteiro(cavalo2);
    int posicaoCavalo3 = movimento->converterPosicaoParaInteiro(cavalo3);
    int posicaoCavalo4 = movimento->converterPosicaoParaInteiro(cavalo4);
    
    bool cavaloEncontrado = false;
    vector<bool> visited(65);
    vector<int> numeroCavalo;

    visited[posicaoRei] = true;
    Fila<T2> fila;
    fila.enfileira(posicaoRei);

    while(!fila.vazia()){
        posicaoRei = fila.getFrente();
        fila.desenfileira(posicaoRei);
        pair<T1,T2> posicao = movimento->converterPosicaoParaPar(posicaoRei);

        delete movimento;
        movimento = new Movimento<T1,T2>(posicao);
        movimento->listarMovimentos();

        vector<T2> listaMovimentos = movimento->converterListaPosicaoParaInteiro();
        vector<T2> listaOrdenadaDeMovimentos(listaMovimentos.size() + 1);
        listaOrdenadaDeMovimentos = countingSort(listaMovimentos,listaOrdenadaDeMovimentos,maiorNumero(listaMovimentos)+1);
        
        for(unsigned int i = 1; i < listaOrdenadaDeMovimentos.size();i++){
            T2 elemento = listaOrdenadaDeMovimentos[i];    
            grafo->insereAresta(posicaoRei,elemento);
            if((elemento == posicaoCavalo1 || elemento == posicaoCavalo2 || elemento == posicaoCavalo3 || elemento == posicaoCavalo4) && !visited[elemento]){
                numeroCavalo.push_back(elemento);
                visited[elemento] = true;
                cavaloEncontrado = true;
            }
            else if(!visited[elemento] && !cavaloEncontrado && (elemento != posicaoCavalo1 || elemento != posicaoCavalo2 || elemento != posicaoCavalo3 || elemento != posicaoCavalo4)){
                visited[elemento] = true;
                fila.enfileira(elemento);             
            }
            else if(!visited[elemento] && cavaloEncontrado && (elemento != posicaoCavalo1 || elemento != posicaoCavalo2 || elemento != posicaoCavalo3 || elemento != posicaoCavalo4)){
                visited[elemento] = true;
            }

        }
    }
    return numeroCavalo;
}

template<typename T1,typename T2>
void Chess<T1,T2>::minimoMovimento(){
    Movimento<T1,T2> converter(rei);
    vector<T2> numeroCavalo = inserirAdjacentes();
    int posicaoRei = converter.converterPosicaoParaInteiro(rei);
    int posicaoCavalo = converter.converterPosicaoParaInteiro(converter.converterPosicaoParaPar(numeroCavalo[0]));
        
    int menor = grafo->BFS(posicaoRei,posicaoCavalo);
    int contador = 1;

    for(unsigned int i = 1;i < numeroCavalo.size();i++){
        posicaoRei = converter.converterPosicaoParaInteiro(rei);
        posicaoCavalo = converter.converterPosicaoParaInteiro(converter.converterPosicaoParaPar(numeroCavalo[i]));
        
        if ( menor > grafo->BFS(posicaoRei,posicaoCavalo)){
            menor = grafo->BFS(posicaoRei,posicaoCavalo);
        }
        else if(menor == grafo->BFS(posicaoRei,posicaoCavalo)){
            contador += 1;
        }
    }

    for(int i = 0; i < contador;i++){
        if(i == contador - 1) { cout << menor <<  endl; }
        else { cout << menor << " "; }
    }
}