// SCC0201 - 2021.2 - Trabalho 01: Campo Minado
// @author João Villaça
// NUSP:   10724239

// Este programa interage com um tabuleiro de Campo Minado
// O tabuleiro é uma matriz de caracteres ascii



#include <stdio.h>
#include <stdlib.h>



// Definição do tabuleiro
#define MINA  '*'
#define VAZIO '.'

// Definição das operações pricipais
typedef enum _OPCODE {
    imprimir = 1,
    dicas = 2,
    controle = 3
} OPCODE;

// Funções utilizadas
void   operacao_imprimir(void);
void   operacao_dicas(void);
char*  ReadLine(FILE* stream, int tamanho_do_buffer, int* eof_alert);



int main(int argc, char** argv) {

    OPCODE operacao;
    scanf("%d", &operacao);

    switch(operacao) {

        case imprimir:
            operacao_imprimir();
            break;

        case dicas:
            break;

        case controle:
            break;

        default:
            break;
    }

    return EXIT_SUCCESS;
}



// (3.2) Opção 1: Imprimir o tabuleiro
void operacao_imprimir(void) {

    char* nome_do_arquivo = NULL;
    int eof_alert = 0;
    nome_do_arquivo = ReadLine(stdin, 4, &eof_alert);

    FILE* board_file = fopen(nome_do_arquivo, "r");
    if(board_file == NULL) {
        puts("board_file == NULL");
        printf("Encerrando | Linha %d", __LINE__);
    }

    int linhas_tabuleiro = 0;
    char** tabuleiro = ReadMap(board_file, &linhas_tabuleiro);
    PrintMap(tabuleiro);

}

// (3.3) Opção 2: Imprimir o tabuleiro com as dicas
void operacao_dicas(void) {

    char* nome_do_arquivo = NULL;
    int eof_alert = 0;
    nome_do_arquivo = ReadLine(stdin, 4, &eof_alert);

}

// Lê um tabuleiro de stream e aloca numa matriz dinamicamente, 
// conta o número de linhas do tabuleiro e atribui por referência a linhas_tabuleiro
// @param Stream/arquivo para ler
// @return Ponteiro para a matriz
char** ReadMap(FILE* stream, int* linhas_tabuleiro) {

    int eof_alert = 0;
    char* linha = NULL;
    char **tabuleiro = NULL;
    int iterador = 0;

    tabuleiro = (char**) malloc(sizeof(char*));

    do {
        tabuleiro[iterador] = ReadLine(stream, 7, &eof_alert);
        if(eof_alert != 1) {
            iterador += 1;
            tabuleiro = (char**) realloc(sizeof())
        }
    } while(eof_alert != 1);
    


}

void PrintMap(char** map) {

}


// Lê uma linha de stream e aloca numa string dinamicamente, 
// se chegar no fim do arquivo, eof_alert recebe o valor 1 por referência
// @param Stream/arquivo para ler
// @return Ponteiro para a string
char* ReadLine(FILE* stream, int tamanho_do_buffer, int* eof_alert) {

    char *string = NULL;
    char buffer[tamanho_do_buffer + 1];
    char letra;
    int iterator = 0;
    int tamanho = 0;

    do {

        fscanf(stream, "%c", &letra);

        if (letra == '\n' || letra == '\r' || letra == EOF) {
            letra = '\0';
        }

        buffer[iterator] = letra;
        iterator += 1;

        if(iterator == tamanho_do_buffer || letra == '\0'){
            tamanho += iterator;
            string = (char*) realloc(string, tamanho);
            memcpy(string + tamanho - iterator, buffer, iterator);
            iterator = 0;
        }
    } while(letra != '\0' && letra != EOF);

    if(letra == EOF) {
        *eof_alert = 1;
    } else {
        *eof_alert = 0;
    }

    string = (char*) realloc(string, tamanho);

    return string;
}