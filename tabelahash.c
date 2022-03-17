#include<stdio.h>
#include<stdlib.h>

#define HTSIZE 128000
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
    n->prox = list->head;
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
        aux = aux->prox;
    }
    return 0;
}

typedef struct HT_st
{
    list_st *vector;
    int count;
}HT_st;

void init_HT(HT_st *ht)
{
    for(int i =0, i<HTSIZE;i++)
    {
        init_list(&ht->vector[i]);
    }
    
    ht->count =0;
}

int hash(int x)
{
    return x % HTSIZE;
}

void insert_th(HT_st *ht, int x)
{
    int hash_value = hash(x);
    insert_list(&ht->vector[hash_value],x);
    ht->count++;
}

int search_th(HT_st *ht, int x)
{
    int hash_value = hash(x);
    
    return search_list(&ht->vector[hash_value],x);
    
}


int main()
{
    
}