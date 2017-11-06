//Kid Mendes de Oliveira Neto 1615310011
//Lorene da Silva Marques 1615310013
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

template<typename T>
class No{
private:
    T valor;        //Conteúdo do nó
    No<T>* esq;     //Nó esquerdo
    No<T>* dir;     //Nó direito
public:
    No(){esq = NULL; dir = NULL;}   //Construtor do nó
    No(T);      //Construtor do nó com parâmetro
    void setValor(T);
    void setEsq(No<T>*);
    void setDir(No<T>*);
    T getValor();
    No<T>* getEsq();
    No<T>* getDir();
};

template <typename T>
class Arvore{
private:
    No<T>* raiz;                //Raiz da árvore
    T verificarZero(T);         //Acrescenta zeros à esquerda quando necessário
    No<T>* insere(T,No<T>*);    //Insere um novo nó
    void remove(T,No<T>*);      //Remove um nó
    void removeAux(No<T>*,No<T>*);  //Remove o nó auxiliar
    T busca(T,No<T>*);          //Busca um nó
    void percorreCentral(No<T>*);   //Percorre a árvore na forma central(crescente)
public:
    Arvore(){raiz = NULL;}
    void setRaiz(No<T>*);
    No<T>* getRaiz();
    T busca(T);
    void percorreCentral();
    No<T>* insere(T);
    void remove(T);
    int getAltura(No<T>*);
    int fatorBalanceamento(No<T>*);
    No<T>* balancearNo(No<T>*);     //Verifica onde inserir o nó
    void balancearArvore(No<T>*);   //Balanceia árvore
    No<T>* RSE(No<T>*);             //Rotação Simples à Esquerda
    No<T>* RSD(No<T>*);             //Rotação Simples à Direita
    No<T>* RDE(No<T>*);             //Rotação Dupla à Esquerda
    No<T>* RDD(No<T>*);             //Rotação Dupla à Direita
};

template <typename T>
class Hash{
private:
    static const int tamanhoTabela = 787;   //Tamanho da tabela hash

    Arvore<T>* tabelaHash[tamanhoTabela];   //Declaração da tabela hash com árvore
public:
    Hash();             //Construtor da tabela hash
    int hash(T);        //Determina em qual índice a chave ficará
    void inserir(T);    //Insere a chave na tabela hash
    void buscaChave(T); //Busca a chave na tabela hash
};

int main() {

    string entrada;         //Chave de entrada
    char numero[5];         //Vetor de char
    Hash<string> tabelaHash;//Tabela hash de string
    ifstream leitura;       //Variável para leitura do arquivo
    leitura.open("chaves.txt"); //Abre o arquivo

    //Loop para inserir na tabela cada linha do arquivo
    while(leitura.getline(numero,5)){
        tabelaHash.inserir(numero);
    }

    leitura.close();    //Fecha o arquivo

    cin >> entrada;                 //Lê a chave de entrada
    tabelaHash.buscaChave(entrada); //Busca a chave de entrada

    return 0;
}

//Nó
template<typename T>
No<T>::No(T valor) {
    this->valor = valor;
    this->esq = NULL;
    this->dir = NULL;
}

template<typename T>
void No<T>::setValor(T valor) {
    this->valor = valor;
}

template<typename T>
T No<T>::getValor() {
    return valor;
}

template <typename T>
void No<T>::setEsq(No<T>* esq) {
    this->esq = esq;
}

template <typename T>
No<T>* No<T>::getEsq() {
    return esq;
}

template <typename T>
void No<T>::setDir(No<T>* dir) {
    this->dir = dir;
}

template <typename T>
No<T>* No<T>::getDir() {
    return dir;
}

//Arvore AVL
template <typename T>
void Arvore<T>::setRaiz(No<T> *raiz) {
    this->raiz = raiz;
}

template <typename T>
No<T>* Arvore<T>::getRaiz() {
    return raiz;
}

template <typename T>
T Arvore<T>::busca(T chave) {   //Retorna o valor procurado, se existir
    chave = verificarZero(chave);
    return busca(chave,raiz);
}

template <typename T>
T Arvore<T>::busca(T chave, No<T>* no) {    //Retorna a chave procurada

    if(no == NULL){
        return "Chave não encontrada.";
    }
    else if(chave > no->getValor()){
        return busca(chave, no->getDir());
    }
    else if(chave < no->getValor()){
        return busca(chave, no->getEsq());
    }
    else{
        chave = no->getValor();
    }
    return chave;
}

template <typename T>
void Arvore<T>::percorreCentral() {     //Método para percorrer a árvore na forma central
    percorreCentral(raiz);
}

template <typename T>
void Arvore<T>::percorreCentral(No<T>* p) {     //Imprime os valores na ordem crescente

    if(p != NULL){
        percorreCentral(p->getEsq());
        cout << p->getValor() << " ";
        percorreCentral(p->getDir());
    }
}

template <typename T>
T Arvore<T>::verificarZero(T chave) {//Insere os zeros à esquerda, se necessário e retorna a chave

    int x = atoi(chave.c_str());

    if(x < 10){
         chave = "000"+chave;
    }
    else if(x < 100 && x > 9){
        chave = "00"+chave;
    }
    else if(x < 1000 && x > 99){
        chave = "0"+chave;
    }

    return chave;
}

template <typename T>
No<T>* Arvore<T>::insere(T chave) {     //Insere a chave na árvore
    Arvore<T> arv;
    chave = verificarZero(chave);
    arv.setRaiz(insere(chave,raiz));
    return arv.getRaiz();
}

template <typename T>
No<T>* Arvore<T>::insere(T chave,No<T>* no) {   //Determina onde inserir a chave na árvore

    if(no == NULL){
        no = new No<T>(chave);
        return no;
    }
    else if(chave < no->getValor()){
        no->setEsq(insere(chave,no->getEsq()));
        no = balancearNo(no);
    }
    else if(chave > no->getValor()){
        no->setDir(insere(chave,no->getDir()));
        no = balancearNo(no);
    }
    return no;
}

template <typename T>
void Arvore<T>::remove(T x) {   //Remove a chave da árvore
    remove(x,raiz);
}

template <typename T>
void Arvore<T>::remove(T x, No<T>* p) { //Localiza e remove a chave da árvore

    if(p == NULL){
        cout << "Erro: item não está na arvore";
    }
    else if(x < p->getValor()){
        remove(x,p->getEsq());
    }
    else if(x > p->getValor()){
        remove(x,p->getDir());
    }
    else if(p->getDir() == NULL){
        No<T>* aux = p;
        p = p->getEsq();
        delete aux;
    }
    else if(p->getEsq() == NULL){
        No<T>* aux = p;
        p = p->getDir();
        delete aux;
    }
    else{
        removeAux(p,p->getEsq());
    }
}

template <typename T>
void Arvore<T>::removeAux(No<T>* q, No<T>* r) { //Remove o nó auxiliar
    if(r->getDir() != NULL){
        removeAux(q,r->getDir());
    }
    else{
        q->setValor(r->getValor());
        q = r;
        r = r->getEsq();
        delete q;
    }
}

template <typename T>
int Arvore<T>::getAltura(No<T>* no){   //Retorna altura do nó

    int altura = 0;

    if(no != NULL){
        int alturaEsquerda = getAltura(no->getEsq());
        int alturaDireita = getAltura(no->getDir());
        int maxAltura = max(alturaEsquerda,alturaDireita);
        altura = maxAltura + 1;
    }

    return altura;
}

template <typename T>
int Arvore<T>::fatorBalanceamento(No<T>* no){  //Retorna o fator de balanceamento do nó

    int alturaEsquerda = getAltura(no->getEsq());
    int alturaDireita = getAltura(no->getDir());
    int fatorBal = alturaDireita - alturaEsquerda;

    return fatorBal;
}

template <typename T>
No<T>* Arvore<T>::RSE(No<T>* no){   //Método de rotação simples à esquerda

    No<T>* noTemporario;

    noTemporario = no->getDir();
    no->setDir(noTemporario->getEsq());
    noTemporario->setEsq(no);

    return noTemporario;
}

template <typename T>
No<T>* Arvore<T>::RSD(No<T>* no){   //Método de rotação simples à direita

    No<T>* noTemporario;

    noTemporario = no->getEsq();
    no->setEsq(noTemporario->getDir());
    noTemporario->setDir(no);

    return noTemporario;
}

template <typename T>
No<T>* Arvore<T>::RDE(No<T>* no){      //Método de rotação dupla à esquerda

    No<T>* noTemporario;

    noTemporario = no->getDir();
    no->setDir(RSD(noTemporario));

    return RSE(no);
}

template <typename T>
No<T>* Arvore<T>::RDD(No<T>* no){   //Método de rotação dupla à direita

    No<T>* noTemporario;

    noTemporario = no->getEsq();
    no->setEsq(RSE(noTemporario));

    return RSD(no);
}

template <typename T>
No<T>* Arvore<T>::balancearNo(No<T>* no){   //Verifica qual rotação aplicar, se necessário

    int fatorBal = fatorBalanceamento(no);

    if(fatorBal < -1){
        if(fatorBalanceamento(no->getEsq()) <= 0){
            no = RSD(no);
        }
        else{
            no = RDD(no);
        }
    }
    else if(fatorBal > 1){
        if(fatorBalanceamento(no->getDir()) < 0){
            no = RDE(no);
        }
        else{
            no = RSE(no);
        }
    }
    return no;
}

template <typename T>
void Arvore<T>::balancearArvore(No<T>* arvore){     //Balanceia a árvore

    No<T>* novaRaiz = NULL;
    novaRaiz = balancearNo(arvore);

    if(novaRaiz != arvore){
        arvore = novaRaiz;
    }
}

//Tabela Hash
template <typename T>
Hash<T>::Hash() {   //Construtor da tabela hash
    for(int i = 0;i < tamanhoTabela;i++){
        tabelaHash[i] = new Arvore<T>;
    }
}

template <typename T>
int Hash<T>::hash(T chave) {   //Construtor da tabela hash com parametro
    int chaveInt = atoi(chave.c_str());

    int hash = (chaveInt/1000)*128*128*128 + ((chaveInt%1000)/100)*128*128 + (((chaveInt%1000)%100)/10)*128 + (((chaveInt%1000)%100)%10);
    int indice;

    indice = hash % tamanhoTabela;

    return indice;
}

template <typename T>
void Hash<T>::inserir(T chave) {   //Insere chave na tabela hash
    int indice = hash(chave);

    tabelaHash[indice]->setRaiz(tabelaHash[indice]->insere(chave));
}

template <typename T>
void Hash<T>::buscaChave(T chave) {    //Busca chave na tabela hash
    int indice = hash(chave);

    T resultado = tabelaHash[indice]->busca(chave);

    if(resultado == "Chave não encontrada." ){
        cout << resultado;
    }
    else{
        tabelaHash[indice]->percorreCentral();
    }
}