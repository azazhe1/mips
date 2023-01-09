#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct entree entree;
struct entree
{
    char *nom;
    char *numero;
    entree *suivant;
};

typedef entree *annuaire;


void afficherAnnuaire(annuaire a){
    annuaire head = a;
    printf("---------------\n");
    while(head != NULL){
        printf("nom :%s num :%s\n", head->nom,head->numero);

        head = head->suivant;
        
    }
    if(head == NULL){
        printf("Fin de l'annuaire\n");
    }
    
}

int insererEntree(char* nom, char * numero, annuaire* a){
    int resultat = 0;
    annuaire head = malloc(sizeof(head));
    head->nom = malloc(sizeof(char*)*100);
    head->numero = malloc(sizeof(char*)*100);
    annuaire indexe;
    indexe = *a;
    annuaire indexe1;
    int exit = 0;
    strcpy(head->nom,nom);
    strcpy(head->numero,numero);
    if(*a == NULL){
        head->suivant = NULL;
        *a = head;
    }else{
        if(nom[0]>(*a)->nom[0]){
            head->suivant = *a;
            *a = head;
        }else{
            while(exit == 0){
                if(indexe!=NULL){

                    if(indexe->nom[0]>nom[0]){
                        indexe1 = indexe;
                        indexe = indexe->suivant;
                         
                    }
                    else{
                        exit++;
                        if(!strcmp(indexe->nom,nom)){
                            resultat = -1;
                        }
                    }
                }else{
                    exit++;
                }
            }
            if(resultat == 0){
                indexe1->suivant = head;
                head->suivant = indexe;
            }
            
        }
    }
    return resultat;
}
void supprimeEntree(char *nom,annuaire * a){
    annuaire indexe;
    indexe = *a;
    annuaire indexe1;
    int exit = 0;
    if((*a)->suivant == NULL){
        a=NULL;
        free(indexe);
    }else{
        while(exit ==0){
            if(!strcmp(indexe->nom,nom)){
                indexe1->suivant = indexe->suivant;
                free(indexe);
                exit++;
            }else{
                indexe1 = indexe;
                indexe = indexe->suivant;
            }
        }
    }
}

int main(void){
    annuaire a = NULL;
    //afficherAnnuaire(a);
    insererEntree("jean","06",&a);
    //afficherAnnuaire(a);
    insererEntree("meam","1",&a);
    //afficherAnnuaire(a);
    insererEntree("nop","3",&a);
    //afficherAnnuaire(a);
    insererEntree("akds","9",&a);
    afficherAnnuaire(a);
    supprimeEntree("jean", &a);
    afficherAnnuaire(a);
}

