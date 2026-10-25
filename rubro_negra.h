
#ifndef RUBRO_NEGRA_H
#define RUBRO_NEGRA_H

enum Cor {
    VERMELHO,
    PRETO
};

struct NoRN {
    int valor;
    Cor cor;

    NoRN* esquerda;
    NoRN* direita;
    NoRN* pai;
};

class RubroNegra {
private:
    NoRN* raiz;
    NoRN* NIL;
    int totalRotacoes;

    int altura(NoRN* no);

    bool validar(NoRN* no, long long minimo,
    long long maximo, int& alturaPreta);

    void rotacaoEsquerda(NoRN* no);
    void rotacaoDireita(NoRN* no);

    void corrigirInsercao(NoRN* no);
    void corrigirRemocao(NoRN* no);

    void destruir(NoRN* no);
    void exibirEmOrdem(NoRN* no);
    void visualizar(NoRN* no, int nivel);

    NoRN* buscarNo(int valor);
    NoRN* minimo(NoRN* no);
    void transplantar(NoRN* antigo, NoRN* novo);

public:
    RubroNegra();
    ~RubroNegra();
    int obterAltura();
    int obterTotalRotacoes();

    bool inserir(int valor);
    bool buscar(int valor);
    bool remover(int valor);

    void exibirEmOrdem();
    void visualizar();
    bool validar();
};

#endif
