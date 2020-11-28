//
// Created by rov3 on 12/11/2020.
//
#include <time.h>
#ifndef ASSINGMENT_MAIN_FUNCTIONS_H
#define ASSINGMENT_MAIN_FUNCTIONS_H
#define INPUT_SIZE 50

typedef struct sheep_struct * position_node_pointer;
typedef struct sheep_struct{
    double latitude, longitude;
    struct tm time;
    position_node_pointer next;
}sheep_position;



position_node_pointer make_sheep_node(double new_latitude, double new_longitude, struct tm new_time);
void position_insert_at_tail(position_node_pointer *ptr_to_head, position_node_pointer new_sheep_ptr);

typedef struct movement_struct * movement_node_pointer;
typedef struct movement_struct{
    position_node_pointer current_position;
    double distance;
    double time_taken;
    double speed;
    char behavior[9];
    movement_node_pointer next;
}sheep_movement;

movement_node_pointer make_movement_node(position_node_pointer previous, position_node_pointer current);
void movement_insert_at_tail(movement_node_pointer *ptr_to_head, movement_node_pointer new_movement_pointer);


double distance(sheep_position * first, sheep_position * second);
double difference_between_times(sheep_position * first, sheep_position * second);
void generate_movement_list(position_node_pointer position, movement_node_pointer* movement_head);
void save_movement_list(movement_node_pointer movement);
#endif //ASSINGMENT_MAIN_FUNCTIONS_H
