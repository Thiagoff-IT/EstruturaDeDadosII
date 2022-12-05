#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct DADO
{
    char *key;
    char *value;
};

typedef struct elemento *Lista; //1

struct elemento
{
    struct DADO dados;     //2
    struct elemento *prox; //3
};

typedef struct elemento Elem; //4

Lista *init_timeTable()
{
    Lista *li = (Lista *)malloc(sizeof(Lista)); //reservar memoria para o primeiro no da lista
    if (li != NULL)
    {
        *li = NULL; //Dando ao ultimo elemento da lista o valor de null
        printf("Lista criada.\n\n");
        return li;
    }
}

int validaKey(char *key)
{
    if (strlen(key) == 8)
    {
        return 1;
    }

    return 0;
}

//INSERINDO DE FORMA ORDENADA
int insert(Lista *li, struct DADO ed_le)
{

    if (li == NULL)
        return 0;
    Elem *no = (Elem *)malloc(sizeof(Elem));
    if (no == NULL)
        return 0;
    no->dados = ed_le;
    if (is_empty(li))
    {
        no->prox = NULL;
        *li = no;
        return 1;
    }
    else if (no->dados.key < (*li)->dados.key)
    {
        no->prox = *li;
        *li = no;
    }
    else
    {
        Elem *aux = (Elem *)malloc(sizeof(Elem));
        aux = *li;
        while (aux->prox && no->dados.key > aux->prox->dados.key)
        {
            aux = aux->prox;
            no->prox = aux->prox;
            aux->prox = no;
        }
    }

    return 1;
}
void imprime_lista(Lista *li)
{
    if (li == NULL)
    {
        return;
    }
    Elem *no = *li;
    while (no != NULL)
    {
        printf("Horario: %s\n", no->dados.key);
        printf("Cidade: %s\n", no->dados.value);
        printf("-------------------------------\n");
        no = no->prox;
    }
}

int is_empty(Lista *li)
{
    if (li == NULL) //lista nula
        return 1;
    if (*li == NULL) //primeiro elemento apontando pra null
        return 1;
    return 0;
}

int main()
{
    struct DADO dados;
    struct Lista *timetable = init_timeTable();
    int option = 0;
    char value[15], key[8];

    while (option > -1)
    {
        printf("1) Inserir dados na tabela\n");
        scanf(" %d", &option);

        switch (option)
        {
        case 1:
        {
            printf("Digite sua cidade:\n");
            scanf("%s", &value);
            printf("Digite seu horário:\n");
            scanf("%s", &key);
            dados.key = key;
            dados.value = value;
            insert(timetable, dados);
            break;
        }

        case 2:
        {
            imprime_lista(timetable);
            break;
        }
        }
    }
}
