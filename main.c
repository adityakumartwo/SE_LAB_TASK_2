/*
    Name:     ADITYA KUMAR
    Reg.No.:  25MCMT10

    How to Run Progam:
    gcc main.c stu_execute.c -o stu_out
    ./stu_out
*/
#include<stdio.h>
#include "stu_header.h"

int main(){

    struct Student students[MAX_STUDENTS];
    int count = 0;

    printf("--- Student Result System __\n");
    printf("Reading data from input.txt ...\n");

    // I. Read Input, which take the input from the file.
    count = read_Input(students, MAX_STUDENTS);

    if(count == 0){

        printf("No valid records found.\n");
        return 0;
    }

    // II. Calculate
    calcu_Results(students, count);

    // III. Display the Output
    show_Output(students, count);

    return 0;

}