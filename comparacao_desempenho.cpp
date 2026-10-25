
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "avl.h"
#include "rubro_negra.h"

using namespace std;
using namespace chrono;

struct Resultado {
    double insercao;
    double pesquisa;
    double remocao;
    int altura;
    int rotacoes;
};

template <typename Arvore>
Resultado testarArvore(Arvore& arvore,
                       const vector<int>& valores) {
    auto inicio = steady_clock::now();

    for (int valor : valores) {
        arvore.inserir(valor);
    }

    auto fim = steady_clock::now();
    double tempoInsercao =
        duration<double, milli>(fim - inicio).count();

    if (!arvore.validar()) {
        cout << "ERRO: arvore invalida apos insercoes!\n";
        return {-1, -1, -1, -1, -1};
    }

    // Pesquisa: metade dos valores existe e metade nao existe.
    size_t acertos = 0;

    inicio = steady_clock::now();

    for (int valor : valores) {
        if (arvore.buscar(valor)) {
            acertos++;
        }
    }

    for (int i = 1; i <= static_cast<int>(valores.size()); i++) {
        if (arvore.buscar(static_cast<int>(valores.size()) + i)) {
            acertos++;
        }
    }

    fim = steady_clock::now();
    double tempoPesquisa =
        duration<double, milli>(fim - inicio).count();

    if (acertos != valores.size()) {
        cout << "ERRO: resultado inesperado nas pesquisas!\n";
        return {-1, -1, -1, -1, -1};
    }

    int altura = arvore.obterAltura();
    

    // Remocao na mesma ordem usada na insercao.
    inicio = steady_clock::now();

    for (int valor : valores) {
        arvore.remover(valor);
    }

    fim = steady_clock::now();
    double tempoRemocao =
        duration<double, milli>(fim - inicio).count();

    if (!arvore.validar()) {
        cout << "ERRO: arvore invalida apos remocoes!\n";
        return {-1, -1, -1, -1, -1};
    }

    int rotacoesTotais = arvore.obterTotalRotacoes();

    return {
        tempoInsercao,
        tempoPesquisa,
        tempoRemocao,
        altura,
        rotacoesTotais
    };
}

void imprimirResultado(const string& nome,
                       const Resultado& r) {
    cout << left << setw(13) << nome
         << right << setw(12) << fixed << setprecision(3)
         << r.insercao
         << setw(12) << r.pesquisa
         << setw(12) << r.remocao
         << setw(10) << r.altura
         << setw(12) << r.rotacoes
         << "\n";
}

void executarCenario(const string& nome,
                     const vector<int>& valores) {
    AVL arvoreAVL;
    RubroNegra arvoreRN;

    cout << "\nCenario: " << nome << "\n";
    cout << "Elementos: " << valores.size() << "\n\n";

    cout << left << setw(13) << "Arvore"
         << right << setw(12) << "Insercao"
         << setw(12) << "Pesquisa"
         << setw(12) << "Remocao"
         << setw(10) << "Altura"
         << setw(12) << "Rotacoes"
         << "\n";

    cout << string(71, '-') << "\n";

    Resultado resultadoAVL =
        testarArvore(arvoreAVL, valores);

    Resultado resultadoRN =
        testarArvore(arvoreRN, valores);

    imprimirResultado("AVL", resultadoAVL);
    imprimirResultado("Rubro-Negra", resultadoRN);

    cout << "\nTempos em milissegundos (ms).\n";
    cout << "As rotacoes contabilizadas incluem insercoes e remocoes.\n";
}

int main() {
    vector<int> tamanhos = {1000, 10000, 50000};

    for (int n : tamanhos) {
        vector<int> crescente(n);

        for (int i = 0; i < n; i++) {
            crescente[i] = i + 1;
        }

        vector<int> decrescente = crescente;
        reverse(decrescente.begin(), decrescente.end());

        vector<int> aleatorio = crescente;
        mt19937 gerador(12345);
        shuffle(aleatorio.begin(), aleatorio.end(), gerador);

        cout << "\n========================================\n";
        cout << "TESTES COM " << n << " ELEMENTOS\n";
        cout << "========================================\n";

        executarCenario("Crescente", crescente);
        executarCenario("Decrescente", decrescente);
        executarCenario("Embaralhado", aleatorio);
    }

    return 0;
}

