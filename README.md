# Sistema de Caixa Eletrônico em C

Projeto acadêmico desenvolvido em linguagem C, com o objetivo de simular o funcionamento de um caixa eletrônico, aplicando conceitos fundamentais de programação, lógica computacional, modularização, manipulação de arquivos, ponteiros, ordenação e recursividade.

## Sobre o projeto

O Sistema de Caixa Eletrônico é uma aplicação em terminal que permite realizar operações de saque, consultar o histórico de transações e verificar o valor total sacado.

O sistema trabalha com um saldo inicial de **R$ 1.000,00** e utiliza um algoritmo de distribuição de cédulas para entregar o valor solicitado com a menor quantidade possível de notas, considerando as denominações disponíveis.

Além das operações principais, o projeto foi desenvolvido para colocar em prática conteúdos estudados durante a graduação, demonstrando como diferentes conceitos da linguagem C podem ser aplicados em um sistema funcional.

## Objetivos

- Desenvolver um sistema de caixa eletrônico utilizando linguagem C.
- Aplicar estruturas condicionais, repetição e funções.
- Trabalhar com ponteiros e passagem de parâmetros por referência.
- Implementar validações para garantir a segurança das operações.
- Utilizar arquivos para armazenar o histórico de saques.
- Aplicar o algoritmo Bubble Sort para organizar os registros.
- Utilizar recursividade para calcular o total de saques realizados.

## Funcionalidades

### 1. Realizar saque

Permite que o usuário informe o valor que deseja retirar da conta.

Antes de concluir a operação, o sistema verifica se:

- O valor informado é maior que zero.
- O valor é múltiplo de R$ 5,00.
- O saldo disponível é suficiente para realizar o saque.

Se todas as condições forem atendidas, o sistema calcula a distribuição das cédulas, registra a operação e atualiza o saldo disponível.

### 2. Distribuição de cédulas

O sistema utiliza uma estratégia de distribuição que prioriza as maiores denominações disponíveis, buscando entregar o valor solicitado com a menor quantidade de cédulas.

As notas utilizadas são:

| Cédula | Valor |
|---|---:|
| R$ 100 | R$ 100,00 |
| R$ 50 | R$ 50,00 |
| R$ 20 | R$ 20,00 |
| R$ 10 | R$ 10,00 |
| R$ 5 | R$ 5,00 |

**Exemplo de saque:**

Para um saque de R$ 285,00, o sistema realiza a seguinte distribuição:

- 2 cédulas de R$ 100,00.
- 1 cédula de R$ 50,00.
- 1 cédula de R$ 20,00.
- 1 cédula de R$ 10,00.
- 1 cédula de R$ 5,00.

Total: 6 cédulas.

### 3. Histórico de saques

As operações aprovadas são armazenadas no arquivo `historico_saques.txt`.

Essa funcionalidade utiliza manipulação de arquivos para registrar os valores sacados e permitir que o histórico seja recuperado mesmo depois que o programa for encerrado.

O sistema também permite consultar os registros armazenados.

### 4. Ordenação com Bubble Sort

O histórico de saques pode ser organizado utilizando o algoritmo Bubble Sort.

O algoritmo compara os valores registrados e realiza trocas entre eles até obter a organização desejada.

Essa implementação permite aplicar conceitos de ordenação e compreender o funcionamento de um algoritmo clássico.

### 5. Consulta do total sacado

O sistema possui uma funcionalidade que calcula o valor acumulado de todos os saques registrados.

Para realizar esse cálculo, é utilizada a técnica de recursividade, na qual uma função chama a si mesma até atingir uma condição de parada.

## Como o sistema funciona

O funcionamento segue uma sequência de etapas:

1. O programa é iniciado com saldo de R$ 1.000,00.
2. O sistema apresenta um menu de opções.
3. O usuário escolhe a operação desejada.
4. Caso escolha realizar um saque, informa o valor.
5. O programa valida as informações fornecidas.
6. Se o saque for aprovado, calcula as cédulas necessárias.
7. O valor é registrado no histórico e descontado do saldo.
8. O usuário pode consultar o histórico ou o total sacado.
9. Ao escolher sair, o programa é encerrado.

## Tecnologias e conceitos utilizados

| Tecnologia ou conceito | Aplicação no projeto |
|---|---|
| Linguagem C | Desenvolvimento da aplicação |
| `stdio.h` | Entrada e saída de dados |
| Funções | Organização e divisão das responsabilidades |
| Estruturas condicionais | Validação das operações |
| Laços de repetição | Processamento e navegação pelo menu |
| Vetores | Armazenamento da quantidade de cédulas |
| Ponteiros | Atualização do saldo por referência |
| Manipulação de arquivos | Persistência do histórico de saques |
| Bubble Sort | Ordenação dos registros |
| Recursividade | Cálculo do total sacado |

## Estrutura do projeto

```text
Sistema-Caixa-Eletronico/
│
├── src/
│   └── main.c
│
├── docs/
│   ├── pseudocodigo.md
│   └── testes.md
│
├── .gitignore
└── README.md
```

### Descrição dos arquivos

- `src/main.c`: contém o código-fonte principal do sistema.
- `docs/pseudocodigo.md`: apresenta a lógica do funcionamento do programa em pseudocódigo.
- `docs/testes.md`: documenta os testes realizados e os resultados esperados.
- `.gitignore`: define os arquivos que não devem ser enviados ao repositório.
- `README.md`: apresenta a documentação geral do projeto.

## Como executar o projeto

### Pré-requisitos

Para executar o sistema, é necessário ter um compilador C instalado, como o GCC.

### 1. Clonar o repositório

```bash
git clone https://github.com/gustavofjose/Sistema-Caixa-Eletronico.git
```

### 2. Acessar a pasta

```bash
cd Sistema-Caixa-Eletronico
```

### 3. Compilar o programa

```bash
gcc src/main.c -o caixa_eletronico
```

### 4. Executar

No Windows:

```bash
caixa_eletronico.exe
```

No Linux ou macOS:

```bash
./caixa_eletronico
```

## Observações importantes

- O saldo inicial é de R$ 1.000,00 e é reiniciado sempre que o programa é executado novamente.
- O histórico de saques permanece salvo no arquivo `historico_saques.txt`.
- O arquivo de histórico é criado automaticamente quando ocorre o primeiro saque aprovado.
- A ordenação é aplicada aos registros durante a consulta, sem alterar a ordem original dos dados armazenados no arquivo.

## Aprendizados

O desenvolvimento deste projeto permitiu aplicar, na prática, conceitos importantes da programação em C, principalmente na organização do código, validação de dados, utilização de ponteiros e persistência de informações.

Também possibilitou compreender melhor o funcionamento de algoritmos de ordenação e recursividade, relacionando os conteúdos estudados em aula com a construção de uma aplicação funcional.


---

Projeto desenvolvido para fins acadêmicos e de aprendizado.
