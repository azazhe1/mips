#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/header.h"
#include "../include/convert_hexa.h"
#include "../include/instructions.h"
#include "../include/memoire.h"

/*Code pour le rendu 4
On a besoin du fichier instructions.h pour les rendus 2-3*/


void get_commande(char *mot_bit, char *commande){//Va regarder l'opcode de notre instrution (sur 32bit)et le comparer avec les opcodes présents dans dico.txt et nous donner la commande 
    char *opcode = (char *)malloc(sizeof(char)*7);
    FILE *fp = fopen("dico.txt", "r");
    char *ligne = (char *)malloc(sizeof(char)*80);
    int exit = 0;
    char *current_op = (char *)malloc(sizeof(char)*7);
    int indice_ligne = 0;
    char char_ligne;
    char type = 'I';
    for(int i =0;i<6;i++){//On récupère l'opcode de notre instruction
        opcode[i] = mot_bit[i];
    }
    opcode[6] = '\0';
    if(!strcmp(opcode,"000000")){//Si c'est un type R on doit prendre les dernier bits et pas les premiers comme opcode
        for(int i =26;i<32;i++){
            type ='R';
            opcode[i- 26] = mot_bit[i];
        }
        opcode[6] = '\0';
    }

    if(fp == NULL){
        perror("Probleme ouverture fichier ");
    }

    while(exit == 0){//On parcour notre fichier jusqu'à trouver notre opcode correspondant
        fgets(ligne,80,fp);
        char_ligne = ligne[indice_ligne];
        while(char_ligne != ':'){
            indice_ligne++;
            char_ligne = ligne[indice_ligne];
        }
        indice_ligne++;
        if((ligne[indice_ligne] == type) ||(ligne[indice_ligne] == 'J')){
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
        }
        indice_ligne=0;
    }
    while(ligne[indice_ligne] != ':'){//On met notre commande dans notre variable
        commande[indice_ligne] = ligne[indice_ligne];
        indice_ligne++;
    }
    commande[indice_ligne] = '\0';
    if(!strcmp(commande,"SRL") || !strcmp(commande,"ROTR")){// ROTR et SRL on le même opcode donc on doit regarder le 11 ème bit 
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

void addi(char *rs,char *rt, char *imm){//Effectue la commande ADDI Comme toute les autre fonctions elle prend en paramètre nos registres en binaire
    int rs_d;
    int rt_d;
    int imm_d;
    int signe = 0;
    int resultat;
    if(imm[0] == '1'){
        signe = 1;
    }
    rs_d = (int)bit_to_decimal(rs,0,0);//passe du binaire en décimal fait ça pour toute les autres fonctions
    rt_d = (int)bit_to_decimal(rt,0,0);
    imm_d = (int)bit_to_decimal(imm,signe,0);
    if(rt_d ==0){//On vérifie qu'on moddifie pas le registre 0
        printf("->ADDI $%d, $%d, %d\n", rt_d,rs_d,imm_d);
        fatal("Ne modiffiez pas le registre 0");
    }
    else{
        resultat = get_value_registre(rs_d) + imm_d; 
        put_value_registre(rt_d,resultat);//Met la valeur dans le registre rd_d
    }
}
void add(char *rs,char *rt, char *rd){//Effectue la commande ADD
    int rs_d;
    int rt_d;
    int rd_d;
    int resultat;
    rs_d = (int)bit_to_decimal(rs,0,0);//passe du binaire en décimal
    rt_d = (int)bit_to_decimal(rt,0,0);
    rd_d = (int)bit_to_decimal(rd,0,0);
    if(rd_d ==0){//On vérifie qu'on moddifie pas le registre 0
        printf("->ADD $%d, $%d, $%d\n", rd_d,rs_d,rt_d);
        fatal("Ne modiffiez pas le registre 0");
    }else{
        resultat = get_value_registre(rs_d) + get_value_registre(rt_d); 
        put_value_registre(rd_d,resultat);//Met la valeur dans le registre rd_d
    }
}
void sub(char *rs,char *rt, char *rd){//Effectue la commande SUB
    int rs_d;
    int rt_d;
    int rd_d;
    int resultat;
    rs_d = (int)bit_to_decimal(rs,0,0);//passe du binaire en décimal
    rt_d = (int)bit_to_decimal(rt,0,0);
    rd_d = (int)bit_to_decimal(rd,0,0);
    if(rd_d ==0){//On vérifie qu'on moddifie pas le registre 0
        printf("->SUB $%d, $%d, $%d\n", rd_d,rs_d,rt_d);
        fatal("Ne modiffiez pas le registre 0");
    }else{
        resultat = get_value_registre(rs_d) - get_value_registre(rt_d); 
        put_value_registre(rd_d,resultat);//Met la valeur dans le registre rd_d
    }
}
void mult_(char *rs, char*rt){////Effectue la commande MULT et stoque les résultat dans LO et HI
    int rs_d;
    int rt_d;
    long long resultat =0;
    long long min = -9223372036854775807;//Valeur max sur 64bits
    long long max = 9223372036854775807;//valeur min sur 64bits
    int hi=0;
    int lo=0;

    rs_d = (int)bit_to_decimal(rs,0,0);//passe du binaire en décimal
    rt_d = (int)bit_to_decimal(rt,0,0);

    resultat = (long long)get_value_registre(rs_d) * (long long)get_value_registre(rt_d);
    if((resultat>max) || (resultat<min)){//Teste si on a pas atteint la valeur max/min
        printf("->MULT $%d, $%d\n",rs_d,rt_d);
        fatal("Resultat de la multiplication trop grand");
        fatal("Débordement de tampon");
    }else{
        lo = (int)resultat &0xffffffff;//Permet d'obtenir les 32 premiers bits de résultat
        hi = resultat>>32;////Permet d'obtenir les 32 derniers bits de résultat
        put_value_registre(32,lo);//Met la valeur dans le registre L0
        put_value_registre(33,(int)hi);//Met la valeur dans le registre HI
            
    }
}
void div_(char *rs, char*rt){//Effectue la commande DIV et stoque le résultat dans LO et le reste dans HI
    int rs_d;
    int rt_d;
    int resultat;
    rs_d = (int)bit_to_decimal(rs,0,0);//passe du binaire en décimal
    rt_d = (int)bit_to_decimal(rt,0,0);
    if(get_value_registre(rt_d) == 0){//On vérifie qu'on ne divise pas par 0
        printf("->DIV $%d, $%d\n",rs_d,rt_d);
        fatal("Division par 0");
    }else{
        resultat = (int)get_value_registre(rs_d) / (int)get_value_registre(rt_d);//Fait la division 
        put_value_registre(32,resultat);//Met le résultat dans L0
        resultat = (int)get_value_registre(rs_d) % (int)get_value_registre(rt_d);//Calcul du reste 
        put_value_registre(33,resultat);//Met le résultat dans HI
    }
    
    
}
void mflo(char *rd){//Effectue la commande MFLO
    int rd_d;
    rd_d = (int)bit_to_decimal(rd,0,0);//passe du binaire en décimal
    if(rd_d ==0){
        printf("->MFLO $%d\n", rd_d);
        fatal("Ne modiffiez pas le registre 0");//On vérifie qu'on moddifie pas le registre 0
    }
    put_value_registre(rd_d,get_value_registre(32));//Met la valeur dans le registre rd_d  
}
void mfhi(char *rd){//Effectue la commande MFHI
    int rd_d;
    rd_d = (int)bit_to_decimal(rd,0,0);//passe du binaire en décimal
    if(rd_d ==0){//On vérifie qu'on moddifie pas le registre 0
        printf("->MFHI $%d\n", rd_d);
        fatal("Ne modiffiez pas le registre 0");
    }
    put_value_registre(rd_d,get_value_registre(33));//Met la valeur dans le registre rd_d
}
void and_(char *rs,char *rt, char *rd){//Effectue la commande AND
    int rs_d;
    int rt_d;
    int rd_d;
    int resultat;
    rs_d = (int)bit_to_decimal(rs,0,0);//passe du binaire en décimal
    rt_d = (int)bit_to_decimal(rt,0,0);
    rd_d = (int)bit_to_decimal(rd,0,0);
    if(rd_d ==0){//On vérifie qu'on moddifie pas le registre 0
        printf("->AND $%d, $%d, $%d\n", rd_d,rs_d,rt_d);
        fatal("Ne modiffiez pas le registre 0");
    }else{
        resultat = get_value_registre(rs_d) & get_value_registre(rt_d);//AND bit a bit
        put_value_registre(rd_d,resultat);//Met la valeur dans le registre rd_d
        
    }
}
void or_(char *rs,char *rt, char *rd){//Effectue la commande OR
    int rs_d;
    int rt_d;
    int rd_d;
    int resultat;
    rs_d = (int)bit_to_decimal(rs,0,0);//passe du binaire en décimal
    rt_d = (int)bit_to_decimal(rt,0,0);
    rd_d = (int)bit_to_decimal(rd,0,0);
    if(rd_d ==0){//On vérifie qu'on moddifie pas le registre 0
        printf("->OR $%d, $%d, $%d\n", rd_d,rs_d,rt_d);
        fatal("Ne modiffiez pas le registre 0");
    }else{
        resultat = get_value_registre(rs_d) | get_value_registre(rt_d);// Ou bit a bit
        put_value_registre(rd_d,resultat);//Met la valeur dans le registre rd_d
        
    }
}
void xor_(char *rs,char *rt, char *rd){//Effectue la commande XOR
    int rs_d;
    int rt_d;
    int rd_d;
    int resultat;

    rs_d = (int)bit_to_decimal(rs,0,0);//passe du binaire en décimal
    rt_d = (int)bit_to_decimal(rt,0,0);
    rd_d = (int)bit_to_decimal(rd,0,0);
    if(rd_d ==0){//On vérifie qu'on moddifie pas le registre 0
        printf("->XOR $%d, $%d, $%d\n", rd_d,rs_d,rt_d);
        fatal("Ne modiffiez pas le registre 0");
    }else{
        resultat = get_value_registre(rs_d) ^ get_value_registre(rt_d);//XOR bit a bit
        put_value_registre(rd_d,resultat);//Met la valeur dans le registre rd_d
        
    }
}
void slt(char *rs,char *rt, char *rd){//Effectue la commande SLT
    int rs_d;
    int rt_d;
    int rd_d;

    rs_d = (int)bit_to_decimal(rs,0,0);//passe du binaire en décimal
    rt_d = (int)bit_to_decimal(rt,0,0);
    rd_d = (int)bit_to_decimal(rd,0,0);
    if(rd_d ==0){//On vérifie qu'on moddifie pas le registre 0
        printf("->SLT $%d, $%d, $%d\n", rd_d,rs_d,rt_d);
        fatal("Ne modiffiez pas le registre 0");
    }else{
        if(get_value_registre(rs_d)<get_value_registre(rt_d)){//Teste si la valeur dans le registre[rs_d] est plus petite que la valeur dans le registre[rt_d]
            put_value_registre(rd_d,1);//Met 1 dans le registre rd_d
        }else{
            put_value_registre(rd_d,0);//Met 0 dans le registre rd_d
        }
        
    }
}
void sll(char *sa,char *rt, char *rd){//Effectue la commande SLL
    int rt_d;
    int rd_d;
    int sa_d;
    int resultat;
    sa_d = (int)bit_to_decimal(sa,0,0);//passe du binaire en décimal
    rt_d = (int)bit_to_decimal(rt,0,0);
    rd_d = (int)bit_to_decimal(rd,0,0);
    if(rd_d ==0){//On vérifie qu'on moddifie pas le registre 0
        printf("->SLL $%d, $%d, %d\n", rd_d,rt_d,sa_d);
        fatal("Ne modiffiez pas le registre 0");
    }else{
        
        resultat = get_value_registre(rt_d)<<sa_d;//left shift opération
        put_value_registre(rd_d,resultat);//Met la valeur dans le registre rd_d
    }
}
void srl(char *sa,char *rt, char *rd){//Efectue la commande SRL
    int rt_d;
    int rd_d;
    int sa_d;
    int resultat;
    sa_d = (int)bit_to_decimal(sa,0,0);//passe du binaire en décimal
    rt_d = (int)bit_to_decimal(rt,0,0);
    rd_d = (int)bit_to_decimal(rd,0,0);
    if(rd_d ==0){//On vérifie qu'on moddifie pas le registre 0
        printf("->SLL $%d, $%d, %d\n", rd_d,rt_d,sa_d);
        fatal("Ne modiffiez pas le registre 0");
    }else{
        
        resultat = (int)get_value_registre(rt_d)>>(int)sa_d;//right shift opération
        put_value_registre(rd_d,resultat);//Met la valeur dans le registre rd_d
    }
}
void rotr(char *sa,char *rt, char *rd){//Effectue la commande ROTR
    int rt_d;
    int rd_d;
    int sa_d;
    int resultat;

    sa_d = (int)bit_to_decimal(sa,0,0);//passe du binaire en décimal
    rt_d = (int)bit_to_decimal(rt,0,0);
    rd_d = (int)bit_to_decimal(rd,0,0);
    if(rd_d ==0){//On vérifie qu'on moddifie pas le registre 0
        printf("->ROTR $%d, $%d, %d\n", rd_d,rt_d,sa_d);
        fatal("Ne modiffiez pas le registre 0");
    }else{
        resultat = ((get_value_registre(rt_d)>>sa_d)|(get_value_registre(rt_d)<<(32-sa_d)));//right shift de sa_d de la valeut puis Ou bit à bit de la valeur left sift de 32-sa_d de la valeur
        put_value_registre(rd_d,resultat);//Met la valeur dans le registre rd_d
    }

}
void lui(char *rt,char *imm){//Effectue la commande LUI
    int rt_d;
    int imm_d;
    int signe =0;
    int resultat;
    rt_d = (int)bit_to_decimal(rt,0,0);//passe du binaire en décimal
    if(imm[0] == '1'){
        signe = 1;
    }
    imm_d = (int)bit_to_decimal(imm,signe,0);
    if(rt_d ==0){//On vérifie qu'on moddifie pas le registre 0
        printf("->LUI $%d, $%d\n", rt_d,imm_d);
        fatal("Ne modiffiez pas le registre 0");
    }else{
        
        resultat = (int)imm_d<<(int)16;//left shift de 16 pour avoir une valeur plus grande dans notre registre 
        put_value_registre(rt_d,resultat);//Met la valeur dans le registre rd_d
    }
    
}
void bgtz(char *rs,char *offset,int mode){//Effectue la commande BGTZ
    int rs_d;
    int offset_d;
    int signe =0;
    int add_tamp =0;
    rs_d = (int)bit_to_decimal(rs,0,0);//passe du binaire en décimal
    if(offset[0] == '1'){
        signe =1;
    }
    offset_d = (int)bit_to_decimal(offset,signe,0);
    add_tamp = ((int)offset_d<<2) + (get_pc());//On applique un <<2 a notre offset pour qu'il soit multiple de 4 et on l'ajoute a pc
    if((add_tamp<0)||(add_tamp%4!=0)){//teste si notre adresse est bien un multiple de 4 et si l'adresse n'est pas négatif
        printf("->BGTZ $%d, %d\n",rs_d,offset_d);
        fatal("L'adresse ciblée est incorecte");
    }else{
        if(get_value_registre(rs_d)>0){//Si registre de rs_d est >0 on branch
            if(last_instrction()){//Si c'est la dernière éxécution a effectuer on ne fait que le branch
                modifier_pc(add_tamp);//modifie pc
            }else{//Sinon on exécute la prochaine instruction puis on branch
                execution(mode);//On exécute la prochaine instruction
                modifier_pc(add_tamp);//On branch
            }
            
        }
    }
    
}
void blez(char *rs,char *offset,int mode){//Effectue la commande BLEZ
    int rs_d;
    int offset_d;
    int signe =0;
    int add_tamp =0;
    rs_d = (int)bit_to_decimal(rs,0,0);//passe du binaire en décimal
    if(offset[0] == '1'){
        signe =1;
    }
    offset_d = (int)bit_to_decimal(offset,signe,0);
    add_tamp = ((int)offset_d<<2) + (get_pc());//On applique un <<2 a notre offset pour qu'il soit multiple de 4 et on l'ajoute a pc
    if((add_tamp<0)||(add_tamp%4!=0)){//teste si notre adresse est bien un multiple de 4 et si l'adresse n'est pas négatif
        printf("->BLEZ $%d, %d\n",rs_d,offset_d);
        fatal("L'adresse ciblée est incorecte");
    }else{
        if(get_value_registre(rs_d)<=0){//teste si la valeur dans le registre est <=0
            if(last_instrction()){//Si c'est la dernière isntruction
                modifier_pc(add_tamp);//modifie pc
            }else{//Sinon on exécute la prochaine instruction puis on branch
                execution(mode);
                modifier_pc(add_tamp);
            } 
        }
    }
    
}
void bne(char *rs,char *rt,char *offset,int mode){//Effectue la commande BNE
    int rs_d;
    int rt_d;
    int  offset_d;
    int signe = 0;
    int add_tamp =0;
    rs_d = (int)bit_to_decimal(rs,0,0);//passe du binaire en décimal
    rt_d = (int)bit_to_decimal(rt,0,0);
    if(offset[0] == '1'){
        signe =1;
    }
    offset_d = (int)bit_to_decimal(offset,signe,0);
    add_tamp = ((int)offset_d<<2) + (get_pc());//On applique un <<2 a notre offset pour qu'il soit multiple de 4 et on l'ajoute a pc
    if((add_tamp<0)||(add_tamp%4!=0)){//teste si notre adresse est bien un multiple de 4 et si l'adresse n'est pas négatif
        printf("->BNE $%d, $%d, %d\n",rs_d,rt_d,offset_d);
        fatal("L'adresse ciblée est incorecte");
    }else{
        if(get_value_registre(rs_d)!=get_value_registre(rt_d)){//Testt la valeur de nos 2 registres sont différent
            if(last_instrction()){//Si c'est la dernière isntruction
                modifier_pc(add_tamp);//modifie pc
            }else{//Sinon on exécute la prochaine instruction puis on branch
                execution(mode);
                modifier_pc(add_tamp);
            }   
        }
    }
    
}
void beq(char *rs,char *rt,char *offset,int mode){//Effectue la commande BEQ
    int rs_d;
    int rt_d;
    int  offset_d;
    int signe = 0;
    int add_tamp =0;
    rs_d = (int)bit_to_decimal(rs,0,0);//passe du binaire en décimal
    rt_d = (int)bit_to_decimal(rt,0,0);
    if(offset[0] == '1'){
        signe =1;
    }
    offset_d = (int)bit_to_decimal(offset,signe,0);
    add_tamp = ((int)offset_d<<2) + (get_pc());//On applique un <<2 a notre offset pour qu'il soit multiple de 4 et on l'ajoute a pc
    if((add_tamp<0)||(add_tamp%4!=0)){//teste si notre adresse est bien un multiple de 4 et si l'adresse n'est pas négatif
        printf("->BEQ $%d, $%d, %d\n",rs_d,rt_d,offset_d);
        fatal("L'adresse ciblée est incorecte");
    }else{
        if(get_value_registre(rs_d)==get_value_registre(rt_d)){//Teste si les valeurs dans nos 2 registres sont égales
            if(last_instrction()){//Si c'est la dernière isntruction
                modifier_pc(add_tamp);//modifie pc
            }else{//Sinon on exécute la prochaine instruction puis on branch
                execution(mode);
                modifier_pc(add_tamp);
            }
        }
    }
    
}
void j(char *adresse,int mode){//Effectue la commande J
    long ad_tamp;
    char *pc = (char *)malloc(sizeof(char)*33);
    char *ad_tamp_bit = (char *)malloc(sizeof(char)*33);
    
    ad_tamp = bit_to_decimal(adresse, 0,0);//passe du binaire en décimal
    ad_tamp = ad_tamp<<2;//On left shift de 2 notre adresse pour qu'elle passe de 26bit a 28
    bit(get_pc(),32,pc);//On convertit PC en binaire pour pouvoir récupérer ses 4 dernier bit et les rajouter a notre adresse
    bit(ad_tamp,32,ad_tamp_bit);//On convertit notre adresse sur 32 bit
    for(int i=0;i<4;i++){// On met les 4 derniers bits de PC dans l'adresse
        ad_tamp_bit[i] = pc[i];
    }
    ad_tamp = bit_to_decimal(ad_tamp_bit,0,0);//passe du binaire en décimal
    if(last_instrction()){//Si c'est la dernière isntruction
        modifier_pc(ad_tamp);//modifie pc
    }else{//Sinon on exécute la prochaine instruction puis on jump
        execution(mode);
        modifier_pc(ad_tamp);
    }
    

    free(pc);
    free(ad_tamp_bit);
    
}
void jal(char *adresse,int mode){
    if(last_instrction()==0){//Effectue la commande JAL
        put_value_registre(31,get_pc()+4);//Dans la doc on fait PC +8 mais je ne comprend pas,
        //PC pointe vers la prochiane instruction donc la prochaine instruction après PC corrspond a PC+4
        //On met dans R[31] l'adresse de PC+4
    }
    j(adresse,mode);//On appel j pour jump a notre adresse
}
void jr(char *rs,int mode){//Effectue la commande JR
    int rs_d;
    rs_d = (int)bit_to_decimal(rs,0,0);//passe du binaire en décimal
    if(get_value_registre(rs_d)<0||(get_value_registre(rs_d)%4 !=0)){//teste si notre adresse est bien un multiple de 4 et si l'adresse n'est pas négatif
        printf("->JR $%d\n",rs_d);
        fatal("L'adresse ciblée est incorecte");
    }else{
        if(last_instrction()){//Si c'est la dernière isntruction
            modifier_pc(get_value_registre(rs_d));//modifie pc avec la valeur présente dans notre registre rs_d
        }else{//Sinon on exécute la prochaine instruction puis on jump
            execution(mode);
            modifier_pc(get_value_registre(rs_d));
        }
    }

}
void sw(char *base, char *rt, char *offset){//Effectue la commande SW
    int offset_d;
    int base_d;
    int rt_d;
    int signe =0;
    int adresse;
    rt_d = (int)bit_to_decimal(rt,0,0);//passe du binaire en décimal
    base_d= (int)bit_to_decimal(base,0,0);
    if(offset[0] == '1'){
        signe =1;
    }
    offset_d = (int)bit_to_decimal(offset,signe,0);
    
    adresse = get_value_registre(base_d) + offset_d;//Notre adresse ciblée vaudra la valeur dans le registre bas_d + notre offset
    
    if((adresse%4!=0)||(adresse<0)){//teste si notre adresse est bien un multiple de 4 et si l'adresse n'est pas négatif
        fatal("L'adresse ciblée est incorecte");
    }else{
        ajouter_donnée(get_value_registre(rt_d),adresse);//On ajjoute en mémoire notre donnée
        
    }

}
void lw(char *base, char *rt, char *offset){//Effectue la commande LW
    int offset_d;
    int base_d;
    int rt_d;
    int signe =0;
    int adresse;
    rt_d = (int)bit_to_decimal(rt,0,0);//passe du binaire en décimal
    base_d= (int)bit_to_decimal(base,0,0);
    if(offset[0] == '1'){
        signe =1;
    }
    offset_d = (int)bit_to_decimal(offset,signe,0);
    if(rt_d==0){//On vérifie qu'on moddifie pas le registre 0
        printf("->LW $%d, $%d(%d)\n",rt_d,offset_d,base_d);
        fatal("Ne modiffiez pas le registre 0");
    }else{
        adresse = get_value_registre(base_d) + offset_d;//Notre adresse ciblée vaudra la valeur dans le registre bas_d + notre offset
        if((adresse%4!=0)||(adresse<0)){//teste si notre adresse est bien un multiple de 4 et si l'adresse n'est pas négatif
            fatal("L'adresse ciblée est incorecte");
        }else{
            put_value_registre(rt_d,obtenir_donnée(adresse));//Met dans notre registre rt_d la donnée présente a l'adresse
        }
    }
}

void final_state(FILE *fp){//Pour le mode 2 on doit mettre l'état final des registre dans notre fichier de sortie
    for(int i=1;i<32;i++){//Parcours nos 32 registres et met la valeur de nos registres s'ils sont différent de 0 dans notre fichier
        if(get_value_registre(i)!=0){
            if(i<10){
                fprintf(fp,"$0%d:%d\n",i,get_value_registre(i));
            }else{
                fprintf(fp,"$%d:%d\n",i,get_value_registre(i));
            }
        }
    }
    if(get_value_registre(32)!=0){//Met la valeur présente dans LO dans notre fichier si elle est différente de 0
        fprintf(fp,"LO:%d\n",get_value_registre(32));
    }
    if(get_value_registre(33)!=0){//Met la valeur présente dans HI dans notre fichier si elle est différente de 0
        fprintf(fp,"HI:%d\n",get_value_registre(33));
    }
}
void afficher_registre_memoire(){//Pour le mode O et 1 on doit afficher dans le terminal l'état des registres
    for(int i=1;i<32;i++){
        if(get_value_registre(i)!=0){
            if(i<10){
                printf("$0%d:%d\n",i,get_value_registre(i));
            }else{
                printf("$%d:%d\n",i,get_value_registre(i));
            }
        }
    }
    if(get_value_registre(32)!=0){
        printf("LO:%d\n",get_value_registre(32));
    }
    if(get_value_registre(33)!=0){
        printf("HI:%d\n",get_value_registre(33));
    }
    liste_Affiche_mem();
}
void application(char *sorit_terminal,int mode){//Fonction principal de l'exécution des commandes
    
    FILE *fp;
    char *cont = (char *)malloc(sizeof(char)*100);
    if(mode==2){//On teste si on doit ouvrir notre fichier
        fp=fopen(sorit_terminal,"w");
        if(fp==NULL){
            fatal("Probleme ouverture fichier ");
        }
    }
    //Nos instructions on était empilé les unes à la suite des autres
    while(last_instrction() == 0){//On parcourir notre mémoire jusqu'a ce qu'on soit à niotre dernière instruction
        execution(mode);//On exécute l'instruction en cour
        if(mode==1){
            afficher_registre_memoire();//on affcihe la mémoire et l'état des registre
            printf("Appuyez sur une touche pour continuer et entrée pour continuer\n");
            scanf("%[^\n]%*c",cont);// On attend qu'une touche soit pressée suivi de \n
        }
    }
    if(mode==0){//Si on est en mode 0 on affiche l'état des registre et pc doit toujours valoir 0 comme notre instruction se trouvera toujours à l'adresse 0
        afficher_registre_memoire();
        modifier_pc(0);
    }

    if(mode==2){//On oubklie pas de fermer notre fichier
        final_state(fp);
        fclose(fp);

    }
    free(cont);
   
}


void execution(int mode){//Fonction qui permet d'appele"r la bonne commande
    char *commande = (char *)malloc(sizeof(char)*5);
    char *rs = (char *)malloc(sizeof(char)*6);
    //int rs;
    char *rt = (char *)malloc(sizeof(char)*6);
    //int rt_d;
    char *rd = (char *)malloc(sizeof(char)*6);
    //int rd_d;
    char *sa = (char *)malloc(sizeof(char)*6);
    //int sa_d;
    char *imm = (char *)malloc(sizeof(char)*17);
    //int imm_d;
    char *adresse = (char *)malloc(sizeof(char)*27);
    //int adresse_d;
    char *instruction_hexa = (char *)malloc(sizeof(char)*9);
    char *mot_bit = (char*)malloc(sizeof(char)*33);

    get_instruction(instruction_hexa);//On va dans notre mémoire(liste chainée) prendre notre instruction(qui est en hexa) corespondante a l'adresse de pc 
    convert_hexa_bit(instruction_hexa,mot_bit);//On convertit notre instruction en binaire pour pouvoir la décoder
    if((mode==0)||(mode==1)){//Si on est en mode 0 ou 1 on doit afficher l'instruction
        printf("%s\n",instruction_hexa);
    }
    if(!strcmp(mot_bit,"00000000000000000000000000000000")){//Si c'est nop c'est spéciale
        strcpy(commande,"NOP");
    }else{
        get_commande(mot_bit,commande);// On va chercher avec l'opcode la commande a faire 
    }
    if(!strcmp(commande,"ADDI")){
        for(int i =6; i<11;i++){//Pour toutes les fonctions ça marche comme ça, on va prendre les bon bit de notre unstrction sur 32, pour les mettre dans rs, sa, rd rt...  
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
        addi(rs,rt,imm);
    }else if(!strcmp(commande,"ADD")){
        for(int i =6; i<11;i++){
            rs[i-6] = mot_bit[i];
        }
        rs[5]='\0';
        for(int i =11; i<16;i++){
            rt[i-11] = mot_bit[i];
        }
        rt[5]='\0';
        for(int i =16; i<21;i++){
            rd[i-16] = mot_bit[i];
        }
        rd[5]='\0';
        add(rs,rt,rd);
    }else if(!strcmp(commande,"SUB")){
        for(int i =6; i<11;i++){
            rs[i-6] = mot_bit[i];
        }
        rs[5]='\0';
        for(int i =11; i<16;i++){
            rt[i-11] = mot_bit[i];
        }
        rt[5]='\0';
        for(int i =16; i<21;i++){
            rd[i-16] = mot_bit[i];
        }
        rd[5]='\0';
        sub(rs,rt,rd);
    }else if(!strcmp(commande,"MULT")){
        for(int i =6; i<11;i++){
            rs[i-6] = mot_bit[i];
        }
        rs[5]='\0';
        for(int i =11; i<16;i++){
            rt[i-11] = mot_bit[i];
        }
        rt[5]='\0';
        mult_(rs,rt);
    }else if(!strcmp(commande,"DIV")){
        for(int i =6; i<11;i++){
            rs[i-6] = mot_bit[i];
        }
        rs[5]='\0';
        for(int i =11; i<16;i++){
            rt[i-11] = mot_bit[i];
        }
        rt[5]='\0';
        div_(rs,rt);
    }else if(!strcmp(commande,"MFLO")){
        for(int i =16; i<21;i++){
            rd[i-16] = mot_bit[i];
        }
        rd[5]='\0';
        mflo(rd);
    }else if(!strcmp(commande,"MFHI")){
        for(int i =16; i<21;i++){
            rd[i-16] = mot_bit[i];
    }
        rd[5]='\0';
        mfhi(rd);
    }else if(!strcmp(commande,"AND")){
        for(int i =6; i<11;i++){
            rs[i-6] = mot_bit[i];
        }
        rs[5]='\0';
        for(int i =11; i<16;i++){
            rt[i-11] = mot_bit[i];
        }
        rt[5]='\0';
        for(int i =16; i<21;i++){
            rd[i-16] = mot_bit[i];
        }
        rd[5]='\0';
        and_(rs,rt,rd);
    }else if(!strcmp(commande,"OR")){
        for(int i =6; i<11;i++){
            rs[i-6] = mot_bit[i];
        }
        rs[5]='\0';
        for(int i =11; i<16;i++){
            rt[i-11] = mot_bit[i];
        }
        rt[5]='\0';
        for(int i =16; i<21;i++){
            rd[i-16] = mot_bit[i];
        }
        rd[5]='\0';
        or_(rs,rt,rd);
    }else if(!strcmp(commande,"XOR")){
        for(int i =6; i<11;i++){
            rs[i-6] = mot_bit[i];
        }
        rs[5]='\0';
        for(int i =11; i<16;i++){
            rt[i-11] = mot_bit[i];
        }
        rt[5]='\0';
        for(int i =16; i<21;i++){
            rd[i-16] = mot_bit[i];
        }
        rd[5]='\0';
        xor_(rs,rt,rd);
    }else if(!strcmp(commande,"SLT")){
        for(int i =6; i<11;i++){
            rs[i-6] = mot_bit[i];
        }
        rs[5]='\0';
        for(int i =11; i<16;i++){
            rt[i-11] = mot_bit[i];
        }
        rt[5]='\0';
        for(int i =16; i<21;i++){
            rd[i-16] = mot_bit[i];
        }
        rd[5]='\0';
        slt(rs,rt,rd);
    }else if(!strcmp(commande,"SLL")){
        for(int i =11; i<16;i++){
            rt[i-11] = mot_bit[i];
        }
        rt[5]='\0';
        for(int i =16; i<21;i++){
            rd[i-16] = mot_bit[i];
        }
        rd[5]='\0';
        for(int i =21; i<26;i++){
            sa[i-21] = mot_bit[i];
        }
        sa[5]='\0';
        sll(sa,rt,rd);
    }else if(!strcmp(commande,"SRL")){
        for(int i =11; i<16;i++){
            rt[i-11] = mot_bit[i];
        }
        rt[5]='\0';
        for(int i =16; i<21;i++){
            rd[i-16] = mot_bit[i];
        }
        rd[5]='\0';
        for(int i =21; i<26;i++){
            sa[i-21] = mot_bit[i];
        }
        sa[5]='\0';
        srl(sa,rt,rd);
    }else if(!strcmp(commande,"ROTR")){
        for(int i =11; i<16;i++){
            rt[i-11] = mot_bit[i];
        }
        rt[5]='\0';
        for(int i =16; i<21;i++){
            rd[i-16] = mot_bit[i];
        }
        rd[5]='\0';
        for(int i =21; i<26;i++){
            sa[i-21] = mot_bit[i];
        }
        sa[5]='\0';
        rotr(sa,rt,rd);
    }else if(!strcmp(commande,"BGTZ")){
        for(int i =6; i<11;i++){
            rs[i-6] = mot_bit[i];
        }
        rs[5]='\0';
        for(int i =16; i<32; i++){
            imm[i-16] = mot_bit[i];
        }
        imm[16]='\0';
        if(mode==0){
            printf("Un saut n'a pas de sens en mode interactif");
        }else{
            bgtz(rs,imm,mode);
        }
        
    }else if(!strcmp(commande,"BLEZ")){
        for(int i =6; i<11;i++){
            rs[i-6] = mot_bit[i];
        }
        rs[5]='\0';
        for(int i =16; i<32; i++){
            imm[i-16] = mot_bit[i];
        }
        imm[16]='\0';
        if(mode==0){
            printf("Un saut n'a pas de sens en mode interactif");
        }else{
            blez(rs,imm,mode);
        }
    }else if(!strcmp(commande,"BNE")){
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
        if(mode==0){
            printf("Un saut n'a pas de sens en mode interactif");
        }else{
            bne(rs,rt,imm,mode);
        }
    }else if(!strcmp(commande,"BEQ")){
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
        if(mode==0){
            printf("Un saut n'a pas de sens en mode interactif");
        }else{
            beq(rs,rt,imm,mode);
        }
    }else if(!strcmp(commande,"LUI")){
        for(int i =11; i<16;i++){
            rt[i-11] = mot_bit[i];
        }
        rt[5]='\0';
        for(int i =16; i<32; i++){
            imm[i-16] = mot_bit[i];
        }
        imm[16]='\0';
        lui(rt,imm);
    }else if(!strcmp(commande,"J")){
        for(int i=6;i<32;i++){
            adresse[i-6] = mot_bit[i];
        }
        adresse[26]='\0';
        if(mode==0){
            printf("Un saut n'a pas de sens en mode interactif");
        }else{
            j(adresse,mode);
        }
    }else if(!strcmp(commande,"JAL")){
        for(int i=6;i<32;i++){
            adresse[i-6] = mot_bit[i];
        }
        adresse[26]='\0';
        if(mode==0){
            printf("Un saut n'a pas de sens en mode interactif");
        }else{
            jal(adresse,mode);
        }
    }else if(!strcmp(commande,"JR")){
        for(int i =6; i<11;i++){
            rs[i-6] = mot_bit[i];
        }
        rs[5]='\0';
        if(mode==0){
            printf("Un saut n'a pas de sens en mode interactif");
        }else{
            jr(rs,mode);
        }
    }else if(!strcmp(commande,"SW")){
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
        sw(rs,rt,imm);
    }else if(!strcmp(commande,"LW")){
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
        lw(rs,rt,imm);
    }

    free(mot_bit);
    free(instruction_hexa);
    free(adresse);
    free(imm);
    free(sa);
    free(rd);
    free(rt);
    free(rs);
    free(commande);
}