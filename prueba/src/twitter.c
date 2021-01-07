//TDA TWITTER 
#include "include/lista.h"
#include "include/twitter.h"

#include <stdlib.h>
#include <string.h>

struct tuit{
    size_t id_twitt;
    size_t id_user; 
    char twitt [MAX_CHAR];
    size_t id_respuesta; 
    size_t *lista_rtas; 
    lista_t *lista_likes;
};

void imprimir_lu(void *dato){
    printf("%lu",*(size_t*)dato);
}
twitt_t* twitt_crear(size_t user,size_t id_tw,size_t id_rta,char* msj){
    twitt_t *t = malloc(sizeof(twitt_t)); 
    if (t == NULL)
        return NULL;
    t->id_user = user; 
    t->id_twitt = id_tw;
    t->id_respuesta = id_rta; 
    strcpy(t->twitt,msj); 
    t->lista_rtas = calloc(MAX_RESPUESTAS,sizeof(size_t));
    t->lista_likes = lista_crear(); 
    return t; 
}

//ACCESO A DATOS
size_t twitt_id (twitt_t *t){
    if(t == NULL)
        return 0;
    return t->id_twitt;
}

size_t twitt_user(twitt_t *t){
    if(t == NULL)
        return 0;
    return t->id_user;
}

char* twitt_msj(twitt_t *t){
    if(t == NULL)
        return NULL;
    return &(t->twitt[0]);
}

size_t twitt_idrta(twitt_t *t){
    if(t == NULL)
        return 0;
    return t->id_respuesta;
}

size_t* twitt_lista_respuestas(twitt_t *t){
    if(t == NULL)
        return NULL;
    return t->lista_rtas;
}

lista_t* twitt_lista_likes(twitt_t *t){
    if(t == NULL)
        return NULL;
    return t->lista_likes; 
}

void twitt_destruir(twitt_t *t){
    if(t == NULL)
        return; 
    free(t->lista_rtas);
    lista_destruir(t->lista_likes,NULL);
    free(t);
}
//FUNCIONES 
size_t twitt_cantidad_likes(const twitt_t *t){
    if(t == NULL)
        return 0; 
    size_t aux=0; 
    nodo_t*n = t->lista_likes->prim;
    while(n != NULL){
        aux++; 
        n = n->sig; 
    } 
    return aux; 
}

bool twitt_dar_like(twitt_t *t, size_t user){
    if(t == NULL)
        return false; 
    if(t->id_user == user)
        return false; 
    
    nodo_t *n = t->lista_likes->prim; 
    lista_imprimir(t->lista_likes,imprimir_lu); 
    while(n != NULL){
        if(*(size_t*)n->elem == user )
            return false; 
        n = n->sig;
    }
   
    if(lista_insertar_comienzo(t->lista_likes,(void*) &user) == false)
        return false;
    //lista_imprimir(t->lista_likes,imprimir_lu); 
    return true;  
}
