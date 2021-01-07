#include "include/lista.h"

#include <stdio.h>
#include <stdlib.h>



nodo_t * crear_nodo (void * dato){
	printf("DATO QUE INGRESA A CREAR NODO %lu\n",*(size_t*)dato); 
	nodo_t *n = malloc(sizeof(nodo_t)); //creo el nodo y le pido memoria
	if (n == NULL) //validacion 
		return n; 

	n->elem = dato;//le asigno el dato
	n->sig = NULL;//apunto el siguiente a null ya que aun no esta en una lista 
	return n;
} 

lista_t *lista_crear(void){
	lista_t *l = malloc(sizeof(lista_t));
	if (l == NULL )
		return NULL;

	l->prim = NULL;//lista vacia, apunto el primer nodo a null 
	return l;
}

void lista_destruir(lista_t *l, void (*destruir_dato)(void *dato)){
	nodo_t *aux,*sig;
	aux = l->prim;

	while(aux != NULL){
		sig = aux->sig;
		if (destruir_dato != NULL)//verifico que mi puntero a funcion no sea nulo
			destruir_dato(aux->elem);//libero la memoria pedida para el dato
		
		free (aux);//libero la memoria perdida para el nodo  
		aux = sig;//lo apunto al siguiente 
	}
	free(l); //libero la lista
}

bool lista_es_vacia(const lista_t *l){
	return (l->prim == NULL);
}

bool lista_insertar_comienzo(lista_t *l, void *dato){
	nodo_t *n = crear_nodo (dato); 
	if (n == NULL)
		return false; 
	n->sig = l->prim; 
	l->prim = n; 
	return true; 
}

bool lista_insertar_final(lista_t *l, void *dato){
	nodo_t *n = crear_nodo(dato); 
	if (n == NULL)
		return false; 

	if (lista_es_vacia(l)){
		l->prim = n; 
		return true;
	}

	nodo_t *aux = l->prim; 
	while(aux->sig != NULL ){
		aux  = aux->sig;
	}
	aux->sig = n; 
	return true;
}

void *lista_extraer_primero(lista_t *l){
	void *dato;
	nodo_t *p = l->prim; 
	l->prim = l->prim->sig;
	dato = p->elem; 
	free(p);
	return dato;  
}

void *lista_extraer_ultimo(lista_t *l){
	if (lista_es_vacia(l))
		return NULL; 
	nodo_t *p, *aux;
	void * dato; 

	p = l->prim;
	if (p->sig == NULL)
		return lista_extraer_primero(l); 

	while(p->sig->sig != NULL)
		p = p->sig; 
	aux  = p->sig; 
	p->sig = NULL; 

	dato = aux->elem; 
	free(aux);
	return dato; 
}

void *lista_buscar(const lista_t *l, const void *dato, int (*cmp)(const void *a, const void *b)){
	//funcion que busca un dato dentro de una lista  (el puntero a funcion compara los dos elementos y devuelve 0 si son iguales 1 si a>b y -1 si b>a)

	nodo_t *n = l->prim; 
	while(n != NULL){
		if (cmp(n->elem,dato) == 0)
			return n->elem; 
		else 
			n = n->sig; 
	}

	return NULL;
}

void *lista_borrar(lista_t *l, const void *dato, int (*cmp)(const void *a, const void *b)){
	nodo_t *n = l->prim; 

	while(n != NULL){
		if (cmp(n->elem,dato) == 0){
			void *aux = n->elem;
			free (n); 
			return aux; 
		} 
		else 
			n = n->sig; 
	}
	return NULL; 
}

//puntero a lista que devuelve 1 si dato1>dato2  
// 0 si son iguales 
// -1 si dato1<dato2

size_t recorrer_lista(lista_t*l){
    size_t size = 1; 
    if (l == NULL)
        return 0; 
    if (l->prim == NULL)
        return 0; 
    nodo_t*aux = l->prim; 
    while(aux->sig != NULL){
        size ++; 
        aux = aux->sig; 
    }
    return size; 
}

bool lista_insertar_ordenado (lista_t *l, nodo_t *n,int(*cmp)(void *dato1, void *dato2), int flag){ 
	if (n == NULL)
		return false; //nodo vacio 
	if (lista_es_vacia(l)){
		l->prim = n; 
		return true; 
	}

	nodo_t *ant, *actual;
	actual = l->prim;
	ant = actual; 
	if (cmp(actual->elem,n->elem) == flag){ //primer elemento
		l->prim = n; 
		n->sig = actual; 
		return true; 
	}


	while(actual != NULL){
		if(cmp(actual->elem,n->elem) == flag ){
			ant->sig = n; 
			n->sig = actual;
			return true;
		} 	// si quiero que sea de menor a mayor flag == 1, menor a mayor flag == -1
		ant = actual; 
		actual = actual->sig; 
	}
	ant->sig = n; 
	n->sig = NULL; 
return true; 
}

bool lista_esta_incluida(const lista_t *a, const lista_t *b){
	if ((a == NULL) || (b == NULL)) //chequeo que no esten vacias
		return false; 

	if (lista_cmp(a,b) == 1)//verifico que a sea menor a b 
		return false;

	nodo_t *l_a, *l_b; 
	bool flag= 1; 

	l_a = a->prim; 
	l_b = b->prim; 

	if (l_a->elem < l_b->elem)// al ser listas ordenadas verifico que si a comienza con numeros mas chicos 

	while(l_a != NULL){ 

		if (l_b == NULL)
			return false;

		while(l_b != NULL){
			if (*((int*)l_a->elem) == *((int*)l_b->elem)){
				flag = true; 
				break;
			}
			else {
				flag = false; 
				l_b = l_b->sig; 
			}
		}

		l_a = l_a->sig;
	}

	return flag;  
}

int lista_cmp(const lista_t *a,const lista_t *b){ //1 si a>b -1 si b>a 0 si son iguales, 3 si hay un error
	if((a == NULL) || (b == NULL) )  //si estan vacias devuelvo error 
		return 3; 
	int cant_a, cant_b;
	cant_a = 0; cant_b = 0;  
	nodo_t *l_a, *l_b; 

	l_a = a->prim; 
	l_b = b->prim; 

	while(l_a != NULL){//recorro a y cuento sus elementos 
		cant_a ++; 
		l_a = l_a->sig; 
	}

	while(l_b != NULL){ //recorro b y cuento sus elementos, verificando si es mayor que a 
		cant_b ++; 
		if (cant_b > cant_a)
			return -1;
		l_b = l_b->sig; 
	}

	if(cant_a > cant_b) // si llego hasta aca b es menor o igual que a asi que verifico por ambas 
		return 1; 
	

	return 0; 
}


bool lista_llenar(lista_t *l, int*v, int size){
	bool flag; 
	int i = 0; 
	for(i = 0; i < size ; i++){
		flag = lista_insertar_final(l,(void*)&v[i]);
	}
	return flag; 
}

void lista_imprimir(lista_t*l,void (*imprimir_dato)(void *dato)){
	nodo_t* aux = l->prim;
	printf("{"); 
	while (aux!=NULL){
		imprimir_dato(aux->elem);
		printf(" --> "); 
		aux = aux->sig; 
	}
	printf("NULL }\n");
}

int lista_ordenar(lista_t*l,int(*cmp)(void *dato, void *dato2),int flag){ // usa el metodo de seleccion 
	if (l->prim == NULL)
		return 0;
	
	nodo_t *iterador = l->prim->sig;
	nodo_t *min,*ant, *aux; //punteros para guardar el minimo, y los de los costados. 

	ant = l->prim; 
	min = l->prim; 

	//primera iteracion 
	
	
	while(iterador != NULL){
		if(cmp(min->elem,iterador->elem) == flag){
			min = iterador; 
			aux = ant;
		}	
		ant = iterador; 			
		iterador = iterador->sig;	
	}

	if (cmp(min->elem,l->prim->elem) != 0 ){//si ya esta ordenado lo dejo asi
	aux->sig = min->sig;
	min->sig = l->prim; 
	l->prim = min;
	}
 	//resto de la lista 

	nodo_t* primero; //puntero al ultimo ordenado. 

	while (min->sig->sig!= NULL ){
		primero = min; 
		min = min->sig; 
		ant = min;
		iterador = min->sig; 
	
		while(iterador != NULL){
			if(cmp(min->elem,iterador->elem) == flag){	
				min = iterador; 
				aux = ant;
			}	
			ant = iterador; 		
			iterador = iterador->sig;	
		}
		if (cmp(min->elem,primero->sig->elem) == 0 ); // si ya esta ordenado no hago nada
		
		else{ 
			aux->sig = min->sig;
			min->sig = primero->sig; 
			primero->sig = min; 
		}
	}
 return 1;
}

