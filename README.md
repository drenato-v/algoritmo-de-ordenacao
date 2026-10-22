# Algoritmos de Ordenação em C

Implementações em C de seis algoritmos clássicos de ordenação, feitas durante um curso da Udemy. Cada arquivo é independente: gera um vetor de inteiros aleatórios, imprime o vetor original e depois o vetor ordenado.

| Arquivo | Algoritmo | Estratégia |
|---|---|---|
| [`bubble-sort.c`](bubble-sort.c) | Bubble Sort | Trocas entre vizinhos |
| [`selection-sort.c`](selection-sort.c) | Selection Sort | Seleção do menor |
| [`insertion-sort.c`](insertion-sort.c) | Insertion Sort | Inserção ordenada |
| [`shell-sort.c`](shell-sort.c) | Shell Sort | Inserção com saltos (*gaps*) |
| [`quick-sort.c`](quick-sort.c) | Quick Sort | Divisão e conquista (partição) |
| [`merge-sort.c`](merge-sort.c) | Merge Sort | Divisão e conquista (intercalação) |

---

## Sumário

1. [O que é ordenação](#o-que-é-ordenação)
2. [Como compilar e executar](#como-compilar-e-executar)
3. [Bubble Sort](#1-bubble-sort)
4. [Selection Sort](#2-selection-sort)
5. [Insertion Sort](#3-insertion-sort)
6. [Shell Sort](#4-shell-sort)
7. [Quick Sort](#5-quick-sort)
8. [Merge Sort](#6-merge-sort)
9. [Comparativo](#comparativo)
10. [Correções realizadas](#correções-realizadas)

---

## O que é ordenação

**Definição.** Um algoritmo de ordenação recebe uma sequência de *n* elementos `⟨a₁, a₂, …, aₙ⟩` e produz uma permutação `⟨a'₁, a'₂, …, a'ₙ⟩` dessa sequência tal que `a'₁ ≤ a'₂ ≤ … ≤ a'ₙ`, segundo uma relação de ordem total definida sobre os elementos.

**Desenvolvimento.** Três critérios ajudam a comparar algoritmos:

- **Complexidade de tempo** — quantas comparações/trocas são feitas em função de *n*, medida em notação assintótica (*Big-O*) para o melhor, o médio e o pior caso.
- **Complexidade de espaço** — quanta memória extra o algoritmo usa. Algoritmos *in-place* usam apenas O(1) de memória adicional.
- **Estabilidade** — um algoritmo é *estável* quando elementos com chaves iguais mantêm a ordem relativa original. Isso importa ao ordenar registros por mais de um campo.

Os algoritmos baseados apenas em comparação têm um limite inferior teórico de **Ω(n log n)** comparações no pior caso. Por isso Merge Sort e Quick Sort (caso médio) são considerados assintoticamente ótimos, enquanto Bubble, Selection e Insertion são O(n²).

**Exemplo.** Ordenar `[5, 3, 8, 1]` produz `[1, 3, 5, 8]`. Se ordenarmos alunos `(Ana, 7), (Bia, 9), (Caio, 7)` por nota, um algoritmo estável garante `(Ana, 7), (Caio, 7), (Bia, 9)` — Ana continua antes de Caio.

---

## Como compilar e executar

É preciso ter um compilador C (`gcc` ou `clang`; no macOS, `xcode-select --install`).

```bash
gcc -Wall bubble-sort.c -o bubble-sort
./bubble-sort
```

Saída de exemplo (os números mudam a cada execução):

```
Original: [11] [99] [66] [87] [89] [63] [0] [96] [58] [77]
Ordenado: [0] [11] [58] [63] [66] [77] [87] [89] [96] [99]
```

O mesmo vale para os outros arquivos. O tamanho do vetor é definido pela constante `tam` no topo de cada arquivo (`#define tam 10`).

Todos os programas seguem a mesma estrutura:

| Função | Papel |
|---|---|
| `preencher(vet)` | Preenche o vetor com valores aleatórios de 0 a 99 |
| `imprimir(vet)` | Mostra o vetor na tela |
| `xxxSort(...)` | O algoritmo de ordenação em si |
| `main()` | Chama `srand(time(NULL))`, preenche, imprime, ordena e imprime de novo |

---

## 1. Bubble Sort

### Definição
O Bubble Sort (ordenação por bolha) é um algoritmo de ordenação por **troca** que percorre repetidamente a sequência comparando pares de elementos **adjacentes** e trocando-os quando estão fora de ordem. Ao fim da *k*-ésima passagem, os *k* maiores elementos ocupam suas posições definitivas no final do vetor.

### Desenvolvimento
O nome vem da imagem dos valores maiores "subindo" como bolhas até o final do vetor. A cada passagem, a parte final já ordenada cresce em uma posição, por isso o laço interno vai só até `tam - i - 1`.

Uma otimização importante é usar uma *flag* de troca: se uma passagem inteira acontece sem nenhuma troca, o vetor já está ordenado e o algoritmo pode parar. Com isso, o melhor caso (vetor já ordenado) cai de O(n²) para O(n).

- **Tempo:** melhor O(n) (com a *flag*), médio O(n²), pior O(n²)
- **Espaço:** O(1) — *in-place*
- **Estável:** sim (só troca quando `vet[j] > vet[j+1]`, nunca em empate)

Trecho de `bubble-sort.c`:

```c
for(i = 0; i < tam - 1; i++) {
    troca = 0;                      // zerada a cada passagem
    for(j = 0; j < tam - i - 1; j++)
        if(vet[j] > vet[j + 1]) {
            /* troca vet[j] e vet[j + 1] */
            troca = 1;
        }
    if(troca == 0) break;           // nenhuma troca: vetor já ordenado
}
```

O arquivo traz duas versões, e a `main` executa as duas: `bubbleSort` (dois `for`, com parada antecipada) e `bubbleSort2` (um `do…while` que repete enquanto houver trocas).

### Exemplo
Vetor `[5, 3, 8, 1]`:

| Passagem | Comparações e trocas | Resultado |
|---|---|---|
| 1 | 5↔3 troca · 5 e 8 ok · 8↔1 troca | `[3, 5, 1, 8]` |
| 2 | 3 e 5 ok · 5↔1 troca | `[3, 1, 5, 8]` |
| 3 | 3↔1 troca | `[1, 3, 5, 8]` |

Uso típico: fins didáticos ou vetores minúsculos/quase ordenados. Na prática é o mais lento desta lista.

---

## 2. Selection Sort

### Definição
O Selection Sort (ordenação por seleção) divide o vetor em uma parte ordenada (à esquerda) e outra não ordenada (à direita) e, a cada iteração *i*, **seleciona o menor elemento** da parte não ordenada e o troca com o elemento da posição *i*.

### Desenvolvimento
Diferente do Bubble Sort, faz no máximo **uma troca por iteração** — no total, no máximo n − 1 trocas. Isso o torna interessante quando escrever na memória é caro. Por outro lado, ele sempre varre toda a parte restante para achar o mínimo, então faz ~n²/2 comparações **mesmo que o vetor já esteja ordenado**.

- **Tempo:** O(n²) em todos os casos
- **Espaço:** O(1) — *in-place*
- **Estável:** não (a troca de longa distância pode passar um elemento por cima de outro igual)

Trecho de `selection-sort.c`:

```c
indiceMenor = i;
for(j = i + 1; j < tam; j++)
    if(vet[j] < vet[indiceMenor]) indiceMenor = j;
if(indiceMenor != i) /* troca vet[i] e vet[indiceMenor] */
```

### Exemplo
Vetor `[5, 3, 8, 1]`:

| i | Menor da parte `[i..fim]` | Troca | Resultado |
|---|---|---|---|
| 0 | 1 (posição 3) | 5 ↔ 1 | `[1, 3, 8, 5]` |
| 1 | 3 (posição 1) | — | `[1, 3, 8, 5]` |
| 2 | 5 (posição 3) | 8 ↔ 5 | `[1, 3, 5, 8]` |

Instabilidade na prática: `[2a, 2b, 1]` → o 1 troca com `2a`, gerando `[1, 2b, 2a]`.

---

## 3. Insertion Sort

### Definição
O Insertion Sort (ordenação por inserção) constrói a sequência ordenada um elemento por vez: assume que o subvetor `vet[0..i-1]` já está ordenado e **insere** `vet[i]` (a *chave*) na posição correta desse subvetor, deslocando para a direita os elementos maiores que ela.

### Desenvolvimento
É o mesmo método que usamos para ordenar cartas na mão. O primeiro elemento é considerado ordenado sozinho, e o laço começa no índice 1. Em vez de várias trocas, o algoritmo **desloca** os maiores uma posição para a direita e grava a chave uma única vez no "buraco" que sobra.

É **adaptativo**: o custo é proporcional ao número de inversões. Num vetor quase ordenado ele é praticamente linear, e por isso é usado dentro de algoritmos híbridos (como o Timsort do Python e o Introsort do C++) para subvetores pequenos.

- **Tempo:** melhor O(n), médio O(n²), pior O(n²) (vetor em ordem decrescente)
- **Espaço:** O(1) — *in-place*
- **Estável:** sim (o `while` para em `vet[j] > chave`, não desloca iguais)

Trecho de `insertion-sort.c`:

```c
chave = vet[i];
j = i - 1;
while(j >= 0 && vet[j] > chave) {
    vet[j + 1] = vet[j];
    j--;
}
vet[j + 1] = chave;
```

### Exemplo
Vetor `[5, 3, 8, 1]` (a barra `|` separa a parte ordenada):

| i | Chave | Ação | Resultado |
|---|---|---|---|
| 1 | 3 | desloca 5 | `[3, 5 \| 8, 1]` |
| 2 | 8 | nada a deslocar | `[3, 5, 8 \| 1]` |
| 3 | 1 | desloca 8, 5 e 3 | `[1, 3, 5, 8]` |

---

## 4. Shell Sort

### Definição
O Shell Sort, proposto por Donald Shell em 1959, é uma generalização do Insertion Sort que ordena por inserção subsequências formadas por elementos separados por uma distância *h* (o **gap**), reduzindo *h* progressivamente até 1. Quando *h* = 1, executa um Insertion Sort comum sobre um vetor já quase ordenado.

### Desenvolvimento
A fraqueza do Insertion Sort é que cada elemento só anda **uma posição por vez**; um valor pequeno no fim do vetor precisa de muitos passos para chegar ao início. O Shell Sort resolve isso permitindo "saltos" longos no começo, que eliminam muitas inversões de uma vez. Quando chega ao gap 1, sobra pouco trabalho.

O desempenho depende da **sequência de gaps**. Este código usa a sequência original de Shell (`tam/2, tam/4, …, 1`), cujo pior caso é O(n²). Outras sequências melhoram isso: Knuth (1, 4, 13, 40, …) dá O(n^1,5); Ciura (1, 4, 10, 23, 57, 132, …) é uma das melhores na prática.

- **Tempo:** depende dos gaps — pior O(n²) com os gaps de Shell; na prática bem mais rápido que os O(n²) anteriores
- **Espaço:** O(1) — *in-place*
- **Estável:** não (os saltos podem inverter elementos iguais)

Trecho de `shell-sort.c`:

```c
for(gap = tam / 2; gap > 0; gap /= 2)
    for(i = gap; i < tam; i++) {
        copia = vet[i];
        for(j = i; j >= gap && vet[j - gap] > copia; j -= gap)
            vet[j] = vet[j - gap];
        vet[j] = copia;
    }
```

### Exemplo
Vetor `[8, 5, 3, 7, 1, 6, 2, 4]` (n = 8):

| Gap | Subsequências ordenadas | Resultado |
|---|---|---|
| 4 | (8,1)→(1,8) · (5,6) · (3,2)→(2,3) · (7,4)→(4,7) | `[1, 5, 2, 4, 8, 6, 3, 7]` |
| 2 | posições pares (1,2,8,3)→(1,2,3,8) · ímpares (5,4,6,7)→(4,5,6,7) | `[1, 4, 2, 5, 3, 6, 8, 7]` |
| 1 | Insertion Sort comum (poucas inversões restantes) | `[1, 2, 3, 4, 5, 6, 7, 8]` |

---

## 5. Quick Sort

### Definição
O Quick Sort, criado por Tony Hoare em 1959, é um algoritmo de **divisão e conquista** que escolhe um elemento chamado **pivô**, **particiona** o vetor de forma que todos os elementos ≤ pivô fiquem à sua esquerda e os maiores à sua direita (o pivô fica então na posição final), e aplica recursivamente o mesmo procedimento às duas partes.

### Desenvolvimento
Todo o trabalho acontece na partição; não há etapa de junção, porque depois de particionar as duas metades já estão no lugar relativo correto. Este código usa o **esquema de partição de Lomuto**: o pivô é o último elemento (`vet[fim]`), e o índice `i` marca a fronteira da região "≤ pivô".

A escolha do pivô decide o desempenho:
- Se o pivô divide o vetor em partes parecidas, a recursão tem profundidade log n → **O(n log n)**.
- Se o pivô é sempre o menor ou o maior, uma das partes fica vazia → **O(n²)**. Com o último elemento como pivô, isso ocorre justamente com vetores **já ordenados** ou em ordem inversa.

Soluções comuns: pivô aleatório, ou *mediana de três* (primeiro, meio e último).

Mesmo com esse pior caso, o Quick Sort costuma ser o mais rápido na prática por ser *in-place* e aproveitar bem a memória cache. É a base do `qsort` e do `std::sort` (em versões híbridas).

- **Tempo:** melhor O(n log n), médio O(n log n), pior O(n²)
- **Espaço:** O(log n) em média, pela pilha de recursão (O(n) no pior caso)
- **Estável:** não

Trecho de `quick-sort.c`:

```c
int particionar(int vet[], int inicio, int fim) {
    int pivo = vet[fim], i = inicio;
    for(int j = inicio; j < fim; j++)
        if(vet[j] <= pivo) { trocar(&vet[i], &vet[j]); i++; }
    trocar(&vet[i], &vet[fim]);
    return i;
}
```

### Exemplo
Vetor `[5, 3, 8, 1, 4]`, pivô = 4:

| Passo | Ação | Vetor |
|---|---|---|
| j=0 | 5 > 4, ignora | `[5, 3, 8, 1, 4]` |
| j=1 | 3 ≤ 4, troca com posição i=0 | `[3, 5, 8, 1, 4]` |
| j=2 | 8 > 4, ignora | `[3, 5, 8, 1, 4]` |
| j=3 | 1 ≤ 4, troca com posição i=1 | `[3, 1, 8, 5, 4]` |
| fim | pivô vai para i=2 | `[3, 1, 4, 5, 8]` (4 na posição final) |

Depois, recursão em `[3, 1]` → `[1, 3]` e em `[5, 8]` (já ordenado). Resultado: `[1, 3, 4, 5, 8]`.

---

## 6. Merge Sort

### Definição
O Merge Sort, atribuído a John von Neumann (1945), é um algoritmo de **divisão e conquista** que divide o vetor ao meio recursivamente até obter subvetores de tamanho 1 (trivialmente ordenados) e depois **intercala** (*merge*) pares de subvetores ordenados em um único subvetor ordenado.

### Desenvolvimento
Enquanto no Quick Sort o trabalho está na divisão, no Merge Sort a divisão é trivial (basta achar o meio) e o trabalho está na **intercalação**: com dois ponteiros, um em cada metade, copia-se sempre o menor dos dois elementos apontados para um vetor auxiliar.

A recorrência é T(n) = 2T(n/2) + O(n), que resolve para **O(n log n)** em **todos** os casos: o desempenho não depende da ordem inicial dos dados. O custo é a memória extra do vetor auxiliar. É estável e muito usado para ordenar listas encadeadas e arquivos grandes que não cabem na memória (ordenação externa).

- **Tempo:** O(n log n) em todos os casos
- **Espaço:** O(n) — vetor auxiliar
- **Estável:** sim (em empate, copia primeiro o elemento da metade esquerda)

Trechos de `merge-sort.c` — a recursão:

```c
void mergeSort(int vet[], int inicio, int fim) {
    if(inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;  // evita overflow de (inicio + fim)
        mergeSort(vet, inicio, meio);
        mergeSort(vet, meio + 1, fim);
        merge(vet, inicio, meio, fim);
    }
}
```

E o coração da intercalação, dentro de `merge` (as duas metades são copiadas antes para os vetores auxiliares `esq` e `dir`):

```c
while(i < tamEsq && j < tamDir) {
    if(esq[i] <= dir[j]) vet[k++] = esq[i++];   // <= garante estabilidade
    else                 vet[k++] = dir[j++];
}
// depois, copia o que sobrou de esq ou de dir
```

### Exemplo
Vetor `[38, 27, 43, 3]`:

```
            [38, 27, 43, 3]
             /           \
        [38, 27]       [43, 3]          ← divisão
        /     \         /    \
     [38]   [27]     [43]   [3]
        \     /         \    /
        [27, 38]       [3, 43]          ← intercalação
             \           /
            [3, 27, 38, 43]
```

Intercalação final: compara 27 × 3 → 3; 27 × 43 → 27; 38 × 43 → 38; sobra 43.

---

## Comparativo

| Algoritmo | Melhor | Médio | Pior | Espaço extra | Estável | Adaptativo |
|---|---|---|---|---|---|---|
| Bubble Sort | O(n) | O(n²) | O(n²) | O(1) | Sim | Sim* |
| Selection Sort | O(n²) | O(n²) | O(n²) | O(1) | Não | Não |
| Insertion Sort | O(n) | O(n²) | O(n²) | O(1) | Sim | Sim |
| Shell Sort | O(n log n) | depende dos gaps | O(n²)** | O(1) | Não | Sim |
| Quick Sort | O(n log n) | O(n log n) | O(n²) | O(log n) | Não | Não |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) | Sim | Não |

\* com a *flag* de parada antecipada · \*\* com a sequência de gaps de Shell (n/2, n/4, …, 1)

**Qual usar?**
- Vetor pequeno ou quase ordenado → **Insertion Sort**
- Desempenho geral em memória → **Quick Sort** (com bom pivô)
- Garantia de O(n log n) ou necessidade de estabilidade → **Merge Sort**
- Poucas escritas na memória → **Selection Sort**
- Meio-termo simples e sem recursão → **Shell Sort**

---

## Correções realizadas

Revisão feita sobre a primeira versão do código:

| Arquivo | Problema | Correção |
|---|---|---|
| `merge-sort.c` | Faltavam a função `merge` e a `main`; o arquivo não compilava | Implementadas `merge` (intercalação estável com vetores auxiliares) e `main` |
| `bubble-sort.c` | Em `bubbleSort`, `troca` era zerada uma só vez; a parada antecipada só funcionava se a primeira passagem não tivesse trocas | `troca = 0` passou para dentro do laço externo |
| `bubble-sort.c` | Em `bubbleSort2`, `troca` nunca voltava a 0, causando laço infinito sempre que havia alguma troca | `troca = 0` no início de cada iteração do `do…while` |
| `bubble-sort.c` | Usava `tam 4` e imprimia um número por linha; `bubbleSort2` nunca era chamada | `tam 10`, saída no mesmo formato dos demais e a `main` testa as duas versões |
| `selection-sort.c` | O laço interno começava em `j = i`, comparando o elemento com ele mesmo | Começa em `j = i + 1` |
| Todos | `rand()` sem `srand()`: os mesmos números a cada execução | `srand(time(NULL))` no início da `main` |
| Todos | A função `print` também preenchia o vetor, e a impressão final era repetida na `main` | Separadas em `preencher()` e `imprimir()` |
| Vários | Erros de digitação nos comentários ("bidmensionais", "reoordenar", "emm") | Corrigidos |

Todos os arquivos compilam sem avisos com `gcc -Wall -Wextra` e foram testados com vetores de 10 e de 2.000 elementos.

---

## Referências

- CORMEN, T. H. et al. *Algoritmos: Teoria e Prática*. 3ª ed. Rio de Janeiro: Elsevier, 2012.
- KNUTH, D. E. *The Art of Computer Programming, Vol. 3: Sorting and Searching*. 2ª ed. Addison-Wesley, 1998.
- SEDGEWICK, R.; WAYNE, K. *Algorithms*. 4ª ed. Addison-Wesley, 2011.
