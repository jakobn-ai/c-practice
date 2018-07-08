#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TESTLENGTH 30 
#define TESTRANGE 100

void count256(unsigned long *A, unsigned int *bytes, unsigned int len){
    unsigned long sorted[len];
    unsigned int frequency[256];
    unsigned int index[256];
    unsigned int i;
    for(i = 0; i < 256; i++) frequency[i] = 0;
    for(i = 0; i < len; i++) frequency[bytes[i]]++;
    index[0] = 0;
    for(i = 1; i < 256; i++) index[i] = index[i - 1] + frequency[i - 1];
    for(i = 0; i < len; i++) sorted[index[bytes[i]]++] = A[i];
    for(i = 0; i < len; i++) A[i] = sorted[i];
}

void sort(unsigned long *A, unsigned int len){
    unsigned int bytes[len];
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < len; j++) bytes[j] = ((A[j] >> (i*8)) & 255);
        count256(A, bytes, len);
    }
}

int main(){
    srand(time(0));
    unsigned long A[TESTLENGTH];
    int i;
    for(i = 0; i < TESTLENGTH; i++){
        A[i] = rand() % TESTRANGE + 1;
        printf("%ld, ", A[i]);
    }
    sort(A, TESTLENGTH);
    printf("\n");
    for(i = 0; i < TESTLENGTH; i++) printf("%ld, ", A[i]);
}