fichier = open("jean.s", "a")
for i in range(0,(427359)):
    fichier.write("ADDI $2, $2, 5025\n")
fichier.close()