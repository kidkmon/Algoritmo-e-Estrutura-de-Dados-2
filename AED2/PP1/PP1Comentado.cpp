//Eduardo Maia Freire - 1615310003
//Kid Mendes de Oliveira Neto - 1615310011
//Lorene da Silva Marques - 1615310013

#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>

#define BRANCO 0 //Não foi visitado
#define CINZA 1     //Está dentro da fila 
#define PRETO 2     //Foi visitdado e saiu da fila

using namespace std;

template<typename T>
class No{                               //Classe Nó utilizada nas classes de Fila e Lista
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
class Lista{                        //Lista dinâmica usada apenas na lista de adjacência(localizada na Classe Grafo)
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
class Fila{                     //Fila utilizada na função de busca em largura(BFS) localizada na classe Grafo e é também utilizada na função de inserirAdjacentes(localizada na classe Chess)
private:                       //Ambas as funções(BFS e inserirAjdacentes) têm como mesmo objetivo enfileirar posições inteiras para armazenas posições que o rei poderá visitar.
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
class Movimento{            //Classe Movimento para poder ter uma lista com as posições que o rei poderá se movimentar.
private:
    pair<T1,T2> posicao;    // Posição será dada em pair pois terá melhor controle para saber as posições possiveis a se movimentar
    vector<pair<T1,T2>> movimentos;     //Vetor que irá armazenar as posições possiveis para se movimentar
public:
    Movimento() {}
    Movimento(pair<T1,T2>);             //Construtor que irá ter como parâmetro a posicao que desejamos saber quais são as posições possiveis dada determinada posição no parâmetro
    void insereMovimentos(pair<T1,T2>,T2,T2);   //Função que irá fazer as mudanças das posições de acordo com o parâmetro dado e irá inserir as posições no vetor de movimentos.
    void verificaMovimentos();          //Função que vai validar se a posição dada na de insereMovimentos() é uma posição do tabuleiro.
    void listarMovimentos();            //Função que aplica o algoritmo de todas as formas possíveis de movimento de um cavalo
    int converterPosicaoParaInteiro(pair<T1,T2>);   //Função que irá conveter uma posição do tipo pair para tipo inteiro
    pair<T1,T2> converterPosicaoParaPar(T2);        //Função que irá converter uma posição do tipo inteiro para o tipo pair.
    vector<T2> converterListaPosicaoParaInteiro();  //Função que irá converter o vetor de movimentos(que é um vetor de pair) para um vetor de inteiro já com os elementos em inteiro
    void print();
};

template<typename T>
class Grafo{
private:
    Lista<T> *posicoes;     //Lista de adjacência que irá armazenar os adjacentes de cada vertice e será uma lista de lista
    int ordem = 0;          //Ordem é a quantidade de vertices em um grafo.
    int tamanho;
public:
    Grafo(T);               //Construtor do Grafo que irá receber como parâmetro a ordem do grafo
    void inicializar(T);    //Função chamada pelo construtor 
    void insereAresta(T, T);    //Função que irá inserir uma aresta entre dois vertices dado no parâmetro. Ex: insereAresta(1,2) => posicoes[1] = 2 e posicoes[2] = 1. Isso se deve porque os elementos dentro de uma posicao significa que sao adjacentes à ele.
    T BFS(T,T);             //Busca em largura, que irá pegar o menor caminho entre dois vertices dado no parâmetro
    void print();
};

template<typename T1,typename T2>
class Chess{        //Classe principal 
private:
    Grafo<T2> *grafo = new Grafo<T2>(64);   //Declarar o Grafo com ordem de 64, devido a ser 64 posições em um tabuleiro de xadrez.
    pair<T1,T2> rei, cavalo1, cavalo2, cavalo3, cavalo4;    //Pair que irá pegar as posições do rei e de todos os cavalos no construtor.
public:
    Chess(pair<T1,T2>,pair<T1,T2>,pair<T1,T2>,pair<T1,T2>,pair<T1,T2>);     //Construtor que terá como parâmetro as posicções do rei e de todos os cavalos.
    int maiorNumero(vector<T2>);                                            //Função que irá pegar o maior numero em um vetor qualquer. Ex: v=[1,2,3,4,6,7,50] , o vetor v tem como maior numero, o 50. 
    vector<T2> countingSort(vector<T2>,vector<T2>,int);                     //Algortimo que irá ordenar os elementos de um vetor em ordem crescente. Complexidade O(n + k), sendo n = tamanho do vetor e k = maior numero de um vetor, respectivamente.
    vector<T2> inserirAdjacentes();         //Função que irá adicionar as posições adjacentes de determinada posição  e irá retornar um vetor de cavalos encontrados com suas respectivas posicoes dentro deste vetor.
    void minimoMovimento();                 //Função que irá fazer uma busca em largura(BFS) e irá mostrar na tela a menor distância percorrida ate achar um cavalo
};

int main(){

    string entrada,numeroEntrada;       //numeroEntrada = quantas entradas ele irá receber

    getline(cin, numeroEntrada);
    
    for(int i = 0; i < atoi(&numeroEntrada[0]);i++){    //atoi = transformar o elemento do tipo char em inteiro
        getline(cin, entrada);
    
        pair<char,int> rei,cavalo1,cavalo2,cavalo3,cavalo4; //    01 34 67 910 1213
                                                            //Ex: a1 c7 e8 h1 e4
        cavalo1 = make_pair(entrada[0],atoi(&entrada[1]));  //Criar um pair com os valores dado na string seguindo a ordem
        cavalo2 = make_pair(entrada[3],atoi(&entrada[4]));
        cavalo3 = make_pair(entrada[6],atoi(&entrada[7]));
        cavalo4 = make_pair(entrada[9],atoi(&entrada[10]));
        rei = make_pair(entrada[12],atoi(&entrada[13]));

        Chess<char,int> jogar(rei,cavalo1,cavalo2,cavalo3,cavalo4);

        jogar.minimoMovimento();
    }

    return 0;
}
//Estudar a implementação aqui abaixo

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
Movimento<T1,T2>::Movimento(pair<T1,T2> posicao){ this->posicao = posicao; }  //Construtor que irá ter como parâmetro a posicao que desejamos saber quais são as posições possiveis dada determinada posição no parâmetro

template<typename T1,typename T2>
void Movimento<T1,T2>::insereMovimentos(pair<T1,T2> posicao, T2 x, T2 y){ //Função que irá fazer as mudanças das posições de acordo com o parâmetro dado e irá inserir as posições no vetor de movimentos.
    pair<T1,T2> chave;

    chave.first = posicao.first + x;
    chave.second = posicao.second + y;

    movimentos.push_back(chave); //push_back = adicionar elemento em um vector
}

template<typename T1,typename T2>
void Movimento<T1,T2>::verificaMovimentos(){ //Função que vai validar se a posição dada na de insereMovimentos() é uma posição do tabuleiro.
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
void Movimento<T1,T2>::listarMovimentos(){ //Função que aplica o algoritmo de todas as formas possíveis de movimento de um cavalo

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
int Movimento<T1,T2>::converterPosicaoParaInteiro(pair<T1,T2> posicao){ //Função que irá conveter uma posição do tipo pair para tipo inteiro
    int soma;   //Ex: a1 = 1,a2 = 2,...h8 = 64

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
pair<T1,T2> Movimento<T1,T2>::converterPosicaoParaPar(T2 posicao){ //Função que irá converter uma posição do tipo inteiro para o tipo pair.
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
vector<T2> Movimento<T1,T2>::converterListaPosicaoParaInteiro(){  //Função que irá converter o vetor de movimentos(que é um vetor de pair) para um vetor de inteiro já com os elementos em inteiro
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
Grafo<T>::Grafo(T ordem){ inicializar(ordem); }   //Construtor do Grafo que irá receber como parâmetro a ordem do grafo

template<typename T>
void Grafo<T>::inicializar(T ordem){ //Função chamada pelo construtor 
    this->ordem = ordem;
    posicoes = new Lista<T>[ordem + 1]; //Lista de Lista de tamanho = ordem + 1
}

template<typename T>  //Função que irá inserir uma aresta entre dois vertices dado no parâmetro. Ex: insereAresta(1,2) => posicoes[1] = 2 e posicoes[2] = 1. Isso se deve porque os elementos dentro de uma posicao significa que sao adjacentes à ele.
void Grafo<T>::insereAresta(T vertice1, T vertice2){
    posicoes[vertice1].insere(vertice2);
    posicoes[vertice2].insere(vertice1);
    tamanho++;
}

template<typename T>
T Grafo<T>::BFS (T inicioVertice, T fimVertice){ //Busca em largura, que irá pegar o menor caminho entre dois vertices dado no parâmetro
    T vertice = inicioVertice; 
    bool found = false;
    vector<int> cor(ordem + 1);
    vector<int> distancia(ordem + 1);
    vector<T> predecessor(ordem + 1);
    
    for(int i = 0; i < ordem + 1; i++){     //Irá deixar todos os elementos com cor branca, distancia infinita e predecessor = -1
        cor[i] = BRANCO;
        distancia[i] = numeric_limits<int>::max();  //Maior numero possivel de inteiro (infinito)
        predecessor[i] = -1; 
    }

    cor[vertice] = CINZA;
    distancia[vertice] = -1;
    predecessor[vertice] = -1;

    Fila<T> fila;
    fila.enfileira(vertice);
    
    while(!fila.vazia() && !found){     //Loop irá continuar até a fila estiver vazia ou a condição de found se torne true
        vertice = fila.getFrente();     //Irá pegar a frente da fila
        fila.desenfileira(vertice);     //Desenfileirar o elemento
        No<T>* posicao = posicoes[vertice].getPrim()->getProx();    //Irá pegar o primeiro elemento da lista, para poder percorrer essa lista começando do inicio

        while(posicao != NULL){     //Loop que irá terminar até o ultimo elemento da lista, chegando no ultimo elemento da lista o proximo dele será Null
            if(cor[posicao->getValor()] == BRANCO){     //Se o elemento da lista ainda nao foi visitado, ele entrará nessa condicao
                cor[posicao->getValor()] = CINZA;       //Troca o valor para visitado
                distancia[posicao->getValor()] = distancia[vertice] + 1;    //Pega a distancia e incrementa 1
                predecessor[posicao->getValor()] = vertice; // O predecessor do elemento será o vertice(que é dado na linha 399)
                fila.enfileira(posicao->getValor());    //Enfileira esse elemento
            }

            if(posicao->getValor() == fimVertice){  //Se o elemento for igual ao fim do vertice, ele ira transformar found em true
                found = true;
            }

            posicao = posicao->getProx();   //Irá pegar o proximo elemento da lista
        }
        cor[vertice] = PRETO; //Depois de sair do loop, ele ira transformar a cor dele em preto, pois ja foi desenfileirado
    }
    
    return distancia[fimVertice];   //Irá retornar a distancia do fimVertice pois ela dará a menor distancia encontrada na BFS
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
Chess<T1,T2>::Chess(pair<T1,T2> rei, pair<T1,T2> cavalo1, pair<T1,T2> cavalo2, pair<T1,T2> cavalo3, pair<T1,T2> cavalo4){ //Construtor que terá como parâmetro as posicções do rei e de todos os cavalos.
    this->rei = rei;
    this->cavalo1 = cavalo1;
    this->cavalo2 = cavalo2;    
    this->cavalo3 = cavalo3;
    this->cavalo4 = cavalo4;
}

template<typename T1,typename T2>
int Chess<T1,T2>::maiorNumero(vector<T2> vetor) {  //Função que irá pegar o maior numero em um vetor qualquer. Ex: v=[1,2,3,4,6,7,50] , o vetor v tem como maior numero, o 50. 
  int maior = vetor[0];
  for(unsigned int i = 1; i < vetor.size(); i++) {
    if (vetor[i] > maior) {
      maior = vetor[i];
    }
  }
  return maior;
}

template<typename T1,typename T2> //Algortimo que irá ordenar os elementos de um vetor em ordem crescente. Complexidade O(n + k), sendo n = tamanho do vetor e k = maior numero de um vetor, respectivamente.
vector<T2> Chess<T1,T2>::countingSort(vector<T2> A,vector<T2> B, int k){ //Estudar slide de countingSort do professor
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
vector<T2> Chess<T1,T2>::inserirAdjacentes(){  //Função que irá adicionar as posições adjacentes de determinada posição  e irá retornar um vetor de cavalos encontrados com suas respectivas posicoes dentro deste vetor.
    Movimento<T1,T2> *movimento = new Movimento<T1,T2>(rei);    // Declarar a classe Movimento como ponteiro, para poder deletar o construtor dele e inserir um novo construtor
    int posicaoRei = movimento->converterPosicaoParaInteiro(rei);   //Transformar a posicao do rei em inteiro
    int posicaoCavalo1 = movimento->converterPosicaoParaInteiro(cavalo1);   //Transformar a posicao do cavalo em inteiro
    int posicaoCavalo2 = movimento->converterPosicaoParaInteiro(cavalo2);   //Transformar a posicao do cavalo em inteiro
    int posicaoCavalo3 = movimento->converterPosicaoParaInteiro(cavalo3);   //Transformar a posicao do cavalo em inteiro
    int posicaoCavalo4 = movimento->converterPosicaoParaInteiro(cavalo4);   //Transformar a posicao do cavalo em inteiro
    
    bool cavaloEncontrado = false;  //Condicao booleana se um cavalo ja foi encontrado
    vector<bool> visited(65);       //Vetor booleano se uma posicao ja foi visitada
    vector<int> numeroCavalo;       //Vetor que irá armazenas quais cavalos foram encontrados e irá adicionar a posicao deles neste vetor

    visited[posicaoRei] = true;     //Posicao do rei ja visitada
    Fila<T2> fila;
    fila.enfileira(posicaoRei);  //Enfileira posicao do rei

    while(!fila.vazia()){   //Loop que irá terminar somente quando a lista for vazia
        posicaoRei = fila.getFrente();  //PEgar a frente da fila,
        fila.desenfileira(posicaoRei);
        pair<T1,T2> posicao = movimento->converterPosicaoParaPar(posicaoRei);   //A posicao será convertida de inteiro para pair para poder pegar as posicoes possiveis para ele se movimentar

        delete movimento;   //Deletar a instacia antiga do movimento
        movimento = new Movimento<T1,T2>(posicao);  //Nova instancia com uma nova posicao no construtor de movimento
        movimento->listarMovimentos();      //Pegar as posicoes possiveis da posicao dada no construtor

        vector<T2> listaMovimentos = movimento->converterListaPosicaoParaInteiro(); //Vetor de inteiro que ira pegar as posicoes possiveis ja transformadas para inteiro
        vector<T2> listaOrdenadaDeMovimentos(listaMovimentos.size() + 1);   //Vetor de inteiro que será o vetor de listaMovimentos ordenado
        listaOrdenadaDeMovimentos = countingSort(listaMovimentos,listaOrdenadaDeMovimentos,maiorNumero(listaMovimentos)+1); //Chmada da funcao de ordenacao de vetor
        
        for(unsigned int i = 1; i < listaOrdenadaDeMovimentos.size();i++){ //Loop para percorrer todos os elementos da listaOrdenadaMovimentos
            T2 elemento = listaOrdenadaDeMovimentos[i];    //Variavel chamada de elemento que é a mesma coisa que  listaOrdenadaDeMovimentos[i]
            grafo->insereAresta(posicaoRei,elemento);       //Inserir as arestas da posicaoREi com as posicoes possiveis que foi dada anteriormente
            if((elemento == posicaoCavalo1 || elemento == posicaoCavalo2 || elemento == posicaoCavalo3 || elemento == posicaoCavalo4) && !visited[elemento]){//Se o elemento for um cavalo
                numeroCavalo.push_back(elemento); //Adicioanr no vetor de numeroCavalo 
                visited[elemento] = true;   //Transformar em true pois ja foi visitado
                cavaloEncontrado = true; //Cavalo encontrado para true
            }
            else if(!visited[elemento] && !cavaloEncontrado && (elemento != posicaoCavalo1 || elemento != posicaoCavalo2 || elemento != posicaoCavalo3 || elemento != posicaoCavalo4)){ //Se o elemento nao for um cavalo e nao foi visitado e o cavalo nao foi encontrado
                visited[elemento] = true; //Visitado[elemento] = true
                fila.enfileira(elemento);             //Irá enfileirar para poder listar os movimentos possiveis
            }
            else if(!visited[elemento] && cavaloEncontrado && (elemento != posicaoCavalo1 || elemento != posicaoCavalo2 || elemento != posicaoCavalo3 || elemento != posicaoCavalo4)){//Se o elemento nao for um cavalo e nao foi visitado e o cavalo foi encontrado
                visited[elemento] = true; //So troca pra true a posicao visitada
            }

        }
    }
    return numeroCavalo; //retornar o vetor de numeroCavalo
}

template<typename T1,typename T2>
void Chess<T1,T2>::minimoMovimento(){ //Função que irá fazer uma busca em largura(BFS) e irá mostrar na tela a menor distância percorrida ate achar um cavalo
    Movimento<T1,T2> converter(rei);    //Declaracao da classe MOvimento so para poder transformar pair em inteiro
    vector<T2> numeroCavalo = inserirAdjacentes();  //Irá pegar o vetor NumeroCavalo da funcao inserirAjacente()
    int posicaoRei = converter.converterPosicaoParaInteiro(rei);    //Converter para inteiro posicao do rei
    int posicaoCavalo = converter.converterPosicaoParaInteiro(converter.converterPosicaoParaPar(numeroCavalo[0]));  //Converter para inteiro posicao do primeiro elemento do vetor numeroCavalo
        
    int menor = grafo->BFS(posicaoRei,posicaoCavalo); //Faz a bfs do primeiro elemento do vetor numeroCavalo com a posicao do rei
    int contador = 1; //contador 1 pois já tem uma posicao de cavalo no vetor

    for(unsigned int i = 1;i < numeroCavalo.size();i++){    //Loop que irá verificar se tem uma distancia menor do que a numeroCavalo[0] e se tem uma distancia com o mesmo numero de outro cavalo
        posicaoRei = converter.converterPosicaoParaInteiro(rei);
        posicaoCavalo = converter.converterPosicaoParaInteiro(converter.converterPosicaoParaPar(numeroCavalo[i]));
        
        if ( menor > grafo->BFS(posicaoRei,posicaoCavalo)){  //Se for menor, ele sera o menor a bfs
            menor = grafo->BFS(posicaoRei,posicaoCavalo);
        }
        else if(menor == grafo->BFS(posicaoRei,posicaoCavalo)){ //Incrementa se a distancia for a mesma
            contador += 1;
        }
    }

    for(int i = 0; i < contador;i++){ //Mostra na tela a quantidade de vezes do menor
        if(i == contador - 1) { cout << menor <<  endl; }
        else { cout << menor << " "; }
    }
}