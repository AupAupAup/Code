/* newline.c */ 
#include <stdio.h>

int main(void) {
   printf("Darstellung von Newline \\n \n");
   printf("Mögliche Ausführung von Newline\n");
   printf("Mit hexadezimaler Angabe : \\xa \xa");
   printf("Mit oktaler Wertangabe   : \\012 \012");
   printf("Mit dezimaler Angabe     : 10%c",10);
   printf("Hallo\0Ich bin nicht mehr lesbar\n");
   return 0;
}