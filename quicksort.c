#include<stdio.h>
#include<stdlib.h>

#define less(A,B) ((A) < (B))
#define exch(A,B) {int t; t=A; A=B; B=t;}
#define SIZE 15
// int v[10]  -> left = v[0] e right = v[9]

int split(int *vector, int left, int right)
{
    int pivot = vector[right];
    
    int j = left;
    
    for(int k=left; k<right;k++)
    {
        if(less(vector[k],pivot))
        {
            exch(vector[k],vector[j]);
            j++;
        }
    }
    
    exch(vector[j],vector[right]);
    
    return j;
}

void quicksort(int *vector,int left, int right)
{
    if(right<=left)
    {
        return;
    }
    
    int j = split(vector,left,right);
    
    quicksort(vector,left,j-1);
    quicksort(vector,j+1,right);
    
}

void print_vector(int *vector,int size)
{
    for(int i=0;i<size;i++)
    {
        if(i!=size-1)
        {
            printf("%d, ",vector[i]);
        }
        else
        {
             printf("%d.\n",vector[i]);
        }
        
    }
}


int main()
{
    
    int array[SIZE];
    
    for(int i=0; i<SIZE;i++)
    array[i] = rand()%10;
    
    printf("Antes de ordenar:\n");
    print_vector(array, SIZE);
    quicksort(array,0,14);
    printf("Depois de ordenar:\n");
    print_vector(array, SIZE);


    return 0;
}