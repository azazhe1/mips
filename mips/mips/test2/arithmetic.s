ADDI $5, $0, 5
ADDI $2, $0, 11
ADD $7, $5, $2
ADDI $11, $0, 7
SUB $8, $7, $2
DIV $5, $2
MFHI $9
MFLO $10
MULT $5, $2

# EXPECTED_ASSEMBLY
# 20050005
# 2002000b
# 00a23820
# 200b0007
# 00E24022
# 00a2001a
# 00004810
# 00005012
# 00a20018

# EXPECTED_FINAL_STATE
# $05:5
# $02:11
# $07:16
# $11:7
# $08:-11
# $09:0
# $10:5
# HI:0
# LO:55
