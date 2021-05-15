#include <stdio.h>

int main(int argc, char** argv){
    float temp;
    scanf("%f", &temp);
    printf("%.2f\n", (5.0*(temp - 32.0))/9.0);
}