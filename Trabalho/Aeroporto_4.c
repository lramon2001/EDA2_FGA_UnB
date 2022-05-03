#include<stdio.h>
#include<stdlib.h>

typedef struct consulta
{
    int *vetor;
    int maximo;
    int tamanho;
} Consulta;

Consulta *inicia_consulta (int tamanho)
{
    
    Consulta *consulta;
    consulta = (Consulta*) malloc(sizeof(Consulta));
    consulta->maximo = 0;
    consulta->tamanho = tamanho;
    consulta->vetor = (int*) calloc(tamanho,sizeof(int));
    
    return consulta;
}

void adiciona_consulta(Consulta *consulta,int viagem)
{
    consulta->vetor[viagem]++;
    if(consulta->vetor[viagem]>consulta->maximo)
    {
        consulta->maximo = consulta->vetor[viagem];
    }
}

void imprime(Consulta *consulta, int maximo)
{
    for(int i=0;i<consulta->tamanho;i++)
    {
        if(consulta->vetor[i] == maximo)
        {
            printf("%d ",i);
        }
    }
    printf("\n");
}


int main() 
{
    Consulta *consulta;
    
  
    int A,V,X,Y,teste=1;
    
    do
    {
         
        //Lendo o numero de aeroportos
        scanf("%d",&A);
        //Lendo o numero de voos
        scanf("%d",&V);
        consulta = inicia_consulta(A+1);
        
        if(A==0 && V==0)
        {
            break;
        }
        printf("Teste %d\n",teste);
        
       
        for(int i=0;i<V;i++)
        {
            //Lendo o valor da origem
            scanf("%d",&X);
            //Lendo o valor do destino
            scanf("%d",&Y);
            adiciona_consulta(consulta,X);
            adiciona_consulta(consulta,Y);
            
        }
       teste++;
     
       imprime(consulta,consulta->maximo);
       printf("\n");

    }
    while(1);
    
}