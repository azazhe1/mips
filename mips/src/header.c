#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fatal(char *message) {
   char error_message[100];

   strcpy(error_message, "[!!] Fatal Error ");
   strncat(error_message, message, 83);
   printf("%s\n",error_message);
   exit(EXIT_FAILURE);
}