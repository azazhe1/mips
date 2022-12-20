#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/header.h"
#include "../include/convert_hexa.h"

/*void application(int *tab, char * operateur, int nb_op, char type,int *registre){
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
*/
void get_commande(char *mot_bit, char *commande){
    char *opcode = (char *)malloc(sizeof(char)*7);
    FILE *fp = fopen("dico.txt", "r");
    char *ligne = (char *)malloc(sizeof(char)*80);
    int exit = 0;
    char *current_op = (char *)malloc(sizeof(char)*7);
    int indice_ligne = 0;
    char char_ligne;
    for(int i =0;i<6;i++){//On récupère l'opcode que notre instruction
        opcode[i] = mot_bit[i];
    }
    opcode[6] = '\0';
    if(!strcmp(opcode,"000000")){//Si c'est un type R on doit prendre les dernier bit et pas les premiers comme opcode
        for(int i =26;i<32;i++){
            opcode[i- 26] = mot_bit[i];
        }
        opcode[6] = '\0';
    }

    if(fp == NULL){
        perror("Probleme ouverture fichier ");
    }

    while(exit == 0){
        fgets(ligne,80,fp);
        char_ligne = ligne[indice_ligne];
        while(char_ligne != ':'){
            indice_ligne++;
            char_ligne = ligne[indice_ligne];
        }
        indice_ligne++;
        indice_ligne++;
        indice_ligne++;
        
        
        for(int i=0;i<6;i++){
            current_op[i] = ligne[indice_ligne];
            indice_ligne++;
        }
        current_op[6] = '\0';
        if(!strcmp(opcode,current_op)){
            exit =1;
        }
        indice_ligne=0; 
    }
    while(ligne[indice_ligne] != ':'){
        commande[indice_ligne] = ligne[indice_ligne];
        indice_ligne++;
    }
    commande[indice_ligne] = '\0';
    if(!strcmp(commande,"SRL") || !strcmp(commande,"ROTR")){
        if(mot_bit[10] == '1'){
            strcpy(commande,"ROTR");
        }else{
            strcpy(commande,"SRL");
        }
    }
    free(current_op);
    free(ligne);
    fclose(fp);
    free(opcode);
}

void application(char *mot_bit, int *registre){
    char *commande = (char *)malloc(sizeof(char)*5);
    char *rs = (char *)malloc(sizeof(char)*6);
    int rs_d;
    char *rt = (char *)malloc(sizeof(char)*6);
    int rt_d;
    char *rd = (char *)malloc(sizeof(char)*6);
    int rd_d;
    char *sa = (char *)malloc(sizeof(char)*6);
    int sa_d;
    char *imm = (char *)malloc(sizeof(char)*17);
    int imm_d;
    char *adresse = (char *)malloc(sizeof(char)*27);
    int adresse_d;  

    get_commande(mot_bit,commande);
    if(!strcmp(commande,"ADDI")){
        for(int i =6; i<11;i++){
            rs[i-6] = mot_bit[i];
        }
        rs[5]='\0';
        for(int i =11; i<16;i++){
            rt[i-11] = mot_bit[i];
        }
        rt[5]='\0';
        for(int i =16; i<32; i++){
            imm[i-16] = mot_bit[i];
        }
        imm[16]='\0';
        rs_d = bit_to_decimal(rs);
        rt_d = bit_to_decimal(rt);
        imm_d = bit_to_decimal(imm);

        if((registre[rs_d] == 67108864)){
            printf("Le registre %d est vide\n",rs_d);
            fatal("registre vide");
        }else{
            if(registre[rt_d] == 67108864){
                registre[rt_d] = registre[rs_d] + imm_d;   
            }else{
                registre[rt_d] = registre[rs_d] + imm_d + registre[rt_d];   
            }
        }
        printf("%d\n",registre[rt_d]);
    }

    free(adresse);
    free(imm);
    free(sa);
    free(rd);
    free(rt);
    free(rs);
    free(commande);
}