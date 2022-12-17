#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/header.h"

void application(int *tab, char * operateur, int nb_op, char type,int *registre){
    int i = 0;
    int nb_registre = 0;
   
    if(type == 'R'){
        nb_registre = nb_op;
    }else{
        nb_registre = nb_op -1;
    }
    if(!strcmp(operateur,"ADDI")){
        printf("%d\n",tab[0]);
        printf("%d\n",tab[1]);
        printf("%d\n",tab[2]);
        if((registre[tab[1]] == 67108864)){
            fatal("Un des registres est vide");
        }else{
            registre[tab[0]] = registre[tab[1]] + tab[2];   
        }
        printf("%d\n",registre[tab[0]]);
    }
}   