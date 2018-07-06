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

listElement *arrayToLinkedList(unsigned long *A, int len){ //Gets length - 1
    listElement *next = NULL;
    for(; len > 0; len--){
        listElement *newListElement;
        newListElement = malloc(sizeof(listElement));
        if(newListElement != NULL){
            newListElement->number = &A[len];
            newListElement->next = next;
            next = newListElement;
        }else{
            printf("You're trying to sort so much it doesn't fit into memory");
            exit(1);
        }
    }
    listElement *newListElement;
    newListElement = malloc(sizeof(listElement));
    if(newListElement != NULL){
        newListElement->number = &A[0];
        newListElement->next = next;
    }else{
        printf("You're trying to sort so much it doesn't fit into memory");
        exit(1);
    } 
    return newListElement;
}

void linkedListToArray(listElement *linkedList, unsigned long *A, int idx){ //Starts at 0
    if(linkedList == NULL) return;
    unsigned long insert = *(linkedList->number);
    linkedListToArray(linkedList->next, A, idx + 1);
    A[idx] = insert;
    free(linkedList);
}

listElement *insert(listElement *toBeInserted, listElement *linkedList){
    toBeInserted->next = NULL;
    if(linkedList == NULL) return toBeInserted;
    if(*(toBeInserted->number) <= *(linkedList->number)){
        toBeInserted->next = linkedList;
        return toBeInserted;
    }
    linkedList->next = insert(toBeInserted, linkedList->next);
    return linkedList;
}

listElement *insertSort(listElement *linkedList){
    if(linkedList == NULL) return linkedList;
    return insert(linkedList, insertSort(linkedList->next));
}

int main(){
    srand(time(0));
    unsigned long A[TESTLENGTH];
    int i;
    for(i = 0; i < TESTLENGTH; i++){
        A[i] = rand() % TESTRANGE + 1;
        printf("%ld, ", A[i]);
    }
    printf("\n");
    linkedListToArray(insertSort(arrayToLinkedList(A, TESTLENGTH - 1)), A, 0);
    for(i = 0; i < TESTLENGTH; i++) printf("%ld, ", A[i]);
}