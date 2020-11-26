#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
//#include "distances.c"

//makes new node for linked list of sheep positions
node_pointer make_sheep_node(double new_latitude, double new_longitude, struct tm new_time){
    node_pointer new_node_ptr;
    new_node_ptr = malloc(sizeof(sheep_position));

    if(new_node_ptr == NULL){
        return NULL; //no memory
    }else {
        //node data
        new_node_ptr -> latitude = new_latitude;
        new_node_ptr -> longitude = new_longitude;
        new_node_ptr -> time = new_time;
        new_node_ptr -> next = NULL;
        return new_node_ptr;
    }

}

//void insert_at_top(node_pointer *ptr_to_head, node_pointer new_sheep_ptr){
//    new_sheep_ptr->next = *ptr_to_head;
//    *ptr_to_head = new_sheep_ptr;
//}

//inserts sheep node at tail of linked list
//need to add code to not add node with identical time
void insert_at_tail(node_pointer *ptr_to_head, node_pointer new_sheep_ptr){
    node_pointer * prev_node;
    node_pointer * current_node;
    current_node = ptr_to_head;

    while(*current_node != NULL){
        prev_node = current_node;
        current_node = &((*current_node)->next);

    }

        new_sheep_ptr->next = *current_node;
        *current_node = new_sheep_ptr;

}

//prints contents of linked list
void display_positions(node_pointer positions){
    printf("The positions recorded are:\n");
    while(positions !=NULL){
        printf("%lf %lf %d/%d/%d %d:%d:%d\n",positions->latitude, positions->longitude,positions->time.tm_mday,
               positions->time.tm_mon,positions->time.tm_year,positions->time.tm_hour,positions->time.tm_min,positions->time.tm_sec);
//        printf("%lf %lf %s\n",positions->latitude, positions->longitude, asctime(&positions->time));
        positions = positions->next;
    }
}
//checks to see how many nodes of the list have no change in position
int check_stationary_nodes(node_pointer positions){
    int stationary= 0;
    while(positions !=NULL){
        if(positions->latitude - positions->next->latitude == 0 && positions->longitude - positions->next->longitude == 0 ) {
            stationary++;
        }
        positions = positions->next;
    }
 return stationary;
}

int main() { int i;

    //setup of global variables
    node_pointer head = NULL;
    node_pointer temp_position;
    char filename[20] = "test";
    int valid_lines = 0, garbage_lines = 0;
    double temp_latitude = 0.0, temp_longitude = 0.0;
    struct tm temp_time;
    char str[INPUT_SIZE];
    FILE *fp;

    //open file containing information
    //    printf("What file do you want to open: ");
    //    scanf(" %[^\n\t]", filename);
    fp = fopen(filename, "r");
    if (!fp) {
        printf("error");
        exit(1);
    }
    //read in GPS data from file specified
    while (!feof(fp)) {
        fgets(str, INPUT_SIZE, fp);
        sscanf(str, "%lf, %lf, %d/%d/%d, %d:%d:%d", &temp_latitude, &temp_longitude, &temp_time.tm_mday,
               &temp_time.tm_mon, &temp_time.tm_year, &temp_time.tm_hour, &temp_time.tm_min, &temp_time.tm_sec);

        if (temp_latitude == 0 && temp_longitude == 0) {
            garbage_lines++;
        } else {
            temp_position = make_sheep_node(temp_latitude, temp_longitude, temp_time);
            insert_at_tail(&head, temp_position);
            valid_lines++;
            temp_latitude = 0.0, temp_longitude = 0.0;
        }

//    printf("%lf %lf %d/%d/%d %d:%d:%d\n", latitude, longitude,temp_tm.tm_mday,temp_tm.tm_mon,temp_tm.tm_year,temp_tm.tm_hour,temp_tm.tm_min,temp_tm.tm_sec);
    }
    display_positions(head);
    int stationary_points;
    stationary_points = check_stationary_nodes(head);
    printf("There were %d lines in total with %d valid lines, %d garbage lines", valid_lines + garbage_lines,
           valid_lines, garbage_lines);
    return 0;

}