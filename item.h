/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * 
 * Author(s):      Mitchell Lee, ...
 *  
 * Date of creation: 18/09/2019
 * 
 * Purpose: Add all item specific functionality include the struct and basic
 *              creation and manipulation tools.
 * 
*******************************************************************************/

struct item {
    int ID;                   /*Must be unique*/
    long ISBN;
    char title[256];
    char author[256];
    char type[256];
    char category[256];
};
typedef struct item item_t;

void print_item(item_node_t* node);
void create_item(item_node_t* node, item_node_t* head);
int new_id (item_node_t* head);
void add_string (item_node_t* node, int i);
