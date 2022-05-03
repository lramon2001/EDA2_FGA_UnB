#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Saida{
int quantidade;
int posicao;
char letra;
}Saida;
merge(struct Saida *v,int l,int r1,int r2){
struct Saida *v2=malloc(sizeof(Saida)*(r2-l+1));
int k=0;
int i = l;
int j = r1+1;
while(i<=r1 && j<=r2){
    if(v[i].quantidade<v[j].quantidade){
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

mergesort(struct Saida *v,int l, int r){
    if(l>=r)return;
int meio = (l+r)/2;
mergesort(v,l,meio);
mergesort(v,meio+1,r);
merge(v,l,meio,r);

}


int main(){
char frase[100001];
scanf("%s", frase);
int j=0;
int z=0;
struct Saida a[strlen(frase)];
a[z].quantidade=0;
for(int i=0;i<strlen(frase);i++){
    if(frase[j]!= frase[i]){
        j=i;
        z++;
    a[z].quantidade=0;
    }
    a[z].quantidade++;
    a[z].posicao = j;
    a[z].letra = frase[j];
}
mergesort(a,0,z);

for(int i=z; i>=0; i--){
    printf(" %d %c %d\n", a[i].quantidade, a[i].letra, a[i].posicao);
}





return 0;
}
