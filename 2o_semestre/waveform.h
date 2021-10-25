#ifndef _WAVEFORM_H_
#define _WAVEFORM_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>
#include <math.h>

typedef struct _coord {
    int index;
    complex double value;
    double magnitude;
} COORD;

FILE* open_file(FILE* stream);

char* ReadLine(FILE* stream, int tamanho_do_buffer, int* eof_alert);

COORD* calcular_magnitude(double complex* vetor_coef, int rdata, int* count);

void insertionsort(COORD* array, int size);

void addzeros(COORD* array, int n_samples, int T);

COORD* callback(COORD* array, int n_samples);

unsigned char *TransformadaInversa(COORD* array, int n_samples);

unsigned char* read_wav_data(char* fname, int* rdata);

double complex *DFT(unsigned char *audio, int length);

#endif