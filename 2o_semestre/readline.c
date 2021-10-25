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

// exemplo de chamada
//
// int eof_alert = 0;
// char* string = NULL;
// string = ReadLine(stdin, 8, &eof_alert);