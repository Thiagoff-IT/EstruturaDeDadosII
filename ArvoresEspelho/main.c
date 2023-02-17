#include <stdio.h>
#include <stdlib.h>

typedef struct arvore {
   char info;
   struct arvore *esq;
   struct arvore *dir;
} Arvore;


Arvore*  cria_arv_vazia (void);
Arvore*  arv_constroi (char c, Arvore* e, Arvore* d);
int      verifica_arv_vazia (Arvore* a);
Arvore*  arv_libera (Arvore* a);
int      arv_pertence (Arvore* a, char c);
void     arv_imprime (Arvore* a);
int      eh_espelho(Arvore * arv_a, Arvore * arv_b);
Arvore*  cria_espelho(Arvore * arv_a);

Arvore* cria_arv_vazia (void) {
   return NULL;
}

Arvore* arv_constroi (char c, Arvore* e, Arvore* d) {
  Arvore* a = (Arvore*)malloc(sizeof(Arvore));
  a->info = c;
  a->esq = e;
  a->dir = d;
  return a;
}

int verifica_arv_vazia (Arvore* a) {
  return (a == NULL);
}

Arvore* arv_libera (Arvore* a) {
  if (!verifica_arv_vazia(a)) {
    arv_libera (a->esq);
    arv_libera (a->dir);
    free(a);
  }
  return NULL;
}

int eh_espelho(Arvore * arv_a, Arvore * arv_b) {
  if (verifica_arv_vazia(arv_a) && verifica_arv_vazia(arv_b)) {
    return 1;
  }
  if (verifica_arv_vazia(arv_a) || verifica_arv_vazia(arv_b)) {
    return 0;
  }
  if (arv_a->info != arv_b->info) {
    return 0;
  }
  return eh_espelho(arv_a->esq, arv_b->dir) && eh_espelho(arv_a->dir, arv_b->esq);
}

Arvore* cria_espelho(Arvore * arv_a) {
  if (verifica_arv_vazia(arv_a)) {
    return cria_arv_vazia();
  }
  return arv_constroi(arv_a->info, cria_espelho(arv_a->dir), cria_espelho(arv_a->esq));
}

int main (int argc, char *argv[]) {
Arvore *a, *a1, *a2, *a3, *a4, *a5;
a1 = arv_constroi('d',cria_arv_vazia(),cria_arv_vazia());
a2 = arv_constroi('b',cria_arv_vazia(),a1);
a3 = arv_constroi('e',cria_arv_vazia(),cria_arv_vazia());
a4 = arv_constroi('f',cria_arv_vazia(),cria_arv_vazia());
a5 = arv_constroi('c',a3,a4);
a = arv_constroi('a',a2,a5);

// Teste da função eh_espelho
Arvore* espelho = cria_espelho(a);
if (eh_espelho(a, espelho)) {
printf("A árvore e seu espelho são espelhos entre si.\n");
} else {
printf("A árvore e seu espelho não são espelhos entre si.\n");
}

// Libera as árvores da memória
arv_libera(a);
arv_libera(espelho);

return 0;
}
