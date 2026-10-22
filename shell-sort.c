//O algoritmo Shell Sort, criado por Donald Shell em 1959, é uma otimização do Insertion Sort. Ele se baseia na ideia de comparar
//elementos distantes entre si por meio de gaps (saltos) com o intuito de reduzir o número de movimentações em relação ao Insertion Sort

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define tam 10

void shellSort(int vet[])
{

    int gap, i, j, copia;

    for(gap = tam / 2; gap > 0; gap /= 2)
    {

        for(i = gap; i < tam; i++)
        {

            copia = vet[i];

            for(j = i; j >= gap && vet[j - gap] > copia; j -= gap)
                vet[j] = vet[j - gap];

            vet[j] = copia;

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

    shellSort(vet);
    printf("Ordenado: ");
    imprimir(vet);

    return 0;

}
