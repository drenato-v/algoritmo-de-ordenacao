//O algoritmo Merge Sort divide o vetor ao meio recursivamente até restarem subvetores de um único elemento
//(que já estão ordenados) e depois intercala (merge) os pares de subvetores ordenados em um só, também ordenado.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define tam 10

//Intercala os subvetores ordenados vet[inicio..meio] e vet[meio+1..fim]
void merge(int vet[], int inicio, int meio, int fim)
{

    int tamEsq = meio - inicio + 1;
    int tamDir = fim - meio;
    int esq[tamEsq], dir[tamDir];
    int i, j, k;

    //copia cada metade para um vetor auxiliar
    for(i = 0; i < tamEsq; i++)    esq[i] = vet[inicio + i];
    for(j = 0; j < tamDir; j++)    dir[j] = vet[meio + 1 + j];

    i = 0;
    j = 0;
    k = inicio;

    //copia sempre o menor dos dois elementos apontados; o <= mantém o algoritmo estável
    while(i < tamEsq && j < tamDir)
    {

        if(esq[i] <= dir[j])
        {

            vet[k] = esq[i];
            i++;

        }
        else
        {

            vet[k] = dir[j];
            j++;

        }

        k++;

    }

    //copia o que sobrou de uma das metades
    while(i < tamEsq)
    {

        vet[k] = esq[i];
        i++;
        k++;

    }

    while(j < tamDir)
    {

        vet[k] = dir[j];
        j++;
        k++;

    }

}

void mergeSort(int vet[], int inicio, int fim)
{

    if(inicio < fim)
    {

        int meio = inicio + (fim - inicio) / 2;
        mergeSort(vet, inicio, meio);
        mergeSort(vet, meio + 1, fim);
        merge(vet, inicio, meio, fim);

    }

}

void preencher(int vet[])
{

    for(int i = 0; i < tam; i++)
    {

        vet[i] = rand() % 100;

    }

}

void imprimir(int vet[])
{

    for(int i = 0; i < tam; i++)
    {

        printf("[%d] ", vet[i]);

    }

    printf("\n");

}

int main()
{

    int vet[tam];

    srand(time(NULL));

    preencher(vet);
    printf("Original: ");
    imprimir(vet);

    mergeSort(vet, 0, tam - 1);
    printf("Ordenado: ");
    imprimir(vet);

    return 0;

}
