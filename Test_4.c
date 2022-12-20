/******************************************************************************
                        TEST 4
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char* s1 = malloc(101);
    char* s2 = malloc(101);
    
    scanf("%s", s1);
    scanf("%s", s2);
    
    printf("%d", (strncmp(s1, s2, strlen(s1)) == 0));
    return 0;
}
