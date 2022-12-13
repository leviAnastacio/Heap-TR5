#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

//Função de comparação dos elementos desejados para o teste, baseada na função de comparação do arquivo header.
int myCOMP(void* x, void* y){
	int ptx = *((int*)x);
	int pty = *((int*)y);
	if(ptx - pty < 5){
		return -1;
	}else{
		if(ptx - pty > 5) 
			return 1;
		else 
			return 0;
	}
}

//Função de imprimir os elementos teste da heap.
void print(void** vet, int P){
	int i;
	printf("VETOR DE %d TAMANHO:\n", P);
	for(i = 0; i < P; i++){
		printf(" %d ", *((int*)vet[i]));
	}
	printf("\n");
}

int main(){
   	HEAP* vet = HEAP_create(10, myCOMP);
   	
   	int* x;
   	int i;
   	
   	printf("INCLUINDO... \n");
	for(i = 0; i < 10; i++){
		x = malloc(sizeof(int));
		*x = i*10;
		HEAP_add(vet, x);
	}
	
	print(vet->elems, vet->P);
  
  	printf("REMOVENDO!");
  	HEAP_remove(vet);
  	
	print(vet->elems, vet->P);
   
	return 0;  
}
