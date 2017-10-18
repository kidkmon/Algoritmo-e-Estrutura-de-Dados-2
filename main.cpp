#include <iostream>
#include <vector>
#include <utility>

#define BRANCO 0
#define CINZA 1
#define PRETO 2

using namespace std;

typedef int Vertice;
typedef int Cor;

template<typename T>
class Lista{
private:
    vector<T> lista;
public:
    Lista (){}
    vector<T> getLista();
    void insere(T);
    int busca(T);
    void remove(T);
    void print();
    void destroy();
};


class Movimento{
private:
    pair<char,int> posicao;
    Lista<pair<char,int>> movimentos;
public:
    Movimento(pair<char,int>);
    void insereMovimentos(pair<char,int>,int,int);
    void listarMovimentos(pair<char,int>);
    void verificaMovimentos();
    void print();
};

class Grafo{
private:
    Lista<int> *adjacentes;
    Movimento posicao;
    int ordem;
    int tamanho;
    void destroy();
public:
    Grafo(int);
    void setPosicao(Movimento);
    void inicializar(int);
    void insereAresta(Vertice, Vertice);
    void removeAresta(Vertice, Vertice);
    void print();
};

class Cavaleiros{
private:
    Grafo c1;
    Grafo c2;
    Grafo c3;
    Grafo c4;
public:
    Cavaleiros(Grafo c1, Grafo c2, Grafo c3, Grafo c4);
    

};

int main(){

    
    return 0;
}

// Início da Lista
template<typename T>
vector<T> Lista<T>::getLista(){
    return lista;
}

template<typename T>
void Lista<T>::destroy(){
    vector<T>().swap(lista);
}

template<typename T>
void Lista<T>::insere(T posicao){
    lista.push_back(posicao);
}

template<typename T>
int Lista<T>::busca(T posicao){
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

template<typename T>
void Lista<T>::remove(T posicao){
    int buscaPosicao = busca(posicao);
    if(buscaPosicao == -1){
        cout << "Lista vazia ou posicao invalida" << endl;
    }
    else{
        lista.erase(lista.begin()+ buscaPosicao);
    }
}

template<typename T>
void Lista<T>::print(){
    for(int i = 0; i < lista.size();i++){
        cout << lista[i] << " ";
    }
    cout << endl;
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
    adjacentes = new Lista<int>[ordem + 1];
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

//Movimento
Movimento::Movimento(pair<char,int> posicao){
    this->posicao = posicao;
}

void Movimento::setPosicao(Movimento posicao){
    this.posicao = posicao; 
}

void Movimento::insereMovimentos(pair<char,int> posicao, int x, int y){
    pair<char,int> chave;

    chave.first = posicao.first + x;
    chave.second = posicao.second + y;
    movimentos.insere(chave);

}

void Movimento::listarMovimentos(pair<char,int> posicao){

    insereMovimentos(posicao,2,-1);
    insereMovimentos(posicao,2,1);
    insereMovimentos(posicao,-2,-1);
    insereMovimentos(posicao,-2,1);
    insereMovimentos(posicao,1,-2);
    insereMovimentos(posicao,1,2);
    insereMovimentos(posicao,-1,-2);
    insereMovimentos(posicao,-1,2);

}

void Movimento::verificaMovimentos(){
    Lista<pair<char,int>> removerPosicao;

    for(int i = 0; i < movimentos.getLista().size();i++){
        if(movimentos.getLista()[i].first >= 'a' && movimentos.getLista()[i].first <= 'h' && movimentos.getLista()[i].second > 0 && movimentos.getLista()[i].second < 9 ){    }
        else{ 
            removerPosicao.insere(movimentos.getLista()[i]);
        }
    }

    for(int i = 0; i < removerPosicao.getLista().size();i++){
        movimentos.remove(removerPosicao.getLista()[i]);
    }
}

void Movimento::print(){
    verificaMovimentos();
    for(int i = 0;i < movimentos.getLista().size();i++){
        cout << movimentos.getLista()[i].first << movimentos.getLista()[i].second << endl;
    }
}

//BFS
//void Grafo::BFS (Grafo grafo, Vertice s){

//}