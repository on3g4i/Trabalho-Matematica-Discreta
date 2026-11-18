#ifndef _LISTA_
#define _LISTA_
#define MAXTAM 12
typedef struct Cidade {
    double x, y;
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

//calcula distancia euclidiana entre duas cidades
double distEuclidiana(double x1, double y1, double x2, double y2 );
//preenche a matriz 12x12
void PreencheMatriz(Lista *L, double matriz[MAXTAM][MAXTAM]);

void ImprimeMatriz(Lista *L, double matriz[MAXTAM][MAXTAM]);

#endif
