#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    
    int entrada;
    scanf("%d", &entrada);

    if(entrada < 19){
        puts("Número pequeno demais.");
        return 0;
    }

    int cont = 0;
    int modulos[3];
    modulos[0] = entrada % 11;
    modulos[1] = entrada % 13;
    modulos[2] = entrada % 19;

    for(int i = 0; i < 3; i++){
        if(modulos[i] == 0){
            cont++;
        }
    }
    switch(cont){
        case 0:
            printf("%d", entrada);
            break;
        case 1:
            printf("Ba");
            if(modulos[0] == 0){
                printf("Ba");
            }
            else if(modulos[1] == 0){
                printf("Dum");
            }
            else if(modulos[2] == 0){
                printf("Tss");
            }
            break;
        case 2:
            if(modulos[0] == 0){
                printf("Ba");
            }
            if(modulos[1] == 0){
                printf("DumDum");
            } else {
                printf("Dum");
            }
            if(modulos[2] == 0){
                printf("Tss");
            }
            break;
        case 3:
            printf("BaDumTssTss");
    }

    printf("\n");
    return 0;
}