#include <stdio.h>
#include <stdlib.h>
#include "heap.h"



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
    // O laço while vai realizar a comparação dos elementos pais com os filhos, escolhendo o menor deles e realizando a troca de posições.
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

//Função de criação e inicialização dos valores da heap.
HEAP* HEAP_create(int n, COMP* compara)
{
    
    HEAP* heap = malloc(sizeof(HEAP));//alocação de memória de um ponteiro do tipo definido heap.
    heap->comparador = compara;
    heap->N = n;
    heap->P = 0;
    heap->elems = malloc(n * sizeof(void *));//alocação de memória dos elementos da heap.
    // Inicializando o vetor de 0 a n, vetor irá receber NULL.
    for(int i = 0; i < n; i++){//Laço que inicializa todas as posições do vetor com o endereço nulo.
        heap->elems[i] = NULL;
    }
    return heap;//Retorna o ponteiro com o endereço do vetor de elementos da heap criado e inicializado.
}

// Função de adição e ordenação do vetor.
void HEAP_add(HEAP* vetor, void* newelem)
{
     
    if(vetor->P < vetor->N){//condicional que verifica se há espaço no vetor da heap.
    
        if(vetor->P == 0){//testa se o vetor esta vazio, em caso valido, a posicao inicial recebera o novo elemento passado por parametro.
            vetor->elems[0] = newelem;
            vetor->P++;//incremento no valor do tamanho da heap.
        }
        
        else{//caso a heap não esteja vazia, o novo elemento será adicionado no final dela
            vetor->elems[vetor->P] = newelem;
            vetor->P++;//incremento no valor do tamanho da heap.
             
            for(int i = vetor->P-1; i>0; i--){
                // O "If" irá fazer operação de bubble up (subida na HEAP). 
                if(vetor->comparador(vetor->elems[i], vetor->elems[i/2]) == -1){//condicional que realiza a comparação entre as posições da heap							
                    void* aux = vetor->elems[i];				//em relação à sua propriedade matemática de ordenação e logo, após
                    vetor->elems[i] = vetor->elems[i/2];			//os elementos e posições são reorganizados com a operação de bubble up
                    vetor->elems[i/2] = aux;					//(subida na heap).
                }
            }
        }
    }
}


// Função de remoção de elementos da heap.
void* HEAP_remove(HEAP* vetor)
{ 
    if(vetor->P < 1){//condicional que verifica se a heap está vazia, caso seja valido, retorna o endereço nulo.
    
        return NULL;
    }
    if(vetor->P == 1){//condicional que verifica caso a heap possua apenas um elemento, caso seja valido, será retornado o endereço desse elemento.
        vetor->P--;
        return vetor->elems[vetor->P];
    }
	else{//remoção do primeiro elemento da heap
        void* aux = vetor->elems[0];//definição de um ponteiro auxiliar do tipo void, que recebe o valor e o endereço do primeiro elemento do vetor para assim ser realizada sua exclusão
        vetor->elems[0] = vetor->elems [vetor->P-1];//Reorganização dos elementos que sobraram na heap após a remoção do primeiro elemento
        vetor->elems[vetor->P - 1] = aux;
        vetor->P--;//decremento no valor do tamanho da heap.
        
	heap_descida(vetor->elems, vetor->P, vetor->comparador);//operação de descida (bubble down).
        
        return aux;//retorno do valor removido na heap.
    }
    
}
