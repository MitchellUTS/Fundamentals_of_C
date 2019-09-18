/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * 
 * Author(s):       Mitchell Lee, ...
 *  
 * Date of creation: 18/09/2019
 * 
 * Purpose: To provide the core framework and functionality for the application.
 * 
*******************************************************************************/


#include "core.h"

/*******************************************************************************
 * Main
*******************************************************************************/
int main(void)
{
    int user_selection;

    item_node_t item_list;

    /* Continue the program until the user types '5' to exit */
    do {
        
        /* Request a selection from the user */
        print_main_menu();
        scanf("%d", &user_selection);

        /* Allow to user to re-input their selection until it is valid */
        while (user_selection < 1 || user_selection > 5) {
           	printf("Invalid choice\n");
            print_main_menu();
            scanf("%d", &user_selection);
        }

        /* Select the function to call based on the user input */
        switch(user_selection) {
            case 1: 
                add_item(&item_list);
                break;
        }

    } while (user_selection != 5);
    return 0;
}

/*******************************************************************************
 * This function prints the initial menu with all instructions on how to use
 * this program.
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
void print_main_menu (void)
{
    printf("\n"
    "1. Add an Item\n"
    "5. Exit the Program\n"
    "Enter your choice (number between 1-5)>\n");
}