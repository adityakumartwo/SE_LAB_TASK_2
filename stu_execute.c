#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "stu_header.h"

// Function to read data fom input.txt
int read_Input(struct Student s[], int max_size){
    FILE *fp = fopen("input.txt", "r");
    if(fp==NULL){
        printf("Error: Make sure file exists.\n");
        return 0;
    }

    
    int count = 0;
    char tempID[20], tempName[50];
    float min[5], maj[5];

    // It read the file line by line
    while (fscanf(fp, "%s %s", tempID,tempName) == 2)
    {
        int valid = 1;

        // check ID and Name
        if (valid_ID(tempID, s, count)==0)
        {
            printf("Skipping invalid or duplicate ID: %s\n",tempID);

            valid = 0;
        }

        if (valid_Name(tempName)==0)
        {
            printf("Skipping invalid Name : %s\n",tempName);
            valid = 0;
        }

        // Read the data and check the marks
        for(int i = 0; i<5; i++){

            fscanf(fp, "%f %f", &min[i], &maj[i]);

            if (valid_Marks(min[i],maj[i])==0)
            {
                printf("Skipping ID %s due to marks out of range.\n",tempID);
                valid = 0;
            }
        }

        // only valid data is saved
        if(valid == 1 && count < max_size){
            strcpy(s[count].id, tempID);

            strcpy(s[count].name, tempName);
            for (int i = 0; i < 5; i++)
            {
                s[count].subjects[i].minor = min[i];
                s[count].subjects[i].major = maj[i];
            }
            count++;
        }
    }
    fclose(fp);
    return count;
}

// This Function calculate the Total, Grade and CGPA
void calcu_Results(struct Student s[], int count){
    for (int i = 0; i < count; i++)
    {
        float grandSum = 0;
        int failFlag = 0;

        for (int j = 0; j < 5; j++)
        {
            float total = s[i].subjects[j].minor + s[i].subjects[j].major;

            s[i].subjects[j].total = total;
            grandSum += total;

            // Student is fail if marks is less than 50
            if(total<50) failFlag = 1;
        }

        s[i].grandTotal = grandSum;
        s[i].percentage = grandSum/5.0;
        s[i].isFail = failFlag;

        show_Grade(s[i].percentage, failFlag, s[i].grade, &s[i].cgpa);
    
    }
    
}

// check id is valid or duplicate
int valid_ID(char *id, struct Student s[], int count){
    for (int i = 0; i<strlen(id); i++)
    {
        if(!isalnum(id[i])) return 0; // Must be letter or numbers
    }
    for(int i = 0; i<count; i++)
    {
        if(strcmp(s[i].id, id) == 0) return 0; // Duplicate Check
    }
    return 1;
}

// check name is valid
int valid_Name(char *name){
    for(int i = 0; i<strlen(name);i++)
    {
        if(!isalpha(name[i])) return 0; // Must be letter only
    }
    return 1;
}

// check marks 
int valid_Marks(float minor, float major)
{
    if(minor < 0 || minor > 40) return 0;
    if(major < 0 || major > 60) return 0;
    return 1;
}

// Determine tha Grade String
// Crucial Rule: If a Student less than 50%  in any individual subject, they are automatically marked as fail(F), and their CGPA becomes 0.0, regardless of their total percentage
void show_Grade(float p, int fail, char *gradeStr, float *cgpa){
    if(fail){
        strcpy(gradeStr, "F");
        *cgpa = 0.0;
    }
    else if (p>=90) {strcpy(gradeStr,"O"); *cgpa = 10.0 ;}
    else if (p>=85) {strcpy(gradeStr,"A+"); *cgpa = 9.0 ;}
    else if (p>=75) {strcpy(gradeStr,"A"); *cgpa = 8.0 ;}
    else if (p>=65) {strcpy(gradeStr,"B+"); *cgpa = 7.0 ;}
    else if (p>=60) {strcpy(gradeStr,"B"); *cgpa = 6.0 ;}
    else if (p>=55) {strcpy(gradeStr,"C"); *cgpa = 5.0 ;}
    else if (p>=50) {strcpy(gradeStr,"D"); *cgpa = 4.0 ;}
    else {strcpy(gradeStr,"F"); *cgpa = 0.0;}
}

void show_Output(struct Student s[], int count){

    FILE *fp = fopen("results.txt", "w");

    if(fp==NULL){
        printf("Error in output file.\n");

        return;
    }

    float classTotal = 0, maxP = -1, minP = 101;

    int gradeCounts[8] = {0};

    // Columns Headers which show the data in tabular form
    // Print to Screen
    printf("\n%-10s %-15s %-25s %-8s %-8s %-5s %-5s\n", "ID", "Name", "Marks (Sub 1-5)", "Total", "Perc", "Grd", "CGPA");

    // Print to File
    fprintf(fp, "\n%-10s %-15s %-25s %-8s %-8s %-5s %-5s\n", "ID", "Name", "Marks (Sub 1-5)", "Total", "Perc", "Grd", "CGPA");

    printf("\n");

    fprintf(fp,"\n");

    for (int i = 0; i < count; i++)
    {
        // string hold the list of marks (e.g., "50","56","60","80","90",)
        char marksStr[50] = "";

        char temp[10];

        for (int j = 0; j < 5; j++)
        {
            sprintf(temp, "%.0f", s[i].subjects[j].total);

            strcat(marksStr,temp);
            if (j<4)
            {
                strcat(marksStr, ","); 
            }
        }
        
        //Print Row to Console
        printf("%-10s %-15s %-25s %-8.2f %-8.2f %-5s %-5.2f\n",
        s[i].id, s[i].name, marksStr, s[i].grandTotal, s[i].percentage, s[i].grade, s[i].cgpa);

        //Print Row to file
        fprintf(fp, "%-10s %-15s %-25s %-8.2f %-8.2f %-5s %-5.2f\n",
        s[i].id, s[i].name, marksStr, s[i].grandTotal, s[i].percentage, s[i].grade, s[i].cgpa);

        // Stats Logic
        classTotal += s[i].percentage;

        if(s[i].percentage>maxP)maxP = s[i].percentage;

        if(s[i].percentage<minP)minP = s[i].percentage;

        // Counts Grades
        if(strcmp(s[i].grade, "O")==0) gradeCounts[0]++;

        else if (strcmp(s[i].grade, "A+")==0) gradeCounts[1]++;
        else if (strcmp(s[i].grade, "A")==0) gradeCounts[2]++;
        else if (strcmp(s[i].grade, "B+")==0) gradeCounts[3]++;
        else if (strcmp(s[i].grade, "B")==0) gradeCounts[4]++;
        else if (strcmp(s[i].grade, "C")==0) gradeCounts[5]++;
        else if (strcmp(s[i].grade, "D")==0) gradeCounts[6]++;

        else gradeCounts[7]++;
    }


    // STATS
    printf("\nClass Average: %.2f%%\n", classTotal / count);
    fprintf(fp,"\nClass Average: %.2f%%\n", classTotal / count);

    printf("Highest Perc : %.2f%%\n", maxP);
    fprintf(fp,"Highest Perc : %.2f%%\n", maxP);

    printf("Lowest Perc : %.2f%%\n", minP);
    fprintf(fp,"Lowest Perc : %.2f%%\n", minP);

    printf("\n No. of students in each grade:\n");

    printf("O : %d\n", gradeCounts[0]);
    printf("A+: %d\n", gradeCounts[1]);
    printf("A : %d\n", gradeCounts[2]);
    printf("B+: %d\n", gradeCounts[3]);
    printf("B : %d\n", gradeCounts[4]);
    printf("C : %d\n", gradeCounts[5]);
    printf("D : %d\n", gradeCounts[6]);

    printf("F : %d\n", gradeCounts[7]);


    fprintf(fp,"\n No. of students in each grade:\n");

    fprintf(fp,"O : %d\n", gradeCounts[0]);
    fprintf(fp,"A+: %d\n", gradeCounts[1]);
    fprintf(fp,"A : %d\n", gradeCounts[2]);
    fprintf(fp,"B+: %d\n", gradeCounts[3]);
    fprintf(fp,"B : %d\n", gradeCounts[4]);
    fprintf(fp,"C : %d\n", gradeCounts[5]);
    fprintf(fp,"D : %d\n", gradeCounts[6]);
    fprintf(fp,"F : %d\n", gradeCounts[7]);

    printf("\nResults saved to results.txt\n");
    fclose(fp);
}