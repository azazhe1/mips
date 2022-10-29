#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"
#include "header.h"
#include "convert_hexa.h"



int fonctions(char *operateur, int tab_opérande[3]){
  char *resultat = (char*)malloc(sizeof(char)*33);
  char *resultat_final = (char*)malloc(sizeof(char)*9);
  char *temp_resultat = (char*)malloc(sizeof(char)*33);
  int quit = 0;
  resultat[0] = '\0';
  resultat_final[0] = '\0';
  int do_final = 1;
  if(!strcmp(operateur,"ADD")){
    resultat = strcat(resultat,Add.opcode);
    resultat[6] = '\0';

    bit(tab_opérande[1], sizeof((Add.rs))-1, temp_resultat);
    resultat = strcat(resultat,temp_resultat);
    printf("%c\n", resultat[11]);
    resultat[6+5] = '\0';

    bit(tab_opérande[2], sizeof((Add.rt))-1,temp_resultat);
    resultat = strcat(resultat,temp_resultat);
    resultat[6+6+6] = '\0';

    bit(tab_opérande[0], sizeof((Add.rd))-1,temp_resultat);
    resultat = strcat(resultat,temp_resultat);
    resultat[5+5+5+6] = '\0';

    resultat = strcat(resultat,Add.sa);
    resultat[6+5+5+5+5] = '\0';

    resultat = strcat(resultat,Add.fonction);
    resultat[32] = '\0';

  }else if(!strcmp(operateur,"SUB")){
    resultat = strcat(resultat,Sub.opcode);
    resultat[6] = '\0';

    bit(tab_opérande[1], sizeof((Sub.rs))-1, temp_resultat);
    resultat = strcat(resultat,temp_resultat);
    printf("%c\n", resultat[11]);
    resultat[6+5] = '\0';

    bit(tab_opérande[2], sizeof((Sub.rt))-1,temp_resultat);
    resultat = strcat(resultat,temp_resultat);
    resultat[6+6+6] = '\0';

    bit(tab_opérande[0], sizeof((Sub.rd))-1,temp_resultat);
    resultat = strcat(resultat,temp_resultat);
    resultat[5+5+5+6] = '\0';

    resultat = strcat(resultat,Sub.sa);
    resultat[6+5+5+5+5] = '\0';

    resultat = strcat(resultat,Sub.fonction);
    resultat[32] = '\0';

  }else if(!strcmp(operateur,"MULT")){
    resultat = strcat(resultat,Sub.opcode);
    resultat[6] = '\0';

    bit(tab_opérande[1], sizeof((Sub.rs))-1, temp_resultat);
    resultat = strcat(resultat,temp_resultat);
    printf("%c\n", resultat[11]);
    resultat[6+5] = '\0';

    bit(tab_opérande[2], sizeof((Sub.rt))-1,temp_resultat);
    resultat = strcat(resultat,temp_resultat);
    resultat[6+6+6] = '\0';

    resultat = strcat(resultat,Mult.rd);
    resultat[5+5+5+6] = '\0';

    resultat = strcat(resultat,Sub.sa);
    resultat[6+5+5+5+5] = '\0';

    resultat = strcat(resultat,Sub.fonction);
    resultat[32] = '\0';

  }/*else if(strcmp(operateur,"DIV")){
    resultat = strcat(resultat,Div.opcode);
    resultat[6] = '\0';
    resultat = strcat(resultat,(char *)bit(tab_opérande[0], sizeof(Div.rs)-1));
    resultat[5+6] = '\0';
    resultat = strcat(resultat,(char *)bit(tab_opérande[1], sizeof(Div.rt)-1));
    resultat[5+6+5] = '\0';
    resultat = strcat(resultat,Div.rd);
    resultat[5+5+5+6] = '\0';
    resultat = strcat(resultat,Div.sa);
    resultat[6+5+5+5+5] = '\0';
    resultat = strcat(resultat,Div.fonction);
    resultat[32] = '\0';

  }else if(strcmp(operateur,"AND")){
    resultat = strcat(resultat,And.opcode);
    resultat[6] = '\0'; 
    resultat = strcat(resultat,(char *)bit(tab_opérande[1], sizeof(And.rs)-1));
    resultat[5+6] = '\0';
    resultat = strcat(resultat,(char *)bit(tab_opérande[2], sizeof(And.rt)-1));
    resultat[5+6+5] = '\0';
    resultat = strcat(resultat,(char *)bit(tab_opérande[0], sizeof(And.rd)-1));
    resultat[5+5+5+6] = '\0';
    resultat = strcat(resultat,And.sa);
    resultat[6+5+5+5+5] = '\0'; 
    resultat = strcat(resultat,And.fonction);
    resultat[32] = '\0';

  }else if(strcmp(operateur,"OR")){
    resultat = strcat(resultat,Or.opcode);
    resultat[6] = '\0'; 
    resultat = strcat(resultat,(char *)bit(tab_opérande[1], sizeof(Or.rs)-1));
    resultat[5+6] = '\0';
    resultat = strcat(resultat,(char *)bit(tab_opérande[2], sizeof(Or.rt)-1));
    resultat[5+6+5] = '\0';
    resultat = strcat(resultat,(char *)bit(tab_opérande[0], sizeof(Or.rd)-1));
    resultat[5+5+5+6] = '\0';
    resultat = strcat(resultat,Or.sa);
    resultat[6+5+5+5+5] = '\0'; 
    resultat = strcat(resultat,Or.fonction);
    resultat[32] = '\0';

  }else if(strcmp(operateur,"XOR")){
    resultat = strcat(resultat,Xor.opcode);
    resultat[6] = '\0'; 
    resultat = strcat(resultat,(char *)bit(tab_opérande[1], sizeof(Xor.rs)-1));
    resultat[5+6] = '\0';
    resultat = strcat(resultat,(char *)bit(tab_opérande[2], sizeof(Xor.rt)-1));
    resultat[5+6+5] = '\0';
    resultat = strcat(resultat,(char *)bit(tab_opérande[0], sizeof(Xor.rd)-1));
    resultat[5+5+5+6] = '\0';
    resultat = strcat(resultat,Xor.sa);
    resultat[6+5+5+5+5] = '\0'; 
    resultat = strcat(resultat,Xor.fonction);
    resultat[32] = '\0';

  }/*else if(strcmp(operateur,"ROTR")){
    resultat = strcat(resultat,Rotr.opcode);
    resultat[6] = '\0'; 
    resultat = strcat(resultat,(char *)bit(tab_opérande[1], sizeof(Rotr.rs)-1));
    resultat[5+6+5] = '\0';
    resultat = strcat(resultat,(char *)bit(tab_opérande[2], sizeof(Rotr.rt)-1));
    resultat[5+5+5+6] = '\0';
    resultat = strcat(resultat,(char *)bit(tab_opérande[0], sizeof(Rotr.rd)-1));
    resultat = strcat(resultat,Rotr.sa);
    resultat[6+5+5+5+5] = '\0'; 
    resultat = strcat(resultat,Rotr.fonction);
    resultat[32] = '\0';

  }*/
  /*else if(strcmp(operateur,"SLL")){
    resultat = strcat(resultat,Sll.opcode);
    resultat[6] = '\0'; 
    resultat = strcat(resultat, Sll.rs);
    resultat[5+6] = '\0';
    resultat = strcat(resultat,(char *)bit(tab_opérande[1], sizeof(Sll.rt)-1));
    resultat[5+6+5] = '\0';
    resultat = strcat(resultat,(char *)bit(tab_opérande[0], sizeof(Sll.rd)-1));
    resultat[5+5+5+6] = '\0';
    resultat = strcat(resultat,(char *)bit(tab_opérande[2], sizeof(Sll.sa)-1));
    resultat[6+5+5+5+5] = '\0'; 
    resultat = strcat(resultat,Sll.fonction);
    resultat[32] = '\0';

  }/*else if(strcmp(operateur,"SRL")){
    resultat = strcat(resultat,Sll.opcode);
    resultat[6] = '\0'; 
    resultat = strcat(resultat, Sll.rs);
    resultat[5+6] = '\0';
    resultat = strcat(resultat,(char *)bit(tab_opérande[1], sizeof(Sll.rt)-1));
    resultat[5+6+5] = '\0';
    resultat = strcat(resultat,(char *)bit(tab_opérande[0], sizeof(Sll.rd)-1));
    resultat[5+5+5+6] = '\0';
    resultat = strcat(resultat,(char *)bit(tab_opérande[2], sizeof(Sll.sa)-1));
    resultat[6+5+5+5+5] = '\0'; 
    resultat = strcat(resultat,Sll.fonction);
    resultat[32] = '\0';

  }*/
  /*else if(strcmp(operateur,"MFHI")){
    resultat = strcat(resultat,Mfhi.opcode);
    resultat[6] = '\0'; 
    resultat = strcat(resultat, Mfhi.rs);
    resultat[5+6] = '\0';
    resultat = strcat(resultat, Mfhi.rt);
    resultat[5+6+5] = '\0';
    resultat = strcat(resultat,(char *)bit(tab_opérande[0], sizeof(Mfhi.rd)-1));
    resultat[5+5+5+6] = '\0';
    resultat = strcat(resultat, Mfhi.sa);
    resultat[6+5+5+5+5] = '\0'; 
    resultat = strcat(resultat,Mfhi.fonction);
    resultat[32] = '\0';

  }else if(strcmp(operateur,"MFLO")){
    resultat = strcat(resultat,Mflo.opcode);
    resultat[6] = '\0'; 
    resultat = strcat(resultat, Mflo.rs);
    resultat[5+6] = '\0';
    resultat = strcat(resultat, Mflo.rt);
    resultat[5+6+5] = '\0';
    resultat = strcat(resultat,(char *)bit(tab_opérande[0], sizeof(Mflo.rd)-1));
    resultat[5+5+5+6] = '\0';
    resultat = strcat(resultat, Mflo.sa);
    resultat[6+5+5+5+5] = '\0'; 
    resultat = strcat(resultat,Mflo.fonction);
    resultat[32] = '\0';

  }/*else if(strcmp(operateur,"JR")){
    resultat = strcat(resultat,Mflo.opcode);
    resultat[6] = '\0'; 
    resultat = strcat(resultat, Mflo.rs);
    resultat[5+6] = '\0';
    resultat = strcat(resultat, Mflo.rt);
    resultat[5+6+5] = '\0';
    resultat = strcat(resultat,(char *)bit(tab_opérande[0], sizeof(Mflo.rd)-1));
    resultat[5+5+5+6] = '\0';
    resultat = strcat(resultat, Mflo.sa);
    resultat[6+5+5+5+5] = '\0'; 
    resultat = strcat(resultat,Mflo.fonction);
    resultat[32] = '\0';

  }*/
  /*else if(strcmp(operateur,"NOP")){
    resultat = strcat(resultat,Nop.opcode);
    resultat[6] = '\0'; 
    resultat = strcat(resultat, Nop.rs);
    resultat[5+6] = '\0';
    resultat = strcat(resultat, Nop.rt);
    resultat[5+6+5] = '\0';
    resultat = strcat(resultat, Nop.rd);
    resultat[5+5+5+6] = '\0';
    resultat = strcat(resultat, Nop.sa);
    resultat[6+5+5+5+5] = '\0'; 
    resultat = strcat(resultat,Nop.fonction);
    resultat[32] = '\0';

  }*/else if(!strcmp(operateur,"EXIT")){
    quit = 1;
    do_final = 0;
  }
  if(do_final){
    gotohexa(resultat, resultat_final);
    printf("%s\n", resultat_final);
  }
  free(temp_resultat);
  free(resultat);
  free(resultat_final);
  return quit;

}
