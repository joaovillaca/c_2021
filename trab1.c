#include <stdio.h>
#include <stdlib.h>

//Trabalho 1 ICC-I 2021
//João Vitor Nascimento Villaça - 10724239

int main(int argc, char** argv){

    int fita[512];

    for(int i = 0; i < 512; i++){
        scanf("%d", &fita[i]);
    }

    int ponteiroInstrucao = 0;
    int opcode;
    int arg1, arg2, dest;

    puts("Saida do programa:");

    while(ponteiroInstrucao < 512){

        opcode = fita[ponteiroInstrucao];

        switch(opcode){

            case 0: //HALT
                ponteiroInstrucao = 512;
                break;

            case 1: //ADD
                arg1 = fita[ponteiroInstrucao + 1];
                arg2 = fita[ponteiroInstrucao + 2];
                dest = fita[ponteiroInstrucao + 3];
                fita[dest] = fita[arg1] + fita[arg2];
                ponteiroInstrucao += 4;
                break;
            
            case 2: //MUL
                arg1 = fita[ponteiroInstrucao + 1];
                arg2 = fita[ponteiroInstrucao + 2];
                dest = fita[ponteiroInstrucao + 3];
                fita[dest] = fita[arg1] * fita[arg2];
                ponteiroInstrucao += 4;
                break;

            case 3: //CLT
                arg1 = fita[ponteiroInstrucao + 1];
                arg2 = fita[ponteiroInstrucao + 2];
                dest = fita[ponteiroInstrucao + 3];
                fita[dest] = fita[arg1] < fita[arg2] ? 1 : 0;
                ponteiroInstrucao += 4;
                break;
            
            case 4: //CEQ
                arg1 = fita[ponteiroInstrucao + 1];
                arg2 = fita[ponteiroInstrucao + 2];
                dest = fita[ponteiroInstrucao + 3];
                fita[dest] = fita[arg1] == fita[arg2] ? 1 : 0;
                ponteiroInstrucao += 4;
                break;

            case 5: //JMP
                arg1 = fita[ponteiroInstrucao + 1];
                ponteiroInstrucao = fita[arg1];
                break;
            
            case 6: //JEQ
                arg1 = fita[ponteiroInstrucao + 1];
                arg2 = fita[ponteiroInstrucao + 2];
                if(fita[arg1] != 0) ponteiroInstrucao = fita[arg2];
                else ponteiroInstrucao += 3;
                break;

            case 7: //CPY
                arg1 = fita[ponteiroInstrucao + 1];
                arg2 = fita[ponteiroInstrucao + 2];
                fita[arg2] = fita[arg1];
                ponteiroInstrucao += 3;
                break;

            case 8: //PUT
                arg1 = fita[ponteiroInstrucao + 1];
                putchar(fita[arg1]);
                ponteiroInstrucao += 2;
                break;
            
            case 9: //PTN
                arg1 = fita[ponteiroInstrucao + 1];
                printf("%d", fita[arg1]);
                ponteiroInstrucao += 2;
                break;
            
            default:
                break;
        }
    }
    
    printf("\n");
    puts("Estado final da fita:");
    for(int i = 0; i < 512; i++){
        printf("%d\n", fita[i]);
    }
    return 0;
}