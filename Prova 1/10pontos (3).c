#include<stdio.h>
#include<stdlib.h>
void merge(int *v,int l,int r1,int r2){
int *v2= malloc(sizeof(int)*(r2-l+1));
int k=0;
int i = l;
int j = r1+1;
while(i<=r1 && j<=r2){
    if(v[i]<v[j]){
        v2[k++]=v[i++];
    }else{
        v2[k++]=v[j++];
    }
}
while(i<= r1)v2[k++]=v[i++];
while(j<= r2)v2[k++]=v[j++];
k=0;
for(i=l;i<=r2;i++){
    v[i]=v2[k++];
}
free(v2);
}

void mergesort(int *v,int l, int r){
    if(l>=r)return;
int meio = (l+r)/2;
mergesort(v,l,meio);
mergesort(v,meio+1,r);
merge(v,l,meio,r);

}
int BuscaBinaria(int *vetor, int procurado, int tamanho){
int inicio = 0;
int fim = tamanho;
int meio;
    while(inicio <= fim){
        meio = (inicio + fim)/2;
        if(procurado > vetor[meio]){
            inicio = meio+1;
        } else if(procurado < vetor[meio]){
                fim = meio-1;
        }else if (procurado == vetor[meio]){
                return 1;
        }

    }

return -1;
}

int main(){
int n;
int input;
int *v;
scanf("%d", &n);

v=malloc(sizeof(int)*n);

for(int i=0; i<n;i++){
    scanf("%d", &v[i]);
}
mergesort(v,0,n-1);

while(scanf("%d", &input)!=EOF){
    if(BuscaBinaria(v,input,n-1)==1){
        printf("sim\n");
    }else printf("nao\n");
}

}
