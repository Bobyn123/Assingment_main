//
// For the graphing of data created by the data_processing section
// Created by Neal Snooke, adapted for use by Robyn Vaughan-Williams for using on graphing movements on 06/12/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

extern char file_name[20];
/**
 * plots the movements of the sheep as vectors with starting latitude and longitude
 * and the tail of the vector and the change in latitude and longitude as the magnitude of the vector
 * @param movement linked list of movements
 */
void plot_movements_as_vectors(movement_node_pointer movement) {
    //taking input file name and inserting it at front of gnuplot output filename
    char output_file[50] = "";
    char gnuplot[50] = "gnuplot ";

    //rearranging strings
    strcat(output_file, file_name);
    output_file[strlen(output_file) - 4] = '\0'; //removing the .TXT section of file name
    strcat(output_file, "_movements.gnuplot");
    strcat(gnuplot, output_file);

    int sizex = 1024;
    int sizey = 824;

    //setting labels
    char chart_title[] = "\"Sheep movement in Latitude and longitude\"";
    char x_label[] = "\"Longitude\"";
    char y_label[] = "\"Latitude\"";
    char color_label[] = "\"Speed\"";

    FILE* datafile;

    // create the output file for writing
    if ((datafile = fopen(output_file, "w")) == NULL) {
        printf("Cannot open output file.\n");
        exit(1);
    }

    // set up the output to produce an svg file output - lots of other possibilities
    fprintf(datafile, "set terminal svg noenhanced linewidth 0.75 size %i,%i\n", sizex, sizey);

    //set the file to save the graph into (without this it goes to the terminal)
    fprintf(datafile, "set output \"%s.svg\"\n", output_file);

    // set the chart title
    fprintf(datafile, "set title %s\n", chart_title);

    //make the axis scale sutomatically based on the range of the data
    fprintf(datafile, "set autoscale\n");

    //set the axis labels and make them visible
    fprintf(datafile, "set xlabel %s\nshow xlabel\n", x_label);
    fprintf(datafile, "set ylabel %s\nshow ylabel\n", y_label);

    // set the colour banding label
    fprintf(datafile, "set cblabel %s\n", color_label);

    // define a set of colours, and the values for those colours
    // the colours mix proportionately for values between those specified
    fprintf(datafile, "set palette defined ( 0 \"black\", %lf \"blue\", %lf \"red\", %lf \"yellow\")\n",stationary_speed, foraging_speed, moving_speed);

    //tells gnuplot to plot a set of vectors without lines and using the last data entry on each line to produce the vector color
    fprintf(datafile, "plot '-' with vectors nohead linecolor palette z title \"%s\"\n", file_name);

    //prints the movement data in vector form to the gnuplot file along with the speed to determine vector color
    while(movement->next != NULL){
        fprintf(datafile,"%lf, %lf, %lf, %lf, %lf\n",movement->current_position->longitude,movement->current_position->latitude,
                movement->next->current_position->longitude - movement->current_position->longitude,movement->next->current_position->latitude - movement->current_position->latitude,
                movement->speed);
        movement = movement->next;
    }

    fclose(datafile);

    printf("Generating vector graph\n");
    system(gnuplot);
}

/**
 * plots a histogram of the movement speed distribution
 * @param movement linked list
 */
void plot_histogram(movement_node_pointer movement){
    extern int num_bars; //number of bars to break the histogram down into
    //taking input file name and inserting it at front of gnuplot output filename
    char output_file[50] = "";
    char gnuplot[50] = "gnuplot ";

    //rearranging strings
    strcat(output_file, file_name);
    output_file[strlen(output_file) - 4] = '\0'; //removing the .TXT section of file name
    strcat(output_file, "_histogram.gnuplot");
    strcat(gnuplot, output_file);

    int sizex = 1024;
    int sizey = 824;

    //setting labels
    char chart_title[] = "\"Sheep movement speeds\"";
    char x_label[] = "\"Speed\"";
    char y_label[] = "\"Total duration\"";

    FILE* datafile;

    // create the output file for writing
    if ((datafile = fopen(output_file, "w")) == NULL) {
        printf("Cannot open output file.\n");
        exit(1);
    }

    // set up the output to produce an svg file output - lots of other possibilities
    fprintf(datafile, "set terminal svg noenhanced linewidth 0.75 size %i,%i\n", sizex, sizey);

    //set the file to save the graph into (without this it goes to the terminal)
    fprintf(datafile, "set output \"%s.svg\"\n", output_file);

    // set the chart title
    fprintf(datafile, "set title %s\n", chart_title);

    //make the axis scale sutomatically based on the range of the data
    fprintf(datafile, "set autoscale\n");

    //set the axis labels and make them visible
    fprintf(datafile, "set xlabel %s\nshow xlabel\n", x_label);
    fprintf(datafile, "set ylabel %s\nshow ylabel\n", y_label);

    //tels gnuplot to plot a graph with boxes
    fprintf(datafile, "plot '-' with boxes  \"%s\"\n", file_name);

    //prints lines of data relating to how long was spent at each speed
    //not yet properly implemented
    while(movement->next != NULL){
        fprintf(datafile,"%lf\n", movement->speed);
        movement = movement->next;
    }

    fclose(datafile);

//    system(gnuplot);  //not asking system to actually run this file as the code is not yet fully implemented, cant figure out how to use gnuplot to plot a histogram
}

/**
 * plots different all of the types of graphs implemented, in this case being the vector and histogram graphs
 * @param movement linked list
 */
void plot_graphs(movement_node_pointer movement){
    plot_movements_as_vectors(movement);
    plot_histogram(movement);
}
