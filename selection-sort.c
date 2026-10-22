//O algoritmo selection sort seleciona, a cada iteração, o menor elemento do vetor e o coloca na posição correta.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define tam 10

void selectionSort(int vet[])
{

    int i, j, indiceMenor, copia;

    for(i = 0; i < tam - 1; i++)
    {

        indiceMenor = i;
        for(j = i + 1; j < tam; j++)
        {

            if(vet[j] < vet[indiceMenor])   indiceMenor = j;

        }

        if(indiceMenor != i)
        {

            copia = vet[i];
            vet[i] = vet[indiceMenor];
            vet[indiceMenor] = copia;

        }

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

    selectionSort(vet);
    printf("Ordenado: ");
    imprimir(vet);

    return 0;

}
