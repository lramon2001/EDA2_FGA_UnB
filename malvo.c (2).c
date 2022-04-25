
   
#include<stdio.h>
#include<stdlib.h>


typedef struct grafo{
    int numero_de_vertices;
    int** arestas;
    int* grau;
}Grafo;

Grafo* cria_Grafo(int nro_vertices);
int insereAresta(Grafo* gr, int orig, int dest);

Grafo* cria_Grafo(int numero_de_vertices){
    Grafo *grafo;
    grafo = (Grafo*) malloc(sizeof(struct grafo));
    
    if(grafo != NULL){
        int i;
        grafo->numero_de_vertices = numero_de_vertices;
        grafo->grau = (int*) calloc(numero_de_vertices,sizeof(int));
        grafo->arestas = (int**) malloc(numero_de_vertices * sizeof(int*));
        
        for(i=0; i<numero_de_vertices; i++)
        {
            grafo->arestas[i] = (int*) malloc(numero_de_vertices * sizeof(int));
        }

    }
    return grafo;
}

int insere_aresta(Grafo* grafo, int origem, int destino){
    if(grafo == NULL)
        return 0;
    if(origem < 0 || origem >= grafo->numero_de_vertices)
        return 0;
    if(destino < 0 || destino >= grafo->numero_de_vertices)
        return 0;

    grafo->arestas[origem][grafo->grau[origem]] = destino;
    grafo->grau[origem]++;
    
    //grafo->arestas[destino][grafo->grau[destino]] = origem;
    //grafo->grau[destino]++;
    
    return 1;
}

void imprime_grafo(Grafo *grafo)
{
    for(int i=0;i<grafo->numero_de_vertices;i++)
    {
        printf("[%d]: ",i);
        for(int j=0;j<grafo->grau[i];j++)
        {
            printf("[%d]-> ",grafo->arestas[i][j]);
        }
        printf("\n");
    }
}

int main(){

 int N,M,J,A;
 int vizinhaca;
 int consulta;
 scanf("%d %d %d",&N,&M,&J);

 Grafo *grafo = cria_Grafo(N);
 
 for(int i=0; i<N;i++)
 {
     scanf("%d",&A);
     for(int j=0;j<A;j++)
     {
         scanf("%d",&vizinhaca);
         insere_aresta(grafo,i,vizinhaca);
     }
 }
   
   int local_que_julius_esteve;
   char vetor_de_consulta[N];
   for(int i=0;i<N;i++)
   {
       vetor_de_consulta[i] ='n';
   }
   for(int i=0;i<M;i++)
   {
      //le o local que julius esteve
      scanf("%d",&local_que_julius_esteve);
      
      // coloca o marcador 1 para a posicao do local que julius esteve no vetor de consulta;
      vetor_de_consulta[local_que_julius_esteve]='y';
      
      // coloca o marcador 1 para as posicoes vizinhas ao local que julius esteve
      
      for(int j=0;j<grafo->grau[local_que_julius_esteve];j++)
      {
          
          vetor_de_consulta[grafo->arestas[local_que_julius_esteve][j]]='y';
      }
   }
   /*
    for(int i=0;i<N;i++)
    {
        printf("%d ",vetor_de_consulta[i]);
    }*/
    
    for(int i=0; i<J;i++)
    {
        scanf("%d",&consulta);
        if(vetor_de_consulta[consulta]=='y')
        {
            printf("Eu vou estar la\n");
        }
        else
        {
            printf("Nao vou estar la\n");
        }
    }
        
        
}









