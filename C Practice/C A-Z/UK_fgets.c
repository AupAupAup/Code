/* scanf5.c */
#include <stdio.h>

int main(void) {
  
  
/* char ch;
   char buf[2];

   printf("Ein Zeichen bitte : ");
   fgets(buf, 2, stdin);
   sscanf(buf, "%c", &ch);
   printf("Das Zeichen : %c\n",ch);
   return 0;
*/

/* scanf6.c */

   char a;
   int b, check;

   printf("Bitte Eingabe machen (Zeichen/Zahl): ");
   check = scanf("%c %i",&a, &b);
   printf("check = %i \n",check);
   // Wenn 1 bad, Wenn 2 gut
   // Analog only mit Zahlen %d%d
   return 0;

}
