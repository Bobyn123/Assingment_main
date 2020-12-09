//
// Code for reading in and processing movement data files
// Created by Robyn vaughan-Williams (rov3 on 03/12/2020.
//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "functions.h"


FILE *fp_read;
//global variables used for file input, counting input types and temp variables
position_node_pointer current_position;
int valid_lines = 0, garbage_lines = 0, no_change_lines = 0;
double current_latitude = 0.0, current_longitude = 0.0, previous_latitude = 0.0, previous_longitude = 0.0;
struct tm current_time, previous_time;
char str[INPUT_SIZE];

/**
 * Makes new node for linked list of sheep positions
 * @param new_latitude
 * @param new_longitude
 * @param new_time
 * @return node containing information of one position
 */
position_node_pointer make_sheep_node(double new_latitude, double new_longitude, struct tm new_time) {
    position_node_pointer new_node_ptr;
    new_node_ptr = malloc(sizeof(sheep_position));

    if (new_node_ptr == NULL) {
        return NULL; //no memory
    } else {
        //node data
        new_node_ptr->latitude = new_latitude;
        new_node_ptr->longitude = new_longitude;
        new_node_ptr->time = new_time;
        new_node_ptr->next = NULL;
        return new_node_ptr;
    }

}


/**
 * Inserts sheep node at tail of list
 * @param ptr_to_head head of linked position list
 * @param new_sheep_ptr new node to be attached to list
 */
void position_insert_at_tail(position_node_pointer* ptr_to_head, position_node_pointer new_sheep_ptr) {
    position_node_pointer *current_node;
    current_node = ptr_to_head;

    while (*current_node != NULL) {
        current_node = &((*current_node)->next);

    }

    new_sheep_ptr->next = *current_node;
    *current_node = new_sheep_ptr;
}

/**
 * Prints contents of position linked list for testing
 * @param position_head
 */
void print_positions_list(position_node_pointer positions) {
    printf("The positions recorded are:\n");
    while (positions != NULL) {
        printf("%lf %lf %d/%d/%d %d:%d:%d\n", positions->latitude, positions->longitude, positions->time.tm_mday,
               positions->time.tm_mon, positions->time.tm_year, positions->time.tm_hour, positions->time.tm_min,
               positions->time.tm_sec);
        positions = positions->next;
    }
}

/**
 * Reads in file of GPS data and generates a linked list of the valid position data
 * @param position_head
 * @param file_name
 */
void read_data(position_node_pointer* position_head, char file_name[20]){
    fp_read = fopen(file_name, "r");
    if (!fp_read) {
        printf("Error: File not found");
        exit(1);
    }

    /**
     * read in GPS data from file specified
     * reads in garbage data at start of file then adds first node as position_head of list
     * TODO refactor this section to reduce code reuse
     */
    while (!feof(fp_read)) {
        while (valid_lines == 0) {
            get_line();
            if (current_latitude == 0 && current_longitude == 0) {
                garbage_lines++; //increments count of lines to be ignored due to bad garbage line
            } else {
                current_position = make_sheep_node(current_latitude, current_longitude, current_time);
                *position_head = current_position;
                update_input_checkers();
                current_latitude = 0.0, current_longitude = 0.0;
            }
        }

        //iterates through file ignoring garbage data and adding nodes
        get_line();

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
                position_insert_at_tail(*&position_head, current_position);
                //record position of current new position for comparison
                update_input_checkers();
            }
        }
        current_latitude = 0, current_longitude = 0;
//    printf("%lf %lf %d/%d/%d %d:%d:%d\n", latitude, longitude,temp_tm.tm_mday,temp_tm.tm_mon,temp_tm.tm_year,temp_tm.tm_hour,temp_tm.tm_min,temp_tm.tm_sec);
    }

//    display_positions(position_head);
    printf("There were %d lines in total with %d valid lines, %d garbage lines and %d lines with no change in position\n\n",
           valid_lines + garbage_lines,
           valid_lines, garbage_lines, no_change_lines);
    fclose(fp_read);

}

/**
 * Helper function for read_data, updates the variables used in comparisons
 */
void update_input_checkers(){
    previous_time = current_time;
    valid_lines++;
    //record position of current new position for comparison
    previous_latitude = current_latitude;
    previous_longitude = current_longitude;
}

/**
 * Helper function for read_data, retrieves next line of input from file
 */
void get_line(){
    fgets(str, INPUT_SIZE, fp_read);
    sscanf(str, "%lf, %lf, %d/%d/%d, %d:%d:%d", &current_latitude, &current_longitude, &current_time.tm_mday,
           &current_time.tm_mon, &current_time.tm_year, &current_time.tm_hour, &current_time.tm_min,
           &current_time.tm_sec);
}