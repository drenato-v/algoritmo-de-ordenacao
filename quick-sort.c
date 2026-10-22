//O algoritmo Quick Sort escolhe um pivô, posiciona-o no lugar correto (menores à esquerda, maiores à direita)
//e repete o processo recursivamente em cada uma das duas partes.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define tam 10

void trocar(int *a, int *b)
{

    int copia = *a;
    *a = *b;
    *b = copia;

}

int particionar(int vet[], int inicio, int fim)
{
    int pivo = vet[fim], i = inicio;
    
    for(int j = inicio; j < fim; j++)
    {

        if(vet[j] <= pivo)
        {

            trocar(&vet[i], &vet[j]);
            i++;

        }

    }

    trocar(&vet[i], &vet[fim]);

    return i;
}

void quickSort(int vet[], int inicio, int fim)
{

    if(inicio < fim)
    {

        //Seleciona o último elemento, pivô, e posiciona-o no lugar correto com os números menores à esquerda e os maiores à direita.
        //Em seguida, particiona o vetor em dois "subvetores" e organiza seguindo o mesmo principio do pivô
        int meio = particionar(vet, inicio, fim);
        quickSort(vet, inicio, meio - 1);
        quickSort(vet, meio + 1, fim);

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

    quickSort(vet, 0, tam - 1);
    printf("Ordenado: ");
    imprimir(vet);

    return 0;

}
