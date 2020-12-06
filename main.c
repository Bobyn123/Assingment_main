#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "functions.h"

double min_movement_duration = 0, max_movement_duration = 604800, max_speed = 50, min_lon = 0, max_lon = 0, min_lat = 0, max_lat = 0;
int num_bars = 20;
char file_name[20] = "Collar_15.TXT";
char config_file[20];

void process_data_file() {
    position_node_pointer position_head = NULL;
    read_data(&position_head, file_name);
    movement_node_pointer movement_head = NULL;
    generate_movement_list(position_head, &movement_head);
    print_movement_list(movement_head);
    save_movement_list(movement_head);
}

void load_config() {
    FILE *fp;
    char str[INPUT_SIZE];
    fp = fopen(config_file, "r");
    if (!fp) {
        printf("Error: File not found");
        exit(1);
    }

    fgets(str, INPUT_SIZE, fp);
    sscanf(str, "%*[^\"]\"%31[^\"]\"", file_name);

    fgets(str, INPUT_SIZE, fp);
    sscanf(str, "%*s < %lf : %lf", &min_movement_duration, &max_movement_duration);

    fgets(str, INPUT_SIZE, fp);
    sscanf(str, "%*s %lf", &max_speed);

    fgets(str, INPUT_SIZE, fp);
    sscanf(str, "%*s %d", &num_bars);

    fgets(str, INPUT_SIZE, fp);
    sscanf(str, "%*s < %lf : %lf", &min_lon, &max_lon);

    fgets(str, INPUT_SIZE, fp);
    sscanf(str, "%*s < %lf : %lf", &min_lat, &max_lat);
    fclose(fp);

    printf("data_file_name \"%s\" \n"
           "movement_duration < %lf : %lf >\n"
           "maximum_speed %lf \n"
           "num_bars %d \n"
           "range_lon < %lf : %lf >\n"
           "range_lat < %lf : %lf >\n",file_name,min_movement_duration, max_movement_duration, max_speed, num_bars, min_lon, max_lon, min_lat, max_lat);
}

void update_config(){
    FILE *fp;
    fp = fopen(config_file, "w");
    if (!fp) {
        printf("Error: File not found");
        exit(1);
    }

    fprintf(fp,"data_file_name \"%s\"\n", file_name);
    fprintf(fp,"movement_duration < %lf : %lf >\n",min_movement_duration, max_movement_duration);
    fprintf(fp,"maximum_speed %lf\n",max_speed);
    fprintf(fp,"num_bars %d\n",num_bars);
    fprintf(fp,"range_lon < %lf : %lf >\n",min_lon,max_lon);
    fprintf(fp,"range_lat < %lf : %lf >\n",min_lat,max_lat);
    fclose(fp);
}

void edit_config(){
    int sub_command = 1;

    while(sub_command) {
        printf("At present the config settings are: \n"
               "data_file_name \"%s\" \n"
               "movement_duration < %lf : %lf >\n"
               "maximum_speed %lf \n"
               "num_bars %d \n"
               "range_lon < %lf : %lf >\n"
               "range_lat < %lf : %lf >\n", file_name, min_movement_duration, max_movement_duration, max_speed,
               num_bars, min_lon, max_lon, min_lat, max_lat);
        printf("What would you like to change:\n"
               "1. Data file\n"
               "2. Movement duration range\n"
               "3. Maximum speed\n"
               "4. Number of bars on graph\n"
               "5. Range of longitude\n"
               "6. Range of latitude\n"
               "0. Exit\n");

        scanf(" %d", &sub_command);
        switch(sub_command){
            case 1:
                printf("Enter new data file name:\n");
                scanf("%s",file_name);
                break;
            case 2:
                printf("Enter the new lower and upper values for the movement duration range:\n");
                scanf(" %lf  %lf", &min_movement_duration, &max_movement_duration);
                break;
            case 3:
                printf("Enter the new maximum speed\n");
                scanf(" %lf",&max_speed);
                break;
            case 4:
                printf("Enter the desired number of bars on graph:\n");
                scanf("%d",&num_bars);
                break;
            case 5:
                printf("Enter the new range for longitude");
                scanf(" %lf %lf",&min_lon,&max_lon);
                break;
            case 6:
                printf("Enter the new range for latitude");
                scanf(" %lf %lf",&min_lat,&max_lat);
                break;
            case 0:
                sub_command = 0;
                break;
            default:
                printf("Invalid input\n");
        }
    }
}

void main_menu() {
    int command = 1;
    //implement menu system
    while(command) {
        printf("1. Load a configuration file \n"
               "2. Load the data and generate the csv output file and graph plots \n"
               "3. Change the current configuration information \n"
               "4. Update the configuration file \n");
        scanf(" %d", &command);
        switch (command) {
            case 1:
                printf("Please specify config file: ");
                scanf("%s", config_file);
                load_config();
                break;
            case 2:
                process_data_file();
                break;
            case 3:
                edit_config();
                break;
            case 4:
                update_config();
                break;
            case 0:
                command = 0;
                printf("Exiting program");
                break;
            default:
                printf("invalid input, please selected input from the options menu\n");
                break;
        }
    }
}

/**
 *
 * @param filename
 */
void createTestPlot() {
    // note that gnuplot can produce an enormous range of plots and is extremely
    // configurable. See http://www.gnuplot.info/documentation.html
    char filename[] = "test_plot.gnuplot";

    int sizex = 1024;
    int sizey = 768;

    // note all these items need double quotes around them in the output
    // so they have been added here
    char charttitle[] = "\"This is an example GnuPlot using vectors\"";
    char plot1title[] = "\"test data sequence\"";
    char xlabel[] = "\"horizontal axis\"";
    char ylabel[] = "\"vertical axis\"";
    char cblabel[] = "\"3rd axis (colour)\"";

    FILE* datafile;

    // create the output file for writing
    if ((datafile = fopen(filename, "w")) == NULL) {
        printf("Cannot open output file.\n");
        exit(1);
    }

    // set up the output to produce an svg file output - lots of other possibilities
    fprintf(datafile, "set terminal svg noenhanced linewidth 0.75 size %i,%i\n", sizex, sizey);

    //set the file to save the graph into (without this it goes to the terminal)
    fprintf(datafile, "set output \"%s.svg\"\n", filename);

    // set the chart title
    fprintf(datafile, "set title %s\n", charttitle);

    //make the axis scale sutomatically based on the range of the data
    fprintf(datafile, "set autoscale\n");

    //set the axis labels and make them visible
    fprintf(datafile, "set xlabel %s\nshow xlabel\n", xlabel);
    fprintf(datafile, "set xlabel %s\nshow ylabel\n", xlabel);

    // set the colour banding label
    fprintf(datafile, "set cblabel %s\n", cblabel);

    // define a set of colours, and the values for those colours
    // the colours mix proportionately for values between those specified
    fprintf(datafile, "set palette defined (0 \"black\", 2.5 \"blue\", 5 \"red\", 10 \"yellow\")\n");

    // plot a set of vectors i.e. (startx, starty, lengthx, lengthy)
    // '-' means the data follows in the file (it could also be in an external file)
    // nohead means no arrows on the lines
    // linecolor palette z means use the data item after the vector to produce the colour
    fprintf(datafile, "plot '-' with vectors nohead linecolor palette z title %s\n", plot1title);

    // draw a spiral shape...
    for (int i=1; i<10; i++){
        fprintf(datafile, "%i, %i, %i, %i, %f\n", i, i-1, 0, 21-(i*2),(double)i/2);
        fprintf(datafile, "%i, %i, %i, %i, %f\n", i, 20-i, 20-(i*2),0,(double)i/2);
        fprintf(datafile, "%i, %i, %i, %i, %f\n", 20-i, 20-i, 0, -(20-(i*2)),(double)i/2);
        fprintf(datafile, "%i, %i, %i, %i, %f\n", 20-i, i, -(19-(i*2)), 0,(double)i/2);
    }
    fclose(datafile);
}

int main(int argc, char *argv[]) {

    createTestPlot();
    system("gnuplot test_plot.gnuplot" );
//    if(argc == 1) {
//        main_menu();
//    }
//    if (argc == 2) {
//        strcpy(config_file,argv[1]);
//        load_config();
//        process_data_file();
//    }

    return 0;

}
