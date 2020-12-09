//
// Created by Robyn on 28/11/2020.
//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "functions.h"

double total_stationary, total_foraging, total_moving, total_implausible;

/**
 * processes the position data of two position nodes and consolidates it into one movement node
 * @param current current position node being processed
 * @return movement node to be linked into a linked list
 */
movement_node_pointer make_movement_node(position_node_pointer current) {
    movement_node_pointer new_node_ptr;
    new_node_ptr = malloc(sizeof(sheep_movement));


    if (new_node_ptr == NULL) {
        return NULL; //no memory
    } else {
        new_node_ptr->current_position = current;
        new_node_ptr->distance = distance(current, current->next);
        new_node_ptr->time_taken = difference_between_times(current, current->next);
        new_node_ptr->speed = new_node_ptr->distance / new_node_ptr->time_taken;
        strcpy(new_node_ptr->behavior, (new_node_ptr->speed > stationary_speed ? (new_node_ptr->speed > foraging_speed ? (new_node_ptr->speed > moving_speed ? "Implausible" : "Moving" ) : "Foraging") : "Stationary"));
        new_node_ptr->next = NULL;
        return new_node_ptr;
    }
}

/**
 * Inserts a movement node at the end of the linked list
 * @param ptr_to_head
 * @param new_movement_ptr
 */
void movement_insert_at_tail(movement_node_pointer *ptr_to_head, movement_node_pointer new_movement_ptr) {
    movement_node_pointer *current_node = ptr_to_head;

    while (*current_node != NULL) {
        current_node = &((*current_node)->next);
    }

    new_movement_ptr->next = *current_node;
    *current_node = new_movement_ptr;
}

/**
 * calculates the difference in time between two position nodes
 * @param first position node
 * @param second position node
 * @return a double containing the difference in time between the two position nodes
 */
double difference_between_times(sheep_position *first, sheep_position *second) {
    time_t first_time = mktime(&first->time);
    time_t second_time = mktime(&second->time);

    return difftime(second_time, first_time);
}

/**
 * generates the linked list of movement data using the linked list of position data
 * @param position linked list of position data
 * @param movement_head empty movement data list
 */
void generate_movement_list(position_node_pointer position, movement_node_pointer* movement_head){
    extern double min_movement_duration, max_movement_duration, max_speed , min_lon , max_lon , min_lat , max_lat;
    movement_node_pointer current_movement;

    current_movement = make_movement_node(position);
    *movement_head = current_movement;

    while (position != NULL) {
        if(position->next != NULL) {
            current_movement = make_movement_node(position);
            if((current_movement->speed<=max_speed)
               && (min_lat <= current_movement->current_position->latitude) && (current_movement->current_position->latitude <= max_lat)
               && (min_lon <= current_movement->current_position->longitude) && (current_movement->current_position->longitude <= max_lon)
               && (min_movement_duration <= current_movement->time_taken) && (current_movement ->time_taken <= max_movement_duration)
                    ){

            movement_insert_at_tail(*&movement_head, current_movement);
                total_stationary += (!strcmp(current_movement -> behavior, "Stationary")) ? current_movement -> time_taken : 0;
                total_foraging += (!strcmp(current_movement -> behavior, "Foraging")) ? current_movement -> time_taken : 0;
                total_moving += (!strcmp(current_movement -> behavior, "Moving")) ? current_movement -> time_taken : 0;
                total_implausible += (!strcmp(current_movement -> behavior, "Implausible")) ? current_movement -> time_taken : 0;
                }
        }
        position = position->next;
    }
}

/**
 * saves the processed movement data to a csv file
 * @param movement node pointer to head of the linked list of movement data
 */
void save_movement_list(movement_node_pointer movement){
    extern char file_name[20];
    char output_file[50] = "";
    strcat(output_file, file_name);
    output_file[strlen(output_file) - 4] = '\0';
    strcat(output_file, "_movements_output");

    FILE *fp_write;
    fp_write = fopen(output_file, "w");
    if (!fp_write) {
        printf("Error: File not found");
        exit(1);
    }
    int i = 1;
    while (movement->next != NULL) {
        fprintf(fp_write, "Movement:%d, %d/%d/%d, %d:%d:%d, %lf, %lf, %lf, %lf, %lfm, %lfs, %lfm/s, %s\n",
                i++, movement->current_position->time.tm_mday, movement->current_position->time.tm_mon, movement->current_position->time.tm_year,
                movement->current_position->time.tm_hour, movement->current_position->time.tm_min, movement->current_position->time.tm_sec,
                movement->current_position->latitude, movement->current_position->longitude, movement->current_position->next->latitude, movement->current_position->next->longitude,
                movement->distance, movement->time_taken, movement->speed, movement->behavior);
        movement = movement->next;
    }
    printf("Total times for each movement category are:\n"
           "Stationary: %.2lfs \n"
           "Foraging: %.2lfs \n"
           "Moving: %.2lfs \n"
           "Implausible: %.2lfs \n ",
           total_stationary,total_foraging,total_moving,total_implausible);
    fclose(fp_write);
}
/**
 * Prints the contents of each node of the linked list for testing purposes
 */
void print_movement_list(movement_node_pointer movement){
    int i = 1;
    while (movement != NULL) {
        printf("Movement:%d, %d/%d/%d, %d:%d:%d, %lf, %lf, %lf, %lf, %lfm, %lfs, %lfm/s, %s\n",
                i++, movement->current_position->time.tm_mday, movement->current_position->time.tm_mon, movement->current_position->time.tm_year,
                movement->current_position->time.tm_hour, movement->current_position->time.tm_min, movement->current_position->time.tm_sec,
                movement->current_position->latitude, movement->current_position->longitude, movement->current_position->next->latitude, movement->current_position->next->longitude,
                movement->distance, movement->time_taken, movement->speed, movement->behavior);
        movement = movement->next;
    }
}
