
#ifndef AVL_H
#define AVL_H

struct NoAVL {
    int valor;
    int altura;
    NoAVL* esquerda;
    NoAVL* direita;
};

class AVL {
private:
    NoAVL* raiz;

    bool validar(NoAVL* no, long long minimo,
    long long maximo, int& alturaCalculada);

    NoAVL* remover(NoAVL* no, int valor);
    NoAVL* menorValor(NoAVL* no);

    int altura(NoAVL* no);
    int fatorBalanceamento(NoAVL* no);

    NoAVL* rotacaoDireita(NoAVL* y);
    NoAVL* rotacaoEsquerda(NoAVL* x);

    NoAVL* inserir(NoAVL* no, int valor);
    void exibirEmOrdem(NoAVL* no);
    void visualizar(NoAVL* no, int nivel);

    void destruir(NoAVL* no);

public:
    AVL();
    ~AVL();
    
    bool validar();
    bool remover(int valor);
    bool inserir(int valor);
    bool buscar(int valor);
    void exibirEmOrdem();
    void visualizar();
};

#endif
