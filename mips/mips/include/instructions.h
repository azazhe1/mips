#include <stdio.h>
#include <stdlib.h>

void get_commande(char *mot_bit, char *commande);
void application(char *sorit_terminal,int mode);
void execution(int mode);
void final_state(FILE *fp);
void afficher_registre_memoire();

void add(char *rs,char *rd, char *rt);
void sub(char *rs,char *rt, char *rd);
void mult_(char *rs, char*rt);
void div_(char *rs, char*rt);
void mflo(char *rd);
void mfhi(char *rd);
void and_(char *rs,char *rt, char *rd);
void or_(char *rs,char *rt, char *rd);
void xor_(char *rs,char *rt, char *rd);
void slt(char *rs,char *rt, char *rd);
void sll(char *sa,char *rt, char *rd);
void srl(char *sa,char *rt, char *rd);
void rotr(char *sa,char *rt, char *rd);
void jr(char *rs,int mode);

void addi(char *rs,char *rt, char *imm);
void lui(char *rt,char *imm);
void bgtz(char *rs,char *offset,int mode);
void blez(char *rs,char *offset,int mode);
void bne(char *rs,char *rt,char *offset,int mode);
void beq(char *rs,char *rt,char *offset,int mode);
void sw(char *base, char *rt, char *offset);
void lw(char *base, char *rt, char *offset);

void j(char *adresse,int mode);
void jal(char *adresse,int mode);