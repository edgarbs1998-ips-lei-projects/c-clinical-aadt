#pragma once

#define QUEUE_OK            0
#define QUEUE_NULL          1
#define QUEUE_NO_MEMORY     2
#define QUEUE_EMPTY         3
#define QUEUE_FULL          4

#include "queueElem.h"

struct queueImpl;
typedef struct queueImpl* PtQueue;

/* Cria uma nova inst�ncia de Queue
Recebe:
	initialCapacity: capacidade inicial da queue
Retorno:
	Refer�ncia da inst�ncia ou;
	NULL no caso de inexist�ncia de mem�ria */
PtQueue queueCreate(unsigned int initialCapacity);

/* Destr�i uma inst�ncia, libertando a mem�ria associada.
Argumentos:
	ptQueue - endere�o da refer�ncia da inst�ncia;
Retorno:
	STACK_NULL se a refer�ncia recebida for NULL, ou;
	STACK_OK em caso de sucesso; */
int queueDestroy(PtQueue* ptQueue);

/* Insere um elemento numa dada inst�ncia
Argumentos:
	queue - refer�ncia da inst�ncia;
	elem - elemento a inserir;
Retorno:
	QUEUE_NULL se a refer�ncia recebida for NULL, ou;
	QUEUE_FULL caso a queue esteja cheia, ou;
	QUEUE_NO_MEMORY caso n�o haja mem�ria para guardar o elemento, ou;
	QUEUE_OK em caso de sucesso */
int queueEnqueue(PtQueue queue, QueueElem elem);

/* Remove um elemento numa dada inst�ncia
Argumentos:
	queue - refer�ncia da inst�ncia;
	ptElem - elemento removido (retorno por refer�ncia);
Retorno:
	QUEUE_NULL se a refer�ncia recebida for NULL, ou;
	QUEUE_EMPTY caso a queue esteja vazia, ou;
	QUEUE_OK em caso de sucesso */
int queueDequeue(PtQueue queue, QueueElem* ptElem);

/* Espreita o elemento do topo numa dada inst�ncia
Argumentos:
	queue - refer�ncia da inst�ncia;
	ptElem - elemento no topo (retorno por refer�ncia);
Retorno:
	QUEUE_NULL se a refer�ncia recebida for NULL, ou;
	QUEUE_EMPTY caso a queue esteja vazia, ou;
	QUEUE_OK em caso de sucesso; */
int queuePeek(PtQueue queue, QueueElem* ptElem);

/* Quantos elementos est�o armazenados numa inst�ncia
Argumentos:
	queue - refer�ncia da inst�ncia;
	ptSize - n�mero de elementos (retorno por refer�ncia);
Retorno:
	QUEUE_NULL se a refer�ncia recebida for NULL, ou;
	QUEUE_OK em caso de sucesso; */
int queueSize(PtQueue queue, int* ptSize);

/* Verifica se a inst�ncia est� vazia (n�o cont�m elementos)
Argumentos:
	queue - refer�ncia da inst�ncia;
Retorno:
	1 caso esteja vazia ou a refer�ncia seja NULL, ou;
	0 caso n�o esteja vazia; */
int queueIsEmpty(PtQueue queue);

/* Limpa uma inst�ncia (remove todos os elementos)
Argumentos:
	queue - refer�ncia da inst�ncia;
Retorno:
	QUEUE_NULL se a refer�ncia recebida for NULL, ou;
	QUEUE_OK em caso de sucesso; */
int queueClear(PtQueue queue);

/* Mostra informa��o sobre uma inst�ncia
Argumentos:
	queue - refer�ncia da inst�ncia; */
void queuePrint(PtQueue queue);