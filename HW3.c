#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct STUDENT {
    char studentID[7];
    char* firstName;
    char* lastName;
    float grade; 
}; 
typedef struct STUDENT stud;

stud* createStud(char id[7], char* fn, char* ln, float gradea) {
    stud *a;

    a = malloc(sizeof(stud));
    a->firstName = malloc(strlen(fn)+1); 
    a->lastName = malloc(strlen(ln)+1);
    
    strcpy(a->studentID, id); strcpy(a->firstName, fn); strcpy(a->lastName, ln);
    a->grade = gradea;
    
    // printf("\nCREATE: %s, %s, %s, %1.2f\n", a->studentID, a->firstName, a->lastName, a->grade);
    return a;
}


int main() { 
    int n = 0;
    scanf("%d\n", &n);

    // settings
    stud studs[n];
    stud *a, *temp;
    char idh[15], fnh[15], lnh[15];
    float gh;

    // getting input 
    for(int i = 0; i < n; i++) {
        scanf("%[^,], %[^,], %[^,], %f\n", idh, fnh, lnh, &gh);
        a = malloc(sizeof(stud));
        a = createStud(idh, fnh, lnh, gh);
        *(studs + i) = *a;
    }

    // sorting
    temp = malloc(sizeof(stud));
    for (int j = 0; j < n-1; j++) {
        for (int i = 0; i < n-j-1; i++) {
            // if a.grade > b.grade, swap them.
            if (studs[i].grade > studs[i + 1].grade) {
                *temp = *(studs+i);
                *(studs + i) = *(studs + i + 1);
                *(studs + i + 1) = *temp;
            } 
            
            // if they are equal but their ids are different, swap them.
            if (studs[i].grade == studs[i + 1].grade) {
                if (atoi(studs[i].studentID) < atoi(studs[i+1].studentID)) {
                    *temp = *(studs+i);
                    *(studs + i) = *(studs + i + 1);
                    *(studs + i + 1) = *temp;
                }
            } 
        }
    }

    // printing to stdout
    for (int i = n-1; i >= 0; i--) {
        *temp = studs[i];

        printf("%s,%s,%s,%.2f\n", temp->studentID, temp->firstName, temp->lastName, temp->grade);
    }

    
    free(temp);
    free(a);
    return 0;
}
