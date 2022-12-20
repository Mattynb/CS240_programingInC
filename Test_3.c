#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct Node {
    char* word;
    struct Node* next;
    struct Node* prev;
}; typedef struct Node Node;

void print(Node* n) {
    if(n == NULL) return;
    if(n->next != NULL) printf("%s,", n->word); else printf("%s", n->word);
    print(n->next);
    
}

Node* findFirst(Node *n) {
    if(n == NULL) return n;
    if(n->prev == NULL) return n;
    return findFirst(n->prev);
}

Node* findLast(Node *n) {
    if(n == NULL) return n;
    if(n->next == NULL) return n;
    return findLast(n->next);
}

Node* add(Node* n, char* w) {
    Node* n2 = malloc(sizeof(Node));
    n2->word = malloc(100);
    strcpy(n2->word,w);
    n2->next = NULL;
    n2->prev = n;
    
    if(n == NULL) return n2;
    
    n->next = n2;
    return n2;
}
   
Node* addA(Node* n, char* w) {
    Node* n2 = malloc(sizeof(Node)); n2->word = malloc(100); strcpy(n2->word,w);n2->next = NULL;n2->prev = NULL;
    
    //printf("\nadding \'%s\'", w); fflush(stdout);
    
    if(n == NULL) return n2;
    
    if(strcmp(n->word, n2->word) < 0) {
        n2->prev = n;
        if(n->next != NULL) {
            n2->next = n->next;
            n->next->prev = n2;
        }
        n->next = n2; 
        //printf("\n "); printf("adding %s after %s because %d(%c) > %d(%c)", n2->word, n->word, *(n2->word + 0),*(n2->word + 0),*(n->word + 0),*(n->word + 0));fflush(stdout);
        return findLast(n2);
    }
    if(n->prev == NULL) {
        n->prev = n2;
        n2->next = n;
        //printf("\n "); print(findFirst(n2));fflush(stdout);
        return findLast(n);
    }
    free(n2->word);
    free(n2);
    //printf("  adding %s", w); fflush(stdout);
    return addA(n->prev, w);
}

Node* addltol(Node* n, Node* n2){
    n = findFirst(n);
    n2 = findFirst(n2);
    
    Node* n3 = NULL;
    
    while(n != NULL) {
        n3 = addA(n3, n->word);
        n = n->next;
        //printf("\nword = %s",n->word);
        //printf("\n "); print(findFirst(n3));fflush(stdout);
    }
    
    
    while(n2 != NULL) {
        n3 = addA(n3, n2->word);
        //printf("\n "); print(findFirst(n3));fflush(stdout);
        n2 = n2->next;
    }
    
    return n3;
}


int main()
{
    Node* l1 = NULL;
    char* w = malloc(101);
    char c;
    int i = 0;
    
    while(1) { 
        c = getchar();
        if(c == '\n' || c == EOF) {
            l1 = add(l1, w);
            i = 0;
            break;
        }
        
        if(c != ' ') *(w + i++) = toupper(c);
        if(c == ' ') {
            l1 = add(l1, w);
            w = malloc(100);
            i = 0;
        }
    }
    
    w = malloc(100);
    Node* l2 = NULL;
    while(1) {
        c = getchar();
        
        if(c == '\n' || c == EOF) {
            char* s = malloc(100);
            if(strcmp(w,s) != 0) l2 = add(l2, w); 
            break;
        }
        
        if(c != ' ') *(w + i++) = toupper(c);
        
        if(c == ' ') { l2 = add(l2, w); w = malloc(100); i = 0;}
    }
    
    if(l1 != NULL) {printf("\n"); print(findFirst(l1));}
    if(l2 != NULL) {printf("\n"); print(findFirst(l2));}   
    
    Node* l3 = addltol(findFirst(l1),findFirst(l2));
    printf("\n"); print(findFirst(l3));    
    
    return 0;
}
