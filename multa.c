#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    
    float velocidade = 0.0;
    float limite = 80.0;

    scanf("%f", &velocidade);

    if(velocidade <= limite){
        printf("Velocidade dentro do limite permitido.\n");
        return 0;
    }

    float multa = 0.0;
    multa = 2 * (velocidade - limite);

    printf("Limite de velocidade excedido! Multado no valor de R$%.2f!\n", multa);
    return 0;
}