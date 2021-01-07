#ifndef TWITTER_H
#define TWITTER_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "lista.h"
// Un tuit puede tener a lo sumo TUIT_MAX_RESPUESTAS respuestas
#define MAX_RESPUESTAS 10
// El mensaje de un tuit puede tener hasta 144 caracteres (sin contar el '\0')
#define MAX_CHAR 144

typedef struct tuit twitt_t;

twitt_t* twitt_crear(size_t user,size_t id_tw,size_t id_rta,char* msj);
size_t twitt_id (twitt_t *t);
size_t twitt_user(twitt_t *t);
char* twitt_msj(twitt_t *t);
size_t twitt_idrta(twitt_t *t);
size_t* twitt_lista_respuestas(twitt_t *t);
lista_t* twitt_lista_likes(twitt_t *t);
void twitt_destruir(twitt_t *t);

size_t twitt_cantidad_likes(const twitt_t *t);
bool twitt_dar_like(twitt_t *t, size_t user);





#endif