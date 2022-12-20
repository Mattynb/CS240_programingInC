#include<stdio.h>
#include<stdlib.h>
#include <string.h>

struct LISTNODE {
    char* s;
    struct LISTNODE* prev;
    struct LISTNODE* next;
};
typedef struct LISTNODE NODE;

void printList(NODE* p) {
    if (p!= NULL) {
        if (p->s != NULL) printf("%s", p->s);
        p = p->next;
    }
    while(p!=NULL) {
        if (p->s != NULL) printf(",%s", p->s);
        p = p->next;
    }
}

NODE* findNode(NODE* first, char* value) {
    if (first == NULL || value == NULL) return NULL;
    if (first->s == NULL) return first ->next;
    if (strcmp(first->s, value) == 0) return first;
    return findNode(first->next, value);
}

NODE* findFirst(NODE* any) {
    if (any == NULL) return NULL;
    if (any->prev == NULL) return any;
    return findFirst(any->prev);
}

NODE* addNode(NODE* first, char* value) {
    NODE* n = malloc(sizeof(NODE));
    n->s = malloc(200);
    strcpy(n->s,value); n->prev = NULL; n->next = NULL;
   
    if (first == NULL) {
        return n;
    }
    n->prev = first;
    first->next = n;
    return n;
}


void removeNode(NODE** addy) {
    // x <> n <> y 
    // x <> y
    NODE *n = *addy;

    if (n == NULL) return;

    NODE* x = n->prev; NODE** xp = &x;
    NODE* y = n->next; NODE** yp = &y;

    if (x!= NULL) x->next = *yp;
    if (y!= NULL) y->prev = *xp;
    
    free(n->s);
    free(n);
}

void removeDuplicates(NODE* first) {
    NODE* p1, *p2;
    p1 = first;

    while (p1 != NULL) {
        p2 = p1->next;

        while (p2 != NULL) {
            if (strcmp(p1->s, p2->s) == 0) removeNode(&p2);
            p2 = p2->next;
        }

        p1 = p1->next;
    }
}

int main() {
    NODE* list = NULL;
    char *word = malloc(200);
    
    while (scanf("%s", word) == 1) {
        list = addNode(list, word);
    }
    
    printList(findFirst(list));
    printf("\n");
    if (findFirst(list)->next != NULL) removeDuplicates(findFirst(list));

    printList(findFirst(list));    
    return 0;
}