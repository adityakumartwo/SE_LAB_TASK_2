#ifndef STU_HEADER_H
#define STU_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stu_constants.h"  // Include the constants here

// --- Structures ---
struct Subject {
    float minor;
    float major;
    float total;
};

struct Student {
    char id[MAX_ID_LEN];    // Uses constant from stu_constants.h
    char name[MAX_NAME_LEN];
    struct Subject subjects[NUM_SUBJECTS];
    float grandTotal;
    float percentage;
    char grade[3];
    float cgpa;
    int isFail;
};


// Input Module
int readInput(struct Student s[], int max_size);
int validateID(char *id, struct Student s[], int count);
int validateName(char *name);
int validateMarks(float minor, float major);

// Computation Module
void calculateResults(struct Student s[], int count);
void getGrade(float p, int fail, char *gradeStr, float *cgpa);

// Output Module
void generateOutput(struct Student s[], int count);

#endif