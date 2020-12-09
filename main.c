/**
 * This is the main file for the project assigned in CS23820 to process sheep movement data by Robyn Vaughan-Williams
 *
 * This project can be interacted with by menu or any number of command line argument linking to config files for the program,
 * config files must follow the format of the config file in Appendix A of the project brief
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "functions.h"

//global variables used in operation of program
double min_movement_duration = 0, max_movement_duration = 604800, max_speed = 50, min_lon = 0, max_lon = 0, min_lat = 0, max_lat = 0;
int num_bars = 20;
char file_name[20];
char config_file[20];

/**
 * reads in collar data, processes data with respect to the specified constrains, graphs the processed data and outputs the processed data to the csv file
 */
void process_data_file() {
    position_node_pointer position_head = NULL;
    read_data(&position_head, file_name);
//    print_positions_list(position_head); //used for testing
    movement_node_pointer movement_head = NULL;
    generate_movement_list(position_head, &movement_head);
//    print_movement_list(movement_head); //used for testing
    plot_graphs(movement_head);
    save_movement_list(movement_head);
}

/**
 * loads the configuration file specified in the config_file variable
 */
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

/**
 * saves the config constrains currently held in the program to the config file specified in the config_file parameter
 */
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

/**
 * Through the use of a menu interface allows the user to edit the current data processing constrains held by the program
 */
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

/**
 * Main menu for use if no program is run without command line arguments
 */
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
 * main function, has options for use in command line input and menu systems
 * @param argc number of inputs
 * @param argv any number of config files for batch processing
 * @return
 */
int main(int argc, char *argv[]) {


    if(argc == 1) {
        main_menu();
    }
    for(int i = 2; i <= argc; i++){
            strcpy(config_file,argv[i-1]);
            load_config();
//            process_data_file();
    }


    return 0;

}
