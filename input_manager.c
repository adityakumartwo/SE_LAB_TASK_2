#include "stu_header.h"

// Check the ID
int validateID(char *id, struct Student s[], int count){
    for (int i = 0; i < strlen(id); i++){
        if(!isalnum(id[i])) return 0;
    }
    for(int i = 0; i < count; i++){
        if(strcmp(s[i].id, id) == 0) return 0;
    }
    return 1;
}

// Check Name
int validateName(char *name){
    for(int i = 0; i < strlen(name); i++){
        if(!isalpha(name[i])) return 0;
    }
    return 1;
}

// Check Marks
int validateMarks(float minor, float major){
    if(minor < 0 || minor > MINOR_MAX) return 0; // constant are used
    if(major < 0 || major > MAJOR_MAX) return 0; // constant are used
    return 1;
}

// It is the Main Input Function
int readInput(struct Student s[], int max_size){
    FILE *fp = fopen("input.txt", "r");
    if(fp == NULL){
        printf("Error: input.txt not found.\n");
        return 0;
    }

    int count = 0;
    char tempID[MAX_ID_LEN], tempName[MAX_NAME_LEN];
    float min[NUM_SUBJECTS], maj[NUM_SUBJECTS];

    while (fscanf(fp, "%s %s", tempID, tempName) == 2)
    {
        int valid = 1;

        if (validateID(tempID, s, count) == 0) {
            printf("Skipping invalid/duplicate ID: %s\n", tempID);
            valid = 0;
        }

        if (validateName(tempName) == 0) {
            printf("Skipping invalid Name : %s\n", tempName);
            valid = 0;
        }

        for(int i = 0; i < NUM_SUBJECTS; i++){
            fscanf(fp, "%f %f", &min[i], &maj[i]);
            if (validateMarks(min[i], maj[i]) == 0) {
                printf("Skipping ID %s due to marks out of range.\n", tempID);
                valid = 0;
            }
        }

        if(valid == 1 && count < max_size){
            strcpy(s[count].id, tempID);
            strcpy(s[count].name, tempName);
            for (int i = 0; i < NUM_SUBJECTS; i++) {
                s[count].subjects[i].minor = min[i];
                s[count].subjects[i].major = maj[i];
            }
            count++;
        }
    }
    fclose(fp);
    return count;
}