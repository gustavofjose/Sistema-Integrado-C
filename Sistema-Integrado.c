#include <stdio.h>

#define SALDO_INICIAL 1000
#define TOTAL_NOTAS 5
#define MAX_HISTORICO 1000
#define ARQUIVO_HISTORICO "historico_saques.txt"

#define SAQUE_VALIDO 0
#define VALOR_INVALIDO 1
#define VALOR_NAO_MULTIPLO 2
#define SALDO_INSUFICIENTE 3

/* Representa um saque registrado no historico. */
struct Saque {
    int numero; /* ordem em que o saque foi feito */
    int valor;
};

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
int carregar_historico(struct Saque saques[], int limite);
void ordenar_saques(struct Saque saques[], int quantidade);
int particionar(struct Saque saques[], int inicio, int fim);
void quick_sort(struct Saque saques[], int inicio, int fim);
int somar_saques_recursivo(const struct Saque saques[], int quantidade);
void exibir_saque(const struct Saque *saque);
void realizar_saque(int *saldo, const int notas[], int total_notas);
void consultar_historico(int usar_quick_sort);
void consultar_total_saques(void);
void exibir_menu(void);

int main(void) {
    int opcao = -1;
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
                printf("\nSaldo disponivel: R$ %d\n", saldo);
                break;

            case 2:
                realizar_saque(&saldo, notas, TOTAL_NOTAS);
                break;

            case 3:
                consultar_historico(0);
                break;

            case 4:
                consultar_total_saques();
                break;

            case 5:
                consultar_historico(1);
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

/* Le os saques registrados e armazena em um vetor de structs. */
int carregar_historico(struct Saque saques[], int limite) {
    FILE *arquivo = fopen(ARQUIVO_HISTORICO, "r");
    int quantidade = 0;
    int valor;

    if (arquivo == NULL) {
        return 0;
    }

    while (quantidade < limite && fscanf(arquivo, "%d", &valor) == 1) {

        if (valor > 0) {
            saques[quantidade].numero = quantidade + 1;
            saques[quantidade].valor = valor;
            quantidade++;
        }
    }

    fclose(arquivo);
    return quantidade;
}

/* Ordena os saques do menor para o maior usando Bubble Sort. */
void ordenar_saques(struct Saque saques[], int quantidade) {
    struct Saque temporario;
    int trocou;

    for (int i = 0; i < quantidade - 1; i++) {
        trocou = 0;

        for (int j = 0; j < quantidade - 1 - i; j++) {

            if (saques[j].valor > saques[j + 1].valor) {
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

/* Separa o vetor: menores que o pivo a esquerda, maiores a direita. */
int particionar(struct Saque saques[], int inicio, int fim) {
    int pivo = saques[fim].valor;
    int i = inicio - 1;
    struct Saque temporario;

    for (int j = inicio; j < fim; j++) {
        if (saques[j].valor <= pivo) {
            i++;
            temporario = saques[i];
            saques[i] = saques[j];
            saques[j] = temporario;
        }
    }

    temporario = saques[i + 1];
    saques[i + 1] = saques[fim];
    saques[fim] = temporario;

    return i + 1;
}

/* Ordena os saques do menor para o maior usando Quick Sort. */
void quick_sort(struct Saque saques[], int inicio, int fim) {

    /* Caso base: trecho com 0 ou 1 elemento ja esta ordenado. */
    if (inicio >= fim) {
        return;
    }

    int posicao_pivo = particionar(saques, inicio, fim);

    quick_sort(saques, inicio, posicao_pivo - 1);
    quick_sort(saques, posicao_pivo + 1, fim);
}

/* Soma os saques utilizando recursividade. */
int somar_saques_recursivo(const struct Saque saques[], int quantidade) {

    /* Caso base: nao existem mais valores para somar. */
    if (quantidade <= 0) {
        return 0;
    }

    /* Soma o ultimo valor e chama a propria funcao novamente. */
    return saques[quantidade - 1].valor +
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

/* Mostra um saque acessando a struct por ponteiro. */
void exibir_saque(const struct Saque *saque) {
    printf("Saque n. %d: R$ %d\n", saque->numero, saque->valor);
}

/* Consulta e apresenta o historico ordenado. */
void consultar_historico(int usar_quick_sort) {
    struct Saque saques[MAX_HISTORICO];
    int quantidade = carregar_historico(saques, MAX_HISTORICO);

    if (quantidade == 0) {
        printf("Ainda nao ha saques registrados.\n");
        return;
    }

    if (usar_quick_sort) {
        quick_sort(saques, 0, quantidade - 1);
        printf("\n=== HISTORICO ORDENADO (QUICK SORT) ===\n");
    }
    else {
        ordenar_saques(saques, quantidade);
        printf("\n=== HISTORICO ORDENADO (BUBBLE SORT) ===\n");
    }

    for (int i = 0; i < quantidade; i++) {
        exibir_saque(&saques[i]);
    }

    if (quantidade == MAX_HISTORICO) {
        printf("Aviso: exibidos no maximo %d registros.\n",
               MAX_HISTORICO);
    }
}

/* Consulta a quantidade e o total dos saques registrados. */
void consultar_total_saques(void) {
    struct Saque saques[MAX_HISTORICO];
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
    printf("1 - Ver saldo\n");
    printf("2 - Realizar saque\n");
    printf("3 - Consultar historico ordenado (Bubble Sort)\n");
    printf("4 - Consultar total sacado (recursividade)\n");
    printf("5 - Consultar historico ordenado (Quick Sort)\n");
    printf("0 - Sair\n");
}
