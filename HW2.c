#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
 char* word;
 int index;
} WORD;

// Function to lower a string
char* lowerWord(char* s) {
 // Create a variable and allocate the memory to store the lower string
 char * temp = malloc(strlen(s) + 1);
 // Copy the original string to the temp variable
 strcpy(temp, s);
 // Loop through each char in the temp variable to make them lower
   for(char *p=temp; *p; p++) *p=tolower(*p);

   return temp;
}

// Swapping to struct
void swap(WORD* w1, WORD* w2) {
 WORD temp = *w1;
 *w1 = *w2;
 *w2 = temp;
}

// Create a struct variable to hold the string and its index
WORD makeWord(char* s, int index) {
 WORD w;
 // Allocate the memory for the string
 w.word = malloc(strlen(s) + 1);
 // Copy the input string to the struct
 strcpy(w.word, s);
 // Assign the index
 w.index = index;

 return w;
}

int main() {
 // Create array of struct WORD
 WORD wordList[10000];
 // Create a char array (string) that will be used to read each input word
 char str[100];
 // Index start from 0
 int k = 0;

 // Read input by scanning each word until EOF
 while (scanf("%s", str) != EOF) { 
  // Store the read input string to the struct array
  wordList[k] = makeWord(str, k);
  // Increase index
  k++;  
 }

 // Buble sort algorithm
 for (int i = 0; i < k-1; i++)      
        for (int j = 0; j < k-i-1; j++) {
         // Make the 2 words that we are comparing to lowercase
         // If we don't lower, the word will be sorted based on ASCII order
         char* w1_lowercase = lowerWord(wordList[j].word); 
         char* w2_lowercase = lowerWord(wordList[j+1].word);
            if (strcmp(w1_lowercase, w2_lowercase) > 0) {
               swap(&wordList[j], &wordList[j+1]);
            }
        }

    // Print out the result
    if (k > 0) {
  for (int i = 0; i < k-1; i++) {
   // First n-1 elements have comma 
   printf("%s,", wordList[i].word);
  }
  // The n-th element doesn't have comma
  printf("%s\n", wordList[k-1].word);

  for (int i = 0; i < k-1; i++) {
   // First n-1 elements have comma 
   printf("%d,", wordList[i].index);
  }
  // The n-th element doesn't have comma
  printf("%d", wordList[k-1].index);
 }
 
 return 0;
}
