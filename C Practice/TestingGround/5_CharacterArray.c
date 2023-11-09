#include <stdio.h>
#include <stdlib.h>


int main(){


char A[22] = {"Hello Everyone"}; // NULL

printf("%s\n",A);

char B[42] = {'H','e','l','l','o','\0'}; // NULL INCLUDED

printf("%s\n",B); 

char* p = B; //  = &B[0]

p[0] = p[1] = p[2] = p[3] = p[4] = 'E'; // no dereferencing
printf("%s\n",B);

*p = 'S'; // only First

printf("%s\n",B);

*(p+1) = 'A'; // else this for later "digits"
printf("%s\n",B);

*(p+2) = 'L';
printf("%s\n",B);

B[2] = 'T';
printf("%s\n",B);

}