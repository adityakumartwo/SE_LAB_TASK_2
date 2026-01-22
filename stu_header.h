#ifndef STU_HEADER
#define STU_HEADER

#include<stdio.h>

// Constants
#define MAX_STUDENTS 100

#define SUBJECTS 5

// Structures
struct Subject{

    float minor;
    float major;
    float total;
};

struct Student {
    char id[100];
    char name[60];
    struct Subject subjects[SUBJECTS];

    float grandTotal;
    float percentage;
    char grade[3];
    float cgpa;
    int isFail;
};

// Function Prototypes like outline functions

int read_Input(struct Student s[], int max_size);
void calcu_Results(struct Student s[], int count);
void show_Output(struct Student s[], int count);



// Functions that are for the internal use

int valid_ID(char *id, struct Student s[], int count);
int valid_Name(char *name);
int valid_Marks(float minor, float major);
void show_Grade(float p, int fail, char *gradeStr, float *cgpa);

#endif


