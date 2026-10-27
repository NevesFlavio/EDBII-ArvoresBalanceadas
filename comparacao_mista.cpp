
#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>

#include "avl.h"
#include "rubro_negra.h"

using namespace std;
using namespace chrono;

const int QUANTIDADE_INICIAL = 50000;
const int QUANTIDADE_OPERACOES = 10000;
const int REPETICOES = 5;

struct Resultado {
    double tempoTotal;
    int altura;
    int rotacoes;
    bool valido;
};

template <typename Arvore>
Resultado testarArvoreMista(Arvore& arvore) {
    auto inicio = steady_clock::now();

    // Carga inicial: inserir 50.000 elementos.
    for (int i = 1; i <= QUANTIDADE_INICIAL; i++) {
        arvore.inserir(i);
    }

    if (!arvore.validar()) {
        return {-1, -1, -1, false};
    }

    // Operacoes misturadas: pesquisar, inserir e remover.
    for (int i = 1; i <= QUANTIDADE_OPERACOES; i++) {
        int novo = QUANTIDADE_INICIAL + i;
        int inexistente = QUANTIDADE_INICIAL
                        + QUANTIDADE_OPERACOES + i;

        // O elemento i existe neste momento.
        if (!arvore.buscar(i)) {
            return {-1, -1, -1, false};
        }

        // Este elemento ainda nao foi inserido.
        if (arvore.buscar(inexistente)) {
            return {-1, -1, -1, false};
        }

        // Inserir um novo elemento.
        arvore.inserir(novo);

        if (!arvore.buscar(novo)) {
            return {-1, -1, -1, false};
        }

        // Remover o elemento antigo.
        if (!arvore.remover(i)) {
            return {-1, -1, -1, false};
        }

        // Confirmar que o elemento removido nao existe mais.
        if (arvore.buscar(i)) {
            return {-1, -1, -1, false};
        }
    }

    auto fim = steady_clock::now();

    double tempo =
        duration<double, milli>(fim - inicio).count();

    if (!arvore.validar()) {
        return {-1, -1, -1, false};
    }

    return {
        tempo,
        arvore.obterAltura(),
        arvore.obterTotalRotacoes(),
        true
    };
}

template <typename Arvore>
Resultado executarRepeticoes() {
    double somaTempos = 0;
    int altura = 0;
    int rotacoes = 0;

    for (int i = 0; i < REPETICOES; i++) {
        Arvore arvore;
        Resultado r = testarArvoreMista(arvore);

        if (!r.valido) {
            return {-1, -1, -1, false};
        }

        somaTempos += r.tempoTotal;
        altura = r.altura;
        rotacoes = r.rotacoes;
    }

    return {
        somaTempos / REPETICOES,
        altura,
        rotacoes,
        true
    };
}

void imprimirResultado(const char* nome,
                       const Resultado& r) {
    cout << left << setw(13) << nome
         << right << setw(16) << fixed << setprecision(3)
         << r.tempoTotal
         << setw(12) << r.altura
         << setw(12) << r.rotacoes
         << "\n";
}

int main() {
    cout << "========================================\n";
    cout << "COMPARACAO COM OPERACOES MISTURADAS\n";
    cout << "========================================\n";

    cout << "Elementos iniciais: "
         << QUANTIDADE_INICIAL << "\n";

    cout << "Repeticoes de cada operacao: "
         << QUANTIDADE_OPERACOES << "\n";

    cout << "Repeticoes do teste: "
         << REPETICOES << "\n\n";

    Resultado resultadoAVL = executarRepeticoes<AVL>();
    Resultado resultadoRN = executarRepeticoes<RubroNegra>();

    if (!resultadoAVL.valido || !resultadoRN.valido) {
        cout << "ERRO: alguma arvore falhou na validacao!\n";
        return 1;
    }

    cout << left << setw(13) << "Arvore"
         << right << setw(16) << "Tempo medio"
         << setw(12) << "Altura"
         << setw(12) << "Rotacoes"
         << "\n";

    cout << string(53, '-') << "\n";

    imprimirResultado("AVL", resultadoAVL);
    imprimirResultado("Rubro-Negra", resultadoRN);

    cout << "\nTempo medio total em milissegundos (ms).\n";
    cout << "O tempo inclui a carga inicial e as operacoes.\n";
    cout << "Altura e rotacoes sao da ultima repeticao.\n";

    return 0;
}
