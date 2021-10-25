// SCC0201 - Introdução a Ciências de Computação
// Trabalho 02: Compressão de Áudio
// @author João Vitor N. Villaça - 10724230

#include "waveform.h"

#define debug 0


int main() {

    char* filename = (char*) malloc(50 * sizeof(char));
    scanf("%s", filename);

    int numero_de_coef = 0;
    scanf("%d\n", &numero_de_coef);

    // n_samples é o tamanho dos samples recebido por referência
    int n_samples = 0;
    unsigned char* wav_data = read_wav_data(filename, &n_samples);

    printf("%d\n", n_samples);

    double complex* vetor_coef = DFT(wav_data, n_samples);

    int count = 0;
    COORD* vetor_magnitudes = calcular_magnitude(vetor_coef, n_samples, &count);
    printf("%d\n", count);
    
    if(debug) {
        for(int i = 0; i < n_samples; i++) {
            printf("%.2lf ", vetor_magnitudes[i].magnitude);
        }
    }

    insertionsort(vetor_magnitudes, n_samples);

    if(debug) {
        for(int i = 0; i < n_samples; i++) {
            printf("%.2lf ", vetor_magnitudes[i].magnitude);
        }
    }

    addzeros(vetor_magnitudes, n_samples, numero_de_coef);

    vetor_magnitudes = callback(vetor_magnitudes, n_samples);

    if(debug) {
        for(int i = 0; i < n_samples; i++) {
            printf("%.1lf + %.1lfi ", creal(vetor_magnitudes[i].value), cimag(vetor_magnitudes[i].value));
        }
    }

    unsigned char* audio = TransformadaInversa(vetor_magnitudes, n_samples);

    // salvando o arquivo binario
    unsigned char header[44];
    FILE* fp = fopen(filename, "rb");
    rewind(fp);
    fread(header, sizeof(unsigned char), 44, fp);
    fclose(fp);
    fp = fopen("comp.wav", "wb");
    fwrite(header, sizeof(unsigned char), 44, fp);
    fwrite(audio, sizeof(unsigned char), n_samples, fp);
    fclose(fp);

    free(filename);
    free(wav_data);
    free(vetor_coef);
    free(vetor_magnitudes);
    free(audio);

    return 0;
}
