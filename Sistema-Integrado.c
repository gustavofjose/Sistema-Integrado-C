#include <stdio.h>

#define SALDO_INICIAL 1000
#define TOTAL_NOTAS 5
#define MAX_HISTORICO 1000
#define ARQUIVO_HISTORICO "historico_saques.txt"

#define SAQUE_VALIDO 0
#define VALOR_INVALIDO 1
#define VALOR_NAO_MULTIPLO 2
#define SALDO_INSUFICIENTE 3

/* Prototipos das funcoes */
int ler_inteiro(const char mensagem[], int *valor);
int validar_saque(int saque, int saldo);
void calcular_notas(int saque, const int notas[],
                    int quantidades[], int total_notas);
void exibir_notas(const int notas[], const int quantidades[],
                  int total_notas);
void atualizar_saldo(int *saldo, int saque);
void exibir_erro(int status);
int salvar_saque(int saque);
int carregar_historico(int saques[], int limite);
void ordenar_saques(int saques[], int quantidade);
int somar_saques_recursivo(const int saques[], int quantidade);
void realizar_saque(int *saldo, const int notas[], int total_notas);
void consultar_historico(void);
void consultar_total_saques(void);
void exibir_menu(void);

int main(void) {
    int opcao;
    int saldo = SALDO_INICIAL;
    const int notas[TOTAL_NOTAS] = {100, 50, 20, 10, 5};

    printf("=== SISTEMA DE CAIXA ELETRONICO ===\n");

    do {
        exibir_menu();

        int leitura = ler_inteiro("Escolha uma opcao: ", &opcao);

        if (leitura == -1) {
            printf("\nEncerrando o sistema.\n");
            break;
        }

        if (leitura == 0) {
            printf("Entrada invalida. Digite uma opcao numerica.\n\n");
            continue;
        }

        switch (opcao) {
            case 1:
                realizar_saque(&saldo, notas, TOTAL_NOTAS);
                break;

            case 2:
                consultar_historico();
                break;

            case 3:
                consultar_total_saques();
                break;

            case 0:
                printf("Sistema encerrado.\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

        printf("\n");

    } while (opcao != 0);

    return 0;
}

/* Le um numero inteiro e limpa o restante da entrada. */
int ler_inteiro(const char mensagem[], int *valor) {
    int resultado;
    int caractere;

    printf("%s", mensagem);
    resultado = scanf("%d", valor);

    if (resultado == EOF) {
        return -1;
    }

    if (resultado != 1) {
        while ((caractere = getchar()) != '\n' && caractere != EOF) {
            /* Limpa a entrada invalida. */
        }
        return 0;
    }

    while ((caractere = getchar()) != '\n' && caractere != EOF) {
        /* Descarta caracteres extras da mesma linha. */
    }

    return 1;
}

/* Verifica se o valor do saque atende as regras. */
int validar_saque(int saque, int saldo) {
    if (saque <= 0) {
        return VALOR_INVALIDO;
    }

    if (saque % 5 != 0) {
        return VALOR_NAO_MULTIPLO;
    }

    if (saque > saldo) {
        return SALDO_INSUFICIENTE;
    }

    return SAQUE_VALIDO;
}

/* Calcula a quantidade de cada cedula usando divisao e modulo. */
void calcular_notas(int saque, const int notas[],
                    int quantidades[], int total_notas) {
    int restante = saque;

    for (int i = 0; i < total_notas; i++) {
        quantidades[i] = restante / notas[i];
        restante = restante % notas[i];
    }
}

/* Mostra as cedulas utilizadas no saque. */
void exibir_notas(const int notas[], const int quantidades[],
                  int total_notas) {
    printf("\nNotas entregues:\n");

    for (int i = 0; i < total_notas; i++) {
        if (quantidades[i] > 0) {
            printf("%d nota(s) de R$ %d\n",
                   quantidades[i], notas[i]);
        }
    }
}

/* Atualiza o saldo original por meio de um ponteiro. */
void atualizar_saldo(int *saldo, int saque) {
    if (saldo != NULL) {
        *saldo = *saldo - saque;
    }
}

/* Exibe a mensagem correspondente ao erro. */
void exibir_erro(int status) {
    if (status == VALOR_INVALIDO) {
        printf("Erro: o valor deve ser maior que zero.\n");
    }
    else if (status == VALOR_NAO_MULTIPLO) {
        printf("Erro: o valor deve ser multiplo de 5.\n");
    }
    else if (status == SALDO_INSUFICIENTE) {
        printf("Erro: saldo insuficiente.\n");
    }
}

/* Salva o saque aprovado no arquivo de texto. */
int salvar_saque(int saque) {
    FILE *arquivo = fopen(ARQUIVO_HISTORICO, "a");
    int sucesso;

    if (arquivo == NULL) {
        printf("Erro: nao foi possivel abrir o arquivo de historico.\n");
        return 0;
    }

    sucesso = (fprintf(arquivo, "%d\n", saque) >= 0);

    if (fclose(arquivo) != 0) {
        sucesso = 0;
    }

    return sucesso;
}

/* Le os saques registrados e armazena os valores em um vetor. */
int carregar_historico(int saques[], int limite) {
    FILE *arquivo = fopen(ARQUIVO_HISTORICO, "r");
    int quantidade = 0;

    if (arquivo == NULL) {
        return 0;
    }

    while (quantidade < limite &&
           fscanf(arquivo, "%d", &saques[quantidade]) == 1) {

        if (saques[quantidade] > 0) {
            quantidade++;
        }
    }

    fclose(arquivo);
    return quantidade;
}

/* Ordena os saques do menor para o maior usando Bubble Sort. */
void ordenar_saques(int saques[], int quantidade) {
    int temporario;
    int trocou;

    for (int i = 0; i < quantidade - 1; i++) {
        trocou = 0;

        for (int j = 0; j < quantidade - 1 - i; j++) {

            if (saques[j] > saques[j + 1]) {
                temporario = saques[j];
                saques[j] = saques[j + 1];
                saques[j + 1] = temporario;

                trocou = 1;
            }
        }

        if (trocou == 0) {
            break;
        }
    }
}

/* Soma os saques utilizando recursividade. */
int somar_saques_recursivo(const int saques[], int quantidade) {

    /* Caso base: nao existem mais valores para somar. */
    if (quantidade <= 0) {
        return 0;
    }

    /* Soma o ultimo valor e chama a propria funcao novamente. */
    return saques[quantidade - 1] +
           somar_saques_recursivo(saques, quantidade - 1);
}

/* Executa todas as etapas de um saque. */
void realizar_saque(int *saldo, const int notas[], int total_notas) {
    int saque;
    int quantidades[TOTAL_NOTAS] = {0};
    int status;
    int leitura;

    printf("\nSaldo disponivel nesta sessao: R$ %d\n", *saldo);

    leitura = ler_inteiro("Digite o valor do saque: ", &saque);

    if (leitura == -1) {
        printf("Entrada encerrada.\n");
        return;
    }

    if (leitura == 0) {
        printf("Erro: digite um valor inteiro.\n");
        return;
    }

    status = validar_saque(saque, *saldo);

    if (status != SAQUE_VALIDO) {
        exibir_erro(status);
        return;
    }

    /* Registra o saque antes de confirmar a operacao. */
    if (!salvar_saque(saque)) {
        printf("Saque cancelado: nao foi possivel registrar a operacao.\n");
        return;
    }

    calcular_notas(saque, notas, quantidades, total_notas);

    exibir_notas(notas, quantidades, total_notas);

    atualizar_saldo(saldo, saque);

    printf("\nSaque realizado com sucesso.\n");
    printf("Saldo restante nesta sessao: R$ %d\n", *saldo);
}

/* Consulta e apresenta o historico ordenado. */
void consultar_historico(void) {
    int saques[MAX_HISTORICO];
    int quantidade = carregar_historico(saques, MAX_HISTORICO);

    if (quantidade == 0) {
        printf("Ainda nao ha saques registrados.\n");
        return;
    }

    ordenar_saques(saques, quantidade);

    printf("\n=== HISTORICO DE SAQUES (ORDEM CRESCENTE) ===\n");

    for (int i = 0; i < quantidade; i++) {
        printf("Saque %d: R$ %d\n", i + 1, saques[i]);
    }

    if (quantidade == MAX_HISTORICO) {
        printf("Aviso: exibidos no maximo %d registros.\n",
               MAX_HISTORICO);
    }
}

/* Consulta a quantidade e o total dos saques registrados. */
void consultar_total_saques(void) {
    int saques[MAX_HISTORICO];
    int quantidade = carregar_historico(saques, MAX_HISTORICO);

    if (quantidade == 0) {
        printf("Ainda nao ha saques registrados.\n");
        return;
    }

    printf("\n=== RESUMO DO HISTORICO ===\n");

    printf("Quantidade de saques registrados: %d\n", quantidade);

    printf("Total sacado: R$ %d\n",
           somar_saques_recursivo(saques, quantidade));

    if (quantidade == MAX_HISTORICO) {
        printf("Aviso: resumo calculado com no maximo %d registros.\n",
               MAX_HISTORICO);
    }
}

/* Apresenta as opcoes disponiveis no sistema. */
void exibir_menu(void) {
    printf("----- MENU -----\n");
    printf("1 - Realizar saque\n");
    printf("2 - Consultar historico de saques (ordenado)\n");
    printf("3 - Consultar total sacado (recursividade)\n");
    printf("0 - Sair\n");
}
