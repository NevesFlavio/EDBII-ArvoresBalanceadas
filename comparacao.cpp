
#include <iostream>
#include "avl.h"
#include "rubro_negra.h"

using namespace std;

void executarComparacao(const char* nome,
                        int valores[], int tamanho) {
    AVL arvoreAVL;
    RubroNegra arvoreRN;

    cout << "\n===== " << nome << " =====\n";

    for (int i = 0; i < tamanho; i++) {
        arvoreAVL.inserir(valores[i]);
        arvoreRN.inserir(valores[i]);

        if (!arvoreAVL.validar() || !arvoreRN.validar()) {
            cout << "ERRO: uma das arvores ficou invalida!\n";
            return;
        }
    }

    cout << "Elementos inseridos: " << tamanho << "\n";
    cout << "\n";
    cout << "Metrica             AVL       Rubro-Negra\n";
    cout << "Altura              "
         << arvoreAVL.obterAltura() << "         "
         << arvoreRN.obterAltura() << "\n";
    cout << "Rotacoes            "
         << arvoreAVL.obterTotalRotacoes() << "         "
         << arvoreRN.obterTotalRotacoes() << "\n";

    cout << "\nRemovendo os mesmos elementos...\n";

    for (int i = 0; i < tamanho; i++) {
        bool removeuAVL = arvoreAVL.remover(valores[i]);
        bool removeuRN = arvoreRN.remover(valores[i]);

        if (!removeuAVL || !removeuRN ||
            !arvoreAVL.validar() || !arvoreRN.validar()) {
            cout << "ERRO durante as remocoes!\n";
            return;
        }
    }

    cout << "\nDepois das remocoes:\n";
    cout << "Altura              "
         << arvoreAVL.obterAltura() << "         "
         << arvoreRN.obterAltura() << "\n";
    cout << "Rotacoes acumuladas "
         << arvoreAVL.obterTotalRotacoes() << "         "
         << arvoreRN.obterTotalRotacoes() << "\n";
}

int main() {
    int crescente[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int decrescente[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int variado[] = {40, 10, 70, 20, 60, 30, 50, 80, 90, 5};

    executarComparacao("INSERCAO CRESCENTE",
                       crescente, 10);

    executarComparacao("INSERCAO DECRESCENTE",
                       decrescente, 10);

    executarComparacao("INSERCAO VARIADA",
                       variado, 10);

    return 0;
}
