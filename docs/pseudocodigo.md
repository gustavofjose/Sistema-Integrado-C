# Pseudocódigo — Sistema de Caixa Eletrônico

## Variáveis principais

| Variável | Tipo | Uso |
|---|---|---|
| `saldo` | inteiro | saldo disponível na sessão (começa em 1000) |
| `saque` | inteiro | valor que o usuário quer sacar |
| `notas[5]` | vetor de inteiros | cédulas disponíveis: 100, 50, 20, 10, 5 |
| `quantidades[5]` | vetor de inteiros | contador de cada cédula entregue |
| `opcao` | inteiro | opção escolhida no menu |
| `saques[]` | vetor de `Saque` (struct com número e valor) | histórico lido do arquivo |

## Algoritmo principal

```text
INICIO
    saldo <- 1000
    notas <- {100, 50, 20, 10, 5}

    REPITA
        ESCREVA menu:
            1 - Ver saldo
            2 - Realizar saque
            3 - Consultar histórico ordenado (Bubble Sort)
            4 - Consultar total sacado (recursividade)
            5 - Consultar histórico ordenado (Quick Sort)
            0 - Sair
        LEIA opcao

        ESCOLHA opcao
            CASO 1: ESCREVA "Saldo disponível: ", saldo
            CASO 2: REALIZAR_SAQUE
            CASO 3: CONSULTAR_HISTORICO usando Bubble Sort
            CASO 4: CONSULTAR_TOTAL
            CASO 5: CONSULTAR_HISTORICO usando Quick Sort
            CASO 0: ESCREVA "Sistema encerrado."
            SENAO:  ESCREVA "Opção inválida."
        FIM ESCOLHA
    ATE opcao = 0
FIM
```

## Realizar saque

```text
REALIZAR_SAQUE
    ESCREVA "Digite o valor do saque: "
    LEIA saque

    SE saque <= 0 ENTAO
        ESCREVA "Erro: o valor deve ser maior que zero."
    SENAO SE saque MOD 5 <> 0 ENTAO
        ESCREVA "Erro: o valor deve ser múltiplo de 5."
    SENAO SE saque > saldo ENTAO
        ESCREVA "Erro: saldo insuficiente."
    SENAO
        GRAVE saque no arquivo historico_saques.txt
        restante <- saque
        PARA i DE 0 ATE 4 FACA
            quantidades[i] <- restante DIV notas[i]
            restante <- restante MOD notas[i]
        FIM PARA
        ESCREVA "Notas entregues:"
        PARA i DE 0 ATE 4 FACA
            SE quantidades[i] > 0 ENTAO
                ESCREVA quantidades[i], " nota(s) de R$ ", notas[i]
            FIM SE
        FIM PARA
        saldo <- saldo - saque
        ESCREVA "Saldo restante: ", saldo
    FIM SE
FIM
```

## Consultar histórico e total

```text
CONSULTAR_HISTORICO
    LEIA todos os valores do arquivo para o vetor saques
    SE não há saques ENTAO
        ESCREVA "Ainda não há saques registrados."
    SENAO
        ORDENE saques por valor (Bubble Sort ou Quick Sort)
        PARA cada saque FACA
            ESCREVA número e valor do saque
        FIM PARA
    FIM SE
FIM

CONSULTAR_TOTAL
    LEIA todos os valores do arquivo para o vetor saques
    ESCREVA quantidade de saques
    ESCREVA SOMAR(saques, quantidade)
FIM

SOMAR(saques, n)            // recursiva
    SE n = 0 ENTAO RETORNE 0
    RETORNE saques[n-1].valor + SOMAR(saques, n-1)
FIM

QUICK_SORT(saques, inicio, fim)      // recursiva
    SE inicio >= fim ENTAO RETORNE
    p <- PARTICIONAR(saques, inicio, fim)   // pivô = último elemento
    QUICK_SORT(saques, inicio, p-1)
    QUICK_SORT(saques, p+1, fim)
FIM
```
