#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LINE_MAX 100

int main() {
    int corrupt = 0;
    int valid = 0;
    int totalMarks = 0;
    int mark;
    char name[50];
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    while(fscanf(file, "%s" ,name) == 1){
        int isNumber = 1;
        int i;
        for ( i = 0; name[i] != '\0'; i++) {
            if (!isdigit(name[i])) {
                isNumber = 0;
                break;
            }
        }
    
        if (isNumber == 1) {
            corrupt++;
            int character;
            while ((character = fgetc(file)) != '\n' && character != EOF);
            continue;
        }

        int result = fscanf(file, " %d", &mark);
        if (result == 1) {
            valid++;
            totalMarks += mark;
        } else {
            corrupt++;
            int character;
            while ((character = fgetc(file)) != '\n' && character != EOF);
            continue;
        }
    }
    fclose(file);
    printf("Valid entries: %d\n", valid);
    printf("Corrupt entries: %d\n", corrupt);
    if (valid > 0) {
        float average = (float)totalMarks / valid;
        printf("Average mark: %.2f\n", average);
    } else {
        printf("No valid entries to calculate average.\n");
    }
}