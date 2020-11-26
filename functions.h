//
// Created by rov3 on 12/11/2020.
//
#include <time.h>
#ifndef ASSINGMENT_MAIN_FUNCTIONS_H
#define ASSINGMENT_MAIN_FUNCTIONS_H
#define INPUT_SIZE 50
typedef struct sheep_struct * node_pointer;
typedef struct sheep_struct{
    double latitude, longitude;
    struct tm time;
    node_pointer next;
}sheep_position;

node_pointer make_sheep_node(double new_latitude, double new_longitude, struct tm new_time);
void insert_at_top(node_pointer *ptr_to_head, node_pointer new_sheep_ptr);
void insert_at_tail(node_pointer *ptr_to_head, node_pointer new_sheep_ptr);
int is_duplicate_node(node_pointer new_sheep, node_pointer current_sheep);
double distance(sheep_position * first, sheep_position * second);
#endif //ASSINGMENT_MAIN_FUNCTIONS_H
