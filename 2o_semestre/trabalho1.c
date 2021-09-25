// SCC0201 - 2021.2 - Trabalho 01: Campo Minado
// @author João Villaça
// NUSP:   10724239

// Este programa interage com um tabuleiro de Campo Minado
// O tabuleiro é uma matriz de caracteres ascii



#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define debug 0



// Definição do tabuleiro
#define MINA  '*'
#define VAZIO '.'



// Definição das operações pricipais
enum OPCODE {
    IMPRIMIR = 1,
    DICAS = 2,
    CONTROLE = 3
};



// Funções utilizadas
void   operacao_imprimir(void);
void   operacao_dicas(void);
void   operacao_controle(void);
char*  ReadLine(FILE* stream, int tamanho_do_buffer, int* eof_alert);
char** ReadMap(FILE* stream, int* linhas_tabuleiro);
void   PrintMap(char** map, int linhas_tabuleiro);
void   FreeMap(char** map, int linhas_tabuleiro);
void   MarcaDicas(char** map, int linhas_tabuleiro);



int main(int argc, char** argv) {

    int operacao;
    scanf("%d\n", &operacao);

    switch(operacao) {

        case IMPRIMIR:
            operacao_imprimir();
            break;

        case DICAS:
            operacao_dicas();
            break;

        case CONTROLE:
            operacao_controle();
            break;

        default:
            break;
    }

    return EXIT_SUCCESS;
}



FILE* abre_arquivo() {
    char* nome_do_arquivo = NULL;
    int eof_alert = 0;
    nome_do_arquivo = ReadLine(stdin, 4, &eof_alert);

    FILE* board_file = fopen(nome_do_arquivo, "r");
    if(board_file == NULL) {
        puts("board_file == NULL");
        return NULL;
    }
    return board_file;
}



// (3.2) Opção 1: Imprimir o tabuleiro
void operacao_imprimir(void) {

    FILE* board_file = abre_arquivo();
    if(board_file == NULL) {
        return;
    }

    int linhas_tabuleiro = 0;
    char** tabuleiro = ReadMap(board_file, &linhas_tabuleiro);

    PrintMap(tabuleiro, linhas_tabuleiro);
    FreeMap(tabuleiro, linhas_tabuleiro);
}

// (3.3) Opção 2: Imprimir o tabuleiro com as dicas
void operacao_dicas(void) {

    FILE* board_file = abre_arquivo();
    if(board_file == NULL) {
        return;
    }

    int linhas_tabuleiro = 0;
    char** tabuleiro = ReadMap(board_file, &linhas_tabuleiro);
    MarcaDicas(tabuleiro, linhas_tabuleiro);
    PrintMap(tabuleiro, linhas_tabuleiro);
    FreeMap(tabuleiro, linhas_tabuleiro);   
}


// (3.4) Opção 3: Jogada do usuário
void operacao_controle(void) {
    FILE* board_file = abre_arquivo();
    if(board_file == NULL) {
        return;
    }
    int x, y;
    scanf("%d %d", &x, &y);
    int linhas_tabuleiro = 0;
    char** tabuleiro = ReadMap(board_file, &linhas_tabuleiro);
    if(tabuleiro[x][y] == '*') {
        MarcaDicas(tabuleiro, linhas_tabuleiro);
        PrintMap(tabuleiro, linhas_tabuleiro);
    } else {
        MarcaDicas(tabuleiro, linhas_tabuleiro);
        int tamanho = strlen(tabuleiro[0]);
        if(tabuleiro[x][y] == '1' || tabuleiro[x][y] == '2' || tabuleiro[x][y] == '3') {
            for(int i = 0; i < linhas_tabuleiro; i++) {
                for(int j = 0; j < tamanho; j++) {
                    if(i == x && j == y) {
                        printf("%c", tabuleiro[i][j]);
                    } else {
                        printf("X");
                    }
                }
                printf("\n");
            }
        }
    }
    FreeMap(tabuleiro, linhas_tabuleiro);
}



// Lê um tabuleiro de stream e aloca numa matriz dinamicamente, 
// conta o número de linhas do tabuleiro e atribui por referência a linhas_tabuleiro
// @param Stream alvo da leitura (arquivo, stdin etc)
// @return Ponteiro para a matriz
char** ReadMap(FILE* stream, int* linhas_tabuleiro) {

    int eof_alert = 0;
    char* linha = NULL;
    char **tabuleiro = NULL;

    tabuleiro = (char**) malloc(sizeof(char*));

    // Loop de ReadLine para ler as linhas do tabuleiro
    // Se não chegar no EOF, o tabuleiro é realocado para alocar mais linhas
    do {
        linha = ReadLine(stream, 8, &eof_alert);
        if(linha == NULL) {
            continue;
        }

        if(eof_alert != 1) {
            *linhas_tabuleiro += 1;

            // alocando mais uma linha no tabuleiro
            tabuleiro = (char**) realloc(tabuleiro, sizeof(char*) * (*linhas_tabuleiro + 1));
            tabuleiro[*linhas_tabuleiro - 1] = (char*) malloc((strlen(linha) + 1) * sizeof(char));
            tabuleiro[*linhas_tabuleiro - 1][strlen(linha)] = '\0';

            // copiando a string para o tabuleiro
            for(int i = 0; i < strlen(linha); i++) {
                tabuleiro[*linhas_tabuleiro - 1][i] = linha[i];
            }
        }
    } while(eof_alert != 1);

    return tabuleiro;
}



// Imprime os labirintos sem dicas
void PrintMap(char** map, int linhas_tabuleiro) {
    for(int i = 0; i < linhas_tabuleiro; i++) {
        puts(map[i]);
    }
}

// free() para os labirintos
void FreeMap(char** map, int linhas_tabuleiro) {
    for(int i = 0; i < linhas_tabuleiro; i++) {
        free(map[i]);
    }
    free(map);
}

// Lê uma linha de stream e aloca numa string dinamicamente, 
// se chegar no fim do arquivo, eof_alert recebe o valor 1 por referência
// @param Stream arquivo para ler
// @return Ponteiro para a string
char* ReadLine(FILE* stream, int tamanho_do_buffer, int* eof_alert) {

    char *string = NULL;
    char buffer[tamanho_do_buffer + 1];
    char letra;
    int iterator = 0;
    int tamanho = 0;

    do {

        letra = fgetc(stream);

        if(letra == EOF) {
            *eof_alert = 1;
            return NULL;
        }

        if (letra == '\n' || letra == '\r') {
            letra = '\0';

            // retorna NULL se a string for só um \n ou \r
            if(tamanho == 0) {
                return NULL;
            }
        }

        buffer[iterator] = letra;
        iterator += 1;

        // após ler um bloco, aloca mais memória para a string
        if(iterator == tamanho_do_buffer || letra == '\0'){
            tamanho += iterator;
            string = (char*) realloc(string, tamanho);
            memcpy(string + tamanho - iterator, buffer, iterator);
            iterator = 0;
        }
    } while(letra != '\0' && letra != EOF);

    string = (char*) realloc(string, tamanho+1);
    string[tamanho] = '\0';

    if(debug) {
        puts(string);
    }

    *eof_alert = 0;
    return string;
}


// Marca as dicas no tabuleiro
void MarcaDicas(char** map, int linhas_tabuleiro) {
    
    int tamanho_linha = strlen(map[0]);

    if(debug) {
        printf("tam = %d\n", tamanho_linha);
    }

    // percorrendo o tabuleiro
    for(int i = 0; i < linhas_tabuleiro; i++) {
        for(int j = 0; j < tamanho_linha; j++) {

            // Marcando as dicas nos adjacentes das bombas
            if(map[i][j] == '*') {

                if(j != tamanho_linha - 1) {
                    if(map[i][j + 1] == '.') {
                        map[i][j + 1] = '1';
                    } else if(map[i][j + 1] != '*') {
                        map[i][j + 1] += 1;
                    }
                }
                if(i != linhas_tabuleiro - 1) {
                    if(map[i + 1][j] == '.') {
                        map[i + 1][j] = '1';
                    } else if(map[i + 1][j] != '*') {
                        map[i + 1][j] += 1;
                    }
                }
                if(i != 0) {
                    if(map[i - 1][j] == '.') {
                        map[i - 1][j] = '1';
                    } else if(map[i - 1][j] != '*') {
                        map[i - 1][j] += 1;
                    }
                }
                if(j != 0) {
                    if(map[i][j - 1] == '.') {
                        map[i][j - 1] = '1';
                    } else if(map[i][j - 1] != '*') {
                        map[i][j - 1] += 1;
                    }
                }
                if(i != (linhas_tabuleiro - 1) && j != (tamanho_linha - 1)) {
                    if(map[i + 1][j + 1] == '.') {
                        map[i + 1][j + 1] = '1';
                    } else if(map[i + 1][j + 1] != '*') {
                        map[i + 1][j + 1] += 1;
                    }
                }
                if(i != 0 && j != 0) {
                    if(map[i - 1][j - 1] == '.') {
                        map[i - 1][j - 1] = '1';
                    } else if(map[i - 1][j - 1] != '*') {
                        map[i - 1][j - 1] += 1;
                    }
                }
                if(i != 0 && j != (tamanho_linha - 1)) {
                    if(map[i - 1][j + 1] == '.') {
                        map[i - 1][j + 1] = '1';
                    } else if(map[i - 1][j + 1] != '*') {
                        map[i - 1][j + 1] += 1;
                    }
                }
                if(j != 0 && i != (linhas_tabuleiro - 1)) {
                    if(map[i + 1][j - 1] == '.') {
                        map[i + 1][j - 1] = '1';
                    } else if(map[i + 1][j - 1] != '*') {
                        map[i + 1][j - 1] += 1;
                    }
                }
            }
        }
    }
}
