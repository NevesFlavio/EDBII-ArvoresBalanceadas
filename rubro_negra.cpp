
#include <iostream>
#include "rubro_negra.h"

using namespace std;

RubroNegra::RubroNegra() {
    NIL = new NoRN;

    NIL->valor = 0;
    NIL->cor = PRETO;
    NIL->esquerda = NIL;
    NIL->direita = NIL;
    NIL->pai = NIL;

    raiz = NIL;
}

RubroNegra::~RubroNegra() {
    destruir(raiz);
    delete NIL;
}

void RubroNegra::destruir(NoRN* no) {
    if (no == NIL) {
        return;
    }

    destruir(no->esquerda);
    destruir(no->direita);
    delete no;
}

void RubroNegra::rotacaoEsquerda(NoRN* no) {
    NoRN* filho = no->direita;

    no->direita = filho->esquerda;

    if (filho->esquerda != NIL) {
        filho->esquerda->pai = no;
    }

    filho->pai = no->pai;

    if (no->pai == NIL) {
        raiz = filho;
    } else if (no == no->pai->esquerda) {
        no->pai->esquerda = filho;
    } else {
        no->pai->direita = filho;
    }

    filho->esquerda = no;
    no->pai = filho;
}

void RubroNegra::rotacaoDireita(NoRN* no) {
    NoRN* filho = no->esquerda;

    no->esquerda = filho->direita;

    if (filho->direita != NIL) {
        filho->direita->pai = no;
    }

    filho->pai = no->pai;

    if (no->pai == NIL) {
        raiz = filho;
    } else if (no == no->pai->direita) {
        no->pai->direita = filho;
    } else {
        no->pai->esquerda = filho;
    }

    filho->direita = no;
    no->pai = filho;
}


void RubroNegra::corrigirInsercao(NoRN* no) {
    while (no->pai->cor == VERMELHO) {
        if (no->pai == no->pai->pai->esquerda) {
            NoRN* tio = no->pai->pai->direita;

            // Caso 1: pai e tio vermelhos
            if (tio->cor == VERMELHO) {
                no->pai->cor = PRETO;
                tio->cor = PRETO;
                no->pai->pai->cor = VERMELHO;
                no = no->pai->pai;
            } else {
                // Caso 2: formato triangular
                if (no == no->pai->direita) {
                    no = no->pai;
                    rotacaoEsquerda(no);
                }

                // Caso 3: formato linear
                no->pai->cor = PRETO;
                no->pai->pai->cor = VERMELHO;
                rotacaoDireita(no->pai->pai);
            }
        } else {
            // Casos simetricos: pai esta a direita
            NoRN* tio = no->pai->pai->esquerda;

            if (tio->cor == VERMELHO) {
                no->pai->cor = PRETO;
                tio->cor = PRETO;
                no->pai->pai->cor = VERMELHO;
                no = no->pai->pai;
            } else {
                if (no == no->pai->esquerda) {
                    no = no->pai;
                    rotacaoDireita(no);
                }

                no->pai->cor = PRETO;
                no->pai->pai->cor = VERMELHO;
                rotacaoEsquerda(no->pai->pai);
            }
        }
    }

    raiz->cor = PRETO;
}


bool RubroNegra::inserir(int valor) {
    NoRN* novo = new NoRN;

    novo->valor = valor;
    novo->cor = VERMELHO;
    novo->esquerda = NIL;
    novo->direita = NIL;
    novo->pai = NIL;

    NoRN* pai = NIL;
    NoRN* atual = raiz;

    while (atual != NIL) {
        pai = atual;

        if (valor < atual->valor) {
            atual = atual->esquerda;
        } else if (valor > atual->valor) {
            atual = atual->direita;
        } else {
            delete novo;
            return false;
        }
    }

    novo->pai = pai;

    if (pai == NIL) {
        raiz = novo;
    } else if (valor < pai->valor) {
        pai->esquerda = novo;
    } else {
        pai->direita = novo;
    }

    corrigirInsercao(novo);
    return true;
}


NoRN* RubroNegra::buscarNo(int valor) {
    NoRN* atual = raiz;

    while (atual != NIL && atual->valor != valor) {
        if (valor < atual->valor) {
            atual = atual->esquerda;
        } else {
            atual = atual->direita;
        }
    }

    return atual;
}

bool RubroNegra::buscar(int valor) {
    return buscarNo(valor) != NIL;
}

void RubroNegra::exibirEmOrdem(NoRN* no) {
    if (no == NIL) {
        return;
    }

    exibirEmOrdem(no->esquerda);
    cout << no->valor << " ";
    exibirEmOrdem(no->direita);
}

void RubroNegra::exibirEmOrdem() {
    exibirEmOrdem(raiz);
    cout << "\n";
}

void RubroNegra::visualizar(NoRN* no, int nivel) {
    if (no == NIL) {
        return;
    }

    visualizar(no->direita, nivel + 1);

    for (int i = 0; i < nivel; i++) {
        cout << "    ";
    }

    cout << no->valor;

    if (no->cor == PRETO) {
        cout << "(P)\n";
    } else {
        cout << "(V)\n";
    }

    visualizar(no->esquerda, nivel + 1);
}

void RubroNegra::visualizar() {
    if (raiz == NIL) {
        cout << "A arvore esta vazia.\n";
        return;
    }

    visualizar(raiz, 0);
}


NoRN* RubroNegra::minimo(NoRN* no) {
    while (no->esquerda != NIL) {
        no = no->esquerda;
    }

    return no;
}

void RubroNegra::transplantar(NoRN* antigo, NoRN* novo) {
    if (antigo->pai == NIL) {
        raiz = novo;
    } else if (antigo == antigo->pai->esquerda) {
        antigo->pai->esquerda = novo;
    } else {
        antigo->pai->direita = novo;
    }

    novo->pai = antigo->pai;
}


void RubroNegra::corrigirRemocao(NoRN* no) {
    while (no != raiz && no->cor == PRETO) {
        if (no == no->pai->esquerda) {
            NoRN* irmao = no->pai->direita;

            // Caso 1: irmao vermelho
            if (irmao->cor == VERMELHO) {
                irmao->cor = PRETO;
                no->pai->cor = VERMELHO;
                rotacaoEsquerda(no->pai);
                irmao = no->pai->direita;
            }

            // Caso 2: irmao preto com filhos pretos
            if (irmao == NIL) {
                no = no->pai;
                continue;
            }

            if (irmao->esquerda->cor == PRETO &&
                irmao->direita->cor == PRETO) {
                irmao->cor = VERMELHO;
                no = no->pai;
            } else {
                // Caso 3: filho distante preto
                if (irmao->direita->cor == PRETO) {
                    irmao->esquerda->cor = PRETO;
                    irmao->cor = VERMELHO;
                    rotacaoDireita(irmao);
                    irmao = no->pai->direita;
                }

                // Caso 4: filho distante vermelho
                irmao->cor = no->pai->cor;
                no->pai->cor = PRETO;
                irmao->direita->cor = PRETO;
                rotacaoEsquerda(no->pai);
                no = raiz;
            }
        } else {
            // Casos simetricos: no esta a direita
            NoRN* irmao = no->pai->esquerda;

            if (irmao->cor == VERMELHO) {
                irmao->cor = PRETO;
                no->pai->cor = VERMELHO;
                rotacaoDireita(no->pai);
                irmao = no->pai->esquerda;
            }

            if (irmao == NIL) {
                no = no->pai;
                continue;
            }

            if (irmao->direita->cor == PRETO &&
                irmao->esquerda->cor == PRETO) {
                irmao->cor = VERMELHO;
                no = no->pai;
            } else {
                if (irmao->esquerda->cor == PRETO) {
                    irmao->direita->cor = PRETO;
                    irmao->cor = VERMELHO;
                    rotacaoEsquerda(irmao);
                    irmao = no->pai->esquerda;
                }

                irmao->cor = no->pai->cor;
                no->pai->cor = PRETO;
                irmao->esquerda->cor = PRETO;
                rotacaoDireita(no->pai);
                no = raiz;
            }
        }
    }

    no->cor = PRETO;
    raiz->cor = PRETO;
    NIL->cor = PRETO;
}


bool RubroNegra::remover(int valor) {
    NoRN* alvo = buscarNo(valor);

    if (alvo == NIL) {
        return false;
    }

    NoRN* removido = alvo;
    Cor corOriginal = removido->cor;
    NoRN* filho;

    if (alvo->esquerda == NIL) {
        filho = alvo->direita;
        transplantar(alvo, alvo->direita);
    } else if (alvo->direita == NIL) {
        filho = alvo->esquerda;
        transplantar(alvo, alvo->esquerda);
    } else {
        removido = minimo(alvo->direita);
        corOriginal = removido->cor;
        filho = removido->direita;

        if (removido->pai == alvo) {
            filho->pai = removido;
        } else {
            transplantar(removido, removido->direita);

            removido->direita = alvo->direita;
            removido->direita->pai = removido;
        }

        transplantar(alvo, removido);

        removido->esquerda = alvo->esquerda;
        removido->esquerda->pai = removido;
        removido->cor = alvo->cor;
    }

    delete alvo;

    if (corOriginal == PRETO) {
        corrigirRemocao(filho);
    }

    raiz->cor = PRETO;
    raiz->pai = NIL;
    NIL->cor = PRETO;

    return true;
}

bool RubroNegra::validar(NoRN* no, long long minimo,
                         long long maximo, int& alturaPreta) {
    if (no == NIL) {
        alturaPreta = 1;
        return true;
    }

    // Verifica se os valores respeitam a ordenacao
    if (no->valor <= minimo || no->valor >= maximo) {
        return false;
    }

    // Verifica se os ponteiros para os pais estao corretos
    if (no->esquerda != NIL && no->esquerda->pai != no) {
        return false;
    }

    if (no->direita != NIL && no->direita->pai != no) {
        return false;
    }

    // Um no vermelho nao pode ter filho vermelho
    if (no->cor == VERMELHO) {
        if (no->esquerda->cor == VERMELHO ||
            no->direita->cor == VERMELHO) {
            return false;
        }
    }

    int alturaEsquerda;
    int alturaDireita;

    if (!validar(no->esquerda, minimo, no->valor, alturaEsquerda)) {
        return false;
    }

    if (!validar(no->direita, no->valor, maximo, alturaDireita)) {
        return false;
    }

    // Todos os caminhos devem ter a mesma altura preta
    if (alturaEsquerda != alturaDireita) {
        return false;
    }

    alturaPreta = alturaEsquerda;

    if (no->cor == PRETO) {
        alturaPreta++;
    }

    return true;
}

bool RubroNegra::validar() {
    // A sentinela NIL deve ser preta e apontar para si mesma
    if (NIL == nullptr || NIL->cor != PRETO ||
        NIL->esquerda != NIL || NIL->direita != NIL) {
        return false;
    }

    // Uma arvore vazia e valida
    if (raiz == NIL) {
        return true;
    }

    // A raiz deve ser preta e nao possuir pai real
    if (raiz->cor != PRETO || raiz->pai != NIL) {
        return false;
    }

    int alturaPreta;

    return validar(raiz, -9223372036854775807LL - 1,
                   9223372036854775807LL, alturaPreta);
}