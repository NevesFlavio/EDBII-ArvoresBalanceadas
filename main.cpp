
#include <iostream>
#include "avl.h"
#include "rubro_negra.h"

using namespace std;

void menuAVL() {
    AVL arvore;
    int opcao;
    int valor;

    do {
        cout << "\n===== ARVORE AVL =====\n";
        cout << "1. Inserir elemento\n";
        cout << "2. Remover elemento\n";
        cout << "3. Buscar elemento\n";
        cout << "4. Exibir em ordem crescente\n";
        cout << "5. Visualizar arvore\n";
        cout << "6. Validar propriedades da AVL\n";
        cout << "0. Voltar ao menu principal\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                cout << "Digite o valor: ";
                cin >> valor;

                if (arvore.inserir(valor)) {
                    cout << "Elemento inserido com sucesso!\n";
                } else {
                    cout << "Esse valor ja existe na arvore!\n";
                }
                break;

            
            case 2:
                cout << "Digite o valor que deseja remover: ";
                cin >> valor;

                if (arvore.remover(valor)) {
                     cout << "Elemento removido com sucesso!\n";
                } else {
                    cout << "Elemento nao encontrado!\n";
                }
                break;


            case 3:
                cout << "Digite o valor que deseja buscar: ";
                cin >> valor;

                if (arvore.buscar(valor)) {
                    cout << "Elemento encontrado!\n";
                } else {
                    cout << "Elemento nao encontrado!\n";
                }
                break;

            case 4:
                cout << "Elementos em ordem crescente: ";
                arvore.exibirEmOrdem();
                break;

            case 5:
                cout << "\nArvore AVL:\n";
                arvore.visualizar();
                break;

            case 6:
                if (arvore.validar()) {
                cout << "AVL valida! Todas as propriedades "
                << "foram preservadas.\n";
                } else {
                cout << "ERRO: a AVL apresenta alguma "
                << "propriedade invalida!\n";
                }
                break;

            case 0:
                cout << "Voltando ao menu principal...\n";
                break;

            default:
                cout << "Opcao invalida!\n";
        }

    } while (opcao != 0);
}


void menuRubroNegra() {
    RubroNegra arvore;
    int opcao;
    int valor;

    do {
        cout << "\n===== ARVORE RUBRO-NEGRA =====\n";
        cout << "1. Inserir elemento\n";
        cout << "2. Remover elemento\n";
        cout << "3. Buscar elemento\n";
        cout << "4. Exibir em ordem crescente\n";
        cout << "5. Visualizar arvore e cores\n";
        cout << "6. Validar propriedades da Rubro-Negra\n";
        cout << "0. Voltar ao menu principal\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                cout << "Digite o valor: ";
                cin >> valor;

                if (arvore.inserir(valor)) {
                    cout << "Elemento inserido com sucesso!\n";
                } else {
                    cout << "Esse valor ja existe na arvore!\n";
                }
                break;

            
            case 2:
                cout << "Digite o valor que deseja remover: ";
                cin >> valor;

                if (arvore.remover(valor)) {
                    cout << "Elemento removido com sucesso!\n";
                } else {
                    cout << "Elemento nao encontrado!\n";
                }
                break;


            case 3:
                cout << "Digite o valor que deseja buscar: ";
                cin >> valor;

                if (arvore.buscar(valor)) {
                    cout << "Elemento encontrado!\n";
                } else {
                    cout << "Elemento nao encontrado!\n";
                }
                break;

            case 4:
                cout << "Elementos em ordem crescente: ";
                arvore.exibirEmOrdem();
                break;

            case 5:
                cout << "\nArvore Rubro-Negra:\n";
                arvore.visualizar();
                break;
            case 6:
                if (arvore.validar()) {
                cout << "Rubro-Negra valida! Todas as propriedades foram preservadas.\n";
                } else {
                cout << "ERRO: a Rubro-Negra apresenta alguma propriedade invalida!\n";
                }
                break;
            case 0:
                cout << "Voltando ao menu principal...\n";
                break;

            default:
                cout << "Opcao invalida!\n";
        }

    } while (opcao != 0);
}


int main() {
    int opcao;

    do {
        cout << "\n===============================\n";
        cout << "    ARVORES BALANCEADAS\n";
        cout << "===============================\n";
        cout << "1. Utilizar arvore AVL\n";
        cout << "2. Utilizar arvore Rubro-Negra\n";
        cout << "0. Encerrar programa\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                menuAVL();
                break;

            case 2:
                menuRubroNegra();
                break;

            case 0:
                cout << "Programa encerrado.\n";
                break;

            default:
                cout << "Opcao invalida!\n";
        }

    } while (opcao != 0);

    return 0;
}
