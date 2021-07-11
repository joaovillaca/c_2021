#include <stdio.h>
#include <stdlib.h>

int main() {

   int i, altura;
   char symbol;

   scanf("%d%*c", &altura);
   //fflush(stdin);
   scanf("%c", &symbol);

   if(altura < 1 || altura > 25){
      puts("Altura invalida");
      return 0;
   }

   for (i = 0; i < altura; i++) {

	    for(int j = 0; j < altura - i - 1; j ++) {
		    printf(" ");
	    }

       //o numero de caracteres eh incrementado em 2 => 1, 3, 5, 7...
       //j <= 2*i = 2*linha_atual + 1 iteração
	    for(int j = 0; j <= (2*i); j++) {
		    printf("%c", symbol);
	    }
		
	    printf("\n");
   }
   return 0;
}