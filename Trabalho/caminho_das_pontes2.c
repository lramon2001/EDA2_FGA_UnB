#include<stdio.h>
#include<stdlib.h>

typedef struct grafo
{
    int numero_de_vertices;
    int eh_ponderado;
    int grau_maximo;
    int **arestas;
    int **pesos;
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
        grafo->pesos = (int**) malloc(numero_de_vertices*sizeof(int*));
        for(i=0;i<numero_de_vertices;i++)
        {
            grafo->pesos[i] = (int*)malloc(numero_de_vertices*sizeof(int*));
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
    
   
    grafo->pesos[origem][grafo->grau[origem]]=peso;
   
    grafo->grau[origem]++;
    if(!eh_digrafo)
    {
        adiciona_aresta(grafo,destino,origem,peso,1);
    }
}

void imprime_grafo(Grafo *grafo)
{
    for(int i=0;i<grafo->numero_de_vertices;i++)
    {
        printf("[%d]: ",i);
        for(int j=0;j<grafo->grau[i];j++)
        {
            printf("[%d: %d]-> ",grafo->arestas[i][j],grafo->pesos[i][j]);
         
        }
           printf("\n");
        
    }
}

int procura_menor_distancia(int *distancia,int *visitado,int numero_de_vertices)
{
    int menor =-1;
    int primeiro =1;
    
    for(int i=0; i< numero_de_vertices;i++)
    {
        if(distancia[i]>=0 && visitado[i] == 0)
        {
            if(primeiro)
            {
                menor = i;
                primeiro =0;
            }
            else
            {
                if(distancia[menor] > distancia[i])
                {
                    menor =i;
                }
            }
        }
    }
    return menor;
}

void menor_caminho_grafo(Grafo*grafo, int inicial, int *anterior, int *distancia)
{
    int i, contador, numero_de_vertices, indice, *visitado,u;
    contador= numero_de_vertices = grafo->numero_de_vertices;
    visitado = (int*) malloc(numero_de_vertices*sizeof(int));
    for(int i=0;i< numero_de_vertices; i++)
    {
        anterior[i] = -1;
        distancia[i] = -1;
        visitado[i] = 0;
    }
    
    distancia[inicial] = 0;
    
   while(contador>0)
    {
        u = procura_menor_distancia(distancia, visitado,numero_de_vertices);
        if(u == -1)
        {
             break;
        }
        visitado[u] = 1;
        contador--;
        for(int i=0; i<grafo->grau[u];i++)
        {
            indice = grafo->arestas[u][i];
            if(distancia[indice]<0)
            {
                distancia[indice] = distancia[u] + grafo->pesos[u][i];
                anterior[indice] = u;
            }
            else
            {
                if(distancia[indice] > distancia[u] +grafo->pesos[u][i])
                {
                    distancia[indice] = distancia[u] +grafo->pesos[u][i];
                    
                    anterior[indice] =u;
                    
                }
            }
        }
    }
    free(visitado);
    
}
void imprime_matriz_de_pesos(Grafo *grafo)
{
    
    for(int i=0;i<grafo->numero_de_vertices;i++)
    {
        
        for(int j=0;j<grafo->numero_de_vertices;j++)
        {
            printf(" %d ",grafo->pesos[i][j]);
         
        }
           printf("\n");
        
    }
}

int main() 
{
    int N,M,S,T,B;
    scanf("%d %d",&N,&M);
    
    
    Grafo *grafo = inicia_grafo(N+2,1,N+2);
    
    for(int i=0;i<M;i++)
    {
       scanf("%d %d %d",&S,&T,&B); 
       adiciona_aresta(grafo,S,T,B,0);
    }
   int *distancia = malloc(grafo->numero_de_vertices * sizeof(int));
   int *anterior = malloc(grafo->numero_de_vertices * sizeof(int));
   int *visitado = malloc(grafo->numero_de_vertices * sizeof(int));
   menor_caminho_grafo(grafo,0,anterior,distancia);
   
   
       printf("%d\n",distancia[grafo->numero_de_vertices-1]);
   


  
}