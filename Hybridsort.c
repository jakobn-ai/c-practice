#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TESTLENGTH 30
#define TESTRANGE 100

struct node{
    unsigned long *number;
    struct node *next;
};

typedef struct node listElement;

listElement* arrayToLinkedList(unsigned long *A, int len){ //Gets length - 1
    listElement *next = NULL;
    for(;; len--){
        listElement *newListElement;
        newListElement = malloc(sizeof(listElement));
        if(newListElement == NULL){
            printf("You're trying to sort so much it doesn't fit into memory");
            exit(1);
        }
        newListElement->number = &A[len];
        newListElement->next = next;
        next = newListElement;
        if(len <= 0) return newListElement;
    }
}

void linkedListToArray(listElement *linkedList, unsigned long *A, int idx){ //Starts at 0
    if(linkedList == NULL) return;
    unsigned long insert = *(linkedList->number);
    linkedListToArray(linkedList->next, A, idx + 1);
    A[idx] = insert;
    free(linkedList);
}

listElement* insert(listElement *toBeInserted, listElement *linkedList){
    toBeInserted->next = NULL;
    if(linkedList == NULL) return toBeInserted;
    if(*(toBeInserted->number) <= *(linkedList->number)){
        toBeInserted->next = linkedList;
        return toBeInserted;
    }
    linkedList->next = insert(toBeInserted, linkedList->next);
    return linkedList;
}

listElement* insertSort(listElement *linkedList){
    if(linkedList == NULL) return linkedList;
    return insert(linkedList, insertSort(linkedList->next));
}

listElement* merge(listElement *linkedList1, listElement *linkedList2){
    if(linkedList1 == NULL) return linkedList2;
    if(linkedList2 == NULL) return linkedList1;
    if(*(linkedList1->number) <= *(linkedList2->number)){
        linkedList1->next = merge(linkedList1->next, linkedList2);
        return linkedList1;
    }else{
        linkedList2->next = merge(linkedList1, linkedList2->next);
        return linkedList2;
    }
}

listElement* sort(unsigned long *A, int len){
    int i;
    int preSortedSize = (len + 9) / 10;
    listElement **preSorted;
    preSorted = malloc(preSortedSize * sizeof(listElement));
    if(preSorted == NULL){
        printf("You're trying to sort so much it doesn't fit into memory");
        exit(1);
    }

    for(i = 0; i < preSortedSize; i++){
        if(i * 10 > TESTLENGTH - 1) preSorted[i] = insertSort(arrayToLinkedList(&A[i * 10], len - (i * 10) - 1));
        else preSorted[i] = insertSort(arrayToLinkedList(&A[i * 10], 9));
    }

    int mergedSize = preSortedSize;
    listElement **mergedSorted;
    while(mergedSize > 1){
        mergedSize = (mergedSize + 1) / 2;
        mergedSorted = malloc(mergedSize * sizeof(listElement));
        if(mergedSorted == NULL){
            printf("You're trying to sort so much it doesn't fit into memory");
            exit(1);
        }

        for(i = 0; i < mergedSize; i++){
            if(preSortedSize % 2 == 1 && i == preSortedSize / 2) mergedSorted[i] = preSorted[2 * i];
            else mergedSorted[i] = merge(preSorted[2 * i], preSorted[(2 * i) + 1]);
        }

        free(preSorted);
        preSortedSize = mergedSize;
        preSorted = malloc(preSortedSize * sizeof(listElement));
        if(preSorted == NULL){
            printf("You're trying to sort so much it doesn't fit into memory");
            exit(1);
        }
        preSorted = mergedSorted;
    }
    listElement *temp = preSorted[0];
    free(preSorted);
    return temp;
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

    linkedListToArray(sort(A, TESTLENGTH), A, 0);
    for(i = 0; i < TESTLENGTH; i++) printf("%ld, ", A[i]);
}