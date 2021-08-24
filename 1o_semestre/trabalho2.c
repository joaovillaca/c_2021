/*
    @author João Villaça - 10724239
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define dbg 0

#define VIVA 'x'
#define MORTA '.'

typedef struct _MODELO {
    int linhas;
    int colunas;
    char** vizinhanca;
    int totalRounds;
} Modelo;

Modelo*  NovoModelo       (int linhas, int colunas, int totalRounds);
void     ApagaModelo      (Modelo* m);
void     PrintVizinhanca  (Modelo* m);
int      VizinhosMoore    (Modelo* m, int lin, int col);
void     TesteMoore       (Modelo* m);
int      VizinhosNeumann  (Modelo* m, int lin, int col);
void     TesteNeumann     (Modelo* m);

int main(int argc, char** argv) {

    int linhas, colunas;
    scanf("%d %d", &linhas, &colunas);
    if(linhas <= 0 || colunas <= 0) {
        puts("Dados de entrada apresentam erro.");
        return 0;
    }
    if(dbg) printf("linhas %d | colunas %d\n", linhas, colunas);

    int geracoes;
    scanf("%d", &geracoes);
    if(geracoes <= 0) {
        puts("Dados de entrada apresentam erro.");
        return 0;
    }
    if(dbg) printf("geracoes %d\n", geracoes);

    char modelo;
    scanf(" %c", &modelo);
    if(dbg) printf("modelo %c\n", modelo);

    Modelo* MeuTeste;
    char input;
    fflush(stdin);

    MeuTeste = NovoModelo(linhas, colunas, geracoes);
    for(int i = 0; i < MeuTeste->linhas; i++) {
        for(int j = 0; j < MeuTeste->colunas; j++) {
            scanf("%c", &input);

            //ignora os \n na matriz
            if(input == '\n') {
                if(j < MeuTeste->colunas) {
                    j--;
                }
                continue;
            }

            MeuTeste->vizinhanca[i][j] = input;
            if(dbg) {
                printf("%c", MeuTeste->vizinhanca[i][j]);
            }
        }
        if(dbg) printf("\n");
    }
    
    switch (modelo) {
        case 'M':
            TesteMoore(MeuTeste);
            PrintVizinhanca(MeuTeste);
            break;
        
        case 'N':
            TesteNeumann(MeuTeste);
            PrintVizinhanca(MeuTeste);
            break;
        
        default:
            puts("Dados de entrada apresentam erro.");
            return 0;
    }

    ApagaModelo(MeuTeste);
    return 0;
}

int VizinhosMoore(Modelo* m, int lin, int col) {
    char** matriz = m->vizinhanca;
    int v = 0;
    
    if(matriz[(lin+1) % m->linhas][(col+1) % m->colunas] == VIVA) {
        v++;
    }
    if(matriz[lin][(col+1) % m->colunas] == VIVA) {
        v++;
    }
    if(matriz[(lin+1) % m->linhas][col] == VIVA) {
        v++;
    }

    // casos de borda de linha
    if(lin - 1 >= 0){
        if(matriz[lin-1][(col+1) % m->colunas] == VIVA) {
            v++;
        }
        if(matriz[lin-1][col] == VIVA) {
            v++;
        }
    }
    else {
        if(matriz[lin-1 + m->linhas][(col+1) % m->colunas] == VIVA) {
            v++;
        }
        if(matriz[lin-1 + m->linhas][col] == VIVA) {
            v++;
        }
    }

    //casos de borda de coluna
    if(col - 1 >= 0) {
        if(matriz[(lin+1) % m->linhas][col-1] == VIVA) {
            v++;
        }
        if(matriz[lin][col-1] == VIVA) {
            v++;
        }
    }
    else {
        if(matriz[(lin+1) % m->linhas][col-1 + m->colunas] == VIVA) {
            v++;
        }
        if(matriz[(lin)][col-1 + m->colunas] == VIVA) {
            v++;
        }
    }

    // vizinho inferior esquerdo
    if(lin - 1 < 0 && col - 1 < 0) {
        if(matriz[lin-1+m->linhas][col-1+m->colunas] == VIVA) {
            v++;
        }
    }
    else{
        if(lin - 1 < 0) {
            if(matriz[lin-1+m->linhas][col-1] == VIVA) {
                v++;
            }
        }
        else if(col - 1 < 0) {
            if(matriz[lin-1][col-1+m->colunas] == VIVA) {
                v++;
            }
        }
        else {
            if(matriz[lin-1][col-1] == VIVA) {
                v++;
            }
        }
    }
    return v;
}

void TesteMoore(Modelo* m) {

    char** alvo = m->vizinhanca;
    int vizinhos_vivos = 0;

    // matriz auxiliar
    char** aux = NULL;
    aux = (char**) malloc(m->linhas * sizeof(char*));
    for(int i = 0; i < m->linhas; i++) {
        aux[i] = (char*) malloc((m->colunas+1) * sizeof(char));
        memset(aux[i], 'o', m->colunas);
        aux[i][m->colunas] = '\0';
    }

    for(int geracao = 0; geracao < m->totalRounds; geracao++) {
        for(int linha = 0; linha < m->linhas; linha++) {
            for(int coluna = 0; coluna < m->colunas; coluna++) {

                if(alvo[linha][coluna] == VIVA) {
                    vizinhos_vivos = VizinhosMoore(m, linha, coluna);
                    if(vizinhos_vivos < 2 || vizinhos_vivos > 3) {
                        aux[linha][coluna] = MORTA;
                        continue;
                    }
                    else {
                        aux[linha][coluna] = VIVA;
                    }
                    continue;
                }

                if(alvo[linha][coluna] == MORTA) {
                    vizinhos_vivos = VizinhosMoore(m, linha, coluna);
                    if (vizinhos_vivos == 3) {
                        aux[linha][coluna] = VIVA;
                    }
                    else {
                        aux[linha][coluna] = MORTA;
                    }
                }
            }
        }

        // copiando a auxiliar para a vizinhança
        for(int i = 0; i < m->linhas; i++) {
            for(int j = 0; j < m->colunas; j++) {
                alvo[i][j] = aux[i][j];
            }
        }

    }

    for(int i = 0; i < m->linhas; i++){
        free(aux[i]);
    }
    free(aux);
}

int VizinhosNeumann(Modelo* m, int lin, int col) {
    char** matriz = m->vizinhanca;
    int v = 0;

    if(matriz[(lin+1) % m->linhas][col] == VIVA) {
        v++;
    }
    if(matriz[(lin+2) % m->linhas][col] == VIVA) {
        v++;
    }
    if(matriz[lin][(col+1) % m->colunas] == VIVA) {
        v++;
    }
    if(matriz[lin][(col+2) % m->colunas] == VIVA) {
        v++;
    }

    // caso de borda de linha
    if(lin - 1 < 0) {
        if(matriz[lin-1 + m->linhas][col] == VIVA) {
            v++;
        }
    }
    else {
        if(matriz[lin-1][col] == VIVA) {
            v++;
        }
    }
    if(lin - 2 < 0){
        if(matriz[lin-2 + m->linhas][col] == VIVA) {
            v++;
        }
    }
    else {
        if(matriz[lin-2][col] == VIVA) {
            v++;
        }
    }

    // caso de borda de coluna
    if(col - 1 < 0) {
        if(matriz[lin][col-1 + m->colunas] == VIVA) {
            v++;
        }
    }
    else {
        if(matriz[lin][col-1] == VIVA) {
            v++;
        }
    }
    if(col - 2 < 0) {
        if(matriz[lin][col-2 + m->colunas] == VIVA) {
            v++;
        }
    }
    else {
        if(matriz[lin][col-2] == VIVA) {
            v++;
        }
    }

    return v;
}

void TesteNeumann(Modelo* m) {

    char** alvo = m->vizinhanca;
    int vizinhos_vivos = 0;
    
    // matriz auxiliar
    char** aux = NULL;
    aux = (char**) malloc(m->linhas * sizeof(char*));
    for(int i = 0; i < m->linhas; i++) {
        aux[i] = (char*) malloc((m->colunas+1) * sizeof(char));
        memset(aux[i], 'o', m->colunas);
        aux[i][m->colunas] = '\0';
    }

    for(int geracao = 0; geracao < m->totalRounds; geracao++) {
        for(int linha = 0; linha < m->linhas; linha++) {
            for(int coluna = 0; coluna < m->colunas; coluna++) {

                if(alvo[linha][coluna] == VIVA) {
                    vizinhos_vivos = VizinhosNeumann(m, linha, coluna);
                    if(vizinhos_vivos < 2 || vizinhos_vivos > 3) {
                        aux[linha][coluna] = MORTA;
                        continue;
                    }
                    else {
                        aux[linha][coluna] = VIVA;
                    }
                    continue;
                }

                if(alvo[linha][coluna] == MORTA) {
                    vizinhos_vivos = VizinhosNeumann(m, linha, coluna);
                    if (vizinhos_vivos == 3) {
                        aux[linha][coluna] = VIVA;
                    }
                    else {
                        aux[linha][coluna] = MORTA;
                    }
                }
            }
        }

        // copiando a auxiliar para a vizinhança
        for(int i = 0; i < m->linhas; i++) {
            for(int j = 0; j < m->colunas; j++) {
                alvo[i][j] = aux[i][j];
            }
        }

    }

    for(int i = 0; i < m->linhas; i++){
        free(aux[i]);
    }
    free(aux);
}

Modelo* NovoModelo(int linhas, int colunas, int totalRounds) {
    Modelo* _novoModelo = NULL;
    _novoModelo = (Modelo*) malloc(sizeof(Modelo));
    _novoModelo->totalRounds = totalRounds;
    _novoModelo->linhas = linhas;
    _novoModelo->colunas = colunas;
    char** ptr = NULL;
    ptr = (char**) malloc(linhas * sizeof(char*));
    for(int i = 0; i < linhas; i++) {
        ptr[i] = (char*) malloc(colunas+1 * sizeof(char));
        memset(ptr[i], 'o', colunas-1);
        ptr[i][colunas-1] = '\0';
    }
    _novoModelo->vizinhanca = ptr;
    return _novoModelo;
}

void ApagaModelo(Modelo* m) {
    for(int i = 0; i < m->linhas; i++) {
        free(m->vizinhanca[i]);
    }
    free(m->vizinhanca);
    free(m);
}

void PrintVizinhanca(Modelo* m) {
    for(int i = 0; i < m->linhas; i++) {
        for (int j = 0; j < m->colunas; j++) {
            printf("%c", m->vizinhanca[i][j]);
        }
        printf("\n");
    }
}
