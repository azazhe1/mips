all: main.o convert_hexa.o header.o fonctions.o lecture_instructions.o
	gcc -g -Wall -Wextra -o main main.o convert_hexa.o fonctions.o header.o lecture_instructions.o -lm -LD_PRELOAD=libsandbox.so
convert_hexa.o: convert_hexa.c convert_hexa.h header.h
	gcc -g -Wall -Wextra -c convert_hexa.c -o convert_hexa.o -lm -LD_PRELOAD=libsandbox.so
fonctions.o: fonctions.c fonctions.h header.h dictionary.h
	gcc -g -Wall -Wextra -c fonctions.c -o fonctions.o -LD_PRELOAD=libsandbox.so
header.o: header.c 
	gcc -g -Wall -Wextra -c header.c -o header.o -LD_PRELOAD=libsandbox.so
lecture_instructions.o: lecture_instructions.c header.h lecture_instructions.h
	gcc -g -Wall -Wextra -c lecture_instructions.c -o lecture_instructions.o -LD_PRELOAD=libsandbox.so
main.o: main.c convert_hexa.h header.h fonctions.h lecture_instructions.h
	gcc -g -Wall -Wextra -c main.c -o main.o -LD_PRELOAD=libsandbox.so
