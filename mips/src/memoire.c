#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/memoire.h"
#include "../include/header.h"
#include "../include/convert_hexa.h"

int registre[35];//On simule nos registres comme les éléments d'un tableau
Memoire *tete_mem = NULL;//Pointeur de tête de notre mémoire (liste chainée)
int address =0;//Au début on commence à l'adresse 0
int last_instruction_add=0;//Au début notre dernière instruction est 0

void insertion_Tete_mem(char *data,int is_inst,int donnée,int adrs){//Fonction qui insert des instrctions et des données au début de notre liste chainée
    Memoire *nouveau = malloc(sizeof(Memoire));
    long max = 4294967292;//L'adresse maximum que l'on peut avoir
    if(address<=max){//Teste si on a pas ateint l'adresse max
        if(is_inst==1){//Si c'est une instrction qu'on veut empiler
            nouveau->instruction = malloc(sizeof(char)*9);
            strcpy(nouveau->instruction, data);//On copie notre instruction
            last_instruction_add+=4;//On incrémente la valeur de la dernière instruction
            nouveau->is_adresse =1;//On dit que c'est une instruction et non une donnée
            nouveau->adresse = address;//On associe l'adresse
            address= address +4;// On incrémente la prochaine adresse de la procahine instruction
            
        }else{// SI c'est une donnée
            nouveau->is_adresse =0;//On dit que c'est une donnée
            nouveau->data = donnée;//On met la donnée
            nouveau->adresse = adrs;//On met l'adresse
        }
        
        if(tete_mem == NULL){//Cas on la liste chainée est null
            nouveau->link = NULL;
            tete_mem=nouveau;
        }else{
            nouveau->link = tete_mem;
            tete_mem=nouveau;
        }
        
    }else{
        fatal("La mémoire est pleine");
    }
}
void insertion_mode_interactif(char *data){//Pour le mode intéractif on doit ajouter l'instruction a l'adresse 0, tout le temps
    Memoire *nouveau;
    
    if(tete_mem == NULL){//Si la liste chainée est vide on met notre instruction qui va pointer vers NULL
        nouveau = malloc(sizeof(Memoire));
        nouveau->instruction=malloc(sizeof(char)*9);
        nouveau->is_adresse=1;
        nouveau->adresse=0;//Adresse 0
        strcpy(nouveau->instruction, data);
        nouveau->link = NULL;
        tete_mem=nouveau;
        last_instruction_add =4;//On ne modifie jamais réellement last_instruction_add(ça vaut toujours 4)

    }else{//si notre liste n'est pas NULL on doit parcourir notre liste jusqu'à trouver le dernier élément
        nouveau=tete_mem;
        while(nouveau->link!=NULL){//Cherche le dernier éléméent donc l'adresse 0
            nouveau=nouveau->link;
        }
        strcpy(nouveau->instruction, data);//On copie l'instruction
    }

}
void suppression_Tete_mem(void){//permet de suprimer un élément de notre liste chainée
    Memoire *new;
    new=tete_mem;
    tete_mem= tete_mem->link;
    if(new->is_adresse){//Si c'est une instruction on doit free la memoire alloué à notre "string"
        free(new->instruction);
    }
    free(new);//Sup l'élément
}
void supp_mem(void){//Suprime  toute notre liste chainée
    while(tete_mem!=NULL){
        suppression_Tete_mem();
      }
}
void liste_Affiche_mem(void){//Affiche la mémoire
    Memoire *new;
    new = tete_mem;
    if(new == NULL){
        printf("Liste vide!\n");
    }else{
        while(new != NULL){//On parcours toute notre liste chainée
            if(new->is_adresse==0){//Si c'est une data on print l'adresse et la data
                printf("0x%08X:%d\n",new->adresse,new->data);
            }
            new=new->link;
        }
    }
}
void lsite(void){//Pas utile pour le projet, mais pour nous si
    Memoire *new;
    new = tete_mem;
    while(new != NULL){
        printf("%d\n", new->adresse);
        new = new->link;
    }
}
void set_registre(void){// Initialise nos registre à 0
    for(int i=0;i<34;i++){
        registre[i] = 0;
   }
}
int parcourir_mem(int add, Memoire **Indexe){//Nous permet de parcourir notre liste chainée jusqu'a une adresse donnée
    int resultat=0;
    while((*Indexe!=NULL) && ((*Indexe)->adresse!=add)){//On parcourir la liste chainnée jusqu'a notre adresse
        *Indexe = (*Indexe)->link;
    }
    
    if(*Indexe==NULL){// ERROR si l'adresse n'éxiste pas
        printf("adresse : %d\n",add);
        fatal("L'adresse ciblée est incorecte");
    }else if((*Indexe)->is_adresse){
        resultat =1;
    }
    
    return resultat;
}
void get_instruction(char *instruction){// Nous permet d'obtenir l'instruction corespondante a l'adresse de pc
    Memoire *Index = tete_mem;
    parcourir_mem(registre[34], &Index);//On parcours notre liste chainée
    if(Index->is_adresse){
        strcpy(instruction, Index->instruction);//Copie l'instruction
        registre[34]+=4;//On incrémente PC de 4
    }else{
        fatal("L'adresse ciblée est incorecte");
    }
}
int last_instrction(void){//Teste si pc vaut l'adresse de la toute dernière instruction qui doit exécuter. On fait ça pour mettre fin à l'exécution
    int end = 0;
    if(registre[34] == last_instruction_add){
        end =1;
    }
    return end;
}
int get_value_registre(int indice){// Permet d'obtenir la valeur présent dans le registre indice
    return registre[indice];
}
void put_value_registre(int indice,int value){// Permet de metre dans le registre indice la valeur donnée
    registre[indice] = value;
}
int get_pc(void){// Nous permet d'obtenir la valeur de pc
    return registre[34];
}
void modifier_pc(int adrs){// Modifie la valeur de pc
    Memoire * Index = tete_mem;
    if(parcourir_mem(adrs,&Index)){//On teste si notre adresse est dans notre liste chainée
        registre[34] = adrs;
    }else{
        printf("adresse : %d\n",adrs);
        fatal("L'adresse ciblée est incorecte");
    }
}
void ajouter_donnée(int data,int add){//Permet d'ajouter en mémoire une donnée
    Memoire *Index = tete_mem;
    while((Index!=NULL) && ((Index)->adresse!=add)){// On parcourir notre liste chainée jusqu'a trouver l'adresse ou NULL
        Index = (Index)->link;
    }
    if(Index == NULL){//Si on ne trouve pas l'adresse (donc NULL) on ajoute l'élément au sommet de notre liste chainée
        insertion_Tete_mem("",0,data,add);
    }else{//Sinon on modifie justela valeur de la donnée 
        
        Index->data=data;
        if(Index->is_adresse){// Si c'est une instruction on doit free l'instruction
            free(Index->instruction);
        }
        Index->is_adresse=0;
        
    }
}
int obtenir_donnée(int adrs){//Permet d'obtenir une donnée a une adresse donnée
    int resultat = 0;
    Memoire *Index = tete_mem;
    while((Index!=NULL) && ((Index)->adresse!=adrs)){// On parcourir notre liste chainée jusqu'a trouver l'adresse ou NULL
        Index = (Index)->link;
    }if(Index==NULL){//Si l'adresse n'est pas la on exit
        fatal("L'adresse ciblée est incorecte");
    }else{
        if(Index->is_adresse){//Si c'est une instruction on donne la valeur de l'instruction en décimal
            resultat = hexa_number_decimal(Index->instruction);
        }else{//Sinon on récupère juste la donnée
            resultat=Index->data;
        }
    }
    return resultat;
}