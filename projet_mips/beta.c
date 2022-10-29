#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "convert_hexa.h"

int commande_in(char * ligne, char *com){// Teste si nous somme à la bonne ligne
    char *commande = malloc(sizeof(char)*9);
    int i =0;
    while((ligne[i]!=':') && (ligne[i]!='\0')){
        commande[i] = ligne[i];
        i++;
    }
    commande[i] = '\0';
    if(!strcmp(commande, com)){
        i = 1;
    }

    free(commande);
    return i;
}

char type(char *ligne){// permet d'avoir le type
    int i = 0;
    while(ligne[i] != ':'){
        i++;
    }
    return ligne[i+1];

}

void get_op(char *ligne, char *op){// permet d'obtenir l'opcode
    int i = 0;
    int j = 0;
    while(ligne[i] != ':'){
        
        i++;
    }
    i = i+3;
    while(ligne[i] != ':'){
        op[j] = ligne[i];
        j++;
        i++;
    }
    op[6] = '\0';
}

void get_param(char *ligne,int *tab){//Pour connaitre les param   
    int i =0;
    int j = 0;
    while(ligne[i] != ':'){
        i++;
    }
    i = i+3;
    while(ligne[i] != ':'){
        i++;
    }
    i++;
    while(ligne[i] != '\0'){
       
        if(ligne[i] != ','){
            tab[j] = ligne[i] - 48;
            j++;
        }
        i++;
        
    }

}
int is_in(int *tab, int value){//Pour savoir si je dois mettre la valeur dedans
    int in = 0;
    for(int i = 0; i<4; i++){
        if(tab[i] == value){
            i = 3;
            in = 1;
        }
    }
    return in;
}
void concat_R(char *mot,int tab[3], int *tab_file, char *opcode, char * fonction){
    char *rs = (char *)malloc(sizeof(char)*6);
    char *rt = (char *)malloc(sizeof(char)*6);
    char *rd = (char *)malloc(sizeof(char)*6);
    char *sa = (char *)malloc(sizeof(char)*6);
    char * mot_hexa = (char*)malloc(sizeof(char)*9);
    int index_param = 0;// Pour savoir ou je le trouve dans tab

    strcpy(rs, "00000");
    rs[5] = '\0';
    strcpy(rt, "00000");
    rt[5] = '\0';
    strcpy(rd, "00000");
    rd[5] = '\0';
    strcpy(sa, "00000");
    sa[5] = '\0';

    if(is_in(tab_file,3)){
        bit(tab[index_param], 5, rd);
        index_param++;
    }
    if(is_in(tab_file,1)){
        bit(tab[index_param], 5, rs);
        index_param++;
    } 
    if(is_in(tab_file,2)){
        bit(tab[index_param], 5, rt);
        index_param++;
    } 
    if(is_in(tab_file,4)){
        bit(tab[index_param], 5, sa);
        index_param++;
    }
    
    printf("%s\n", opcode);
    printf("%s\n", rs);
    printf("%s\n", rt);
    printf("%s\n", rd);
    printf("%s\n", sa);
    printf("%s\n", fonction);
    mot = strcat(mot,opcode);
    mot[6] = '\0';
    mot = strcat(mot,rs);
    mot[6+5] = '\0';
    mot = strcat(mot,rt);
    mot[6+6+6] = '\0';
    mot = strcat(mot,rd);
    mot[6+5+5+5] = '\0';
    mot = strcat(mot,sa);
    mot[6+5+5+5+5] = '\0';
    mot = strcat(mot,fonction);
    mot[32] = '\0';
    printf("%s\n", mot);
    gotohexa(mot, mot_hexa);
    printf("%s\n", mot_hexa);
    free(mot_hexa);
    free(sa);
    free(rd);
    free(rt);
    free(rs);
    
}

void fonctions(char *commande, int tab[3]){
    FILE *fp = fopen("dico.txt", "r");

    char *ligne = (char *)malloc(sizeof(char)*100);
    char *opcode = (char *)malloc(sizeof(char)*7);
    
    char *fonction = (char *)malloc(sizeof(char)*7);
    int *tab_file = (int *)malloc(24);
    char *mot = (char*)malloc(sizeof(char)*33);
    int exit = 0;
   
    mot[0] = '\0';
    strcpy(fonction, "000000");
    fonction[6] = '\0';

    tab_file[0] = 0;
    tab_file[1] = 0;
    tab_file[2] = 0;
    tab_file[3] = 0;

    if(fp == NULL){
        perror("Probleme ouverture fichier ");
    }
    while(exit !=1){
        fscanf(fp,"%s",ligne);
        printf("%s\n", ligne);
        exit = commande_in(ligne, commande );
    }
    get_op(ligne, opcode);
    //printf("%s\n", opcode);
    get_param(ligne,tab_file);

    if(type(ligne) == 'R'){
        strcpy(fonction, opcode);
        fonction[6] = '\0';
        strcpy(opcode, "000000");
        opcode[6] = '\0';
    }
    concat_R(mot,tab,tab_file,opcode,fonction);

    free(mot);
    free(tab_file);
    free(fonction);
    free(opcode);
    free(ligne);
    fclose(fp);
}

int main(){
    char *caca = malloc(9);
    gotohexa("00000000101000100011100000100010", caca);
    //int tab[3] = {7,5,2};
 //   fonctions("SUB", tab);

    free(caca);
}