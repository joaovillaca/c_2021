// @author Joao Vitor N. Villaça - NUSP 10724239

#include <stdio.h>
#include <stdlib.h>

#define debug 1
#define NOVO 200

// Procura o valor no vetor e incrementa a ocorrencia em vetor_aux
// @return Numero novo: -1 // Numero repetido: posição no vetor
int anota_valor(int valor, int* vetor, int tamanho, int* vetor_aux) {
    for(int i = 0; i < tamanho; i++) {
        if(vetor[i] == valor) {
            vetor_aux[i] += 1;
            return i;
        }
    }
    return NOVO;
}

int main(int argc, char** argv) {

    int tamanho = 0;
    int vetor[100];
    int ocorrencias[100];
    
    // inicializa os vetores com -1
    for(int i = 0; i < 100; i++) {
        vetor[i] = -1;
        ocorrencias[i] = -1;
    }

    char dump;
    int num = 0;
    for(int i = 0; i < 100; i++) {
        scanf("%d", &num);
        dump = fgetc(stdin);

        if(anota_valor(num, vetor, tamanho, ocorrencias) == NOVO) {
            tamanho++;
            vetor[tamanho - 1] = num;
            ocorrencias[tamanho - 1] = 1;
        }

        if(dump == EOF || dump == '\n') {
            break;
        }
    }

    for(int i = 0; i < tamanho; i++) {
        printf("%d (%d)", vetor[i], ocorrencias[i]);
        printf("\n");
    }

    return 0;

}