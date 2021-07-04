#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define debug 0

// Le string sem tamanho definido via stdin
// alocada dinamicamente na memoria
// é carregada para a memória em blocos de 4 bytes
// @return Ponteiro para a string alocada dinamicamente
char* read_line() {

    char* String = NULL;
    char  letra = 'a';
    int tamanho = 0, bufferIndex = 0;
    char buffer[5] = "0000\0";
    
    // loop:
    // lê as letras até achar \n
    // ou até encher o buffer com 4 caracteres
    // depois realoca a string com o tamanho do
    // bloco lido, passa coloca esse bloco na string
    // e limpa o buffer para a proxima iteração
    do{
        letra = getchar();

        if(letra == '\n'){
            buffer[bufferIndex] = '\0';
        }
        else {
            buffer[bufferIndex] = letra;
        }

        bufferIndex++;

        if(debug) printf("buffer[%d]: %s\n", bufferIndex, buffer);

        if(bufferIndex == 4 || letra == '\n') {

            tamanho += bufferIndex;
            String = (char*) realloc(String, tamanho);
            if(String == NULL) {
                return NULL;
            }

            memcpy(String + tamanho - bufferIndex, buffer, bufferIndex);
            if(debug) puts(String);

            bufferIndex = 0;
            memset(buffer, '0', 4);
        }

    } while(letra != '\n');

    return String;
}

int main(int argc, char** argv) {

    int numeroLinhas;
    scanf("%d\n", &numeroLinhas);
    if (numeroLinhas <= 0) {
        printf("Erro: numero de linhas invalido.\n");
        return 0;
    }

    // Livro é um vetor de strings dinâmicas (sem tamanho definido)
    // cada posição tem um char* que depois pode chamar malloc()
    char** Livro = (char**) malloc(numeroLinhas * sizeof(char*));
    if(Livro == NULL) {
        printf("Erro ao carregar o livro.\n");
        return 1;
    }
    for(int i = 0; i < numeroLinhas; i++) {
        Livro[i] = read_line();
        if(Livro[i] ==  NULL) {
            printf("Erro ao ler linha %d. (Erro ao realocar a linha na memória)\n", i + 1);
            return 1;
        }
    }

    int numeroLinhasLegiveis;
    scanf("%d", &numeroLinhasLegiveis);
    if (numeroLinhasLegiveis <= 0) {
        printf("Erro: numero de linhas legiveis invalido.\n");
        return 0;
    }

    // LinhasLegiveis é um vetor dinâmico de inteiros
    int* LinhasLegiveis = (int*) malloc(numeroLinhasLegiveis * sizeof(int));
    if (LinhasLegiveis == NULL) {
        printf("Erro ao carregar as linhas legiveis.\n");
        return 1;
    }
    for(int i = 0; i < numeroLinhasLegiveis; i++) {
        scanf("%d", &LinhasLegiveis[i]);
        getchar();
    }

    if(debug) {
        for(int i = 0; i < numeroLinhasLegiveis; i++) {
            printf("%d", LinhasLegiveis[i]);
        }
        printf("\n");
    }

    // Acessando e imprimindo as
    // linhas legiveis do livro
    for(int i = 0; i < numeroLinhasLegiveis; i++) {
        puts(Livro[LinhasLegiveis[i]]);
    }

    for(int i = 0; i < numeroLinhas; i++) {
        free(Livro[i]);
    }
    free(Livro);
    free(LinhasLegiveis);

    return EXIT_SUCCESS;
}