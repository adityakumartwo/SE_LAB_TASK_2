#include "stu_header.h"

void generateOutput(struct Student s[], int count){
    FILE *fp = fopen("results.txt", "w");
    if(fp == NULL){
        printf("Error creating output file.\n");
        return;
    }

    float classTotal = 0;
    // Initialize the max to a very small number and the min to a very large number
    float maxP = -1.0; 
    float minP = 101.0; 
    
    // Grade of counters: Indexing with what are shown mapping -> 0:O, 1:A+, 2:A, 3:B+, 4:B, 5:C, 6:D, 7:F
    int gradeCounts[8] = {0};

    printf("\n%-10s %-15s %-25s %-8s %-8s %-5s %-5s\n", 
           "ID", "Name", "Marks (Sub1-5)", "Total", "Perc", "Grd", "CGPA");
    printf("----------------------------------------------------------------------------------\n");

    fprintf(fp, "%-10s %-15s %-25s %-8s %-8s %-5s %-5s\n", 
            "ID", "Name", "Marks (Sub1-5)", "Total", "Perc", "Grd", "CGPA");
    fprintf(fp, "----------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++)
    {
        // Format the marks string
        char marksStr[50] = "";
        char temp[10];
        for (int j = 0; j < NUM_SUBJECTS; j++) {
            sprintf(temp, "%.0f", s[i].subjects[j].total);
            strcat(marksStr, temp);
            if (j < NUM_SUBJECTS - 1) strcat(marksStr, ", ");
        }

        printf("%-10s %-15s %-25s %-8.2f %-8.2f %-5s %-5.2f\n",
               s[i].id, s[i].name, marksStr, s[i].grandTotal, s[i].percentage, s[i].grade, s[i].cgpa);

        fprintf(fp, "%-10s %-15s %-25s %-8.2f %-8.2f %-5s %-5.2f\n",
                s[i].id, s[i].name, marksStr, s[i].grandTotal, s[i].percentage, s[i].grade, s[i].cgpa);

        // --- Stats Tracking ---
        classTotal += s[i].percentage;

        // Check the Maximum
        if(s[i].percentage > maxP) maxP = s[i].percentage;
        
        // Check the Minimum
        if(s[i].percentage < minP) minP = s[i].percentage;

        // Grades checking is here
        if(strcmp(s[i].grade, "O")==0) gradeCounts[0]++;
        else if(strcmp(s[i].grade, "A+")==0) gradeCounts[1]++;
        else if(strcmp(s[i].grade, "A")==0) gradeCounts[2]++;
        else if(strcmp(s[i].grade, "B+")==0) gradeCounts[3]++;
        else if(strcmp(s[i].grade, "B")==0) gradeCounts[4]++;
        else if(strcmp(s[i].grade, "C")==0) gradeCounts[5]++;
        else if(strcmp(s[i].grade, "D")==0) gradeCounts[6]++;
        else gradeCounts[7]++; // F
    }

    printf("----------------------------------------------------------------------------------\n");

    fprintf(fp, "----------------------------------------------------------------------------------\n");

    
    // Class Average
    float avg = (count > 0) ? (classTotal / count) : 0.0;
    
    printf("\nClass Average: %.2f%%\n", avg);
    fprintf(fp, "\nClass Average: %.2f%%\n", avg);

    // Highest and Lowest
    printf("Highest Perc : %.2f%%\n", maxP);
    fprintf(fp, "Highest Perc : %.2f%%\n", maxP);

    printf("Lowest Perc  : %.2f%%\n", minP);
    fprintf(fp, "Lowest Perc  : %.2f%%\n", minP);

    // Distribution of grade
    printf("\nNo. of students in each grade:\n");
    fprintf(fp, "\nNo. of students in each grade:\n");

    char *labels[] = {"O", "A+", "A", "B+", "B", "C", "D", "F"};
    for(int k=0; k<8; k++){
        printf("%-3s: %d\n", labels[k], gradeCounts[k]);
        fprintf(fp, "%-3s: %d\n", labels[k], gradeCounts[k]);
    }

    printf("\nResults saved to results.txt\n");
    fclose(fp);
}