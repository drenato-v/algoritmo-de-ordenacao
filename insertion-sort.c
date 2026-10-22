//Insertion Sort pressupõe que o primeiro elemento do vetor no indice 0 está na posição correta e a partir do segundo insere 
//cada elemento na posição correta em relação aos seus anteriores, iterando sobre cada indice.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define tam 10

void insertionSort(int vet[])
{

    int i, j, chave;

    for(i = 1; i < tam; i++)
    {

        chave = vet[i];

        //j recebe o valor do indice antecedente ao i
        j = i - 1;

        while(j >= 0 && vet[j] > chave)
        {

            vet[j + 1] = vet[j];
            j--;

        }

        vet[j + 1] = chave;

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

    insertionSort(vet);
    printf("Ordenado: ");
    imprimir(vet);

    return 0;

}
