#ifndef __LISTA__
#define __LISTA__


#include <stdbool.h>
#include <stddef.h>

struct nodo
{
	void * elem;
	struct nodo *sig; 
};

struct lista
{
	struct nodo * prim; 
};
typedef struct lista lista_t;
typedef struct nodo nodo_t; 


nodo_t * crear_nodo (void * elem); 

lista_t *lista_crear(void);

void lista_destruir(lista_t *l, void (*destruir_dato)(void *dato));

bool lista_es_vacia(const lista_t *l);

bool lista_insertar_comienzo(lista_t *l, void *dato);

bool lista_insertar_final(lista_t *l, void *dato);

void *lista_extraer_primero(lista_t *l);

void *lista_extraer_ultimo(lista_t *l);

void *lista_buscar(const lista_t *l, const void *dato, int (*cmp)(const void *a, const void *b));

void *lista_borrar(lista_t *l, const void *dato, int (*cmp)(const void *a, const void *b));

size_t recorrer_lista(lista_t*l); 
//void lista_recorrer(const lista_t *l, bool (*visitar)(void *dato, void *extra), void *extra);

bool lista_insertar_ordenado (lista_t *l, nodo_t *n,int(*cmp)(void *dato1, void *dato2), int flag);
// si la lista esta ordenada de  menor a mayor flag == 1, mayor a menor flag == -1

int lista_cmp(const lista_t* a,const lista_t *b);// compara el tamaño de dos listas  1 si a>b  -1 si a<b  0 si a == b 

bool lista_esta_incluida(const lista_t *a, const lista_t *b);

bool lista_llenar(lista_t *l, int*v, int size); //llena la lista con ints 


void lista_imprimir(lista_t*l,void (*imprimir_dato)(void *dato)); 


int lista_ordenar(lista_t *l,int(*cmp)(void *dato, void *dato2),int flag); // si el flag = 1 menor a mayor, flag = -1 mayor a menor 

#endif