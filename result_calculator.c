#include "stu_header.h"

void getGrade(float p, int fail, char *gradeStr, float *cgpa){
    if(fail){
        strcpy(gradeStr, "F");
        *cgpa = 0.0;
    }
    else if (p >= 90) { strcpy(gradeStr, "O"); *cgpa = 10.0; }
    else if (p >= 85) { strcpy(gradeStr, "A+"); *cgpa = 9.0; }
    else if (p >= 75) { strcpy(gradeStr, "A"); *cgpa = 8.0; }
    else if (p >= 65) { strcpy(gradeStr, "B+"); *cgpa = 7.0; }
    else if (p >= 60) { strcpy(gradeStr, "B"); *cgpa = 6.0; }
    else if (p >= 55) { strcpy(gradeStr, "C"); *cgpa = 5.0; }
    else if (p >= 50) { strcpy(gradeStr, "D"); *cgpa = 4.0; }
    else { strcpy(gradeStr, "F"); *cgpa = 0.0; }
}

// It is the Main Computation Function
void calculateResults(struct Student s[], int count){
    for (int i = 0; i < count; i++) {
        float grandSum = 0;
        int failFlag = 0;

        for (int j = 0; j < NUM_SUBJECTS; j++) {
            float total = s[i].subjects[j].minor + s[i].subjects[j].major;
            s[i].subjects[j].total = total;
            grandSum += total;

            // Use the constant PASS_MARK (50)
            if(total < PASS_MARK) failFlag = 1; 
        }

        s[i].grandTotal = grandSum;
        s[i].percentage = grandSum / (float)NUM_SUBJECTS;
        s[i].isFail = failFlag;

        getGrade(s[i].percentage, failFlag, s[i].grade, &s[i].cgpa);
    }
}