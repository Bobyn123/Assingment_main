#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

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

void insert_at_top(node_pointer *ptr_to_head, node_pointer new_sheep_ptr){
    new_sheep_ptr->next = *ptr_to_head;
    *ptr_to_head = new_sheep_ptr;
}

void insert_at_tail(node_pointer *ptr_to_head, node_pointer new_sheep_ptr){
    node_pointer * prev_node;
    node_pointer * current_node;
    current_node = ptr_to_head;

    while(*current_node != NULL){
        prev_node = current_node;
        current_node = &((*current_node)->next);
    }

//    if(is_duplicate_node(new_sheep_ptr,prev_node)){
//        new_sheep_ptr->next = *current_node;
//        *current_node = new_sheep_ptr;
//    }

    new_sheep_ptr->next = *current_node;
    *current_node = new_sheep_ptr;
}

int is_duplicate_node(node_pointer new_sheep, node_pointer current_sheep){

    if(current_sheep->time.tm_mon == new_sheep->time.tm_mon && current_sheep->time.tm_year == new_sheep->time.tm_year &&
    current_sheep->time.tm_hour == new_sheep->time.tm_hour && current_sheep->time.tm_min == new_sheep->time.tm_min && current_sheep->time.tm_sec == new_sheep->time.tm_sec){
        return 0;
    }else{
        return 1;
    }

}
void display_positions(node_pointer positions){
    printf("The positions recorded are:\n");
    while(positions !=NULL){
        printf("%lf %lf %d/%d/%d %d:%d:%d\n",positions->latitude, positions->longitude,positions->time.tm_mday,
               positions->time.tm_mon,positions->time.tm_year,positions->time.tm_hour,positions->time.tm_min,positions->time.tm_sec);
        positions = positions->next;
    }
}

int main() {
    node_pointer head = NULL;
    node_pointer temp_position;
    char filename[20] = "test";
    int  valid_lines = 0, garbage_lines = 0;
    double temp_latitude =0.0, temp_longitude = 0.0;
    struct tm temp_time;
    char str[INPUT_SIZE];
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
    while(!feof(fp)) {
    fgets(str, INPUT_SIZE,fp);
    sscanf(str, "%lf, %lf, %d/%d/%d, %d:%d:%d", &temp_latitude, &temp_longitude, &temp_time.tm_mday, &temp_time.tm_mon, &temp_time.tm_year, &temp_time.tm_hour, &temp_time.tm_min, &temp_time.tm_sec);

    if(temp_latitude == 0 && temp_longitude == 0){
        garbage_lines++;
    }else{
        temp_position = make_sheep_node(temp_latitude,temp_longitude,temp_time);
        insert_at_tail(&head, temp_position);
        valid_lines++;
        temp_latitude =0.0, temp_longitude = 0.0;
    }

//    printf("%lf %lf %d/%d/%d %d:%d:%d\n", latitude, longitude,temp_tm.tm_mday,temp_tm.tm_mon,temp_tm.tm_year,temp_tm.tm_hour,temp_tm.tm_min,temp_tm.tm_sec);
    }
    display_positions(head);
    printf("There were %d lines in total with %d valid lines and %d garbage lines",valid_lines+garbage_lines,valid_lines,garbage_lines);
    return 0;
}
