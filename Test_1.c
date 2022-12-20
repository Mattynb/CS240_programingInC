/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>

int
main ()
{
  char input[10000];
  int lineC = 1;
  int wordcount = 0;
  int flag = 1;			//1 means its currently in a word.
  int c;
  int counter;
  int i = 0;
  int inputcount = 0;
  while(scanf("%c", &(input[i++])) != EOF){
      //printf ("%c", *(input + i));
        inputcount++;
  }
 

  int j;
  for (j = 0; j < inputcount; j++){
      
     if (inputcount == 0) {
         break;
     }
    
    c = input[j];
    //printf("%c == %d", c, j);
    
    if ((c == ' '|| c == '\n') && flag && counter!=0){
	  ++wordcount;
	  flag = 0;
	  printf (" %d %d\n", lineC, wordcount);
	}
	if (counter ==0){
        putchar('\n');
        ++counter;
    }
	if (j == inputcount && flag) {
	    printf (" %d %d", lineC, ++wordcount);
	}
    
	if (c == '\n') {
	  lineC++;
	}
	if (c != '\n' && c != ' '){
	  putchar (c);
	  flag = 1;
	}
	
  }
  
  return 0;
}
