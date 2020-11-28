#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
//TODO refactor main function to put file intake section in functions, then move into seperate source file
void get_input(){

}

int main() {
    //setup of initial variables

    //setup of linked list
    position_node_pointer position_head = NULL;
    position_node_pointer current_position;

    char filename[20] = "Collar_12.TXT"; //filename hardcoded for testing have option to change later
    FILE *fp;

    //variables used for file input, counting input types and temp variables
    int valid_lines = 0, garbage_lines = 0, no_change_lines = 0;
    double current_latitude = 0.0, current_longitude = 0.0, previous_latitude = 0.0, previous_longitude = 0.0;
    struct tm current_time, previous_time;
    char str[INPUT_SIZE];

    //open file containing information
    //    printf("What file do you want to open: ");
    //    scanf(" %[^\n\t]", filename);
    fp = fopen(filename, "r");
    if (!fp) {
        printf("Error: File not found");
        exit(1);
    }

    /**
     * read in GPS data from file specified
     * reads in garbage data at start of file then adds first node as position_head of list
     * TODO refactor this section to reduce code reuse
     */
    while (!feof(fp)) {
        while (valid_lines == 0) {
            fgets(str, INPUT_SIZE, fp);
            sscanf(str, "%lf, %lf, %d/%d/%d, %d:%d:%d", &current_latitude, &current_longitude, &current_time.tm_mday,
                   &current_time.tm_mon, &current_time.tm_year, &current_time.tm_hour, &current_time.tm_min,
                   &current_time.tm_sec);
            if (current_latitude == 0 && current_longitude == 0) {
                garbage_lines++; //increments count of lines to be ignored due to bad garbage line
            } else {
                current_position = make_sheep_node(current_latitude, current_longitude, current_time);
                position_head = current_position;
                previous_time = current_time;
                valid_lines++;
                //record position of current new position for comparison
                previous_latitude = current_latitude;
                previous_longitude = current_longitude;
                current_latitude = 0.0, current_longitude = 0.0;
            }
        }

        //iterates through file ignoring garbage data and adding nodes
        fgets(str, INPUT_SIZE, fp);
        sscanf(str, "%lf, %lf, %d/%d/%d, %d:%d:%d", &current_latitude, &current_longitude, &current_time.tm_mday,
               &current_time.tm_mon, &current_time.tm_year, &current_time.tm_hour, &current_time.tm_min,
               &current_time.tm_sec);

        if (current_latitude == 0 && current_longitude == 0) {
            garbage_lines++; //increments count of lines to be ignored due to bad garbage line
        } else {
            if (current_time.tm_sec == previous_time.tm_sec && current_time.tm_min == previous_time.tm_min &&
                current_time.tm_hour == previous_time.tm_hour
                    ) {
                garbage_lines++; //increments count of lines to be ignored due to no change in time

            } else if (current_latitude == previous_latitude && current_longitude == previous_longitude) {
                no_change_lines++; //increments count of lines with no change in position

            } else {
                current_position = make_sheep_node(current_latitude, current_longitude, current_time);
                position_insert_at_tail(&position_head, current_position);
                //record position of current new position for comparison
                previous_latitude = current_latitude;
                previous_longitude = current_longitude;
                valid_lines++;
            }
        }
        current_latitude = 0, current_longitude = 0;
//    printf("%lf %lf %d/%d/%d %d:%d:%d\n", latitude, longitude,temp_tm.tm_mday,temp_tm.tm_mon,temp_tm.tm_year,temp_tm.tm_hour,temp_tm.tm_min,temp_tm.tm_sec);
    }
//    display_positions(position_head);
    printf("There were %d lines in total with %d valid lines, %d garbage lines and %d lines with no change in position\n\n",
           valid_lines + garbage_lines,
           valid_lines, garbage_lines, no_change_lines);
    fclose(fp);

    movement_node_pointer movement_head = NULL;

    generate_movement_list(position_head, &movement_head);

    save_movement_list(movement_head);

    return 0;

}
