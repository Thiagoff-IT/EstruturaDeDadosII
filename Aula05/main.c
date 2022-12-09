#include <stdio.h>
#include <stdlib.h>
void merge(int v[], int direita, int esquerda, int aux[])
{
    int meio = (direita + esquerda) / 2;
    int i = direita;
    int j = meio + 1;
    int k = 0;
    while (i <= meio || j <= esquerda)
    {
        if (i <= meio && (j > esquerda || v[i] < v[j]))
        {
            aux[k] = v[i];
            i++;
        }
        else
        {
            aux[k] = v[j];
            j++;
        }
        k++;
    }
}

void mergeSortOrdena(int v[], int direita, int esquerda, int aux[])
{
    printf("esquerda-> %d, direita->%d\n", esquerda,direita);
    int meio = (direita + esquerda) / 2;
    if (direita == esquerda)
    {
        return;
    }

    if (direita < esquerda)
    {
        mergeSortOrdena(v, direita, meio, aux);
        mergeSortOrdena(v, meio + 1, esquerda, aux);
        merge(v, direita, esquerda, aux);

        for (int l = 0; l < esquerda - direita + 1; l++)
        {
            v[direita + l] = aux[l];
        }
    }
}

void mergeSort(int v[], int tamanho)
{
    int *aux = malloc(sizeof(int) * tamanho);
    mergeSortOrdena(v, 0, tamanho, aux);
    free(aux);
}

int EstaOrdemCrescente(int vetor[], int tamanho)
{
    for (int i = 1; i < tamanho; i++)
        if (vetor[i - 1] > vetor[i])
            return 0;
    return 1;
}

int main()
{
    int a[] = {1,2,3,5,4};

    int tamanhoVetor = sizeof(a) / sizeof(int);
    int checarOrdenado = EstaOrdemCrescente(a, tamanhoVetor);

    

    if (checarOrdenado)
    {
        printf("Vetor está ordenado!\n");
    }
    else
    {
        mergeSort(a, tamanhoVetor);
    }

    for (int i = 0; i < tamanhoVetor; i++)
    {

        printf("%d \n", a[i]);
    }
}
