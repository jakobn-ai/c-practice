#include <stdio.h> //STDOUT output
#include <stdlib.h> //Random
#include <time.h> //Seed Random

#define TESTLENGTH 30 //How big is the array to be sorted
#define TESTRANGE 100 //Numbers from 1 - TESTRANGE will be in the test array

void swap(unsigned long *A, int x, int y){ //swaps values in array A at indices x and y
    unsigned long temp = A[x];
    A[x] = A[y];
    A[y] = temp;
}

//The heap is represented by an array where the left subheap is at index * 2 + 1 and the right subheap is at index * 2 + 2
//We are using a maximum heap
void sift(unsigned long *A, int k, int n){ //A[k] up to A[n] is a heap, except at A[k] the heap condition is possibly violated
    int sub; //Index for subheaps
    while((k << 1) + 1 <= n){ //We can stop as soon as the left subheap is the end
        sub = (k << 1) + 1; //Index of the left subheap
        if(sub < n && A[sub] < A[sub + 1]) sub++; //Right subheap must exist and right subheap is larger -> investigate right subheap
        if(A[k] > A[sub]) return; //Heap condition no longer violated
        swap(A, k, sub);
        k = sub; //may be violated at a deeper level now
    }
}

void sort(unsigned long *A, int len){ //Gets length - 1
    for(int i = len >> 1; i >= 0; i--) sift(A, i, len); //Turn into a heap. The right halfth does not violate the heap condition anyways as it forms the leaves
    while(len > 0){ //periodically put the root to the end and restore the heap
        swap(A, 0, len);
        len--;
        sift(A, 0, len);
    }
}

int main(){
    srand(time(0)); //seed
    unsigned long A[TESTLENGTH]; //Test array
    int i;
    for(i = 0; i < TESTLENGTH; i++){ //Build and print test array
        A[i] = rand() % TESTRANGE + 1;
        printf("%ld, ", A[i]);
    }
    sort(A, TESTLENGTH - 1);
    printf("\n");
    for(i = 0; i < TESTLENGTH; i++) printf("%ld, ", A[i]); //Print sorted array
}