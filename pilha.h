#include "lista.h"
#ifndef _PILHA_
#define _PILHA_
#define MAXTAMPILHA 12

typedef Cidade TipoChave;

typedef struct  Celula
{
    TipoChave Cidade;
}TipoItem;

typedef struct  Pilha
{
    TipoItem Item[MAXTAMPILHA];
    int Topo;
}Pilha;
void CriaPilha(Pilha *p);
void Empilha(TipoItem x, Pilha *p);
int VaziaPilha(Pilha *p);
void Desempilha(TipoItem *x, Pilha *p);

#endif