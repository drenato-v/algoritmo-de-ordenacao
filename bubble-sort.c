//Algoritmo Bubble Sort (bolha) desenvolvido para reordenar vetores (variáveis unidimensionais)

//O algoritmo Bubble Sort percorre o vetor comparando pares de elementos adjacentes e troca 
//suas posições sempre que o elemento anterior é maior que o próximo. Esse processo se repete 
//várias vezes até que todos os elementos estejam em ordem, fazendo com que os maiores valores 
//'flutuem' para o final do vetor a cada iteração.

//Bubble Sort é lento em sua composição

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define tam 10


void bubbleSort(int vet[])
{

    int i, j, copia, troca;

    for(i = 0; i < tam - 1; i++)
    {

        //troca é zerada a cada passagem: se uma passagem inteira terminar sem trocas,
        //o vetor já está ordenado e o algoritmo pode parar
        troca = 0;

        for(j = 0; j < tam - i - 1; j++)
        {

            if(vet[j] > vet[j + 1])
            {

                copia = vet[j];
                vet[j] = vet[j + 1];
                vet[j + 1] = copia;
                troca = 1;

            }

        }

        if(troca == 0) break;

    }

}

void bubbleSort2(int vet[])
{
    
    int j, troca, copia;

    do{

        //zera a flag no início de cada passagem; sem isso o laço nunca termina
        troca = 0;

        for(j = 0; j < tam - 1; j++)
        {

            if(vet[j] > vet[j + 1])
            {

                copia = vet[j];
                vet[j] = vet[j + 1];
                vet[j + 1] = copia;
                troca = 1;

            }

        }

    }while(troca);

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

    int v[tam];

    srand(time(NULL));

    preencher(v);
    printf("Original:   ");
    imprimir(v);

    bubbleSort(v);
    printf("bubbleSort: ");
    imprimir(v);

    preencher(v);
    printf("\nOriginal:    ");
    imprimir(v);

    bubbleSort2(v);
    printf("bubbleSort2: ");
    imprimir(v);

    return 0;
}
