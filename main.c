/*
    Name:     ADITYA KUMAR
    Reg.No.:  25MCMT10

    How to Run Progam:
    gcc main.c input_manager.c result_calculator.c report_generator.c -o stu_out
    ./stu_out
*/
#include "stu_header.h"

int main() {
    struct Student students[MAX_STUDENTS];
    int count = 0;

    printf("--- Modular Student System (Constant-Enhanced) ---\n");

    count = readInput(students, MAX_STUDENTS);

    if (count == 0) {
        printf("No valid records found.\n");
        return 0;
    }

    calculateResults(students, count);
    generateOutput(students, count);

    return 0;
}