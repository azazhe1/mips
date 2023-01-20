#On suppose qu'un tableau a été stocké dans la mémoire et commence à l'adresse 1000
# le tableau est de taille 8
#On stocke les élément de notre tableau (pas le vrai code, mais on a besoin de faire ça)

#########################
ADDI $1, $0, 190        #
SW $1, 1000($0)         #
ADDI $1, $0, 27         #
SW $1, 1004($0)         #
ADDI $1, $0, -13        #
SW $1, 1008($0)         #
ADDI $1, $0, 0          #
SW $1, 1012($0)         #
ADDI $1, $0, 42         #
SW $1, 1016($0)         #
ADDI $1, $0, 666        #
SW $1, 1020($0)         #
ADDI $1, $0, 7          #
SW $1, 1024($0)         #
ADDI $1, $0, -99        #
SW $1, 1028($0)         #
#########################
#VRAI CODE
#On connait la taille , 8
ADDI $1, $0, 8 #Commme je n'ai pas de label je suis obligéde faire ça
ADDI $5, $0, 0 # On commence a compter
#On connait aussi l'adresse de départ
ADDI $2, $0, 1000 # Pour passer d'un élément a unautre on fait +4
LW $3, 0($2)
ADD $4, $4, $3
ADDI $5, $5, 1
ADDI $2, $2, 4
BNE $5, $1, -5

# EXPECTED_ASSEMBLY
# 200100be
# ac0103e8
# 2001001b
# ac0103ec
# 2001fff3
# ac0103f0
# 20010000
# ac0103f4
# 2001002a
# ac0103f8
# 2001029a
# ac0103fc
# 20010007
# ac010400
# 2001ff9d
# ac010404
# 20010008
# 20050000
# 200203e8
# 8c430000
# 00832020
# 20a50001
# 20420004
# 14a1fffb

# EXPECTED_FINAL_STATE
# $01:8
# $02:1032
# $03:-99
# $04:820
# $05:8
