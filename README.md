# Árvores Balanceadas: AVL e Rubro-Negra

## 1. Descrição do projeto

Este projeto implementa duas estruturas de dados de busca balanceadas: a árvore AVL e a árvore Rubro-Negra.

O objetivo é permitir a inserção, a remoção e a busca de elementos, além da exibição dos valores em ordem crescente e da visualização da estrutura da árvore no terminal.

As implementações utilizam algoritmos próprios de balanceamento, sem recorrer a bibliotecas que implementem essas estruturas prontas.

## 2. Funcionalidades

As duas árvores oferecem as seguintes operações:

- Inserir um elemento.
- Remover um elemento.
- Buscar um elemento.
- Exibir os elementos em ordem crescente.
- Visualizar a estrutura da árvore no terminal.
- Validar as propriedades de balanceamento da estrutura.

O programa possui um menu interativo que permite escolher qual árvore utilizar.

As implementações também tratam situações como a inserção de valores duplicados, a busca por valores inexistentes e a tentativa de remover elementos que não estão na árvore.

## 3. Árvore AVL

A árvore AVL é uma árvore binária de busca que mantém o balanceamento por meio do controle das alturas das subárvores.

Para cada nó, o fator de balanceamento é calculado pela diferença entre as alturas das subárvores esquerda e direita.

O fator de balanceamento deve permanecer entre -1 e 1.

Quando uma inserção ou remoção viola essa condição, a árvore realiza rotações para recuperar o balanceamento.

As operações de balanceamento utilizadas são:

- Rotação simples à direita.
- Rotação simples à esquerda.
- Rotação dupla esquerda-direita.
- Rotação dupla direita-esquerda.

A implementação também verifica a ordenação dos elementos, as alturas armazenadas e os fatores de balanceamento.

## 4. Árvore Rubro-Negra

A árvore Rubro-Negra é uma árvore binária de busca que utiliza cores nos nós para manter o balanceamento.

Cada nó possui uma cor: vermelha ou preta.

A implementação utiliza uma sentinela `NIL` preta para representar as folhas ausentes, simplificando os algoritmos de inserção e remoção.

As principais propriedades verificadas são:

- A raiz é preta.
- Os nós vermelhos não possuem filhos vermelhos.
- Todos os caminhos de um nó até as folhas sentinelas possuem a mesma quantidade de nós pretos.
- Os valores respeitam a propriedade de ordenação de uma árvore binária de busca.
- Os ponteiros entre pais e filhos são consistentes.

O balanceamento é realizado por rotações e alterações de cores durante as operações de inserção e remoção.

A implementação segue o modelo tradicional de árvore Rubro-Negra, sem exigir que as ligações vermelhas estejam sempre inclinadas à esquerda.

## 5. Organização dos arquivos

- `main.cpp`: menu principal e interação com o usuário.
- `avl.h`: declaração das estruturas e da classe AVL.
- `avl.cpp`: implementação das operações da árvore AVL.
- `rubro_negra.h`: declaração das estruturas e da classe Rubro-Negra.
- `rubro_negra.cpp`: implementação das operações da árvore Rubro-Negra.
- `testes.cpp`: testes automatizados das duas estruturas.
- `README.md`: documentação do projeto.

## 6. Compilação

É necessário ter um compilador C++ compatível com o padrão C++17, como o GCC.

Para compilar o programa principal, execute no terminal, dentro da pasta do projeto:

```bash
g++ -std=c++17 -Wall -Wextra main.cpp avl.cpp rubro_negra.cpp -o arvores
```

No Windows PowerShell, execute o programa com:

```powershell
.\arvores.exe
```

## 7. Execução dos testes

Os testes automatizados são compilados separadamente do programa principal, pois o arquivo `testes.cpp` possui sua própria função `main()`.

Para compilar:

```bash
g++ -std=c++17 -Wall -Wextra testes.cpp avl.cpp rubro_negra.cpp -o testes
```

Para executar no Windows PowerShell:

```powershell
.\testes.exe
```

Os testes verificam operações de inserção, busca e remoção, tratamento de duplicatas e valores inexistentes, além da validação das propriedades das árvores após operações selecionadas.

O programa apresenta um resumo com o total de testes, o número de sucessos e o número de falhas. Se algum teste falhar, o programa retorna um código de saída diferente de zero.

## 8. Complexidade

Considerando árvores corretamente balanceadas, as operações de busca, inserção e remoção possuem complexidade de tempo \(O(\log n)\), em que \(n\) é o número de elementos.

A exibição dos elementos em ordem crescente e a validação completa da árvore possuem complexidade \(O(n)\), pois podem precisar visitar todos os nós.

A visualização da estrutura também pode visitar todos os nós, dependendo do tamanho da árvore.

## 9. Considerações finais

O projeto permite estudar e comparar duas estratégias clássicas de balanceamento de árvores binárias de busca.

A árvore AVL utiliza alturas e rotações para manter um balanceamento mais rigoroso. A árvore Rubro-Negra utiliza cores, rotações e regras específicas para garantir que sua altura permaneça proporcional ao logaritmo do número de elementos.

Os testes automatizados ajudam a verificar se as operações preservam as propriedades necessárias para o funcionamento correto das estruturas.

## 10. Análise comparativa experimental

### 10.1. Metodologia

Foram comparadas as árvores AVL e Rubro-Negra utilizando os mesmos conjuntos de dados e as mesmas sequências de operações. Foram utilizados três cenários de inserção, cada um com dez valores: crescente, decrescente e variado.

Após as inserções, foram registradas a altura das árvores e a quantidade de rotações realizadas. Em seguida, os mesmos elementos foram removidos na mesma ordem nas duas estruturas, registrando-se o total acumulado de rotações e verificando-se a validade das árvores após cada operação.

### 10.2. Resultados

| Sequência | Estrutura | Altura após inserções | Rotações na inserção | Rotações na remoção | Total |
|---|---|---:|---:|---:|---:|
| Crescente | AVL | 4 | 6 | 3 | 9 |
| Crescente | Rubro-Negra | 5 | 5 | 3 | 8 |
| Decrescente | AVL | 4 | 6 | 3 | 9 |
| Decrescente | Rubro-Negra | 5 | 5 | 3 | 8 |
| Variada | AVL | 4 | 3 | 1 | 4 |
| Variada | Rubro-Negra | 4 | 3 | 1 | 4 |

Após a remoção de todos os elementos, ambas as árvores apresentaram altura zero, indicando que estavam vazias.

### 10.3. Diferenças nas estratégias de balanceamento

A árvore AVL utiliza as alturas das subárvores para manter o fator de balanceamento de cada nó entre -1 e 1. Essa exigência produz um balanceamento mais rigoroso e pode resultar em árvores menores.

A árvore Rubro-Negra utiliza cores, rotações e regras que limitam a altura sem exigir o mesmo grau de equilíbrio local da AVL. Isso permite que a árvore tenha uma altura ligeiramente maior, mas pode reduzir a quantidade de rotações necessárias em determinadas sequências de operações.

### 10.4. Interpretação dos resultados

Nas sequências crescentes e decrescentes, a AVL apresentou altura 4, enquanto a Rubro-Negra apresentou altura 5. A AVL também realizou seis rotações durante as inserções, contra cinco da Rubro-Negra. Durante as remoções, ambas realizaram três rotações.

Na sequência variada, as duas estruturas apresentaram altura 4, três rotações durante as inserções e uma durante as remoções. Portanto, nesse cenário, não houve diferença nessas métricas.

Os resultados sugerem que a AVL pode manter uma árvore mais compacta em determinados conjuntos de dados, enquanto a Rubro-Negra pode realizar menos rotações em algumas sequências. Entretanto, os experimentos utilizaram apenas dez elementos por cenário e não mediram diretamente o tempo de execução. Assim, não é possível afirmar que uma estrutura será sempre superior à outra.

### 10.5. Vantagens, limitações e aplicações

A AVL é uma opção interessante para sistemas em que as buscas são muito frequentes e as alterações são relativamente menos frequentes, pois seu balanceamento rigoroso pode favorecer buscas eficientes.

A Rubro-Negra pode ser vantajosa em sistemas que realizam inserções e remoções frequentes, pois sua estratégia de balanceamento admite maior flexibilidade. Ainda assim, o custo real depende da distribuição dos dados e do perfil de operações.

Para um sistema de logística, como o cenário proposto, a escolha deve considerar a frequência de consultas, inserções e remoções, além dos requisitos de desempenho. Os experimentos realizados não são suficientes para determinar uma vencedora universal. Uma avaliação mais completa exigiria conjuntos maiores, mais sequências e medições de tempo de execução.

### 10.6. Conclusão

Os testes demonstraram que ambas as implementações mantiveram suas propriedades de balanceamento nos cenários avaliados. A AVL apresentou menor altura nas sequências ordenadas, enquanto a Rubro-Negra realizou uma rotação a menos durante as inserções desses cenários. Na sequência variada, as métricas observadas foram iguais.

Portanto, os resultados reforçam que a escolha entre AVL e Rubro-Negra deve considerar o padrão de utilização do sistema. A teoria ajuda a explicar as diferenças observadas, mas experimentos maiores são necessários para fundamentar uma recomendação específica para o sistema de logística.
