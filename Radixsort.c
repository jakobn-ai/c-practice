#include <stdio.h> //STDOUT output
#include <stdlib.h> //Random
#include <time.h> //Seed Random

#define TESTLENGTH 30 //How big is the array to be sorted
#define TESTRANGE 100 //Numbers from 1 - TESTRANGE will be in the test array

void count256(unsigned long *A, unsigned int *bytes, unsigned long *sorted, unsigned int len){ //Counting sort with 256 discrete values. 
    unsigned int frequency[256]; //Array with the frequencies of the 256 values
    unsigned int index[256]; //Will be derived from frequency, the respective indices
    unsigned int i;
    for(i = 0; i < 256; i++) frequency[i] = 0; //Clear frequencies
    for(i = 0; i < len; i++) frequency[bytes[i]]++; //Counting phase
    index[0] = 0;
    for(i = 1; i < 256; i++) index[i] = index[i - 1] + frequency[i - 1]; //Indexing phase
    for(i = 0; i < len; i++) sorted[index[bytes[i]]++] = A[i]; //Filling phase
}

void sort(unsigned long *A, unsigned long *sorted, unsigned int len){ //Radix sort. Takes the array to be sorted, the array to contain the sorted version, and the length of these arrays.
    unsigned int bytes[len]; //The n-th byte of the numbers to be sorted is copied into here
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < len; j++) bytes[j] = ((A[j] >> (i*8)) & 255); //Mask the bytes out
        count256(A, bytes, sorted, len);
        A = sorted; //Overwrite. Counting is stable!
    }
}

int main(){
    srand(time(0)); //seed
    unsigned long A[TESTLENGTH]; //Test array
    unsigned long sorted[TESTLENGTH];
    int i;
    for(i = 0; i < TESTLENGTH; i++){ //Build and print test array
        A[i] = rand() % TESTRANGE + 1;
        printf("%ld, ", A[i]);
    }
    sort(A, sorted, TESTLENGTH);
    printf("\n");
    for(i = 0; i < TESTLENGTH; i++) printf("%ld, ", sorted[i]); //Print sorted array
}
