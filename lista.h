#ifndef _LISTA_
#define _LISTA_
#define MAXTAM 12
#define VISITADA 1
#define NAOVISITADA 0
typedef struct Cidade {
    double x, y;
    int visita;
}Cidade;

typedef struct Lista{
    int Tamanho;
    Cidade Item[MAXTAM];
}Lista;

Lista * CriaLista();
//Preenche a Lista com um novo valor de cidade, retorna 1 se sucesso
int PreencheLista(Lista *L, Cidade c);
//Verifica Se a Lista está vazia
int Vazia (Lista *L);

int Busca(Lista *L, Cidade c);

#endif
