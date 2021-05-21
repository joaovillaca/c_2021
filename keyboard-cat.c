#include <stdio.h>

int main(){

    char buffer[49];
    int tamanho;

    char aux;
    int contador = 0;

    while(1){
        if(contador > 48) break;
        if(aux == '\n') break;
            
        aux = fgetc(stdin);

        if(aux != ' '){
            if(aux == '_') buffer[contador] = ' ';
            else if(aux == 'E') buffer[contador] = '\n';
            else buffer[contador] = aux;

            contador++;
        }
    }

    scanf("%d", &tamanho);

    int cifra[tamanho];

    for(int i = 0; i < tamanho; i++){
        scanf("%d", &cifra[i]);
    }

    for(int i = 0; i < tamanho; i++){
        printf("%c", buffer[cifra[i]]);
    }

    return 0;
}

