#include <stdio.h>
typedef struct {
    double a, b, resultado;
    int sucesso;
    char operador;
} Operacao;

// 1) Protótipos
void mostrarMenu(void);
void limparLinha(void);
int lerOpcaoMenu(void);
double lerDouble(const char *mensagem);
char obterOperador(int opcao);

// 1.1) Protótipos == OPERAÇÕES
double somar(double a, double b);
double subtrair(double a, double b);
double multiplicar(double a, double b);
double dividir(double a, double b, double *resultado);

// 1.2) Protótipos == Histórico
void salvarOperacao(Operacao hist[], int *total, int *idx, Operacao op);
void mostrarHistorico(const Operacao hist[], int total, int idx);

int main(void) {
    double a, b, resultado;
    int opcao;
    Operacao hist[5];
    int total = 0;
    int idx = 0;

    printf("==========CALCULADORA==========\n");
    
    do {
        opcao = lerOpcaoMenu();
        if (opcao == 0) {
            printf("Saindo...\n");
            break;
        }
        if (opcao == 5) {
            mostrarHistorico(hist, total, idx);
            continue;
        }

        if (opcao >= 1 && opcao <= 4) {
            a = lerDouble("\nDigite o primeiro valor: ");
            b = lerDouble("\nDigite o segundo valor: ");

            Operacao op;
            switch (opcao) {
                case 1:
                    resultado = somar(a,b);
                    printf("\nResultado(SOMA): %.2f\n\n", resultado);

                    op.a = a;
                    op.b = b;
                    op.operador = '+';
                    op.resultado = resultado;
                    op.sucesso = 1;
                    salvarOperacao(hist, &total, &idx, op);
                    break;
                case 2:
                    resultado = subtrair(a,b);
                    printf("\nResultado(SUBTRACAO): %.2f\n\n", resultado);

                    op.a = a;
                    op.b = b;
                    op.operador = '-';
                    op.resultado = resultado;
                    op.sucesso = 1;
                    salvarOperacao(hist, &total, &idx, op);
                    break;
                case 3:
                    resultado = multiplicar(a,b);
                    printf("\nResultado(MULTIPLICACAO): %.2f\n\n", resultado);

                    op.a = a;
                    op.b = b;
                    op.operador = '*';
                    op.resultado = resultado;
                    op.sucesso = 1;
                    salvarOperacao(hist, &total, &idx, op);
                    break;
                case 4:
                    op.a = a;
                    op.b = b;
                    op.operador = '/';

                    if (dividir(a,b, &resultado)) {
                        printf("\nResultado(DIVISAO: %.2f\n\n",resultado);
                        op.resultado = resultado;
                        op.sucesso = 1;
                    } else {
                        printf("\nErro: divisao por zero!\n\n");
                    }
                    salvarOperacao(hist, &total, &idx, op);
                    break;
            }
        } else {
            printf("\nNumero invalido. Tente novamente!\n");
        }
    } while (opcao != 0);
    return 0;
}

// 2) Implementações
void mostrarMenu(void) {
    printf("Escolha a operacao:\n");
    printf(" 1 == SOMA\n 2 == SUBTRACAO\n 3 == MULTIPLICACAO\n 4 == DIVISAO\n 5 == Historico\n 0 == SAIR\n");
}
void limparLinha(void) {
    int limp;
    while ((limp = getchar()) != '\n' && limp != EOF) {}
}
int lerOpcaoMenu(void) {
    int opcao, valid;
    do {
        mostrarMenu();
        valid = scanf("%d",&opcao);

        if (valid != 1) {
            printf("\nEntrada Invalida! Digite um numero.\n");
            limparLinha();
            continue;
        }

        if (opcao < 0 || opcao > 5) {
            printf("\nNumero Invalido. Tente novamente.");
        }
    } while (opcao < 0 || opcao > 5);
    return opcao;
}
double lerDouble(const char *mensagem) {
    double valor;
    int valid;

    do {
        printf("%s",mensagem);
        valid = scanf("%lf",&valor);

        if (valid != 1) {
            printf("\nValor Invalido! Tente novamente.");
            limparLinha();
        }
    } while (valid != 1);
    return valor;
}
char obterOperador(int opcao) {
    switch (opcao) {
        case 1: return '+';
        case 2: return '-';
        case 3: return '*';
        case 4: return '/';
        default: return '?';
    }
}

// 2.1) Implementações == OPERAÇÕES
double somar(double a, double b) {
    return a+b;
}
double subtrair(double a, double b) {
    return a-b;
}
double multiplicar(double a, double b) {
    return a*b;
}
double dividir(double a, double b, double *resultado) {
    if (b == 0.0) {
        return 0; // Erro: Divisão por zero
    }
    *resultado = a/b;
    return 1; // Sucesso
}

// 2.2) Implementações == HISTÓRICO
void salvarOperacao(Operacao hist[], int *total, int *idx, Operacao op) {
    hist[*idx] = op;
    *idx = (*idx + 1) % 5;

    if (*total < 5) {
        (*total)++;
    }
}
void mostrarHistorico(const Operacao hist[], int total, int idx) {
    if (total == 0) {
        printf("\nHistorico vazio.\n\n");
        return;
    }
    printf("\n=====HISTORICO (Ultimas %d)=====\n",total);
    int start = (total == 5) ? idx : 0;
    for (int i = 0; i < total; i++) {
        int pos = (start + i) % 5;
        Operacao op = hist[pos];

        if (op.sucesso) {
            printf("%d %.2f %c %.2f = %.2f\n", i + 1, op.a, op.operador, op.b, op.resultado);
        } else {
            printf("%d %.2f %c %.2f = ERRO\n", i + 1, op.a, op.operador, op.b);
        }
    }
    printf("\n");
}