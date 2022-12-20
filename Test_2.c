#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct NODE {
 char *word; // the word
 struct NODE *next; // address of the next node
}; typedef struct NODE NODE;

void printN(NODE* first) {
    if(first == NULL) {return;}
    if(first->next == NULL){
        printf("%s", first->word);
        return;
    }
    printf("%s,", first->word);
    printN(first->next);
}

NODE* addNode(NODE* any, char* w) {
    NODE* n = malloc(sizeof(NODE));
    n->word = malloc(101);
    strcpy(n->word, w);
    n->next = NULL;
    
    if (any == NULL) return n;
    if(any->next != NULL){
        addNode(any->next, w);
    }
    
    any->next = n;
    return n;
}

int contains(NODE* first, char* w) {
    if (first == NULL) return 0;
    if (strcmp(first->word, w)==0) {
        return 1;
    }
    return contains(first->next, w);
}

void print2s(NODE* first) {
    NODE* repeat = malloc(sizeof(NODE));
    NODE* repeatFirst = NULL;
    
    while (first != NULL) {
        NODE *second = first->next;
        
        while (second != NULL) {
            if (strcmp(first->word,second-> word) == 0) {
                if (repeatFirst == NULL) {
                    repeat = addNode(repeat, first->word);
                    NODE** repeatfp = &repeat;
                    repeatFirst = *repeatfp;
                }
                else {
                    if (!contains(repeatFirst, first->word)) repeat = addNode(repeat, first->word);
                }
            }
            
            second = second->next;
        }
    
        first = first->next;
    }
    
    if ( repeatFirst != NULL) {
        printf("\n");
        printN(repeatFirst);
    }
}

int main()
{
    NODE* first = NULL;
    NODE* other = NULL;
    char* word = malloc(101);
    int count = 0;
    
    if (scanf("%s", word) == 1){
       first = addNode(other, word);
       NODE** fp = &first;
       other = *fp;
       for (int i = 0; word[i] != '\0'; ++i, count++) if (count >= 10000) break;
    }
    
    while (scanf("%s", word) == 1) {
        if (count >= 10000) break;
        other = addNode(other, word);
        for (int i = 0; word[i] != '\0'; ++i, count++)if (count >= 10000) break;
    }
    
    printN(first);
    print2s(first);
    
    return 0;
}
