
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

#define TAM_MAX_PALAVRA 15
#define TAM_LINHA 128
#define ALT 16
#define LARG 16
#define QUANTIDADE_SEQUENCIAS 4

// ========================================
// VARIAVEIS GERAIS
// ========================================

int saldo = 1000;

typedef enum {
    SEQUENCIA_PA,
    SEQUENCIA_PG,
    SEQUENCIA_FIBONACCI,
    SEQUENCIA_PRIMOS
} TipoSequencia;

const char *nomesSequencias[4] = {
    "PA (a1=5, r=3)",
    "PG (a1=2, q=2)",
    "Fibonacci (F1=1, F2=1)",
    "Primos (a partir de 2)"
};

// ========================================
// LEITURA DE INTEIROS
// ========================================

int lerInteiro(const char *mensagem, int *valor) {
    char linha[TAM_LINHA];
    char *fim;
    long numero;

    printf("%s", mensagem);

    if (fgets(linha, sizeof(linha), stdin) == NULL)
        return 0;

    errno = 0;
    numero = strtol(linha, &fim, 10);

    if (fim == linha || errno == ERANGE ||
        numero < INT_MIN || numero > INT_MAX) {
        return 0;
    }

    while (*fim != '\0' && isspace((unsigned char)*fim))
        fim++;

    if (*fim != '\0')
        return 0;

    *valor = (int)numero;
    return 1;
}

// ========================================
// MODULO 1 - CRIPTOGRAFIA
// ========================================

int normalizarShift(int shift) {
    int deslocamento = shift % 26;

    if (deslocamento < 0)
        deslocamento += 26;

    return deslocamento;
}

int ehPrimo(int numero) {
    int divisor;

    if (numero < 2)
        return 0;

    for (divisor = 2; divisor * divisor <= numero; divisor++) {
        if (numero % divisor == 0)
            return 0;
    }

    return 1;
}

void gerarTermos(TipoSequencia tipo, int quantidade, int termos[]) {
    int i;

    switch (tipo) {

        case SEQUENCIA_PA:
            for (i = 0; i < quantidade; i++)
                termos[i] = 5 + 3 * i;
            break;

        case SEQUENCIA_PG: {
            int termo = 2;

            for (i = 0; i < quantidade; i++) {
                termos[i] = termo;
                termo *= 2;
            }
            break;
        }

        case SEQUENCIA_FIBONACCI:
            if (quantidade > 0)
                termos[0] = 1;

            if (quantidade > 1)
                termos[1] = 1;

            for (i = 2; i < quantidade; i++)
                termos[i] = termos[i - 1] + termos[i - 2];
            break;

        case SEQUENCIA_PRIMOS: {
            int candidato = 2;

            for (i = 0; i < quantidade; i++) {
                while (!ehPrimo(candidato))
                    candidato++;

                termos[i] = candidato;
                candidato++;
            }
            break;
        }
    }
}

int lerPalavra(char palavra[]) {
    char linha[TAM_LINHA];
    size_t tamanho;
    size_t i;

    while (1) {
        printf("Palavra (ate 15 letras): ");

        if (fgets(linha, sizeof(linha), stdin) == NULL)
            return 0;

        if (strchr(linha, '\n') == NULL && !feof(stdin)) {
            int c;

            while ((c = getchar()) != '\n' && c != EOF);

            printf("Entrada muito longa.\n");
            continue;
        }

        linha[strcspn(linha, "\r\n")] = '\0';
        tamanho = strlen(linha);

        if (tamanho == 0 || tamanho > TAM_MAX_PALAVRA) {
            printf("Informe de 1 a 15 letras.\n");
            continue;
        }

        for (i = 0; i < tamanho; i++) {
            if (linha[i] >= 'A' && linha[i] <= 'Z')
                linha[i] = (char)(linha[i] - 'A' + 'a');

            else if (linha[i] < 'a' || linha[i] > 'z')
                break;
        }

        if (i != tamanho) {
            printf("Use somente letras de A a Z.\n");
            continue;
        }

        strcpy(palavra, linha);
        return 1;
    }
}

void aplicarCesar(const char palavra[], int shift, char resultado[]) {
    int deslocamento = normalizarShift(shift);
    int i;

    for (i = 0; palavra[i] != '\0'; i++) {
        int letra = palavra[i] - 'a';

        resultado[i] =
            (char)('a' + (letra + deslocamento) % 26);
    }

    resultado[i] = '\0';
}

void aplicarSequencia(
    const char palavra[],
    const int termos[],
    int quantidade,
    char resultado[]
) {
    int i;

    for (i = 0; i < quantidade; i++) {
        int letra = palavra[i] - 'a';

        resultado[i] =
            (char)('a' + (letra + termos[i] % 26) % 26);
    }

    resultado[quantidade] = '\0';
}

void imprimirTermos(const int termos[], int quantidade) {
    int i;

    printf("Termos: ");

    for (i = 0; i < quantidade; i++)
        printf("%d%s", termos[i],
               i + 1 == quantidade ? "\n" : ", ");
}

void salvarResultados(
    const char palavra[],
    int shift,
    int quantidadeLetras,
    const int tipos[],
    int quantidade,
    int termos[][TAM_MAX_PALAVRA],
    char resultados[][TAM_MAX_PALAVRA + 1]
) {
    FILE *arquivo = fopen("resultado_criptografia.txt", "a");
    FILE *log = fopen("log_criptografia.txt", "a");
    int i, j;

    if (arquivo != NULL) {
        for (i = 0; i < quantidade; i++) {
            fprintf(arquivo,
                "Palavra codificada: %s | Original: %s | SHIFT: %d | Sequencia: %s | Termos: ",
                resultados[i], palavra, shift, nomesSequencias[tipos[i]]);

            for (j = 0; j < quantidadeLetras; j++)
                fprintf(arquivo, "%d%s", termos[i][j],
                    j + 1 == quantidadeLetras ? "" : ", ");

            fprintf(arquivo, " | Letras: %d\n", quantidadeLetras);
        }

        fclose(arquivo);
        printf("Resultados salvos.\n");
    } else {
        printf("Erro ao salvar resultados.\n");
    }

    if (log != NULL) {
        fprintf(log, "Palavra: %s | SHIFT: %d\n", palavra, shift);

        for (i = 0; i < quantidade; i++)
            fprintf(log, "%s | Resultado: %s\n",
                nomesSequencias[tipos[i]], resultados[i]);

        fclose(log);
    }
}

void executarCriptografia(int comparar) {
    char palavra[TAM_MAX_PALAVRA + 1];
    char palavraCesar[TAM_MAX_PALAVRA + 1];

    char resultados[4][TAM_MAX_PALAVRA + 1];

    int termos[4][TAM_MAX_PALAVRA] = {{0}};
    int tipos[4];

    int quantidadeLetras;
    int quantidade;
    int shift;
    int i;

    if (!lerPalavra(palavra))
        return;

    if (!lerInteiro("SHIFT: ", &shift)) {
        printf("SHIFT invalido.\n");
        return;
    }

    if (comparar) {
        quantidade = 4;

        for (i = 0; i < 4; i++)
            tipos[i] = i;
    } else {
        int escolha;

        printf("\n1. PA\n");
        printf("2. PG\n");
        printf("3. Fibonacci\n");
        printf("4. Primos\n");
        printf("0. Voltar\n");

        if (!lerInteiro("Escolha: ", &escolha))
            return;

        if (escolha == 0)
            return;

        if (escolha < 1 || escolha > 4) {
            printf("Opcao invalida.\n");
            return;
        }

        quantidade = 1;
        tipos[0] = escolha - 1;
    }

    quantidadeLetras = (int)strlen(palavra);

    aplicarCesar(palavra, shift, palavraCesar);

    printf("\nCamada 1 - Cesar: %s\n", palavraCesar);

    for (i = 0; i < quantidade; i++) {
        gerarTermos(
            (TipoSequencia)tipos[i],
            quantidadeLetras,
            termos[i]
        );

        aplicarSequencia(
            palavraCesar,
            termos[i],
            quantidadeLetras,
            resultados[i]
        );

        printf("\n%s\n", nomesSequencias[tipos[i]]);

        imprimirTermos(termos[i], quantidadeLetras);

        printf("Resultado final: %s\n", resultados[i]);
    }

    if (comparar)
        printf("\nA comparacao nao mede seguranca criptografica.\n");

    salvarResultados(
        palavra, shift, quantidadeLetras,
        tipos, quantidade, termos, resultados
    );
}

// ========================================
// SENHA E AUTENTICACAO
// ========================================

int criptografarSenha(const char senha[], char resultado[]) {
    int termos[TAM_MAX_PALAVRA];
    int tamanho = (int)strlen(senha);
    char cesar[TAM_MAX_PALAVRA + 1];

    if (tamanho < 1 || tamanho > TAM_MAX_PALAVRA)
        return 0;

    gerarTermos(SEQUENCIA_PA, tamanho, termos);

    aplicarCesar(senha, 3, cesar);

    aplicarSequencia(cesar, termos, tamanho, resultado);

    return 1;
}

int cadastrarSenha(void) {
    FILE *arquivo;
    char senha[TAM_MAX_PALAVRA + 1];
    char codificada[TAM_MAX_PALAVRA + 1];
    int i;

    arquivo = fopen("senha.dat", "r");

    if (arquivo != NULL) {
        fclose(arquivo);
        return 1;
    }

    printf("\n===== CADASTRO DE SENHA =====\n");

    while (1) {
        printf("Crie uma senha de 1 a 15 letras: ");

        if (fgets(senha, sizeof(senha), stdin) == NULL)
            return 0;

        senha[strcspn(senha, "\r\n")] = '\0';

        if (strlen(senha) == 0 ||
            strlen(senha) > TAM_MAX_PALAVRA) {
            printf("Tamanho invalido.\n");
            continue;
        }

        for (i = 0; senha[i] != '\0'; i++) {
            if (!isalpha((unsigned char)senha[i]))
                break;

            senha[i] = (char)tolower((unsigned char)senha[i]);
        }

        if (senha[i] != '\0') {
            printf("Use somente letras de A a Z.\n");
            continue;
        }

        break;
    }

    criptografarSenha(senha, codificada);

    arquivo = fopen("senha.dat", "w");

    if (arquivo == NULL) {
        printf("Erro ao salvar senha.\n");
        return 0;
    }

    fprintf(arquivo, "%s", codificada);
    fclose(arquivo);

    printf("Senha cadastrada com sucesso!\n");

    return 1;
}

int autenticarUsuario(void) {
    FILE *arquivo;

    char senha[TAM_MAX_PALAVRA + 1];
    char codificada[TAM_MAX_PALAVRA + 1];
    char senhaSalva[TAM_MAX_PALAVRA + 1];

    int i;

    arquivo = fopen("senha.dat", "r");

    if (arquivo == NULL)
        return 0;

    if (fscanf(arquivo, "%15s", senhaSalva) != 1) {
        fclose(arquivo);
        return 0;
    }

    fclose(arquivo);

    printf("Digite sua senha: ");

    if (fgets(senha, sizeof(senha), stdin) == NULL)
        return 0;

    senha[strcspn(senha, "\r\n")] = '\0';

    if (strlen(senha) == 0 ||
        strlen(senha) > TAM_MAX_PALAVRA)
        return 0;

    for (i = 0; senha[i] != '\0'; i++) {
        if (!isalpha((unsigned char)senha[i]))
            return 0;

        senha[i] = (char)tolower((unsigned char)senha[i]);
    }

    if (!criptografarSenha(senha, codificada))
        return 0;

    if (strcmp(codificada, senhaSalva) == 0) {
        printf("Acesso autorizado!\n");
        return 1;
    }

    printf("Senha incorreta! Acesso negado.\n");

    return 0;
}

// ========================================
// MODULO 2 - SISTEMA DE SAQUE
// ========================================

void moduloSaque(void) {
    int saque;

    printf("\n===== SISTEMA DE SAQUE =====\n");

    if (!autenticarUsuario())
        return;

    printf("Saldo atual: R$ %d\n", saldo);

    if (!lerInteiro("Digite o valor do saque: ", &saque)) {
        printf("Valor invalido.\n");
        return;
    }

    if (saque <= 0) {
        printf("Erro: valor invalido.\n");
    }
    else if (saque % 5 != 0) {
        printf("Erro: o valor deve ser multiplo de 5.\n");
    }
    else if (saque > saldo) {
        printf("Erro: saldo insuficiente.\n");
    }
    else {
        int notas[] = {100, 50, 20, 10, 5};
        int restante = saque;
        int quantidade;
        int i;

        printf("\nNotas entregues:\n");

        for (i = 0; i < 5; i++) {
            quantidade = restante / notas[i];

            if (quantidade > 0) {
                printf("%d nota(s) de %d\n",
                    quantidade, notas[i]);

                restante %= notas[i];
            }
        }

        saldo -= saque;

        printf("\nSaque realizado!\n");
        printf("Novo saldo: R$ %d\n", saldo);
    }
}

// ========================================
// MODULO 3 - SISTEMA DE PIXELS
// ========================================

unsigned char img[ALT][LARG] = {
    {41,39,40,43,48,36,41,49,69,35,33,50,47,37,31,65},
    {50,71,66,40,65,55,43,42,43,65,63,50,38,70,61,55},
    {41,34,15,47,42,50,56,49,46,55,44,53,47,63,58,44},
    {49,55,34,75,47,190,183,182,189,166,195,183,60,60,29,47},
    {46,37,51,38,176,172,194,166,167,175,162,175,195,34,50,39},
    {38,68,63,171,178,181,182,175,229,231,231,173,194,163,36,55},
    {43,35,59,193,190,208,171,181,233,226,224,159,171,189,47,54},
    {33,36,51,183,161,153,163,181,245,239,237,183,165,186,29,33},
    {67,63,67,177,191,199,186,184,237,228,228,183,177,181,35,41},
    {54,36,30,183,181,168,161,183,204,168,181,187,174,194,39,64},
    {45,25,41,201,199,199,145,166,184,182,186,193,160,160,61,33},
    {60,53,28,33,208,188,180,147,171,149,177,171,182,63,52,61},
    {56,39,58,50,33,183,176,187,165,169,181,168,53,44,50,21},
    {45,52,45,58,61,54,62,52,46,45,37,66,61,42,60,34},
    {38,41,39,36,50,42,58,58,51,42,42,44,55,54,39,47},
    {34,47,50,42,49,65,42,47,65,42,50,60,50,50,35,50}
};

void moduloPixels(void) {
    long soma = 0;

    int hist[8] = {0};

    unsigned char mascara[ALT][LARG] = {{0}};

    int area = 0;

    int linMin = ALT, linMax = -1;
    int colMin = LARG, colMax = -1;

    long somaLin = 0, somaCol = 0;

    int i, j;

    for (i = 0; i < ALT; i++) {
        for (j = 0; j < LARG; j++) {
            int v = img[i][j];

            soma += v;

            hist[v / 32]++;

            mascara[i][j] = (v > 128) ? 1 : 0;

            if (mascara[i][j]) {
                area++;

                somaLin += i;
                somaCol += j;

                if (i < linMin) linMin = i;
                if (i > linMax) linMax = i;

                if (j < colMin) colMin = j;
                if (j > colMax) colMax = j;
            }
        }
    }

    printf("\n===== CAÇADORES DE PIXELS =====\n");

    printf("Pixels analisados: %d\n", ALT * LARG);

    printf("Soma: %ld\nMedia: %.3f\n",
        soma, (double)soma / (ALT * LARG));

    printf("Histograma: ");

    for (i = 0; i < 8; i++)
        printf("%d%s", hist[i], i == 7 ? "\n" : ", ");

    printf("\nMascara (# = objeto; . = fundo)\n");

    for (i = 0; i < ALT; i++) {
        for (j = 0; j < LARG; j++)
            putchar(mascara[i][j] ? '#' : '.');

        putchar('\n');
    }

    if (area > 0) {
        int altura = linMax - linMin + 1;
        int largura = colMax - colMin + 1;

        printf("Area: %d pixels\n", area);

        printf("Caixa delimitadora: linhas %d-%d, colunas %d-%d\n",
            linMin, linMax, colMin, colMax);

        printf("Altura x largura: %d x %d\n",
            altura, largura);

        printf("Centroide (linha, coluna): (%.2f, %.2f)\n",
            (double)somaLin / area,
            (double)somaCol / area);

        printf("Taxa de ocupacao: %.2f%%\n",
            100.0 * area / (altura * largura));
    }
}

// ========================================
// PROGRAMA PRINCIPAL
// ========================================

int main(void) {
    int opcao;

    printf("====================================\n");
    printf("       SISTEMA INTEGRADO EM C       \n");
    printf("====================================\n");

    if (!cadastrarSenha()) {
        printf("Erro no cadastro. Sistema encerrado.\n");
        return 1;
    }

    do {
        printf("\n========== MENU PRINCIPAL ==========\n");

        printf("1. Sistema de saque\n");
        printf("2. Sistema de criptografia\n");
        printf("3. Sistema de pixels\n");
        printf("0. Sair\n");

        if (!lerInteiro("Escolha uma opcao: ", &opcao)) {
            printf("Entrada invalida.\n");
            continue;
        }

        switch (opcao) {
            case 1:
                moduloSaque();
                break;

            case 2: {
                int escolha;

                printf("\n1. Criptografar com uma sequencia\n");
                printf("2. Comparar todas as sequencias\n");
                printf("0. Voltar\n");

                if (!lerInteiro("Escolha: ", &escolha))
                    break;

                if (escolha == 1)
                    executarCriptografia(0);
                else if (escolha == 2)
                    executarCriptografia(1);
                else if (escolha != 0)
                    printf("Opcao invalida.\n");

                break;
            }

            case 3:
                moduloPixels();
                break;

            case 0:
                printf("Sistema encerrado.\n");
                break;

            default:
                printf("Opcao inexistente.\n");
        }

    } while (opcao != 0);

    return 0;
}
