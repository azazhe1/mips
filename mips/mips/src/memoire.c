#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/memoire.h"
#include "../include/header.h"
#include "../include/convert_hexa.h"

int registre[35];
Memoire *tete_mem = NULL;
int address =0;
int last_instruction_add=0;

void insertion_Tete_mem(char *data,int is_inst,int donnée,int adrs){
    Memoire *nouveau = malloc(sizeof(Memoire));
    long max = 4294967292;//L'adresse maximum que l'on peut avoir
    if(address<=max){
        if(is_inst==1){
            nouveau->instruction = malloc(sizeof(char)*9);
            strcpy(nouveau->instruction, data);
            last_instruction_add+=4;
            nouveau->is_adresse =1;
            nouveau->adresse = address;
            address= address +4;
            
        }else{
            nouveau->is_adresse =0;
            nouveau->data = donnée;
            nouveau->adresse = adrs;
        }
        
        if(tete_mem == NULL){
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
void insertion_mode_interactif(char *data){
    Memoire *nouveau;
    
    if(tete_mem == NULL){
        nouveau = malloc(sizeof(Memoire));
        nouveau->instruction=malloc(sizeof(char)*9);
        nouveau->is_adresse=1;
        nouveau->adresse=0;
        strcpy(nouveau->instruction, data);
        nouveau->link = NULL;
        tete_mem=nouveau;
        last_instruction_add =4;

    }else{
        nouveau=tete_mem;
        while(nouveau->link!=NULL){
            nouveau=nouveau->link;
        }
        strcpy(nouveau->instruction, data);
    }

}
void suppression_Tete_mem(void){
    Memoire *new;
    new=tete_mem;
    tete_mem= tete_mem->link;
    if(new->is_adresse){
        free(new->instruction);
    }
    free(new);
}
void supp_mem(void){
    while(tete_mem!=NULL){
        suppression_Tete_mem();
      }
}
void liste_Affiche_mem(void){
    Memoire *new;
    new = tete_mem;
    if(new == NULL){
        printf("Liste vide!\n");
    }else{
        while(new != NULL){
            if(new->is_adresse==0){
                printf("0x%08X:%d\n",new->adresse,new->data);
            }
            new=new->link;
        }
    }
}
void lsite(void){
    Memoire *new;
    new = tete_mem;
    while(new != NULL){
        printf("%d\n", new->adresse);
        new = new->link;
    }
}
void set_registre(void){
    for(int i=0;i<34;i++){
        registre[i] = 0;
   }
}
int parcourir_mem(int add, Memoire **Indexe){
    int resultat=0;
    while((*Indexe!=NULL) && ((*Indexe)->adresse!=add)){
        *Indexe = (*Indexe)->link;
    }
    
    if(*Indexe==NULL){
        printf("adresse : %d\n",add);
        fatal("L'adresse ciblée est incorecte");
    }else if((*Indexe)->is_adresse){
        resultat =1;
    }
    
    return resultat;
}
void get_instruction(char *instruction){
    Memoire *Index = tete_mem;
    parcourir_mem(registre[34], &Index);
    if(Index->is_adresse){
        strcpy(instruction, Index->instruction);
        registre[34]+=4;
    }else{
        fatal("L'adresse ciblée est incorecte");
    }
}
int last_instrction(void){
    int end = 0;
    if(registre[34] == last_instruction_add){
        end =1;
    }
    return end;
}
int get_value_registre(int indice){
    return registre[indice];
}
void put_value_registre(int indice,int value){
    registre[indice] = value;
}
int get_pc(void){
    return registre[34];
}
void modifier_pc(int adrs){
    Memoire * Index = tete_mem;
    if(parcourir_mem(adrs,&Index)){
        registre[34] = adrs;
    }else{
        printf("adresse : %d\n",adrs);
        fatal("L'adresse ciblée est incorecte");
    }
}
void ajouter_donnée(int data,int add){
    Memoire *Index = tete_mem;
    while((Index!=NULL) && ((Index)->adresse!=add)){
        Index = (Index)->link;
    }
    if(Index == NULL){
        insertion_Tete_mem("",0,data,add);
    }else{
        
        Index->data=data;
        if(Index->is_adresse){
            free(Index->instruction);
        }
        Index->is_adresse=0;
        
    }
}
int obtenir_donnée(int adrs){
    int resultat = 0;
    Memoire *Index = tete_mem;
    while((Index!=NULL) && ((Index)->adresse!=adrs)){
        Index = (Index)->link;
    }if(Index==NULL){
        fatal("L'adresse ciblée est incorecte");
    }else{
        if(Index->is_adresse){
            resultat = hexa_number_decimal(Index->instruction);
        }else{
            resultat=Index->data;
        }
    }
    return resultat;
}