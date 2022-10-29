#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "convert_hexa.h"
#include "header.h"

int main(){
  char *commande = ec_malloc(sizeof(char)*20);
  char *code = ec_malloc(33);
  char *mot = ec_malloc(9);
  code = bit(543293640,32);
  printf("%s\n", code);
  mot = gotohexa(code);
  printf("%s\n", mot);
  int exit =0;
  while(exit != 1){
    scanf("%[^\n]%*c", commande);
    if(strcmp(commande, "")==0){
      fatal("Dont use double Enter");
    }else{
    printf("%s\n", commande);
    }
  }

  free(code);
  free(mot);
  free(commande);
}
