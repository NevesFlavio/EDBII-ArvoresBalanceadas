
#include <iostream>
#include "avl.h"
#include "rubro_negra.h"

using namespace std;

int totalTestes = 0;
int testesFalhos = 0;

void verificar(bool resultado, const char* descricao) {
    totalTestes++;

    if (resultado) {
        cout << "[OK] " << descricao << "\n";
    } else {
        cout << "[ERRO] " << descricao << "\n";
        testesFalhos++;
    }
}

void testarAVL() {
    cout << "\n===== TESTES DA AVL =====\n";

    AVL arvore;

    verificar(arvore.validar(), "AVL vazia e valida");
    verificar(!arvore.buscar(10), "Busca em arvore vazia");

    verificar(arvore.inserir(20), "Inserir 20");
    verificar(arvore.validar(), "AVL valida apos inserir 20");

    verificar(arvore.inserir(10), "Inserir 10");
    verificar(arvore.validar(), "AVL valida apos inserir 10");

    verificar(arvore.inserir(30), "Inserir 30");
    verificar(arvore.validar(), "AVL valida apos inserir 30");

    verificar(!arvore.inserir(20), "Rejeitar valor duplicado");
    verificar(arvore.validar(), "AVL continua valida apos duplicata");

    verificar(arvore.buscar(10), "Buscar valor existente");
    verificar(!arvore.buscar(99), "Buscar valor inexistente");

    verificar(arvore.remover(10), "Remover folha");
    verificar(arvore.validar(), "AVL valida apos remover folha");

    verificar(arvore.inserir(5), "Inserir 5");
    verificar(arvore.validar(), "AVL valida apos inserir 5");

    verificar(arvore.remover(20), "Remover no com dois filhos");
    verificar(arvore.validar(), "AVL valida apos remover no com dois filhos");

    verificar(!arvore.remover(99), "Nao remover valor inexistente");
    verificar(arvore.validar(), "AVL continua valida apos remocao inexistente");

    AVL sequencia;

    for (int i = 1; i <= 7; i++) {
        verificar(sequencia.inserir(i), "Inserir na sequencia AVL");
        verificar(sequencia.validar(), "AVL valida apos cada insercao");
    }

    for (int i = 1; i <= 7; i++) {
        verificar(sequencia.remover(i), "Remover da sequencia AVL");
        verificar(sequencia.validar(), "AVL valida apos cada remocao");
    }

    verificar(!sequencia.remover(1), "AVL vazia rejeita remocao");
    verificar(sequencia.validar(), "AVL vazia continua valida");
}

void testarRubroNegra() {
    cout << "\n===== TESTES DA RUBRO-NEGRA =====\n";

    RubroNegra arvore;

    verificar(arvore.validar(), "Rubro-Negra vazia e valida");
    verificar(!arvore.buscar(10), "Busca em arvore vazia");

    verificar(arvore.inserir(20), "Inserir 20");
    verificar(arvore.validar(), "RN valida apos inserir 20");

    verificar(arvore.inserir(10), "Inserir 10");
    verificar(arvore.validar(), "RN valida apos inserir 10");

    verificar(arvore.inserir(30), "Inserir 30");
    verificar(arvore.validar(), "RN valida apos inserir 30");

    verificar(!arvore.inserir(20), "Rejeitar valor duplicado");
    verificar(arvore.validar(), "RN continua valida apos duplicata");

    verificar(arvore.buscar(10), "Buscar valor existente");
    verificar(!arvore.buscar(99), "Buscar valor inexistente");

    verificar(arvore.remover(10), "Remover folha");
    verificar(arvore.validar(), "RN valida apos remover folha");

    verificar(arvore.inserir(5), "Inserir 5");
    verificar(arvore.validar(), "RN valida apos inserir 5");

    verificar(arvore.remover(20), "Remover no com dois filhos");
    verificar(arvore.validar(), "RN valida apos remover no com dois filhos");

    verificar(!arvore.remover(99), "Nao remover valor inexistente");
    verificar(arvore.validar(), "RN continua valida apos remocao inexistente");

    RubroNegra sequencia;

    for (int i = 1; i <= 7; i++) {
        verificar(sequencia.inserir(i), "Inserir na sequencia RN");
        verificar(sequencia.validar(), "RN valida apos cada insercao");
    }

    for (int i = 1; i <= 7; i++) {
        verificar(sequencia.remover(i), "Remover da sequencia RN");
        verificar(sequencia.validar(), "RN valida apos cada remocao");
    }

    verificar(!sequencia.remover(1), "RN vazia rejeita remocao");
    verificar(sequencia.validar(), "RN vazia continua valida");
}



int main() {
    testarAVL();
    testarRubroNegra();

    cout << "\n===== RESUMO DOS TESTES =====\n";
    cout << "Total: " << totalTestes << "\n";
    cout << "Sucesso: " << totalTestes - testesFalhos << "\n";
    cout << "Falhas: " << testesFalhos << "\n";

    if (testesFalhos == 0) {
        cout << "TODOS OS TESTES PASSARAM!\n";
    } else {
        cout << "EXISTEM TESTES COM FALHA!\n";
    }

    return testesFalhos == 0 ? 0 : 1;
}
