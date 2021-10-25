#include "waveform.h"

#define debug 0


// calcula o argumento de cada um dos números complexos em vetor_coef
// @param n_samples - tamanho da sample do arquivo wav lido
COORD* calcular_magnitude(double complex* vetor_coef, int n_samples, int* count) {
    COORD* vetor_magnitudes = NULL;
    vetor_magnitudes = (COORD*) malloc(n_samples * sizeof(COORD));
    for(int i = 0; i < n_samples; i++) {
        vetor_magnitudes[i].magnitude = cabs(vetor_coef[i]);
        vetor_magnitudes[i].index = i;
        vetor_magnitudes[i].value = vetor_coef[i];
        if(debug) {
            printf("%.2lf ", vetor_magnitudes[i].magnitude);
        }
        if(creal(vetor_coef[i]) <= 0.0 && cimag(vetor_coef[i]) <= 0.0) {
            *count += 1;
        }
    }
    return vetor_magnitudes;
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


// @author Gabriel Alves Kuabara - Monitor ICC II
unsigned char* read_wav_data(char* fname, int* r_data) {
    FILE* fp = fopen(fname, "rb");
    unsigned char buf4[4];

    fseek(fp, 40, SEEK_SET);
    fread(buf4, sizeof(buf4), 1, fp);
    int dataSize = buf4[0] | buf4[1]<<8 | buf4[2]<<16 | buf4[3]<<24;
    *r_data = dataSize;

    unsigned char* data = malloc(sizeof(*data) * (dataSize));
    
    int i = 0;
    while (i < dataSize) {
        fread(&data[i++], sizeof(unsigned char), 1, fp);
    }
    fclose(fp);
    return data;
}


// @author Gabriel Alves Kuabara - Monitor ICC II
double complex *DFT(unsigned char *audio, int length) {
    double complex *coef = (double complex *) calloc(length, sizeof(double complex));

    for (int k = 0; k < length; k++) {
        for (int n = 0; n < length; n++) {
            coef[k] += audio[n] * cexp((-2.0 * M_PI * (((k+1) * n * 1.0) / (length * 1.0))) * _Complex_I);
        }
        //printf("%.1lf + %.1lfi | ", creal(coef[k]), cimag(coef[k]));
    }
    return coef;
}

// Insertion sort decrescente adaptado para a struct COORD
void insertionsort(COORD* array, int size){
    int i, j;
    COORD key;
    for (i = 1; i < size; i++) {
        key = array[i];
        j = i - 1;
        while (j >= 0 && array[j].magnitude < key.magnitude) {
            array[j + 1].value = array[j].value;
            array[j + 1].index = array[j].index;
            array[j + 1].magnitude = array[j].magnitude;
            j = j - 1;
        }
        array[j + 1].magnitude = key.magnitude;
        array[j + 1].value = key.value;
        array[j + 1].index = key.index;
    }
}


// item 6 - deixa somente os T primeiros coeficientes no vetor
// e preenche o restante com zeros
void addzeros(COORD* array, int n_samples, int T) {
    int aux;
    for(int i = 0; i < T; i++) {
        aux = (int) array[i].magnitude;
        printf("%d\n", aux);
    }
    for(int i = 0; i < n_samples; i++) {
        if(array[i].magnitude < array[T-1].magnitude) {
            array[i].value = 0;
        }
    }
}

// item 7 - retorna os coeficientes para as posições antes da ordenação
COORD* callback(COORD* array, int n_samples) {
    COORD* ret = (COORD*) malloc(n_samples * sizeof(COORD));
    for(int i = 0; i < n_samples; i++) {
        ret[array[i].index].value = array[i].value;
        ret[array[i].index].index = array[i].index;
    }
    free(array);
    return ret;
}

unsigned char *TransformadaInversa(COORD* array, int n_samples) {
    double complex* coef = (double complex*) malloc(n_samples * sizeof(double complex));
    unsigned char* ret = (unsigned char*) malloc(n_samples * sizeof(unsigned char));

    for(int i = 0; i < n_samples; i++) {
        for(int j = 0; j < n_samples; j++) {
            coef[i] += array[j].value * cexp((2.0 * M_PI * (((j+1) * i * 1.0) / (n_samples * 1.0))) * _Complex_I);
        }
        coef[i] = coef[i]/n_samples;
        ret[i] = (unsigned char) creal(coef[i]);
        if(debug) {
            printf("%u ", ret[i]);
        }
    }
    return ret;
}