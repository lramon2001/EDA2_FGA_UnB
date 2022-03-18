#include<stdio.h>
#include<stdlib.h>

#define HTSIZE 100
#define HTNULL -1

typedef struct node
{
    int num;
    struct node *next;
    
}node;

typedef struct list_st
{
    node *head;
    int count;
}list_st;

void init_list(list_st *list)
{
    list->head = NULL;
    list->count = 0;
}

void insert_list(list_st *list, int x)
{
    //alocar um novo no 
    node *n = malloc(sizeof(node));
    //n guardar valor de x
    n->num = x;
    // fazer o novo no apontar pro no cabeca da lista
    n->next = list->head;
    // n vira o novo no head
    list->head = n;
    //aumentar o tamanho da lista
    list->count++;
}

int search_list(list_st *list, int x)
{
    node *aux = list->head;
    
    while(aux!=NULL)
    {
        if(aux->num == x)
        {
            return 1;
        }
        aux = aux->next;
    }
    return 0;
}

typedef struct HT_st
{
    list_st *vector;
    int count;
}HT_st;

void init_ht(HT_st *ht)
{
    ht->vector = malloc(sizeof(list_st)*HTSIZE);
    for(int i =0; i<HTSIZE;i++)
    {
        init_list(&ht->vector[i]);
    }
    
    ht->count =0;
}

int hash(int x)
{
    return x % HTSIZE;
}

void insert_ht(HT_st *ht, int x)
{
    int hash_value = hash(x);
    insert_list(&ht->vector[hash_value],x);
    ht->count++;
}

int search_ht(HT_st *ht, int x)
{
    int hash_value = hash(x);
    
    return search_list(&ht->vector[hash_value],x);
    
}

void print_list(list_st *list)
{
    node *aux = list->head;
    printf("head-> ");
    while(aux!=NULL)
    {
        printf("%d-> ",aux->num);
        aux = aux->next;
    }
    printf("NULL\n");
}

void print_ht(HT_st *ht)
{
    for(int i=0;i<HTSIZE;i++)
    {
        printf("HT[%i]:\n ",i);
        print_list(&ht->vector[i]);
    }
}

void print_feedback(HT_st *ht)
{
    for(int i=0;i<HTSIZE;i++)
    {
        printf("HT[%d]: Há %d elementos nessa posição.\n",i,ht->vector[i].count);
    }
}

int main()
{
   HT_st hash_table;
   init_ht(&hash_table);
   int n;
   //quantidade de numeros a serem procurados
   scanf("%d",&n);
   int input;
   for(int i=0;i<n;i++)
   {
       scanf("%d",&input);
       insert_ht(&hash_table,input);
   }
   
   for(int i=0; i<500;i++)
   {
       insert_ht(&hash_table,rand()%1000);
   }
   int question;
  /* while(scanf("%d",&question)!=EOF)
   {
       
       
       if(search_ht(&hash_table,question))
       {
           printf("sim\n");
       }
       else
       {
           printf("nao\n");
       }
   }
   printf("\n");
   */
   
   print_ht(&hash_table);
   
   return 0;
}