#include <stdlib.h>
#include <stdio.h>
// ----------------------------------

// ----------------------------------

int main (void) {

int a = -129,*pI = &a; 
printf("&a=%p\na=%d\n&pI=%p\npI=%p\n*pi=%d\n",&a,a,&pI,pI,*pI); //adresse,value,adresse,stored adress,(dereferenced) value of storedadress
char *pC;

// wir wollen die stored adresse von pointer pI in pointer pC uebergeben
// -> Typecast

pC = (char*)pI;

printf("\n\npI=%p\npC=%p\n\n*pI=%d\n*pC=%d\n",pI,pC,*pI,*pC);
//sizeof signed char is 1byte = 8 bits everything will be the same value to signed int between [-128,127] rest = trash value
}

// jesus ist das unuebersichtlich