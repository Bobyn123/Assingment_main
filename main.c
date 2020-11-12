#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
// (\d\d\.)+(\d) lat
// (-\d\.)+(\d) long
int main() {
    char filename[20] = "Test";
    sheep_position temp_position;
    FILE *fp;

    //open file containing information
    //    printf("What file do you want to open: ");
    //    scanf(" %[^\n\t]", filename);
    fp = fopen(filename, "r");
    if(!fp){
        printf("error");
        exit(1);
    }
    //read in GPS data from file specified
//    while(!feof(fp)) {
        fscanf(fp, "%[] ",temp_position.latitude,temp_position.longitude);
//    }
        printf("%f %f",temp_position.latitude, temp_position.longitude);
    return 0;
}
