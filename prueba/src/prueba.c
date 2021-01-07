//ARCHIVO PRUEBA 
#include "include/lista.h"
#include "include/twitter.h"

#define ID_VIKY 85
#define ID_TWITT 4
#define ID_LAUTI 69
#define MSJ "Lauti esta re bueno"

int main(void){
    twitt_t *t = twitt_crear(ID_VIKY,ID_TWITT,0,MSJ); 
    if (t == NULL){
        printf("No asigno memoria\n"); 
        return 0; 
    }
    printf("ID DEL USER: %lu\nID DEL TWITT: %lu\nMENSAJE DEL TWITT: %s\nCANTIDAD DE LIKES INICIALES: %lu\n",twitt_user(t),twitt_id(t),twitt_msj(t),twitt_cantidad_likes(t)); 

    if(twitt_dar_like(t,ID_VIKY)== false)
        printf("No le podes dar like a tu mismo twitt gila\n"); 
    if(twitt_dar_like(t,ID_LAUTI))
        printf("Lauti le dio like\n"); 
    printf("Cantidad de likes: %lu\n",twitt_cantidad_likes(t)); 
   //LE DOY VARIOS LIKES 
    int i; 
    for (i=0;i<7;i++){
        if(twitt_dar_like(t,ID_LAUTI+i)==false)
            printf("No le pudo dar like al nro: %i\n",i);
    }
    printf("Cantidad de likes: %lu\n",twitt_cantidad_likes(t)); 
    twitt_destruir(t);

    return 0;
}