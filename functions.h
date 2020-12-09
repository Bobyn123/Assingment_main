//
// Created by rov3 on 12/11/2020.
//
#include <time.h>
#ifndef ASSINGMENT_MAIN_FUNCTIONS_H
#define ASSINGMENT_MAIN_FUNCTIONS_H
#define INPUT_SIZE 50
#define moving_speed 12.00
#define foraging_speed 0.33
#define stationary_speed 0.02

/**
 * struct for storing position data of sheep in linked list format with latitude, longitude and time
 */
typedef struct sheep_struct * position_node_pointer;
typedef struct sheep_struct{
    double latitude, longitude;
    struct tm time;
    position_node_pointer next;
}sheep_position;

/**
 * struct for storing sheep movements in linked list
 * with distance travelled, time taken for movement,
 * speed of movement and behavior exhibited
 * as well as linking to the starting position node
 */
typedef struct movement_struct * movement_node_pointer;
typedef struct movement_struct{
    position_node_pointer current_position;
    double distance;
    double time_taken;
    double speed;
    char behavior[9];
    movement_node_pointer next;
}sheep_movement;

/**
 * Makes new node for linked list of sheep positions
 * @param new_latitude
 * @param new_longitude
 * @param new_time
 * @return node containing information of one position
 */
position_node_pointer make_sheep_node(double new_latitude,
                                      double new_longitude,
                                      struct tm new_time);
/**
 * Inserts sheep node at tail of list
 * @param ptr_to_head head of linked position list
 * @param new_sheep_ptr new node to be attached to list
 */
void position_insert_at_tail(position_node_pointer *ptr_to_head,
                             position_node_pointer new_sheep_ptr);

/**
 * Prints contents of position linked list for testing
 * @param position_head
 */
void print_positions_list(position_node_pointer positions);

/**
 * Reads in file of GPS data and generates a linked list of the valid position data
 * @param position_head
 * @param file_name
 */
void read_data(position_node_pointer* position_head,
               char file_name[20]);

/**
 * Helper function for read_data, updates the variables used in comparisons
 */
void update_input_checkers();

/**
 * Helper function for read_data, retrieves next line of input from file
 */
void get_line();

/**
 * processes the position data of two position nodes and consolidates it into one movement node
 * @param current current position node being processed
 * @return movement node to be linked into a linked list
 */
movement_node_pointer make_movement_node(position_node_pointer previous);

/**
 * Inserts a movement node at the end of the linked list
 * @param ptr_to_head
 * @param new_movement_ptr
 */
void movement_insert_at_tail(movement_node_pointer *ptr_to_head,
                             movement_node_pointer new_movement_pointer);

/**
 * calculates the difference in time between two position nodes
 * @param first position node
 * @param second position node
 * @return a double containing the difference in time between the two position nodes
 */
double difference_between_times(sheep_position * first,
                                sheep_position * second);

/**
 * generates the linked list of movement data using the linked list of position data
 * @param position linked list of position data
 * @param movement_head empty movement data list
 */
void generate_movement_list(position_node_pointer position,
                            movement_node_pointer* movement_head);

/**
 * saves the processed movement data to a csv file
 * @param movement node pointer to head of the linked list of movement data
 */
void save_movement_list(movement_node_pointer movement);

/**
 * Prints the contents of each node of the linked list for testing purposes
 */
void print_movement_list(movement_node_pointer movement);
/**
 *
 * The great circle distance or the orthodromic distance is the shortest distance
 * between two points on a sphere
 * @param other
 * @return distance in m
 */
double distance(sheep_position * first,
                sheep_position * second);

/**
 * plots the movements of the sheep as vectors with starting latitude and longitude
 * and the tail of the vector and the change in latitude and longitude as the magnitude of the vector
 * @param movement linked list of movements
 */
void plot_movements_as_vectors(movement_node_pointer movement);

/**
 * plots a histogram of the movement speed distribution
 * @param movement
 */
void plot_histogram(movement_node_pointer movement);

/**
 * plots different all of the types of graphs implemented, in this case being the vector and histogram graphs
 * @param movement linked list
 */
void plot_graphs(movement_node_pointer movement);
#endif //ASSINGMENT_MAIN_FUNCTIONS_H
