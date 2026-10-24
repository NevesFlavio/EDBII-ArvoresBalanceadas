
#include <iostream>
#include "avl.h"

using namespace std;

AVL::AVL() {
    raiz = nullptr;
}

AVL::~AVL() {
    destruir(raiz);
}


NoAVL* AVL::menorValor(NoAVL* no) {
    NoAVL* atual = no;

    while (atual != nullptr && atual->esquerda != nullptr) {
        atual = atual->esquerda;
    }

    return atual;
}

NoAVL* AVL::remover(NoAVL* no, int valor) {
    if (no == nullptr) {
        return nullptr;
    }

    if (valor < no->valor) {
        no->esquerda = remover(no->esquerda, valor);
    } else if (valor > no->valor) {
        no->direita = remover(no->direita, valor);
    } else {
        // Caso 1: no sem filhos
        if (no->esquerda == nullptr &&
            no->direita == nullptr) {
            delete no;
            return nullptr;
        }

        // Caso 2: no com apenas um filho
        if (no->esquerda == nullptr) {
            NoAVL* temp = no->direita;
            delete no;
            return temp;
        }

        if (no->direita == nullptr) {
            NoAVL* temp = no->esquerda;
            delete no;
            return temp;
        }

        // Caso 3: no com dois filhos
        NoAVL* sucessor = menorValor(no->direita);
        no->valor = sucessor->valor;
        no->direita = remover(no->direita, sucessor->valor);
    }

    // Atualiza a altura do no
    int alturaEsquerda = altura(no->esquerda);
    int alturaDireita = altura(no->direita);

    if (alturaEsquerda > alturaDireita) {
        no->altura = alturaEsquerda + 1;
    } else {
        no->altura = alturaDireita + 1;
    }

    // Verifica o balanceamento
    int fb = fatorBalanceamento(no);

    // Caso LL
    if (fb > 1 && fatorBalanceamento(no->esquerda) >= 0) {
        return rotacaoDireita(no);
    }

    // Caso LR
    if (fb > 1 && fatorBalanceamento(no->esquerda) < 0) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    // Caso RR
    if (fb < -1 && fatorBalanceamento(no->direita) <= 0) {
        return rotacaoEsquerda(no);
    }

    // Caso RL
    if (fb < -1 && fatorBalanceamento(no->direita) > 0) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    return no;
}

bool AVL::remover(int valor) {
    if (!buscar(valor)) {
        return false;
    }

    raiz = remover(raiz, valor);
    return true;
}


int AVL::altura(NoAVL* no) {
    if (no == nullptr) {
        return 0;
    }

    return no->altura;
}

int AVL::fatorBalanceamento(NoAVL* no) {
    if (no == nullptr) {
        return 0;
    }

    return altura(no->esquerda) - altura(no->direita);
}

NoAVL* AVL::rotacaoDireita(NoAVL* y) {
    NoAVL* x = y->esquerda;
    NoAVL* auxiliar = x->direita;

    x->direita = y;
    y->esquerda = auxiliar;

    int alturaEsquerdaY = altura(y->esquerda);
    int alturaDireitaY = altura(y->direita);

    if (alturaEsquerdaY > alturaDireitaY) {
        y->altura = alturaEsquerdaY + 1;
    } else {
        y->altura = alturaDireitaY + 1;
    }

    int alturaEsquerdaX = altura(x->esquerda);
    int alturaDireitaX = altura(x->direita);

    if (alturaEsquerdaX > alturaDireitaX) {
        x->altura = alturaEsquerdaX + 1;
    } else {
        x->altura = alturaDireitaX + 1;
    }

    return x;
}

NoAVL* AVL::rotacaoEsquerda(NoAVL* x) {
    NoAVL* y = x->direita;
    NoAVL* auxiliar = y->esquerda;

    y->esquerda = x;
    x->direita = auxiliar;

    int alturaEsquerdaX = altura(x->esquerda);
    int alturaDireitaX = altura(x->direita);

    if (alturaEsquerdaX > alturaDireitaX) {
        x->altura = alturaEsquerdaX + 1;
    } else {
        x->altura = alturaDireitaX + 1;
    }

    int alturaEsquerdaY = altura(y->esquerda);
    int alturaDireitaY = altura(y->direita);

    if (alturaEsquerdaY > alturaDireitaY) {
        y->altura = alturaEsquerdaY + 1;
    } else {
        y->altura = alturaDireitaY + 1;
    }

    return y;
}

NoAVL* AVL::inserir(NoAVL* no, int valor) {
    if (no == nullptr) {
        NoAVL* novo = new NoAVL;

        novo->valor = valor;
        novo->altura = 1;
        novo->esquerda = nullptr;
        novo->direita = nullptr;

        return novo;
    }

    if (valor < no->valor) {
        no->esquerda = inserir(no->esquerda, valor);
    } else if (valor > no->valor) {
        no->direita = inserir(no->direita, valor);
    } else {
        return no;
    }

    int alturaEsquerda = altura(no->esquerda);
    int alturaDireita = altura(no->direita);

    if (alturaEsquerda > alturaDireita) {
        no->altura = alturaEsquerda + 1;
    } else {
        no->altura = alturaDireita + 1;
    }

    int fb = fatorBalanceamento(no);

    // Caso LL
    if (fb > 1 && valor < no->esquerda->valor) {
        return rotacaoDireita(no);
    }

    // Caso RR
    if (fb < -1 && valor > no->direita->valor) {
        return rotacaoEsquerda(no);
    }

    // Caso LR
    if (fb > 1 && valor > no->esquerda->valor) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    // Caso RL
    if (fb < -1 && valor < no->direita->valor) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    return no;
}

bool AVL::inserir(int valor) {
    if (buscar(valor)) {
        return false;
    }

    raiz = inserir(raiz, valor);
    return true;
}

bool AVL::buscar(int valor) {
    NoAVL* atual = raiz;

    while (atual != nullptr) {
        if (valor == atual->valor) {
            return true;
        }

        if (valor < atual->valor) {
            atual = atual->esquerda;
        } else {
            atual = atual->direita;
        }
    }

    return false;
}

void AVL::exibirEmOrdem(NoAVL* no) {
    if (no == nullptr) {
        return;
    }

    exibirEmOrdem(no->esquerda);
    cout << no->valor << " ";
    exibirEmOrdem(no->direita);
}

void AVL::exibirEmOrdem() {
    exibirEmOrdem(raiz);
    cout << "\n";
}

void AVL::visualizar(NoAVL* no, int nivel) {
    if (no == nullptr) {
        return;
    }

    visualizar(no->direita, nivel + 1);

    for (int i = 0; i < nivel; i++) {
        cout << "    ";
    }

    cout << no->valor << "\n";

    visualizar(no->esquerda, nivel + 1);
}

void AVL::visualizar() {
    if (raiz == nullptr) {
        cout << "A arvore esta vazia.\n";
        return;
    }

    visualizar(raiz, 0);
}

void AVL::destruir(NoAVL* no) {
    if (no == nullptr) {
        return;
    }

    destruir(no->esquerda);
    destruir(no->direita);
    delete no;
}


bool AVL::validar(NoAVL* no, long long minimo,
                  long long maximo, int& alturaCalculada) {
    if (no == nullptr) {
        alturaCalculada = 0;
        return true;
    }

    // Verifica se o valor respeita os limites da arvore
    if (no->valor <= minimo || no->valor >= maximo) {
        return false;
    }

    int alturaEsquerda;
    int alturaDireita;

    bool esquerdaValida = validar(
        no->esquerda, minimo, no->valor, alturaEsquerda
    );

    bool direitaValida = validar(
        no->direita, no->valor, maximo, alturaDireita
    );

    if (!esquerdaValida || !direitaValida) {
        return false;
    }

    // Calcula a altura real do no
    if (alturaEsquerda > alturaDireita) {
        alturaCalculada = alturaEsquerda + 1;
    } else {
        alturaCalculada = alturaDireita + 1;
    }

    // Confere se a altura armazenada esta correta
    if (no->altura != alturaCalculada) {
        return false;
    }

    // Verifica a propriedade de balanceamento da AVL
    int diferenca = alturaEsquerda - alturaDireita;

    if (diferenca < -1 || diferenca > 1) {
        return false;
    }

    return true;
}

bool AVL::validar() {
    int alturaCalculada = 0;

    return validar(
        raiz, -9223372036854775807LL - 1,
        9223372036854775807LL, alturaCalculada
    );
}
