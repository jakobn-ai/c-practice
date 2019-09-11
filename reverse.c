#include <stdlib.h>
#include <stdio.h>

typedef struct Node Node;
struct Node {
    int payload;
    Node* next;
};

void printAll(Node* list) {
    if (list == 0) {
        printf("\n");
    } else {
        printf("%d, ", list->payload);
        printAll(list->next);
    }
}

Node* init(int payload) {
    Node* newHead = malloc(sizeof(Node));
    newHead->next = 0;
    newHead->payload = payload;
    return newHead;
}

Node* prepend(Node* list, int payload) {
    if (list == 0) {
        return init(payload);
    } else {
        Node* newHead = malloc(sizeof(Node));
        newHead->payload = payload;
        newHead->next = list;
        return newHead;
    }
}

Node* append(Node* list, int payload) {
    if (list == 0) {
        return init(payload);
    } else if (list->next == 0) {
        list->next = init(payload);
        return list;
    } else {
        list->next = append(list->next, payload);
        return list;
    }
}

Node* popFirst(Node* list) {
    Node* newHead = list->next;
    free(list);
    return newHead;
}

Node* popLast(Node* list) {
    if (list->next == 0) {
        free(list);
        return 0;
    } else if (list->next->next == 0) {
        free(list->next);
        list->next = 0;
        return list;
    } else {
        return popLast(list->next);
    }
}

Node* reverse(Node* list, Node* newTail) {
    if (list->next == 0) {
        list->next = newTail;
        return list;
    } else {
        Node* new = reverse(list->next, list);
        list->next = newTail;
        return new;
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("requires list length\n");
        return 1;
    }
    Node* list = 0;
    for (int i = 1; i <= atoi(argv[1]); i++) {
        list = prepend(list, i);
    }
    list = reverse(list, 0);
    printAll(list);
    while (list != 0) {
        list = popFirst(list);
    }
    return 0;
}
