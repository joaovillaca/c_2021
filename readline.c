#include <stdio.h>
#include <stdlib.h>
#define debug 1

char* read_line() {

    char* String = NULL;
    char  letra;
    int tamanho = 0;
    
    // Loop:
    // ler a letra;
    // realocar a string para colocar a proxima letra
    // adicionar a nova letra à string
    // se for um \n, para e entra um \0 no lugar
    do {
        scanf("%c", &letra);
        tamanho++;
        String = (char*) realloc(String, tamanho + 1);
        if(String == NULL) return NULL;
        String[tamanho] = '\0';
        String[tamanho - 1] = letra;
    } while(letra != '\n');

    String = (char*) realloc(String, tamanho);
    String[tamanho - 1] = '\0';
    if(debug) puts(String);
    return String;
}

int main(int argc, char** argv) {

    int numeroLinhas;
    scanf("%d\n", &numeroLinhas);
    if (numeroLinhas <= 0) {
        printf("Erro: numero de linhas invalido.\n");
        return 0;
    }

    char** Livro = (char**) malloc(numeroLinhas * sizeof(char*));
    if(Livro == NULL) {
        printf("Erro ao carregar o livro.\n");
        return 1;
    }
    for(int i = 0; i < numeroLinhas+1; i++) {
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
    }

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