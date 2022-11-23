
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int * id; // array para armazenar as compoentes de cada elemento;
    int count; // número de elementos
    int n; // contagem de componentes atual;
} UF;

UF * init_UF(int n);  // inicializa N itens com nomes de inteiros (0 até N-1)
int count_UF(UF * uf);  // retorna o número de componentes
int connected_UF(UF * uf, int p, int q); // retorna true se p e q estão na mesma componente
int find_UF(UF * uf, int p); // identifica a componente de p (0 até N-1)
void union_UF(UF * uf, int p, int q); // adiciona conexão entre p e q

UF * init_UF(int n){
    int i;
    UF * uf;

    uf = malloc(sizeof(UF));

    uf->id = malloc(sizeof(int) * n);
    uf->n = n;
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
    return(find_UF(uf, p) == find_UF(uf,q));
}

int find_UF(UF * uf, int p){
    while (p!= uf->id[p]){
        p = uf->id[p];
    }
    return p;
}

void union_UF(UF * uf, int p, int q){
    int aux = find_UF(uf,p);
    for (int i = 0; i < uf->n; i++)
        if (find_UF(uf,i) == aux) {
            //printf("CONECTANDO o %dcom o %d\n\n ", i, uf->id[q]);
            uf->id[i] = uf->id[q];};
    uf->count--;
    return;
}

int main(){
    int n, p, q;
    UF * uf;
    printf("Digita a quantidade de elementos:\n");
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
    printf("%d Componentes", count_UF(uf));
}
