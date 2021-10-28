#include <stdio.h>
#include <stdlib.h>

#define debug 0

// Funções
int  **aloca_matriz(int lin, int col);
void quadtree(int** matriz, int lin, int col);
void traversal(int** matriz, int lin_org, int lin_end, int col_org, int col_end);
int  checa_quadrante(int** matriz, int lin_org, int lin_end, int col_org, int col_end);

int main() {

    // leitura de linhas e colunas
    int lin=0, col=0;
    scanf("%d%d\n", &lin, &col);
    if(debug) printf("lin=%d col=%d\n", lin, col);

    int **matriz = aloca_matriz(lin, col);

    quadtree(matriz, lin, col);
    return 0;

}

void quadtree(int** matriz, int lin, int col) {
    traversal(matriz, 0, lin-1, 0, col-1);
}

// @param lin_org : linha de origem
// @param lin_end : linha final
// @param col_org : coluna de origem
// @param col_end : coluna final
void traversal(int** matriz, int lin_org, int lin_end, int col_org, int col_end) {
    int check = 0;
    check = checa_quadrante(matriz, lin_org, lin_end, col_org, col_end);
    if(debug) {
        printf("check = %d\n", check);
    }
    if(check == -1) {
        printf("-1 ");
        traversal(matriz, lin_org, (lin_org+lin_end)/2, col_org, (col_org+col_end)/2);
        traversal(matriz, lin_org, (lin_org+lin_end)/2, (((col_org+col_end)/2) + 1), col_end);
        traversal(matriz, (((lin_org+lin_end)/2) + 1), lin_end, col_org, (col_org+col_end)/2);
        traversal(matriz, (((lin_org+lin_end)/2) + 1), lin_end, (((col_org+col_end)/2) + 1), col_end);
    }
    else {
        printf("%d ", check);
        return;
    }
}

int checa_quadrante(int** matriz, int lin_org, int lin_end, int col_org, int col_end) {
    int aux1=0, aux2=0;
    aux2 = matriz[lin_org][col_org];
    for(int i = lin_org; i <= lin_end; i++) {
        for(int j = col_org; j <= col_end; j++) {
            aux1 = matriz[i][j];
            if(aux1 != aux2) {
                return -1;
            }
        }
    }
    if(debug) {
        printf("aux1 = %d\n", aux1);
    }
    return aux1;
}


int **aloca_matriz(int lin, int col) {

    // ponteiros das linhas da matriz
    int **matriz = NULL;
    matriz = (int**) malloc(lin * sizeof(int*));

    // leitura da matriz
    for(int i = 0; i < lin; i++) {

        // alocação da linha a ser lida
        matriz[i] = (int*) malloc(col * sizeof(int));

        for(int j = 0; j < col; j++) {
            scanf("%d", &matriz[i][j]);
        }
        getchar(); // pega o \n

        if(debug) {
            printf("matriz [%d] = ", i);
            for(int k = 0; k < col; k++) {
                printf("%d ", matriz[i][k]);
            }
            printf("\n");
        }
    }

    return matriz;
}