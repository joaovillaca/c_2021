// @author Joao Vitor N. Villaça - NUSP 10724239

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define debug 0

// Alem de executar o floodfill, incrementa os visitados e marca eles com *
// @return Saiu do labirinto: 1 Nao saiu: 0 
int floodFill(char** matriz, int M, int N, int x, int y, int* visitados) {

    matriz[x][y] = '*';
    *visitados += 1;

    // saida do labirinto
    if(x == 0 || x == (M - 1) || y == (N - 1) || y == 0) {
        return 1;
    }

    // Cima
    if(matriz[x - 1][y] == '.') {
        if(floodFill(matriz, M, N, x - 1, y, visitados)) {
            return 1;
        }
    }
    
    // Direita
    if(matriz[x][y + 1] == '.') {
        if(floodFill(matriz, M, N, x, y + 1, visitados)) {
            return 1;
        }
    }

    // Baixo
    if(matriz[x + 1][y] == '.') {
        if(floodFill(matriz, M, N, x + 1, y, visitados)) {
            return 1;
        }
    }

    // Esquerda
    if(matriz[x][y - 1] == '.') {
        if(floodFill(matriz, M, N, x, y - 1, visitados)) {
            return 1;
        }
    }
    
    return 0;
}

void printLabirinto(char** map, int M) {
    for(int i = 0; i < M; i++) {
        puts(map[i]);
    }
}

int main(int argc, char** argv) {

    char filename[100];
    char aux;
    
    // lendo o nome do arquivo
    for(int i = 0; i < 100; i++) {
        aux = fgetc(stdin);
        if(aux == '\n' || aux == EOF) {
            filename[i] = '\0';
            break;
        }
        filename[i] = aux;
    }

    if(debug) {
        puts(filename);
    }

    FILE* fp = fopen(filename, "r");

    int M, N;
    int x, y;

    fscanf(fp, "%d %d\n", &M, &N);
    fscanf(fp, "%d %d\n", &x, &y);

    if(debug) {
        printf("M = %d N = %d x = %d y = %d\n", M, N, x, y);
    }

    // alocando o labirinto
    char** labirinto = (char**) malloc(M * sizeof(char*));
    for(int i = 0; i < M; i++) {
        labirinto[i] = (char*) malloc((N + 1) * sizeof(char));
    }

    // colocando \0 no final das colunas
    for(int i = 0; i < M; i++) {
        labirinto[i][N] = '\0';
    }

    int npessoas = 0;
    int ncaminhos = 0;
    int visitados = 0;

    // lendo o labirinto
    // contando . e #
    for(int i = 0; i < M; i++) {
        for(int j = 0; j < N; j++) {
            fscanf(fp, "%c\n", &labirinto[i][j]);
            if(labirinto[i][j] == '#') {
                npessoas++;
            }
            if(labirinto[i][j] == '.') {
                ncaminhos++;
            }
        }
    }

    if(debug) {
        printLabirinto(labirinto, M);
    }

    floodFill(labirinto, M, N, x, y, &visitados);

    double exploracao = 0.0;
    exploracao = 100.0 * ((double) visitados / (double) ncaminhos);

    if(debug) {
        printf("visitados = %lf\nncaminhos = %lf\n", (double)visitados, (double)ncaminhos);
    }

    printLabirinto(labirinto, M);

    printf("\nVoce escapou de todos! Ninguem conseguiu te segurar!\n");
    printf("Veja abaixo os detalhes da sua fuga:\n");
    printf("----Pessoas te procurando: %d\n", npessoas);
    printf("----Numero total de caminhos validos:   %d\n", ncaminhos);
    printf("----Numero total de caminhos visitados: %d\n", visitados);
    printf("----Exploracao total do labirinto: %.1lf%%\n", floor(exploracao)); 

    for(int i = 0; i < M; i++) {
        free(labirinto[i]);
    }
    free(labirinto);

    fclose(fp);
    return 0;
}
