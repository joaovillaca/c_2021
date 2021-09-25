#include <stdio.h>
#include <math.h>

// Estrutura de dados
typedef struct _ponto {
    int x;
    int y;
    int terreno;
} Ponto;

// Funções
float DistanciaEuclidiana(Ponto src, Ponto dest);
float DistanciaHermanns(Ponto src, Ponto dest);

int main(int argc, char** argv){

    int linhas;
    scanf("%d", &linhas);
    if(linhas <= 0) {
        puts("Falha no processamento dos dados.");
        return 0;
    }    

    Ponto PontoInicial, PontoAtual, PontoAnterior;
    
    scanf("%d %d %d", &PontoInicial.x, &PontoInicial.y, &PontoInicial.terreno);
    if(PontoInicial.terreno < -1 || PontoInicial.terreno > 1){
        puts("Falha no processamento dos dados.");
        return 0;
    }
    
    PontoAnterior.x = PontoInicial.x;
    PontoAnterior.y = PontoInicial.y;
    PontoAnterior.terreno = PontoInicial.terreno;

    float deltaEuclides = 0, deltaHermanns = 0;
    int parques = 0, casas = 0, terrenos = 0;
    float distEuclidiana;
    float distHermanns;

    for(int i = 1; i <= linhas; i++){

        if(i == linhas) {
            PontoAtual.x = PontoInicial.x;
            PontoAtual.y = PontoInicial.y;
        }
    
        scanf("%d %d %d", &PontoAtual.x, &PontoAtual.y, &PontoAtual.terreno);
        if(PontoAtual.terreno < -1 || PontoAtual.terreno > 1){
            puts("Falha no processamento dos dados.");
            return 0;
        }

        switch(PontoAnterior.terreno) {
            
            case -1:
                distEuclidiana = DistanciaEuclidiana(PontoAnterior, PontoAtual);
                deltaEuclides = deltaEuclides + distEuclidiana;
                deltaHermanns = deltaHermanns + distEuclidiana;
                terrenos++;
                break;
            
            case  0:
                distHermanns = DistanciaHermanns(PontoAnterior, PontoAtual);
                deltaEuclides = deltaEuclides + distHermanns;
                deltaHermanns = deltaHermanns + distHermanns;
                casas++;
                break;
            
            case  1:
                deltaEuclides = deltaEuclides + DistanciaEuclidiana(PontoAnterior, PontoAtual);
                deltaHermanns = deltaHermanns + DistanciaHermanns(PontoAnterior, PontoAtual);
                parques++;
                break;
            
            default:
                printf("Erro | pontoAnterior.terreno = %d | linha #%d\n", PontoAnterior.terreno, i + 1);
        }
        PontoAnterior = PontoAtual;
    }
    
    printf("Ao todo, foi passado por %d terrenos baldios, %d terrenos residenciais e %d parques.\n", terrenos, casas, parques);
    printf("A diferenca total de distancia percorrida foi de %.2f metros.\n", deltaHermanns - deltaEuclides);
    return 0;
}

float DistanciaEuclidiana(Ponto src, Ponto dest) {
    return sqrt(pow(dest.x - src.x, 2) + pow(dest.y - src.y, 2));
}

float DistanciaHermanns(Ponto src, Ponto dest) {
    return fabs(dest.x - src.x) + fabs(dest.y - src.y);
}
