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
int Busca(Lista *L, Cidade c){
    if(Vazia(L)){
        return -1;
    } else {
        for (int i = 0; i < L->Tamanho; i++)
        {
            if(L->Item[i].x == c.x && L->Item[i].y == c.y){
                return i;
            }
        }
        return -1;
    }
}
   

