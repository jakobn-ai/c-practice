#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TESTLENGTH 10000
#define TESTRANGE 100

void swap(long *A, long x, long y){
    long temp = A[x];
    A[x] = A[y];
    A[y] = temp;
}

void sink(long *A, long k, long n){
    long j;
    while((k << 1) + 1 <= n){
        j = (k << 1) + 1;
        if(j < n && A[j] > A[j + 1]) j++;
        if(A[k] < A[j]) return;
        swap(A, k, j);
        k = j;
    }
}

void sort(long *A, int len){
    for(int i = len >> 1; i >= 0; i--) sink(A, i, len);
    while(len > 0){
        swap(A, 0, len);
        len--;
        sink(A, 0, len);
    }
}

int main(){
    srand(time(0));
    long A[TESTLENGTH];
    int i;
    for(i = 0; i < TESTLENGTH; i++){
        A[i] = rand() % TESTRANGE + 1;
        printf("%ld, ", A[i]);
    }
    sort(A, TESTLENGTH - 1);
    printf("\n");
    for(i = 0; i < TESTLENGTH; i++) printf("%ld, ", A[i]);
}