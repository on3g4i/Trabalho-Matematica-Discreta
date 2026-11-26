#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
//Distância euclidiana entre (x1,y1) e (x2,y2)
double distEuclidiana(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}
//Calcula a quantidade de permutações possíveis antes do usuário decidir se quer ver os caminhos
int Permutacoes(int n){
      if (n == 0 || n == 1) {
        return 1;
    }
    // Passo recursivo
    return n * Permutacoes(n - 1);
}
//Preenche a matriz de adjacências com as distâncias euclidianas
void PreencheMatriz(Lista *L, double matriz[MAXTAM][MAXTAM])
{
    for (int i = 0; i < L->Tamanho; i++)
    {
        for (int j = i + 1; j < L->Tamanho; j++)
        {
            double d = distEuclidiana(L->Item[i].x, L->Item[i].y, L->Item[j].x, L->Item[j].y); // calcula a distancia
            matriz[i][j] = d;                                                                  // triangulo superior igual ao triandulo inferior
            matriz[j][i] = d;
        }
        matriz[i][i] = 0; // cidade com ela mesma é 0
    }
}
//Imprime a matriz de adjacências das cidades
void ImprimeMatriz(double matriz[MAXTAM][MAXTAM])
{
    printf(" Matriz %d x %d\n", MAXTAM, MAXTAM);
    printf("         "); // pra linha de cima da tabela ficar alinhada quando printa
    for (int i = 0; i < MAXTAM; i++)
    {
        printf("C%-7d", i + 1); // printa a cidade
    }
    printf("\n");
    for (int i = 0; i < MAXTAM; i++)
    {
        printf("C%-4d", i + 1); // printa cidade
        for (int j = 0; j < MAXTAM; j++)
        {
            printf("%8.2f", matriz[i][j]); // printa resultado
        }
        printf("\n");
    }
}
//Cria a lista de cidades à partir do arquivo de entradas.txt
Lista *ListaCompletaCidades(Lista *Lista, FILE *arquivo)
{
    if (Lista == NULL)
    {
        Lista = CriaLista();
    }
    if (arquivo == NULL)
    {
        return NULL;
    }
    else
    {
        Cidade c;
        int contador = 0;
        c.visita = 0;
        while (fscanf(arquivo, "%lf %lf", &c.x, &c.y) == 2)
        {
            contador++;
            if (!PreencheLista(Lista, c))
            {
                printf("Erro, Lista de Cidades Cheia");
            }
        }
        return Lista;
    }
}
//Imprime os menores caminhos
 void ImprimeMenoresCaminhos(
    int caminhos[5][MAXTAM], int tamanhos[5], double distancias[5], int quantidade)
{
    double distanciaTotal = 0;
    // Exibe os caminhos armazenados em ordem e soma suas distâncias.
    for (int i = 0; i < quantidade; i++) {
        printf("%d) ", i + 1);
        for (int j = 0; j < tamanhos[i]; j++) {
            printf("%sC%d", j == 0 ? "" : " -> ", caminhos[i][j] + 1);
        }
        printf(" | Distância: %.2f\n", distancias[i]);
        distanciaTotal += distancias[i];
    }
    printf("Distância total dos caminhos: %.2f\n", distanciaTotal);
}

//Função responsável por pegar todos os caminhos possíveis entre c1 e c2.
void CaminhoCidades(Cidade c1, Cidade c2, double matriz[MAXTAM][MAXTAM], Lista *l){
    //Mantém a profundidade da busca e a cidade de origem entre chamadas recursivas
    static int profundidade = 0;
    static int origemBusca = -1;
    // Armazenam, em ordem crescente de distância, no máximo cinco caminhos.
    static int menores[5][MAXTAM];
    static int tamanhos[5];
    static double distancias[5];
    static int quantidadeMenores = 0;

    //Encontra os índices das cidades na lista
    int inicio = Busca(l, c1);
    int destino = Busca(l, c2);
    if (inicio == -1 || destino == -1) {
        printf("Erro: cidade de origem ou destino não encontrada\n");
        return;
    }

    //Na primeira chamada, limpa as visitas e marca a origem
    if (profundidade == 0) {
        for (int i = 0; i < l->Tamanho; i++) {
            l->Item[i].visita = NAOVISITADA;
        }
        origemBusca = inicio;
        quantidadeMenores = 0;
        l->Item[inicio].visita = VISITADA;
    }

    //Ao alcançar o destino, registra o caminho se estiver entre os cinco menores.
    if (inicio == destino) {
        int candidato[MAXTAM];
        int tamanho = 0;
        int atual = destino;
        // Reconstrói o caminho seguindo os predecessores registrados na busca.
        while (atual != origemBusca) {
            candidato[tamanho++] = atual;
            atual = l->Item[atual].visita - 2;
        }
        candidato[tamanho++] = origemBusca;
        // A reconstrução começa no destino; inverte para guardar da origem ao destino.
        for (int i = 0; i < tamanho / 2; i++) {
            int troca = candidato[i];
            candidato[i] = candidato[tamanho - i - 1];
            candidato[tamanho - i - 1] = troca;
        }

        double distancia = 0;
        // Soma as distâncias entre cidades consecutivas do caminho.
        for (int i = 1; i < tamanho; i++) {
            distancia += matriz[candidato[i - 1]][candidato[i]];
        }

        // Localiza a posição do caminho na lista ordenada de menores distâncias.
        int posicao = 0;
        while (posicao < quantidadeMenores &&
               distancias[posicao] <= distancia) {
            posicao++;
        }
        if (posicao < 5) {
            // Abre espaço e insere o candidato se ele estiver entre os cinco menores.
            if (quantidadeMenores < 5) {
                quantidadeMenores++;
            }
            for (int i = quantidadeMenores - 1; i > posicao; i--) {
                distancias[i] = distancias[i - 1];
                tamanhos[i] = tamanhos[i - 1];
                for (int j = 0; j < tamanhos[i]; j++) {
                    menores[i][j] = menores[i - 1][j];
                }
            }
            distancias[posicao] = distancia;
            tamanhos[posicao] = tamanho;
            for (int i = 0; i < tamanho; i++) {
                menores[posicao][i] = candidato[i];
            }
        }

        if (profundidade == 0) {
            l->Item[inicio].visita = NAOVISITADA;
            printf("Os %d menores caminhos entre C%d e C%d:\n",
                   quantidadeMenores, origemBusca + 1, destino + 1);
            ImprimeMenoresCaminhos(menores, tamanhos, distancias, quantidadeMenores);
        }
        return;
    }

    //Percorre as cidades vizinhas ainda não visitadas
    for (int vizinha = 0; vizinha < l->Tamanho; vizinha++) {
        if (matriz[inicio][vizinha] > 0 &&
            l->Item[vizinha].visita == NAOVISITADA) {
            //Registra a cidade anterior e continua a busca recursivamente
            l->Item[vizinha].visita = inicio + 2;
            profundidade++;
            CaminhoCidades(l->Item[vizinha], c2, matriz, l);
            //Desmarca a vizinha para permitir que apareça em outro caminho
            l->Item[vizinha].visita = NAOVISITADA;
            profundidade--;
        }
    }

    //Ao encerrar a busca, desmarca a cidade de origem
    if (profundidade == 0) {
        l->Item[inicio].visita = NAOVISITADA;
        // A busca completa terminou: imprime somente os caminhos armazenados.
        if (quantidadeMenores == 0) {
            printf("Nenhum caminho encontrado entre as cidades.\n");
            printf("Distância total dos caminhos: 0.00\n");
        } else {
            printf("Os %d menores caminhos entre C%d e C%d:\n",
                   quantidadeMenores, origemBusca + 1, destino + 1);
            ImprimeMenoresCaminhos(menores, tamanhos, distancias, quantidadeMenores);
        }
    }
}
int main()
{
    //Abre o arquivo de entradas em modo de leitura 
    FILE *arquivo = fopen("Entradas.txt", "r");
    Lista *Cidades = NULL;
    if (arquivo != NULL)
    {
        //Retorna uma lista de cidades de tamanho MAXTAM, que é 12
        Cidades = ListaCompletaCidades(Cidades, arquivo);
        fclose(arquivo);
    }
    //Tratamento de erros de arquivos
    else
    {
        printf("Erro, Arquivo não encontrado\n");
        return 0;
    }

    if (Cidades == NULL)
    {
        printf("Erro, não foi possível preencher as cidades na lista\n");
    }
    else
    {
        //Matriz de adjacências, neste caso, toda cidade se relaciona com as outras, porém nenhuma se relaciona consigo mesma
        double matriz[MAXTAM][MAXTAM] = {0};
        //Preenche a matriz com a distância euclidiana entre as cidades
        PreencheMatriz(Cidades, matriz);
        //Imprime a matriz de adjacências com os valores
        ImprimeMatriz(matriz);
        //Executa a parte principal do código, onde o usuário define a cidade de início e a cidade de fim
        do
        {
            //Pede as coordenadas das cidades
            printf("Digite as coordenadas da cidade 1 (x,y)\n");
            Cidade *cidade1 = (Cidade *)malloc(sizeof(Cidade));
            scanf("%lf%lf", &cidade1->x, &cidade1->y);
            printf("Digite as coordenadas da cidade 2 (x,y)\n");
            Cidade *cidade2 = (Cidade *)malloc(sizeof(Cidade));
            scanf("%lf%lf", &cidade2->x, &cidade2->y);
            //Deixa para o usuário decidir se quer verificar o caminho, ou se quer sair do sistema de verificação
            int opc;
            //São MAXTAM-1 permutações, deixando o usuário ciente da quantidade de informações que serão resgatadas 
            printf("MENU\n1)Verificar os caminhos possíveis.\n0) Sair.\nQuantidade de permutações possíveis entre as cidades:%d\n", Permutacoes(MAXTAM - 1));
            scanf("%d", &opc);
            //Se a opção for 0, fim do código
            if (!opc)
            {
                return 1;
            }
            else
            {
                //Caso contrário, printa todos os caminhos possíveis entre cidade 1 e cidade 2 com busca em profundidade
                CaminhoCidades(*cidade1, *cidade2, matriz, Cidades);
            }
            //Libera as cidades alocadas para a próxima iteração
            free(cidade1);
            free(cidade2);
        } while (1);
    }

    return 0;
}