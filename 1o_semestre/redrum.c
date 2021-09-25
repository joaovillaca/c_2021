// @author João Villaça
// nusp 10724239

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define debug 0

// Lê string sem tamanho definido via stdin
// alocada dinamicamente na memoria
// é carregada para a memória em blocos
// @return Ponteiro para a string alocada dinamicamente
// @param bufferSize tamanho dos blocos de alocação
char* ReadLine(int bufferSize) {

    char* String = NULL;
    char  input = 'a';
    int tamanhoString = 0, bufferIndex = 0;
    
    char buffer[bufferSize + 1]; 
    buffer[bufferSize] = '\0';
    memset(buffer, '@', bufferSize);
    
    // loop:
    // lê as letras até achar \n
    // ou até encher o buffer com n caracteres
    // depois realoca a string com o tamanho do
    // bloco lido, passa coloca esse bloco na string
    // e limpa o buffer para a proxima iteração
    do {
        input = fgetc(stdin);

        if(input == '\n'){
            buffer[bufferIndex] = '\0';
            bufferIndex++;
        }
        else {
            if(isalnum(input) || input == ' ' || input == '/'){
                buffer[bufferIndex] = input;
                bufferIndex++;
            }
        }

        if(bufferIndex == bufferSize || input == '\n' || input == '\r') {
            tamanhoString += bufferIndex;
            String = (char*) realloc(String, tamanhoString);
            if(String == NULL) {
                return NULL;
            }
            memcpy(String + tamanhoString - bufferIndex, buffer, bufferIndex);
            bufferIndex = 0;
        }
    } while(input != '\n');

    return String;
}

// Transforma a string inteira em lowercase
void Lowercase(char* String) {
    for(int i = 0; String[i]; i++){
        String[i] = tolower(String[i]);
    }
}


// a função compara os caracteres das extremidades pro meio
int Palindromo_recursivo(char* string, int tamanho) {

    if(tamanho >= strlen(string)/2) {
        return 1;
    }

    if(string[tamanho] == ' ' || string[tamanho] == '/') {
        return Palindromo_recursivo(string, ++tamanho);
    }

    if(string[tamanho] == string[strlen(string) - tamanho - 1]) {
        if(debug) printf("%c == %c\n", string[tamanho], string[strlen(string) - tamanho - 1]);
        return Palindromo_recursivo(string, ++tamanho);
    }

    return 0;
}

// a função compara as posições dos espaços para o caso do palindromo indireto
int Palindromo_indireto(char* string, int size, int index, int* espacos, int* espacos_invertidos, int num_espacos) {
    if(index < size && (string[index] == string[strlen(string) - index - 1])) {
        if(espacos[index] == espacos_invertidos[index]) {
            return Palindromo_indireto(string, size, ++index, espacos, espacos_invertidos, num_espacos);
        }
        return 1;
    }
    return 0;
}


int main(int argc, char** argv) {

    char* linha = NULL;
    linha = ReadLine(8);
    Lowercase(linha);

    if(Palindromo_recursivo(linha, 0)) {
        puts("Palindromo direto");
        free(linha);
        return 0;
    }

    char* linha_limpa      = (char*) malloc((strlen(linha) + 1) * sizeof(char));
    char* linha_palindromo = (char*) malloc((strlen(linha) + 1) * sizeof(char));

    // linha_palindromo é a palavra invertida para checar o palindromo indireto
    linha_palindromo[strlen(linha)] = '\0';
    for(int i = 0, j = strlen(linha) - 1; j >= 0; i++){
        linha_palindromo[i] = linha[j--];
    }
    if(debug) puts(linha_palindromo);

    // espacos são os indices dos espacos na string
    // e espacos_palindromo sao os indices de espaco da palavra invertida
    int espacos[strlen(linha)];
    int espacos_palindromo[strlen(linha)];

    // contando espacos/barras e limpando da linha
    int cont = 0, newsize = 0;
    int shift = strlen(linha);
    for(int i = 0; i < strlen(linha); i++) {
        if(linha[i] == ' '|| linha[i] == '/'){
            espacos[cont] = i;
            cont++;
        }
        if(isalnum(linha[i])) {
            for(int j = i; j < shift; j++){
                linha[j] = linha[j + 1];
            }
            linha_limpa[newsize] = linha[i];
            newsize++;
            shift--;
            i--;
        }
    }
    linha_limpa[newsize] = '\0';
    linha_limpa = realloc(linha_limpa, newsize + 1);

    // contando os espacos e barras da linha invertida
    int aux = 0;
    for(int i = 0; i < strlen(linha_palindromo); i++) {
        if(linha_palindromo[i] == ' ' || linha_palindromo[i] == '/'){
            espacos_palindromo[aux] = i;
            aux++;
        }
    }

    if(Palindromo_indireto(linha_palindromo, strlen(linha), 0, espacos, espacos_palindromo, cont)) {
        puts("Palindromo indireto");
        free(linha);
        free(linha_limpa);
        free(linha_palindromo);
        return 0;
    }

    puts("Nao eh um palindromo");
    free(linha);
    free(linha_limpa);
    free(linha_palindromo);
    return 0;
}