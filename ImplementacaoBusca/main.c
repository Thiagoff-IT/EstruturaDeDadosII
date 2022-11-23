
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int * id;
    int n;
    int count;
} UF;

UF * init_UF(int n);
int count_UF(UF * uf);
int connected_UF(UF * uf, int p, int q);
int find_UF(UF * uf, int p);
void union_UF(UF * uf, int p, int q);

UF * init_UF(int n){
    int i;
    UF * uf;

    uf = malloc(sizeof(UF));

    uf->n = n;
    uf->id = malloc(sizeof(int) * n);
    uf->count = n;
    for (i = 0; i < uf->count; ++i) {
        uf->id[i] = i;
    }

    return(uf);
}

int count_UF(UF * uf){
    return(uf->count);
}

int connected_UF(UF * uf, int p, int q){
    return(uf->id[p] == uf->id[q]);
}

int find_UF(UF * uf, int p){
    return(uf->id[p]);
}

void union_UF(UF * uf, int p, int q){
    int p_id = uf->id[p];
    int q_id = uf->id[q];
    int i;

    if (p_id == q_id) return;

    for(i = 0; i < uf->n; i++)
        if(uf->id[i] == p_id) uf->id[i] = q_id;

    uf->count--;
}

int main(){
    int n, p, q;
    UF * uf;

    scanf("%d", &n);

    uf = init_UF(n);

    scanf("%d %d", &p, &q);
    while(p > -1 && q > -1){

        if(!connected_UF(uf, p, q)){
            printf("%d %d\n", p, q);
            union_UF(uf, p, q);
        }

        scanf("%d %d", &p, &q);
    }
}
