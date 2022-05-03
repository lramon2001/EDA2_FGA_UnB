#include<stdio.h>
#include<stdlib.h>
typedef int Item;
#define less(A,B) ((A) < (B))
#define lesseq(A,B) ((A) <= (B))
#define exch(A,B) { Item t; t=A;A=B;B=t; }
#define cmpexch(A,B) { if (less(B,A)) exch(A,B); }

int separa(int *V,int l,int r)
{
  int c=V[r];
  int j=l;
  int aux;
  for(int k=l;k<r;k++)
    if(V[k]<c)
    {
        aux=V[k];
        V[k]=V[j];
        V[j]=aux;
      j++;
    }
    aux=V[j];
    V[j]=V[r];
    V[r]=aux;
  return j;
}

void quicksortM3(Item *V,int l, int r)
{
  if (r<=l) return;

  cmpexch(V[(l+r)/2],V[r]);
    cmpexch(V[l],V[(l+r)/2]);
      cmpexch(V[r],V[(l+r)/2]);

  int j=separa(V,l,r);
  quicksortM3(V,l,j-1);
  quicksortM3(V,j+1,r);
}
void quickselect(int *v,int l, int r, int k){
int i;
i= separa(v,l,r);
if(r<=l)return;
if(i>k)quickselect(v,l,i-1,k);
if(i<k)quickselect(v,i+1,r,k);
}
int main(){
int n,p,x;
int *v;
scanf("%d %d %d", &n, &p, &x);
v= malloc (sizeof(int)*n);
for(int i=0; i<n; i++){
    scanf("%d", &v[i]);
}
int iniciop =x*p;

quickselect(v,0,n-1,iniciop);
quickselect(v,iniciop+1,n-1,iniciop+x-1);
quicksortM3(v,iniciop,iniciop+x-1);

for(int j=iniciop; j<=iniciop+x-1; j++){
    printf("%d\n", v[j]);
}






}
