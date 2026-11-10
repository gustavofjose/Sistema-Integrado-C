# Sistema-Integrado-C

## Visão Geral

Sistema integrado desenvolvido em linguagem C que reúne três módulos funcionais em uma única aplicação com interface de menu interativo. O projeto demonstra a aplicação prática de conceitos fundamentais de programação estruturada, incluindo estruturas de controle, funções, manipulação de arquivos e processamento de dados.

## Objetivo

Desenvolver uma aplicação modular capaz de integrar diferentes soluções computacionais em um ambiente unificado, aplicando boas práticas de programação e organizando funcionalidades distintas de forma coesa e escalável.

## Funcionalidades

### 3.1. Módulo Bancário

Simulação de operações de saque com validações completas:

- Cadastro e autenticação de senha
- Validação de valores (positivos e múltiplos de cinco)
- Verificação de saldo disponível
- Cálculo automático de cédulas necessárias
- Atualização de saldo após transação

### 3.2. Módulo de Criptografia

Codificação e decodificação de palavras utilizando múltiplos métodos:

- Cifra de César (deslocamento de 3 posições)
- Progressão Aritmética (PA)
- Progressão Geométrica (PG)
- Sequência de Fibonacci
- Sequência de números primos
- Comparação entre métodos de codificação
- Registro de operações em arquivos de texto

### 3.3. Módulo de Processamento de Imagens

Análise de matrizes de imagem 16 × 16 pixels:

- Leitura e análise de pixels
- Construção de histograma
- Geração de máscara binária
- Cálculo de área ocupada
- Identificação de caixa delimitadora (*Bounding Box*)
- Cálculo de centroide
- Cálculo de taxa de ocupação

## Tecnologias Utilizadas

| Tecnologia | Aplicação |
|---|---|
| Linguagem C | Desenvolvimento da aplicação |
| GCC | Compilação do código-fonte |
| Visual Studio Code | Edição e organização do código |
| GitHub | Versionamento e disponibilização |

## Estrutura do Projeto

```text
Sistema-Integrado-C/
│
├── Sistema-Integrado.c
├── README.md
├── LICENSE
└── .gitignore
```

**Arquivos gerados durante a execução:**

- `senha.dat` — Armazenamento de credenciais
- `resultado_criptografia.txt` — Resultados das operações de criptografia
- `log_criptografia.txt` — Registro de operações realizadas

## Como Executar

### Pré-requisitos

- GCC instalado e configurado
- Terminal ou ambiente de desenvolvimento compatível com C

### Compilação

```bash
gcc Sistema-Integrado.c -o Sistema-Integrado.exe
```

### Execução (Windows)

```powershell
.\Sistema-Integrado.exe
```

## Organização do Sistema

Ao iniciar a aplicação, o usuário tem acesso ao menu principal:

| Opção | Funcionalidade |
|---|---|
| 1 | Operações bancárias |
| 2 | Criptografia |
| 3 | Processamento de imagens |
| 0 | Encerrar o programa |

Cada opção direciona o usuário ao módulo correspondente, permitindo utilização independente das funcionalidades.

## Considerações Finais

O desenvolvimento deste sistema proporcionou a aplicação prática de conceitos da programação estruturada, demonstrando como funções e estruturas de controle podem organizar uma aplicação com múltiplas funcionalidades. O projeto também abordou tópicos como sequências matemáticas, manipulação de arquivos, validação de dados e operações sobre matrizes.

**Observação:** Os métodos de criptografia implementados possuem finalidade exclusivamente didática e não devem ser utilizados para proteger informações reais. A Cifra de César e as sequências matemáticas empregadas não oferecem segurança criptográfica adequada.

## Licença

Este projeto está disponibilizado sob a licença MIT. Consulte o arquivo [LICENSE](LICENSE) para conhecer os termos de utilização, modificação e distribuição.

---

**Projeto acadêmico desenvolvido para fins educacionais, como aplicação prática dos conceitos de programação em linguagem C.**
