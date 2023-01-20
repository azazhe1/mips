#include <stdio.h>
#include <stdlib.h>

typedef struct MEMOIRE{
    char *instruction;
    int adresse;
    int is_adresse;
    int data;
    struct MEMOIRE *link;
}Memoire;

void liste_Affiche_mem(void);
void suppression_Tete_mem(void);
void insertion_Tete_mem(char *data,int is_inst,int donnée,int adrs);
void supp_mem(void);
void set_registre(void);
int parcourir_mem(int add, Memoire **Indexe);
void get_instruction(char *instruction);
int last_instrction(void);
void put_value_registre(int indice,int value);
int get_value_registre(int indice);
int get_pc(void);
void modifier_pc(int adrs);
void ajouter_donnée(int data,int add);
int obtenir_donnée(int adrs);
void insertion_mode_interactif(char *data);
void lsite(void);