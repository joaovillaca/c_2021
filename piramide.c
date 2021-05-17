#include <stdio.h>
#include <stdlib.h>

int main() {

   int i, espacos, altura;
   char symbol;

   scanf("%d%*c", &altura);
   //fflush(stdin);
   scanf("%c", &symbol);

   if(altura < 1 || altura > 25){
      puts("Altura invalida");
      return 0;
   }

   espacos = altura - 1;

   for (i = 0; i < altura; i++) {

	    for(int j = 0; j < espacos; j ++) {
		    printf(" ");
	    }
	    for(int j = 0; j <= (2*i); j++) {
		    printf("%c", symbol);
	    }
		
	    printf("\n");
	    espacos--;
   }
   return 0;
}