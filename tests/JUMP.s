#Teste des commandes J et JAL

ADDI $1, $0, 24
BEQ $2, $1, 11
NOP
JAL 11
ADDI $2, $2, 1
J 9
ADDI $2, $2, 1
J 1  
ADDI $2, $2, 1
J 7
ADDI $2, $2, 1
J 5
ADD $2, $2, $31
NOP

# EXPECTED_ASSEMBLY
# 20010018
# 1041000b
# 00000000
# 0c00000b
# 20420001
# 08000009
# 20420001
# 08000001
# 20420001
# 08000007
# 20420001
# 08000005
# 005f1020
# 00000000

# EXPECTED_FINAL_STATE
# $01:24
# $02:24
# $31:20