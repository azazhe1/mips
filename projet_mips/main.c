#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "convert_hexa.h"
#include "header.h"
#include "fonctions.h"
#include "lecture_instructions.h"

int main(){
  /*
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
  */
 /*
 int tab[3] = {7,5,2};
 int a ;
 a = fonctions("ADD", tab);
  */
 /*
  printf("Instruction : %s\n", "ADDI $5, $0, 5");
  printf("Opérateur : %s\n", lecture_operateur("ADDI $5, $0, 5"));

  printf("Instruction : %s\n", "ADD $7, $15, $2");
  int* result = lecture_operandeR("ADD $7, $15, $2");

  int i = 0;
  for(i=0; i<3; i++){
    printf("%d ", result[i]);
  }
  printf("\n");  
  */
  /*char *commande = (char*)malloc(sizeof(char)*20);
  int exit =0;
  int *result;
  char *operateur = (char*)malloc(sizeof(char)*8);
  int size = 0;
  //char *operateur2 = (char*)malloc(sizeof(char)*8);
  while(strcmp(commande, "EXIT")){
    scanf("%[^\n]%*c", commande);
      commande[19] = '\0';
      operateur = lecture_operateur(commande);
      result = lecture_operandeR(commande);
      
      exit = fonctions(operateur, result);
  }
  free(commande);
  free(operateur);  
  free(result);
  int tab[3] = {7,5,2};
  char * t = "ADD";
  
  fonctions(t,tab);

  fonctions(t,tab);
  fonctions(t,tab);
  */
  char *test = malloc(sizeof(char)*33);
  char *mot = malloc(sizeof(char)*9);
  mot[0] = '\0';
  char* operateur = (char*)malloc(sizeof(char)*8);
  int *tab = malloc(sizeof(int)*3);
  char *commande = (char*)malloc(sizeof(char)*20);
  int exit = 0;
  while(exit == 0){
    scanf("%[^\n]%*c", commande);
    if(strcmp(commande, "\0")==0){
      fatal("Dont use double Enter");
      exit = 1;
    }else{
    lecture_operateur (commande, operateur);
    lecture_operandeR(commande, tab);
    exit = fonctions(operateur, tab);
    }
  }
  
  free(commande);
  free(operateur);
  free(tab);
  free(test);
  free(mot);
  

}
