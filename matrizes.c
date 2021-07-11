#include <stdio.h>
#include <stdlib.h>
#define or ||
#define DEBUG 1

int **alocarMatriz(int lin, int col){

    if(lin <= 0 or col <= 0) return NULL;

    int **ponteiroMatriz;
    ponteiroMatriz = (int**) malloc(lin * sizeof(int*));
    for(int i = 0; i < lin; i++){
        ponteiroMatriz[i] = (int*) malloc(col * sizeof(int));
        if(DEBUG) printf("linha alocada [%d]\n", i);
    }
    return ponteiroMatriz;
}

int apagarMatriz(int** ponteiroMatriz, int lin){

    if(lin == 0 or ponteiroMatriz == NULL) return 1;

    for(int i = 0; i < lin; i++){
        if(DEBUG) printf("Apagando matriz[coluna%d]...\n", i);
        free(ponteiroMatriz[i]);
    }
    free(ponteiroMatriz);
    if(DEBUG) printf("Apagando instância da matriz...\n");
    return 0;
}

int main(){

    int numeroLinhasA, numeroColunasA;
    int numeroLinhasB, numeroColunasB;

    scanf("%d %d", &numeroLinhasA, &numeroColunasA);
    scanf("%d %d", &numeroLinhasB, &numeroColunasB);
    if(DEBUG){
        printf("entrada: [%d][%d]\n", numeroLinhasA, numeroColunasA);
        printf("entrada: [%d][%d]\n", numeroLinhasB, numeroColunasB);
    }

    if(numeroColunasA != numeroLinhasB
        or numeroLinhasA  < 0
        or numeroColunasA < 0
        or numeroLinhasB  < 0
        or numeroColunasB < 0) {

        printf("Valores invalidos para a multiplicacao.");
        return 0;
    }

    int seedGeradora;
    scanf("%d", &seedGeradora);
    srand(seedGeradora);
    if(DEBUG) printf("Seed geradora definida | seedGeradora = %d\n", seedGeradora);

    int **matrizA;
    matrizA = alocarMatriz(numeroLinhasA, numeroColunasA);
    
    //matriz preenchida com numeros aleatorios entre -25 e 24
    for(int i = 0; i < numeroLinhasA; i++){
        for(int j = 0; j < numeroColunasA; j++){
            matrizA[i][j] = rand()%50 - 25;
            if(DEBUG) printf("matrizA[%d][%d]: %d ", i, j, matrizA[i][j]);
        }
        if(DEBUG) printf("\n");
    }

    int **matrizB;
    matrizB = alocarMatriz(numeroLinhasB, numeroColunasB);

    for(int i = 0; i < numeroLinhasB; i++){
        for(int j = 0; j < numeroColunasB; j++){
            matrizB[i][j] = rand()%50 - 25;
            if(DEBUG) printf("matrizB[%d][%d]: %d ", i, j, matrizB[i][j]);
        }
        if(DEBUG) printf("\n");
    }

    int **matrizObjeto;
    matrizObjeto = alocarMatriz(numeroLinhasA, numeroColunasB);

    int auxiliar;

    for(int linhaAtual = 0; linhaAtual < numeroLinhasA; linhaAtual++){
        for(int colunaAtual = 0; colunaAtual < numeroColunasB; colunaAtual++){
            auxiliar = 0;

            for(int iterador = 0; iterador < numeroLinhasB; iterador++){

                auxiliar += matrizA[linhaAtual][iterador] * matrizB[iterador][colunaAtual];
                if(DEBUG) printf("aux: %d ", auxiliar);
            }

            matrizObjeto[linhaAtual][colunaAtual] = auxiliar;
            if(DEBUG) printf("\nResultado[%d][%d]: %d\n", linhaAtual, colunaAtual, auxiliar);
        }
        if(DEBUG) printf("\n");
    }

    for(int i = 0; i < numeroLinhasA; i++){
        printf("Linha %d: ", i);
        for(int j = 0; j < numeroColunasB; j++){
            printf("%d ", matrizObjeto[i][j]);
        }
        printf("\n");
    }

    apagarMatriz(matrizA, numeroLinhasA);
    apagarMatriz(matrizB, numeroLinhasB);
    apagarMatriz(matrizObjeto, numeroLinhasA);

    return EXIT_SUCCESS;
}