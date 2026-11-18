#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lista.h"
//Cria uma Lista Nova e a retorna
Lista * CriaLista(){
   Lista * L = (Lista*)malloc(sizeof(Lista));
    L->Tamanho = 0;
    return L;
}
//Preenche a Lista com um novo valor de cidade, retorna 1 se sucesso
int PreencheLista(Lista *L , Cidade c){
    if(L->Tamanho == MAXTAM){
        printf("Erro: Vetor de listas preenchidos ao máximo");
        return 0;
    }
    L->Tamanho +=1;
    L->Item[L->Tamanho -1] = c;
    return 1;

}
//Verifica Se a Lista está vazia
int Vazia (Lista *L){
    return !L->Tamanho;
}

double distEuclidiana(double x1, double y1, double x2, double y2 ){
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void PreencheMatriz(Lista *L, double matriz[MAXTAM][MAXTAM]){
    for(int i = 0; i<L->Tamanho; i++){
        matriz[i][i] = 0;                                                                        //cidade com ela mesma é 0
        for(int j = i+1; j<L->Tamanho; j++){
            double d = distEuclidiana(L->Item[i].x, L->Item[i].y, L->Item[j].x, L->Item[j].y);   //calcula a distancia
            matriz[i][j] = d;                                                                    //triangulo superior igual ao triandulo inferior
            matriz[j][i] = d;
        }
    }
}

void ImprimeMatriz(Lista *L, double matriz[MAXTAM][MAXTAM]){
    printf(" Matriz %d x %d\n", L->Tamanho, L->Tamanho);
    printf("         ");                                                                         //pra linha de cima da tabela ficar alinhada quando printa
    for(int i = 0; i<L->Tamanho; i++){
        printf("C%-7d", i+1);                                                                    //printa a cidade
    }
    printf("\n");
    for(int i = 0; i<L->Tamanho; i++){
        printf("C%-4d", i+1);                                                                    //printa cidade
        for(int j = 0; j<L->Tamanho; j++){
            printf("%8.2f", matriz[i][j]);                                                       //printa resultado
        }
        printf("\n");
    }
}
