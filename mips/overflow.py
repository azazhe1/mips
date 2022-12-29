fichier = open("jean.s", "a")
for i in range(0,(32767)):
    fichier.write("ADDI $1, $0, " + str(i)+ "\n")
fichier.close()