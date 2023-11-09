#include <stdio.h>
#include <stdlib.h>


// int arr[] = int* arr
int sumofelements (int arr[]) {

int i, sum = 0;
int size = 5;

for (i = 0; i < size; i++){
    sum = sum + arr[i];
}

return sum;
}


int main(){

int A[5] = {1,2,3,4,5};
int total = sumofelements(&A[0]);
printf("%d",total);


}