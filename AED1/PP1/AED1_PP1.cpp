//Kid Mendes de Oliveira Neto - 1615310011
//Lorene da Silva Marques - 1615310013

#include <iostream>

using namespace std;

typedef int Posicao;
typedef string Chave;

template <typename T>
class Ni{
private:
    T linha;        //Linha armazenada na classe Ni
public:
    Ni(){}
    void setLinha(T);
    T getLinha();
    void print();
};

template <typename T>
class Lista{
private:
    Ni<T> *ni;
    int TAM;    //Tamanho total da lista
    int n;      //Tamanho corrente da Lista
    bool posicaoValida(Posicao);    //Verifica se a posição existe
    bool vazia();                   //Verifica se a lista está vazia
public:
    Lista (){ Lista(100); }
    Lista(int);
    void insere(Ni<T>);
    Ni<T>* busca(Chave);
    void remove(Posicao, Ni<T>&);
    int buscaIndice(Chave);         //Retorna o índice do elemento procurado na Lista
    Ni<T>* buscaElemento(int);      //Retorna o elemento procurado na Lista
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

template<typename T>
class Pilha{
private:
    No<T>* topo;
    No<T>* fundo;
public:
    Pilha();
    void empilhar(T);
    void desempilhar(T);
    bool vazia();
};

template<typename T>
bool verificarPrint(Ni<T>*);    //Verificar se o comando PRINT é valido

template<typename T>
void executarPrint(Ni<T>*);    //Imprime o valor na tela

template <typename T>
Pilha<T> verificarFuncao(int,Pilha<T>,Lista<string>);   //Busca e executa a Função desejada

int main() {

    Ni<string> ni;              //Linha do programa Ni
    string entrada;             //Ler cada linha do código Ni
    Lista<string> interpretador(120);       //Interpretador Ni
    Pilha<int> pilha;           //Guarda os indices das chamadas de funções
    int indice;                 //Posição no interpretador

    do{
        getline(cin,entrada);
        ni.setLinha(entrada);
        interpretador.insere(ni);
    }while(entrada != "~");     //Final da entrada do interpretador Ni

    Ni<string>* linhaZ = interpretador.busca("Z :");    //Procura a existência da função Z
    indice = interpretador.buscaIndice("Z :") + 1;      //Retorna o índice após a função Z

    //Se existir a função Z entrará nesta condição
    if(linhaZ != NULL){
        //Ao encontrar uma linha em branco, o loop irá terminar
        do{
            //Linha correspondente ao indice utilizando o indice no parâmetro
            Ni<string>* linha = interpretador.buscaElemento(indice);

            //Se for o método PRINT
            if(verificarPrint(linha)){
                executarPrint(linha);
            }

                //Se for  uma chamada de função
            else if(linha->getLinha()[4] >= 'A' && linha->getLinha()[4] < 'Z'){
                char &nomeFuncao= linha->getLinha()[4];
                string  nomeFuncaoStr= &nomeFuncao;

                //Empilha a próxima linha de Z a ser executada
                pilha.empilhar(indice + 1);
                //Busca o indice da chamada de função
                int indiceFuncao = interpretador.buscaIndice(nomeFuncaoStr+" :") + 1;
                while(pilha.vazia() == 0){  //Loop enquanto a lista não está vazia
                    pilha = verificarFuncao(indiceFuncao,pilha,interpretador);
                    pilha.desempilhar(indiceFuncao);
                }
            }
            indice++;       //Incrementa o índice
        }while(interpretador.buscaElemento(indice) != NULL);
    }

    return 0;
}

template <typename T>
bool verificarPrint(Ni<T>* linha){  //Verificar se o comando PRINT é valido
    if(linha->getLinha()[4] == 'P' && linha->getLinha()[5] == 'R' && linha->getLinha()[6] == 'I' && linha->getLinha()[7] == 'N' && linha->getLinha()[8] == 'T'){
        return true;
    }
    else{
        return false;
    }
}

template <typename T>
void executarPrint(Ni<T>* linha){   //Imprime o valor na tela
    for(int i = 0; i < signed(sizeof(linha)+4);i++){
        if(i == 9 && linha->getLinha()[i] == ' ') {
            cout << linha->getLinha()[i+1] << linha->getLinha()[i+2];
            cout << " ";
        }
    }
}

template <typename T>
//Busca e executa a Função desejada
Pilha<T> verificarFuncao(int indice,Pilha<T> pilha,Lista<string> interpretador){
    pilha.empilhar(indice);     //Empilha o indice onde começa a função

    //Ao encontrar uma linha em branco, o loop irá terminar
    do {
        //Se for o método PRINT
        if (verificarPrint(interpretador.buscaElemento(indice))) {
            executarPrint(interpretador.buscaElemento(indice));
        }
            //Se for uma chamada de função
        else if (interpretador.buscaElemento(indice)->getLinha()[4] >= 'A' &&
                 interpretador.buscaElemento(indice)->getLinha()[4] < 'Z') {
            char &nomeFuncao = interpretador.buscaElemento(indice)->getLinha()[4];
            string nomeFuncaoStr = &nomeFuncao;
            //Empilha a proxima linha da funçao a ser executada
            pilha.empilhar(indice);

            //Busca o índice da chamada de função
            int indiceFuncao = interpretador.buscaIndice(nomeFuncaoStr+" :") + 1;
            pilha = verificarFuncao(indiceFuncao,pilha,interpretador);
            pilha.desempilhar(indiceFuncao);
        }
        indice++;
    }while (interpretador.buscaElemento(indice) != NULL);
    pilha.desempilhar(indice);
    return pilha;
}

template <typename T>
Lista<T>::Lista(int tam){
    n = 0;
    TAM = tam;
    ni = new Ni<T>[TAM];
}

template <typename T>
void Ni<T>::setLinha(T linha) {
    this->linha = linha;
}

template <typename T>
T Ni<T>::getLinha() {
    return linha;
}

template <typename T>
void Ni<T>::print() {
    cout << linha;
}

template <typename T>
void Lista<T>::insere(Ni<T> x) {
    if(n < TAM){
        ni[n] = x;
        n++;
    }
    else{
        cout << "Lista cheia" << endl;
    }
}

template <typename T>
Ni<T>* Lista<T>::busca(Chave linha) {
    int i = n;
    while(linha != ni[i].getLinha()){
        i--;
    }

    if(i >= 0){
        return &ni[i];
    }
    else{
        return NULL;
    }
}

template <typename T>
int Lista<T>::buscaIndice(Chave linha) {        //Busca o indice na Lista pela linha
    int i = n;
    while(linha != ni[i].getLinha()){
        i--;
    }

    if(i > 0){
        return i;
    }
    else{
        return 0;
    }
}

template <typename T>
Ni<T>* Lista<T>::buscaElemento(int indice) {       //Busca o elemento na Lista pelo indice
    int i = n;
    while(ni[indice].getLinha() != ni[i].getLinha()){
        i--;
    }
    if(ni[indice].getLinha() == ""){
        return NULL;
    }
    if(i >= 0){
        return &ni[i];
    }
    else{
        return 0;
    }
}

template <typename T>
bool Lista<T>::posicaoValida(Posicao posicao) {
    return 1 <= posicao && posicao <= n;
}

template <typename T>
bool Lista<T>::vazia() {
    return n == 0;
}

template <typename T>
void Lista<T>::remove(Posicao posicao, Ni<T> &nii) {

    if(!vazia() && posicaoValida(posicao)){
        nii = ni[posicao];
        for(int i = posicao;i < n; i++){
            ni[i] = ni[i + 1];
        }
        n--;
    }
    else{
        cout << "Lista vazia ou posicao invalida" << endl;
    }
}

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

template<typename T>
Pilha<T>::Pilha() {
    fundo = new No<T>();
    fundo->setProx(NULL);
    topo = fundo;
}

template<typename T>
void Pilha<T>::empilhar(T valor) {
    No<T>* aux = new No<T>();
    topo->setValor(valor);
    aux->setProx(topo);
    topo = aux;
}

template<typename T>
void Pilha<T>::desempilhar(T valor) {
    No<T>* aux = topo;
    topo = topo->getProx();
    topo->setValor(valor);
    delete aux;
}

template <typename T>
bool Pilha<T>::vazia() {
    if(topo == fundo){
        return true;
    }
    else{
        return false;
    }
}