#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

//Função de criação "HEAP_create" para criar e inicializar o vetor do usuário.

static int filho_esq(int index) {
    return (2*index) + 1;
}

static int filho_dir(int index) {
    return (2*index) + 2;
}

static void heap_descida(void **elems, int P, COMP *comparador)
{
    int pai_pos = 0;
    int filhoe_pos = filho_esq(pai_pos);
    int filhod_pos = filho_dir(pai_pos);
    int menor = pai_pos; 
    // O while vai ficar comparando os pais com os filhos, escolhendo o menor deles e realizando a troca.
    while (pai_pos < P - 1)
    {
        if (filhoe_pos < P && comparador(elems[filhoe_pos], elems[pai_pos]) == -1)
        {
            menor = filhoe_pos;        
        }

        if (filhod_pos < P && comparador(elems[filhod_pos], elems[menor]) == -1)
        {
            menor = filhod_pos;

        }
        
        if (menor == pai_pos)
        {
            break;    
        }
        
        // Ação de troca.
        void *aux = elems[pai_pos];
        elems[pai_pos] = elems[menor];
        elems[menor] = aux;

        // Atualização de índices.
        pai_pos = menor;
        filhoe_pos = filho_esq(pai_pos);
        filhod_pos = filho_dir(pai_pos);
    }
}

HEAP* HEAP_create(int n, COMP* compara)
{
    // Memória alocada para a HEAP com o malloc
    HEAP* heap = malloc(sizeof(HEAP));
    // Comparador recebe compara.
    heap->comparador = compara;
    // N (número máximo de elementos) recebe n (parâmetro).
    heap->N = n;
    // P (número de elementos do vetor) recebe zero para inicializar.
    heap->P = 0;
    // Aloca memória dos elentos.
    heap->elems = malloc(n * sizeof(void *));
    // Inicializando o vetor de 0 a n, vetor irá receber NULL.
    for(int i = 0; i < n; i++)
    {
        heap->elems[i] = NULL;
    }
    // Retorna a heap.
    return heap;
}

// Função de adição e ordenação do vetor.
void HEAP_add(HEAP* vetor, void* newelem)
{
    // Verificação do tamanho HEAP, o novo elemento será adicionado e o tamanho do vetor será aumentado.   
    if(vetor->P < vetor->N)
    {
        // Verificando se a HEAP está vazia.
        if(vetor->P == 0)
        {
            // Adição do novo elemento no começo da HEAP.
            vetor->elems[0] = newelem;
            vetor->P++;
        }
        // Adição do novo elemento no final da HEAP e incrementação do vetor.
        else
        {
            vetor->elems[vetor->P] = newelem;
            vetor->P++;
             
            for(int i = vetor->P-1; i>0; i--)
            {
                // O "If" irá fazer operação de bubble up (subida na HEAP). 
                if(vetor->comparador(vetor->elems[i], vetor->elems[i/2]) == -1)
                {
                    void* aux = vetor->elems[i];
                    vetor->elems[i] = vetor->elems[i/2];
                    vetor->elems[i/2] = aux;
                }
            }
        }
    }
}

// Função de remoção de elementos da HEAP.


void* HEAP_remove(HEAP* vetor)
{ 
    // Verificando se há elementos na HEAP.
    if(vetor->P < 1)
    {
        return NULL;
    }
    if(vetor->P == 1)
    {
        vetor->P--;
        return vetor->elems[vetor->P];
    }
	else 
    {
        // Criação de um ponteiro para apontar para o elemento a ser removido.
        void* aux = vetor->elems[0];
        // Ocorre a troca do último elemento com o primeiro.
        vetor->elems[0] = vetor->elems [vetor->P-1]; 
        vetor->elems[vetor->P - 1] = aux;
        
        // Decrementa o vetor.
        vetor->P--;
        //operação de descida
        heap_descida(vetor->elems, vetor->P, vetor->comparador);
        // Retorna o elemento removido.
        return aux;
    }
    
}
