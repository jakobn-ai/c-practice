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
    len--; //Adjust for array indexrra
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

listElement* insert(listElement *toBeInserted, listElement *linkedList){ //Insertsort-style insertion
    toBeInserted->next = NULL;
    if(linkedList == NULL) return toBeInserted; //Inserting into empty list
    if(*(toBeInserted->number) <= *(linkedList->number)){ //Smaller than first element
        toBeInserted->next = linkedList;
        return toBeInserted; //New head of list
    }
    linkedList->next = insert(toBeInserted, linkedList->next); //Otherwise insert into rest of list
    return linkedList;
}

listElement* insertSort(listElement *linkedList){ //Recursively insert elements
    if(linkedList == NULL) return linkedList; //End of list
    return insert(linkedList, insertSort(linkedList->next));
}

listElement* merge(listElement *linkedList1, listElement *linkedList2){ //Merges two pre-sorted lists
    if(linkedList1 == NULL) return linkedList2; //Return remaining list if one is empty
    if(linkedList2 == NULL) return linkedList1;
    if(*(linkedList1->number) <= *(linkedList2->number)){
        linkedList1->next = merge(linkedList1->next, linkedList2); //Merge rest of list
        return linkedList1;
    }else{
        linkedList2->next = merge(linkedList1, linkedList2->next);
        return linkedList2;
    }
}

void sort(unsigned long *A, int len){
    int i; //Counter
    int preSortedSize = (len + 9) / 10; //Ceiling tenth
    listElement **preSorted; //To be merged
    preSorted = malloc(preSortedSize * sizeof(listElement));
    if(preSorted == NULL){
        printf("You're trying to sort so much it doesn't fit into memory");
        exit(1);
    }

    for(i = 0; i < preSortedSize; i++){ //Iterate through arrays
        if(i * 10 > len - 1) preSorted[i] = insertSort(arrayToLinkedList(&A[i * 10], len - (i * 10))); //Insertsort last portion of the array
        else preSorted[i] = insertSort(arrayToLinkedList(&A[i * 10], 10)); //Insertsort ten array elements
    }

    int mergedSize = preSortedSize;
    listElement **mergedSorted; //Second array of lists to store the merged lists
    while(mergedSize > 1){ //Iteratively merge
        mergedSize = (mergedSize + 1) / 2; //Ceiling half
        mergedSorted = malloc(mergedSize * sizeof(listElement));
        if(mergedSorted == NULL){
            printf("You're trying to sort so much it doesn't fit into memory");
            exit(1);
        }

        for(i = 0; i < mergedSize; i++){
            if(preSortedSize % 2 == 1 && i == preSortedSize / 2) mergedSorted[i] = preSorted[2 * i]; //Place last list if an odd number of lists was to be merged
            else mergedSorted[i] = merge(preSorted[2 * i], preSorted[(2 * i) + 1]); //Merge two lists
        }

        free(preSorted);
        preSortedSize = mergedSize; //Reallocate preSorted as mergedSorted
        preSorted = malloc(preSortedSize * sizeof(listElement));
        if(preSorted == NULL){
            printf("You're trying to sort so much it doesn't fit into memory");
            exit(1);
        }
        preSorted = mergedSorted;
    }
    listElement *temp = preSorted[0]; //To be returned
    free(preSorted);
    return linkedListToArray(temp, A, 0);
}

int main(){
    srand(time(0)); //seed
    unsigned long A[TESTLENGTH]; //Test array
    int i;
    for(i = 0; i < TESTLENGTH; i++){ //Build and print test array
        A[i] = rand() % TESTRANGE + 1;
        printf("%ld, ", A[i]);
    }
    printf("\n");

    sort(A, TESTLENGTH);
    for(i = 0; i < TESTLENGTH; i++) printf("%ld, ", A[i]); //Print sorted array
    printf("\n");
}
