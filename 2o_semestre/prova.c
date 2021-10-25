// Prova 1 - ICC II - 2021.2
// @author João Vitor Nascimento Villaça - 10724239

#include <stdio.h>
#include <stdlib.h>

void imprimeVetor(int* vetor, int tamanho){
	int i;
	printf("Vetor: ");
	for (i=0; i<tamanho; i++) printf("%i ", vetor[i]);
	printf("\n");
}

int** alloc_matrix(int m) {
	int **mat = malloc(sizeof(int*)*m);
	srand(m);
	
	int in = 0;
	// aloca matriz ordenada
	for (int i = 0; i < m; i++) {
		mat[i] = malloc(sizeof(int)*m);
	    	for (int j = 0; j < m; j++) {
			if (i == j) in+= (rand()%3)+1;
			else in += rand()%3;
			mat[i][j] = in;
		}
	}
	// desordena matriz triangular superior
	for (int i = 0; i < m-2; i++) {
	    	for (int j = i+1; j < m-1; j++) {
			int swaps = (int)((m-j)/2.0)+1;
			for (int t = 1; t <= swaps; t++) {
				int a = (rand()%(m-j))+j;
				int b = (rand()%(m-j))+j;
				int tmp = mat[i][a];
				mat[i][a] = mat[i][b];
				mat[i][b] = tmp;
			}
		}

	}
	return mat;
}

int nao_otimizada (void){
	int m;
	scanf("%d", &m);
	
	int vetor[m*m];
	int** matriz = alloc_matrix(m);
	
    // ============================== contagem de operações
    // obs: utilizei o código disponibilizado no runcodes (solucao_bruta.c)

	int i, j, k = 0;
	for (i=0; i<m; i++)
		for (j=0; j<m; j++)
			vetor[k++] = matriz[i][j];   // aritmetica * m

	for(i = 0; i < m*m-1; i++){
		for(j = 0; j < m*m-1-i; j++){
			if (vetor[j] > vetor[j+1]){  // (aritmetica + comparacao) * m * m - i
				int aux = vetor[j];
				vetor[j] = vetor[j+1];   // aritmetica * m * m - i
				vetor[j+1] = aux;        // aritmetica * m * m - i
			}
		}
	}

	k = 0;
	for (i=0; i<m; i++){
		for (j=0; j<m; j++){
			matriz[i][j] = vetor[k++];    // aritmetica * m
			printf("%i ", matriz[i][j]);
		}
		printf("\n");
	}

    // ============================== formulando a equação

    // f(n) = a * (m) + (a + c) * m * (m - i) + a * m * (m - i) + a * m * (m - i) + a * m = 
    // = 2a * m + (3a + c) * m * (m - i) =
    // = 2a * m + (3a + c) * (m^2 - mi) =
    // = 2a * m + 3a * (m^2 - mi) + c * (m^2 - mi) =
    // = 2a * m + (3am^2 - 3ami) + (cm^2 - cmi) =
    // = 2am + 3am^2 - 3ami + cm^2 - cmi
    // f(n) = 3am^2 + cm^2 + 2am - (3a - c) * mi

    // ============================== achando a forma fechada

    // somatorio 1: (a) de i = 1 até m                ---> (m^2 + 1) / 2
    // somatorio 2: [(3a + c) * m-i] de 1 até m       ---> [(m-1) * ((m-1) + 1)] / 2
    // somatorio 3: (a) de i = 1 até m                ---> (m^2 + 1) / 2

    // forma fechada (trocando m por n):
    // f(n) = [a * (2 * ((n^2 + 1) / 2))] + [(3a + c) * ((n-1) * ((n-1) + 1))) / 2] =
    // f(n) = [a * (n^2 + 1)] + [(3a + c) * (n^2 - n) / 2]

	free(matriz);

	return 0;
}


// Otimização + contagem de operações da nova solução
// obs: utilizei o código disponibilizado no runcodes (solucao_bruta.c)

int main (int argc, char** argv){
	int m;
	scanf("%d", &m);
	
	int vetor[m*m];
	int** matriz = alloc_matrix(m);
	
	int i, j, k = 0;
	for (i=0; i<m; i++)
		for (j=0; j<m; j++)
			vetor[k++] = matriz[i][j];  // aritmetica * m

    // otimização: a variavel 'troca' ativa a quebra do loop
    // quando o inteiro alvo já está ordenado
    // obs: utilizei o código disponibilizado no runcodes (solucao_bruta.c)
    int troca;
	for(i = 0; i < m*m-1; i++){
        troca = 0;
		for(j = 0; j < m*m-1-i; j++){
			if (vetor[j] > vetor[j+1]){  // aritmetica + comparação * m * m - i
				int aux = vetor[j];
				vetor[j] = vetor[j+1];   // aritmetica * m * m - i
				vetor[j+1] = aux;        // aritmetica * m * m - i
                troca = 1;
			}
		}
        if(troca == 0) {                 // comparação * m * m
            break;
        }
	}

	k = 0;
	for (i=0; i<m; i++){
		for (j=0; j<m; j++){
			matriz[i][j] = vetor[k++];   // aritmetica * m
			printf("%i ", matriz[i][j]);
		}
		printf("\n");
	}

    // ============================== formulando a equação
    
    // f(n) = 2 * (a * m) + (3a + c) * (m*m-i) + c * m^2

    // somatorio 1: (a) de i = 1 até m                ---> (m^2 + 1) / 2
    // somatorio 2: [(3a + c) * m-i] de 1 até m       ---> [(m-1) * ((m-1) + 1)] / 2
    // somatorio 3: (a) de i = 1 até m                ---> (m^2 + 1) / 2
    // somatorio 4: (c) de i = 1 até m*m              ---> (m + 1) * m / 2 ---> (m^2 + m) / 2

    // ============================== achando a forma fechada

    // f(n) = 2a * (m^2 + 1) + (3a + c) * ((m-1) * ((m-1) + 1))) + c * (m^2 + m) =
    // f(n) = 2a * (2m^2 + 2) + (3a + c) * (m^2 - m) + c * (m^2 + m) (operações separadas por tipo)
    // f(n) = 4m^2 + 2 (somente o número total de operações)

	free(matriz);

	return 0;
}
