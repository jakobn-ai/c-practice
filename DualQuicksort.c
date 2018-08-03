#include <stdio.h> //STDOUT output
#include <stdlib.h> //Random
#include <time.h> //Seed random

#define TESTLENGTH 30 //How big is the array to be sorted
#define TESTRANGE 100 //Numbers from 1 - TESTRANGE will be in the test array

struct node{ //A structure to be used for the linked list
    unsigned long *number; //Pointer to the payload
    struct node *next; //Pointer to the next node
};

typedef struct node listElement; //Typedefinition as linked list. The referenced element will be the first, the last will be the one that has NULL as next

listElement* arrayToLinkedList(unsigned long *A, int len){
    len--; //Adjust for array index
    listElement *next = NULL; //List will be built reversely, so the last element has NULL as next
    for(;; len--){ //End condition will be in return statement
        listElement *newListElement;
        newListElement = malloc(sizeof(listElement));
        if(newListElement == NULL){
            printf("You're trying to sort so much it doesn't fit into memory");
            exit(1);
        }
        newListElement->number = &A[len]; //Point to the the position in the array
        newListElement->next = next; //Point to the next element
        next = newListElement; //To be set in next iteration
        if(len <= 0) return newListElement;
    }
}

void linkedListToArray(listElement *linkedList, unsigned long *A, int idx){ //Starts at 0. Additionally takes array to be written to.
    if(linkedList == NULL) return; //End condition: at end of list
    unsigned long insert = *(linkedList->number); //Save number
    linkedListToArray(linkedList->next, A, idx + 1); //Recursively fill next position
    A[idx] = insert; //Write
    free(linkedList);
}

listElement* append(listElement *linkedList1, listElement *linkedList2){
    if(linkedList2 == NULL) return linkedList1;
    if(linkedList1 == NULL) return linkedList2;
    if(linkedList1->next == NULL) linkedList1->next = linkedList2; //reached end of list1
    else append(linkedList1->next, linkedList2);
    return linkedList1;
}

void partition(listElement **pivots, listElement *restOfList){ //Takes an array of five linked lists where indices 1, 3 are the pivots and indices 0, 2, 4 are empty, and the list to be pivoted
    if(restOfList == NULL) return; //end condition
    listElement *temp = restOfList; //separate first element
    restOfList = restOfList->next;
    temp->next = NULL;
    partition(pivots, restOfList); //recursive call with the rest of the list
    int pivotIndex; //where to put the element
    if(*(temp->number) <= *(pivots[1]->number)) pivotIndex = 0;
    else if(*(temp-> number) <= *(pivots[3]->number)) pivotIndex = 2;
    else pivotIndex = 4;
    append(temp, pivots[pivotIndex]); //it is better to have the shorter list first because the shorter list gets iterated
    pivots[pivotIndex] = temp;
}

listElement* pivot(listElement *linkedList){ //Actual sorting
    if(linkedList == NULL || linkedList->next == NULL) return linkedList; //end condition
    listElement* pivots[5]; //indices 1, 3 are the pivots
    pivots[0] = NULL; //indices 0, 2, 4 are empty
    pivots[2] = NULL;
    pivots[4] = NULL;
    listElement *restOfList = linkedList->next->next; //separate first two elements
    linkedList->next->next = NULL;
    if(*(linkedList->number) <= *(linkedList->next->number)){
        pivots[3] = linkedList->next;
        linkedList->next = NULL;
        pivots[1] = linkedList;
    }else{
        pivots[1] = linkedList->next;
        linkedList->next = NULL;
        pivots[3] = linkedList;
    }
    partition(pivots, restOfList); //sort the other elements into pivots
    int i;
    for(i = 0; i <= 4; i += 2) pivots[i] = pivot(pivots[i]); //recursively sort indices 0, 2, 4
    for(i = 4; i > 0; i--) pivots[i - 1] = append(pivots[i - 1], pivots[i]); //append them all, it is better to have the shorter list first
    return pivots[0];
}

void sort(unsigned long *A, int len){
    linkedListToArray(pivot(arrayToLinkedList(A, len)), A, 0);
}

int main(){
    srand(time(0)); //seed
    unsigned long A[TESTLENGTH]; //Test array
    int i;
    for(i = 0; i < TESTLENGTH; i++){ //Build and print test array
        A[i] = rand() % TESTRANGE + 1;
        printf("%ld, ", A[i]);
    }

    sort(A, TESTLENGTH);
    printf("\n");
    for(i = 0; i < TESTLENGTH; i++) printf("%ld, ", A[i]); //Print sorted array
    printf("\n");
}
