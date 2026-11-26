#include "pilha.h"
#include <stdio.h>

void Empilha (TipoItem x, Pilha *p){
    if(p->Topo == MAXTAM){
        printf("Erro: Pilha Cheia");
    } else{
        p->Topo+=1;
        p->Item[p->Topo -1] = x;
    }
}
void CriaPilha(Pilha *p){
    p->Topo = 0;
}

int VaziaPilha(Pilha *p){
    return p->Topo == 0;
}
void Desempilha(TipoItem *x, Pilha *p){
    if(VaziaPilha(p)){
        printf("Erro: pilha vazia");
    } else {
        p->Topo-= 1;
        *x = p->Item[p->Topo];
    }
}