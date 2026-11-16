
# Relatório Técnico — Sistema de Caixa Eletrônico

## 1. Introdução

Este trabalho consiste no desenvolvimento de um sistema simples de caixa eletrônico utilizando a linguagem C. A proposta é simular algumas operações que existem em um caixa eletrônico, principalmente a realização de saques e a consulta das operações feitas.

O sistema foi desenvolvido como atividade acadêmica para praticar os conteúdos estudados durante as aulas. Durante a implementação, foram utilizados conceitos como funções, vetores, ponteiros, estruturas de repetição, validação de dados e manipulação de arquivos.

## 2. Objetivo do trabalho

O principal objetivo foi criar um programa que consiga receber um valor de saque, verificar se a operação pode ser realizada e apresentar quais cédulas serão entregues.

Além disso, foram adicionadas opções para consultar o histórico de saques e calcular o total retirado. Dessa forma, o trabalho também permite aplicar conceitos de ordenação, recursividade e armazenamento de informações em arquivos.

## 3. Funcionamento do sistema

Quando o programa é iniciado, o saldo começa em R$ 1.000,00 e um menu é apresentado ao usuário. Pelo menu, é possível escolher entre ver o saldo, realizar um saque, consultar o histórico, consultar o total sacado, consultar o histórico ordenado com Quick Sort ou encerrar o programa.

Na opção de saque, o usuário informa o valor desejado. O sistema verifica se o valor é positivo, se é múltiplo de cinco e se não ultrapassa o saldo disponível. Caso alguma dessas condições não seja atendida, uma mensagem informa que o saque não pode ser realizado.

Quando o valor é válido, o programa calcula a quantidade de cédulas necessárias, registra o saque no arquivo de histórico e atualiza o saldo.

## 4. Distribuição das cédulas

Para entregar o valor solicitado, o programa utiliza as cédulas de R$ 100, R$ 50, R$ 20, R$ 10 e R$ 5. O cálculo começa pela maior cédula e continua com as menores até completar o valor do saque.

Por exemplo, em um saque de R$ 285,00, a distribuição será:

- 2 cédulas de R$ 100,00;
- 1 cédula de R$ 50,00;
- 1 cédula de R$ 20,00;
- 1 cédula de R$ 10,00;
- 1 cédula de R$ 5,00.

Com essa estratégia, o sistema consegue formar o valor utilizando a menor quantidade de cédulas para as denominações disponíveis.

## 5. Organização do código

O código foi separado em funções para deixar cada parte do programa responsável por uma tarefa. Entre as principais funções estão:

- `ler_inteiro`: recebe e verifica a entrada numérica do usuário;
- `validar_saque`: confere se o saque atende às condições necessárias;
- `calcular_notas`: calcula a quantidade de cada cédula;
- `exibir_notas`: mostra a distribuição das cédulas;
- `atualizar_saldo`: realiza a atualização do saldo;
- `salvar_saque`: registra um saque aprovado no arquivo;
- `carregar_historico`: recupera os valores que já foram registrados;
- `ordenar_saques`: organiza os valores do histórico com Bubble Sort;
- `quick_sort` e `particionar`: organizam os valores do histórico com Quick Sort;
- `trocar`: troca dois saques de lugar recebendo ponteiros para as structs;
- `exibir_saque`: mostra um saque recebendo um ponteiro para a struct;
- `somar_saques_recursivo`: calcula o total dos saques usando recursividade.

Essa divisão ajuda a entender o código e facilita a manutenção, pois cada função possui uma responsabilidade principal.

## 6. Conteúdos da linguagem C utilizados

Durante o desenvolvimento foram aplicados diferentes conteúdos estudados na disciplina:

- **Condicionais:** utilizadas para verificar se o saque pode ser realizado.
- **Laços de repetição:** utilizados no menu e nos cálculos das cédulas.
- **Vetores:** utilizados para guardar a quantidade de cada tipo de cédula e os valores do histórico.
- **Funções:** utilizadas para separar as tarefas do programa.
- **Structs:** cada saque do histórico é guardado em uma `struct Saque`, com número e valor.
- **Ponteiros:** utilizados para atualizar o saldo por referência e para acessar a struct com o operador `->`.
- **Manipulação de arquivos:** utilizada para salvar e recuperar o histórico de saques.

## 7. Ordenação e recursividade

Para organizar os valores apresentados na consulta do histórico, foi utilizado o algoritmo Bubble Sort. Ele compara os valores próximos e realiza trocas quando necessário, repetindo esse processo até que a lista esteja ordenada.

Também foi implementado o Quick Sort, disponível na opção 5 do menu. Ele escolhe o último elemento como pivô, coloca os valores menores à esquerda e os maiores à direita e depois chama a si mesmo para ordenar cada lado. Enquanto o Bubble Sort tem complexidade O(n²), o Quick Sort tem, em média, O(n log n).

Também foi utilizada a recursividade no cálculo do total sacado. Nesse caso, a função soma um valor do histórico e chama a si mesma para processar os próximos valores. A condição de parada acontece quando todos os registros foram considerados.

Uma diferença entre os dois algoritmos aparece quando há saques com o mesmo valor: o Bubble Sort é estável e mantém esses saques na ordem em que foram feitos, enquanto o Quick Sort não é estável e pode mostrá-los em outra ordem (por exemplo, "Saque n. 3" antes de "Saque n. 1", ambos de R$ 50). Os valores ficam ordenados do mesmo jeito; só muda a ordem entre os empates.

Essas partes foram incluídas para praticar os conteúdos de algoritmos trabalhados durante as aulas.

## 8. Armazenamento do histórico

O histórico é armazenado no arquivo `historico_saques.txt`. Quando um saque é aprovado, seu valor é acrescentado ao arquivo. Na consulta, o programa lê os registros salvos para apresentar as informações e calcular o total.

O histórico continua disponível após fechar e abrir o programa novamente, porque fica guardado no arquivo. Porém, o saldo não é salvo: a cada nova execução, ele começa novamente em R$ 1.000,00. Essa é uma limitação da versão atual do trabalho.

## 9. Testes realizados

Foram considerados os seguintes valores para verificar as validações do sistema:

| Valor informado | Resultado esperado | Motivo |
|---:|---|---|
| R$ 50,00 | Saque permitido | Valor positivo, múltiplo de 5 e dentro do saldo |
| R$ 95,00 | Saque permitido | Valor positivo, múltiplo de 5 e dentro do saldo |
| R$ 123,00 | Saque recusado | Não é múltiplo de 5 |
| R$ 1.005,00 | Saque recusado | Valor maior que o saldo inicial |

Cada teste foi feito em uma execução nova do programa (saldo inicial de R$ 1.000,00), escolhendo a opção 2 do menu.

### Teste 1 — R$ 50 (válido)

```text
Saldo disponivel nesta sessao: R$ 1000
Digite o valor do saque: 50

Notas entregues:
1 nota(s) de R$ 50

Saque realizado com sucesso.
Saldo restante nesta sessao: R$ 950
```

Análise: o valor é múltiplo de 5 e cabe no saldo. Uma única nota de 50 resolve o saque.

### Teste 2 — R$ 95 (válido)

```text
Saldo disponivel nesta sessao: R$ 1000
Digite o valor do saque: 95

Notas entregues:
1 nota(s) de R$ 50
2 nota(s) de R$ 20
1 nota(s) de R$ 5

Saque realizado com sucesso.
Saldo restante nesta sessao: R$ 905
```

Análise: 95 / 100 = 0 (resto 95); 95 / 50 = 1 (resto 45); 45 / 20 = 2 (resto 5); 5 / 10 = 0 (resto 5); 5 / 5 = 1 (resto 0). As notas com quantidade zero (100 e 10) não são exibidas.

### Teste 3 — R$ 123 (inválido)

```text
Saldo disponivel nesta sessao: R$ 1000
Digite o valor do saque: 123
Erro: o valor deve ser multiplo de 5.
```

Análise: 123 % 5 = 3, então não é possível formar o valor com as cédulas disponíveis. O saque é recusado, o saldo não muda e nada é gravado no histórico.

### Teste 4 — R$ 1005 (inválido)

```text
Saldo disponivel nesta sessao: R$ 1000
Digite o valor do saque: 1005
Erro: saldo insuficiente.
```

Análise: 1005 é múltiplo de 5, mas é maior que o saldo de R$ 1.000,00. O saque é recusado, o saldo não muda e nada é gravado no histórico.

Também é importante verificar se o histórico é salvo corretamente e se as opções de consulta apresentam os valores registrados.

## 10. Limitações atuais

O programa atende às operações propostas, mas ainda pode receber melhorias. Atualmente, o saldo volta para R$ 1.000,00 quando o programa é iniciado novamente, mesmo que exista um histórico de saques salvo. O sistema também trabalha com um limite máximo de registros carregados para o histórico.

Como melhoria futura, seria possível salvar o saldo em arquivo e desenvolver outras operações, como depósito e consulta de extrato mais detalhado.

## 11. Conclusão

A realização deste trabalho ajudou a colocar em prática os conteúdos estudados em linguagem C. Durante o desenvolvimento, foi possível trabalhar com funções, vetores, ponteiros, structs e arquivos, além de aplicar Bubble Sort, Quick Sort e recursividade.

Também foi importante pensar nas validações para evitar que o programa aceitasse valores incorretos. O resultado foi um sistema simples, mas que reúne diferentes conceitos da programação e permite entender melhor como eles podem ser utilizados em um projeto.

---

**Trabalho acadêmico — Ciência da Computação | UNICID**
