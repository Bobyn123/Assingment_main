//
// Created by Robyn on 28/11/2020.
//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "functions.h"

movement_node_pointer make_movement_node(position_node_pointer current, position_node_pointer next) {
    movement_node_pointer new_node_ptr;
    new_node_ptr = malloc(sizeof(sheep_movement));


    if (new_node_ptr == NULL) {
        return NULL; //no memory
    } else {
        new_node_ptr->current_position = current;
        new_node_ptr->distance = distance(current, next);
        new_node_ptr->time_taken = difference_between_times(current, next);
        new_node_ptr->speed = new_node_ptr->distance / new_node_ptr->time_taken;
        strcpy(new_node_ptr->behavior, (new_node_ptr->speed > stationary_speed ? (new_node_ptr->speed > foraging_speed ? (new_node_ptr->speed > moving_speed ? "Implausible" : "Moving" ) : "Foraging") : "Stationary"));
        new_node_ptr->next = NULL;
        return new_node_ptr;
    }
}

void movement_insert_at_tail(movement_node_pointer *ptr_to_head, movement_node_pointer new_movement_ptr) {
    movement_node_pointer *current_node = ptr_to_head;

    while (*current_node != NULL) {
        current_node = &((*current_node)->next);
    }

    new_movement_ptr->next = *current_node;
    *current_node = new_movement_ptr;
}

double difference_between_times(sheep_position *first, sheep_position *second) {
    time_t first_time = mktime(&first->time);
    time_t second_time = mktime(&second->time);

    return difftime(second_time, first_time);
}

void generate_movement_list(position_node_pointer position, movement_node_pointer* movement_head){
    extern double max_speed , min_lon , max_lon , min_lat , max_lat;
    movement_node_pointer current_movement;

    current_movement = make_movement_node(position, position->next);
    *movement_head = current_movement;

    while (position != NULL) {
        if(position->next != NULL) {
            current_movement = make_movement_node(position, position->next);
            if(current_movement->speed<=max_speed
            && (min_lat <= current_movement->current_position->latitude && current_movement->current_position->latitude>= max_lat)
            && (min_lon <= current_movement->current_position->longitude && current_movement->current_position->longitude >= max_lon)
                    ){

            movement_insert_at_tail(*&movement_head, current_movement);

                }
        }
        position = position->next;
    }
}

void save_movement_list(movement_node_pointer movement){
    FILE *fp_write;
    fp_write = fopen("output", "w");
    if (!fp_write) {
        printf("Error: File not found");
        exit(1);
    }
    int i = 1;
    while (movement != NULL) {
        fprintf(fp_write, "Movement:%d, %d/%d/%d, %d:%d:%d, %lf, %lf, %lf, %lf, %lfm, %lfs, %lfm/s, %s\n",
                i++, movement->current_position->time.tm_mday, movement->current_position->time.tm_mon, movement->current_position->time.tm_year,
                movement->current_position->time.tm_hour, movement->current_position->time.tm_min, movement->current_position->time.tm_sec,
                movement->current_position->latitude, movement->current_position->longitude, movement->current_position->next->latitude, movement->current_position->next->longitude,
                movement->distance, movement->time_taken, movement->speed, movement->behavior);
        movement = movement->next;
    }
}

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
