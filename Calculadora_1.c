#include <stdio.h>

int main(void) {
    double a, b, resultado;
    int escolha,valid,limp;

    printf("==========CALCULADORA==========\n");

    // Loop até o usuário escolher uma opção válida
    do {
        printf("Escolha a operacao:\n 1 == SOMA\n 2 == SUBTRACAO\n 3 == MULTIPLICACAO\n 4 == DIVISAO\n 0 == SAIR\n");
        valid = scanf("%d", &escolha);
        if (valid != 1){
            printf("\nEntrada Invalida! Digite um numero.\n");
            while((limp = getchar()) != '\n' && limp != EOF){}
            escolha = -1;
            continue;
        } 
        if (escolha >= 1 && escolha <= 4) {
            printf("\nDigite o primeiro valor: ");
            valid = scanf("%lf", &a);
            if (valid != 1){
                printf("\nValor invalido para o primeiro numero!\n");
                while ((limp = getchar()) != '\n' && limp != EOF){}
                continue;
            }

            printf("\nDigite o segundo valor: ");
            valid = scanf("%lf", &b);
            if (valid != 1){
                printf("\nValor invalido para o segundo numero!\n");
                while ((limp = getchar()) != '\n' && limp != EOF){}
                continue;
            }

            switch (escolha) {
                case 1:
                    resultado = a + b;
                    printf("\nResultado (SOMA): %.2f\n\n", resultado);
                    break;
                case 2:
                    resultado = a - b;
                    printf("\nResultado (SUBTRACAO): %.2f\n\n", resultado);
                    break;
                case 3:
                    resultado = a * b;
                    printf("\nResultado (MULTIPLICACAO): %.2f\n\n", resultado);
                    break;
                case 4:
                    if (b != 0) {
                        resultado = a / b;
                        printf("\nResultado (DIVISAO): %.2f\n\n", resultado);
                    } else {
                        printf("\nErro: divisao por zero!\n\n");
                    }
                    break;
            }
        } else if (escolha == 0){
            printf("Saindo...\n");
        } else {
            printf("\nNumero invalido. Tente novamente!\n");
        }
    } while (escolha != 0);
    return 0;
}