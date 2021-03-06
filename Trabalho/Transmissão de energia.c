#include<stdio.h>
#include<stdlib.h>

typedef struct grafo
{
    int numero_de_vertices;
    int eh_ponderado;
    int grau_maximo;
    int **arestas;
    float **pesos;
    int *grau;
}Grafo;

Grafo *inicia_grafo(int numero_de_vertices, int eh_ponderado, int grau_maximo)
{
    Grafo *grafo = (Grafo*) malloc (sizeof(Grafo));
    if(grafo!=NULL)
    {
    int i;
    grafo->numero_de_vertices = numero_de_vertices;
    grafo->eh_ponderado = (eh_ponderado!=0)?1:0;
    grafo->grau_maximo = grau_maximo;
    grafo-> grau = (int*)calloc(numero_de_vertices,sizeof(int));
    grafo->arestas = (int**)malloc(numero_de_vertices*sizeof(int*));
    for( i=0; i<numero_de_vertices;i++)
    {
        grafo->arestas[i] =(int*) malloc(grau_maximo*sizeof(int));
    }
    if(eh_ponderado)
    {
        grafo->pesos = (float**) malloc(numero_de_vertices*sizeof(int));
        for(i=0;i<numero_de_vertices;i++)
        {
            grafo->pesos[i] = (float*)malloc(numero_de_vertices*sizeof(float*));
        }
    }
    }
    return grafo;
}

void adiciona_aresta(Grafo *grafo,int origem,int destino, int peso,int eh_digrafo)
{
    if(grafo == NULL)
    {
        return;
    }

    if(origem<0 || origem>= grafo->numero_de_vertices)
    {
        return;
    }

    if(destino<0 || destino>= grafo->numero_de_vertices)
    {
        return;
    }
    grafo->arestas[origem][grafo->grau[origem]] = destino;

    if(grafo->eh_ponderado)
    {
        grafo->pesos[origem][grafo->grau[origem]]=peso;
    }
    grafo->grau[origem]++;
    if(!eh_digrafo)
    {
        adiciona_aresta(grafo,destino,origem,0,1);
    }
}

void remove_aresta(Grafo *grafo, int origem,int destino, int eh_digrafo)
{
       if(grafo == NULL)
    {
        return;
    }

    if(origem<0 || origem>= grafo->numero_de_vertices)
    {
        return;
    }

    if(destino<0 || destino>= grafo->numero_de_vertices)
    {
        return;
    }

    int i=0;

    while(i<grafo->numero_de_vertices && grafo->arestas[origem][i]!=destino)
    {
        i++;
    }
    if(i== grafo->grau[origem])
    {
        return;
    }
    grafo->grau[origem]--;

    grafo->arestas[origem][i] = grafo->arestas[origem][grafo->grau[origem]];

    if(grafo->eh_ponderado)
    {
       grafo->pesos[origem][i] = grafo->arestas[origem][grafo->grau[origem]];
    }

    if(!eh_digrafo)
    {
        remove_aresta(grafo,destino,origem,1);
    }
}
void busca_em_profundidade(Grafo *grafo,int inicial, int *visitados, int contador)
{
    int i;
    visitados[inicial] = contador;

    for(i =0; i<grafo->grau[inicial]; i++)
    {
        if(!visitados[grafo->arestas[inicial][i]])
        {
            busca_em_profundidade(grafo,grafo->arestas[inicial][i],visitados,contador+1);
        }
    }

}
int conta_ilhas(Grafo *grafo,int *visitados)
{
    int contador=0;
    int i;
    int count=1;
    for(int j=0; j<grafo->numero_de_vertices;j++){
        visitados[j]=0;
    }


    for(i=0;i<grafo->numero_de_vertices;i++)
    {
        if(visitados[i]==0)
        {
            busca_em_profundidade(grafo,i,visitados,count);
            contador++;
        }
    }

    return contador;

}

int main(){
int E, L;
int e1,e2;
int cont =0;
int ilhas=0;
scanf("%d %d", &E, &L);

while(E!= 0 && L!= 0){
        cont++;
    int vetor[E];
    Grafo *grafo= inicia_grafo(E,0,L);
    for(int i=0; i<L; i++){
        scanf("%d %d", &e1, &e2);
        adiciona_aresta(grafo,e1-1,e2-1,0,0);
    }

    ilhas=conta_ilhas(grafo,vetor);
    printf("Teste %d\n", cont);
    if(ilhas>1){
        printf("falha\n");
    }else{
        printf("normal\n");
    }
    printf("\n");
    scanf("%d %d", &E, &L);
}



return 0;
}
