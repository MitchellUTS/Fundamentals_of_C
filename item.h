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
    int member1;
    char member2;
};
typedef struct item item_t;

void print_item(item_t item);
void create_item(item_t* item);
int validate_item(item_t* item);