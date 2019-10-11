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
int main(int argc, char** argv)
{
    int user_selection = 0, sort_num = -1;

    printf("%d\n", sort_num);

    /*item_node_t item_list;
    item_node_t* list = NULL;
    list = (item_node_t*) malloc(sizeof(item_node_t)); Uncomment later*/
    
    /*NODE TEST
    ((item_t*)(item_list->item_data))->ID = 1;
    ((item_t*)(item_list->item_data))->ISBN = 1234;
    ((item_t*)(item_list->item_data))->title = "Hello World";
    ((item_t*)(item_list->item_data))->author = "Programmer";
    ((item_t*)(item_list->item_data))->type = "Textbook";
    ((item_t*)(item_list->item_data))->category = "IT";
    */

    /* Continue the program until the user types '5' to exit */
    do {
        
        /* Request a selection from the user */
        print_main_menu();
        scanf("%d", &user_selection);

        /* Allow to user to re-input their selection until it is valid */
        while (user_selection < 0 || user_selection > 6) {
           	printf("Invalid choice\n");
            print_main_menu();
            scanf("%d", &user_selection);
        }

        char source[256], destination[256], password[1024];
        /* Select the function to call based on the user input */
        switch(user_selection) {
            case 1:
                printf("Enter the location of your file to encrypt> ");
                scanf("%255s", source);
                printf("Enter the location to save the encrypted file> ");
                scanf("%255s", destination);
                printf("Enter the password to encrypt the file with> ");
                scanf("%1023s", password);
                mask_file(source, destination, password);
                break;

            case 2:
                printf("Enter the location of your file to decrypt> ");
                scanf("%255s", source);
                printf("Enter the location to save the decrypted file> ");
                scanf("%255s", destination);
                printf("Enter the password to decrypt the file with> ");
                scanf("%1023s", password);
                mask_file(source, destination, password);
                break;

            case 3:
                printf("Enter the location of your file to compress> ");
                scanf("%255s", source);
                printf("Enter the location to save the compressed file> ");
                scanf("%255s", destination);
                compress_file(source, destination);
                break;
            
            case 4:
                printf("Enter the location of your file to decompress> ");
                scanf("%255s", source);
                printf("Enter the location to save the decompressed file> ");
                scanf("%255s", destination);
                decompress_file(source, destination);
                break;

                break;
            case 5:
                /* item_t* new_item = (item_t*) malloc(sizeof(item_t));
                item_node_t* new_node = (item_node_t*) malloc(sizeof(item_node_t));
                new_node->item_data = new_item;
                create_item(node, list);*/ 
                break;
            case 6: 
			    sort_num = sort_option();
				/*merge_sort(&list);*/
				break;
        }

    } while (user_selection != 0);
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
    "1. Encrypt a File\n"
    "2. Decrypt a File\n"
    "3. Compress a File\n"
    "4. Decompress a File\n"
    /*"5. Add an Item\n"
	"6. Sort Database\n"*/
    "0. Exit the Program\n"
    "Enter your choice (number between 0-6)>\n");
}

/*******************************************************************************
 * This function prints the initial menu with all instructions on how to use
 * this program.
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
int sort_option(void) {
	
	int user_selection;
	
	/* Request a selection from the user */
	print_sorting_menu();
	scanf("%d", &user_selection);
	        
	/* Allow to user to re-input their selection until it is valid */
	while (user_selection < 1 || user_selection > 5) {
		printf("Only 1 available. Enter 1\n"); /*Temporary*/
		print_sorting_menu();
		scanf("%d", &user_selection);
	}	
	
	return user_selection;
}

/*******************************************************************************
 * This function prints the initial menu with all instructions on how to use
 * this program.
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
void print_sorting_menu (void)
{
    printf("\n"
    "1. Sort by ID\n"
	"2. Sort by Title\n"
	"3. Sort by Author\n"
    "4. Sort by Type\n"
	"5. Sort by Genre\n"
    "Enter your choice (number between 1-5)>\n");
}