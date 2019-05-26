#include "list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct listImpl {
	ListElem* elements;
	unsigned int size;
	unsigned int capacity;
} ListImpl;

/*
Cria uma nova instância da List.
Recebe:
initialCapacity - capacidade inicial (se aplicável)
Retorno:
referência da instância ou;
NULL no caso de inexistência de memória.
*/
PtList listCreate(unsigned int initialCapacity) {

	PtList newList = (PtList)malloc(sizeof(ListImpl));
	if (newList == NULL) return NULL;

	newList->elements = (ListElem*)malloc(initialCapacity * sizeof(ListElem));

	if (newList->elements == NULL) return NULL;

	newList->size = 0;
	newList->capacity = initialCapacity;

	return newList;
}

/*
Destroi uma instância, libertando a memória associada.
Argumentos:
ptList - endereço da referência da instância;
Retorno:
LIST_NULL se a referência recebida for NULL, ou;
LIST_OK em caso de sucesso;
*/
int listDestroy(PtList* ptList) {

	PtList list = *ptList;

	if (list == NULL) return LIST_NULL;

	free(list->elements);
	free(list);

	*ptList = NULL;

	return LIST_OK;
}

/*
Adiciona um elemento numa dada instância.
Argumentos:
list - referência da instância;
rank - o rank/índice para a operação (0 >= r <= size);
elem - elemento a emlistar;
Retorno:
LIST_NULL se a referência recebida for NULL, ou;
LIST_FULL caso a lista esteja cheia, ou;
LIST_NO_MEMORY caso nao haja memória para guardar o elemento, ou;
LIST_INVALID_RANK caso o rank seja inválido para a operação, ou;
LIST_OK em caso de sucesso;
*/
int listAdd(PtList list, int rank, ListElem elem) { // O(n)
	if (list == NULL) return LIST_NULL;
	if (list->size == list->capacity) return LIST_FULL;

	if (rank < 0 || rank > list->size) return LIST_INVALID_RANK;

	//que algoritmo do arrayList ?! -> insertAtOrdered
	for (int i = list->size; i > rank; i--) {
		list->elements[i] = list->elements[i - 1];
	}

	list->elements[rank] = elem;

	list->size++;

	return LIST_OK;
}

/*
Remove um elemento numa dada instância.
Argumentos:
list - referência da instância;
rank - índice do elemento;
ptElem - elemento removido (retorno por referência);
Retorno:
LIST_NULL se a referência recebida for NULL, ou;
LIST_EMPTY caso a pilha esteja vazia, ou;
LIT_INVALID_RANK caso o rank seja inválido para a operação, ou;
LIST_OK em caso de sucesso;
*/
int listRemove(PtList list, int rank, ListElem* ptElem) { //O(n)
	if (list == NULL) return LIST_NULL;
	if (list->size == 0) return LIST_EMPTY;
	if (rank < 0 || rank > list->size - 1) return LIST_INVALID_RANK;

	*ptElem = list->elements[rank];
	list->size--;

	for (int i = rank; i < list->size; i++) {
		list->elements[i] = list->elements[i + 1];
	}

	return LIST_OK;
}

int listGet(PtList list, int rank, ListElem* ptElem) { //O(1)
	if (list == NULL) return LIST_NULL;
	if (list->size == 0) return LIST_EMPTY;
	if (rank < 0 || rank > list->size) return LIST_INVALID_RANK;

	*ptElem = list->elements[rank];
	return LIST_OK;
}

int listSet(PtList list, int rank, ListElem elem, ListElem* ptOldElem) { //O(1)
	if (list == NULL) return LIST_NULL;
	if (list->size == 0) return LIST_EMPTY;
	if (rank < 0 || rank > list->size) return LIST_INVALID_RANK;

	*ptOldElem = list->elements[rank];
	list->elements[rank] = elem;
	return LIST_OK;
}

/*
Quantos elementos estão armazenados numa instância.
Argumentos:
list - referência da instância;
ptSize - número de elementos (retorno por referência);
Retorno:
LIST_NULL se a referência recebida for NULL, ou;
LIST_OK em caso de sucesso;
*/
int listSize(PtList list, int* ptSize) { //O(1)
	if (list == NULL) return LIST_NULL;

	*ptSize = list->size;

	return LIST_OK;
}

/*
Verifica se a instância está vazia (não contém elementos)
Argumentos:
list - referência da instância;
Retorno:
1 caso esteja vazia ou a referência seja NULL, ou;
0 caso não esteja vazia;
*/
int listIsEmpty(PtList list) { //O(1)
	if (list == NULL) return 1;
	if (list->size == 0) return 1;
	return 0;
}

/*
Limpa uma instância (remove todos os elementos)
Argumentos:
list - referência da instância;
Retorno:
LIST_NULL se a referência recebida for NULL, ou;
LIST_OK em caso de sucesso;
*/
int listClear(PtList list) { //O(1)
	if (list == NULL) return LIST_NULL;

	list->size = 0;

	return LIST_OK;
}

/*
Mostra informação sobre uma instância
Argumentos:
list - referência da instância;
*/
void listPrint(PtList list) {

	if (list == NULL)
		printf("LIST NULL \n");
	else if ( /*listIsEmpty(list)*/ list->size == 0)
		printf("LIST EMPTY \n");
	else {
		for (int rank = 0; rank < list->size; rank++) {
			printf("Rank %d : ", rank);
			listElemPrint(list->elements[rank]);
		}
	}
}