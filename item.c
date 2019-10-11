/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * 
 * Author(s):      Mitchell Lee, Christopher Wong...
 *  
 * Date of creation: 18/09/2019
 * 
 * Purpose: Add all item specific functionality include the struct and basic
 *              creation and manipulation tools.
 * 
*******************************************************************************/
#include "core.h"

/*******************************************************************************
 * This function prints a item structure with a newline at the end
 * inputs:
 * - item_t* item: this is a pointer to the item that needs to be printed.
 * outputs:
 * - none
*******************************************************************************/
void print_item(item_node_t* node)
{
    char format_string[] = "%003d %l %s %s %s %s\n";

    printf(format_string, 
    		((item_t*)(current->item_data))->ID, 
			((item_t*)(current->item_data))->ISBN,
			((item_t*)(current->item_data))->title, 
			((item_t*)(current->item_data))->author, 
			((item_t*)(current->item_data))->type, 
			((item_t*)(current->item_data))->category);
}

void create_item(item_node_t* node, item_node_t* head) {

	int id = -1;
	long isbn;
	char title[256], author[256], type[256], category[256];
	
	item_t* new_item = (item_t*) malloc(sizeof(item_t));
	item_node_t* new_node = (item_node_t*) malloc(sizeof(item_node_t));
	new_node->item_data = new_item;
  
	item_node_t* last = *head; 

	printf("Enter Title:\n");
	add_string(node, 1);
	printf("Enter Author:\n");
	add_string(node, 2);
	printf("Enter Type:\n");
	add_string(node, 3);
	printf("Enter Category:\n");
	add_string(node, 4);
	
	while (id == -1) {
		id = new_id(head);
	}
	
	((item_t*)(current->item_data))->ISD == id; 
	((item_t*)(current->item_data))->ISBN == 10101010; 
	
	new_node->next = NULL; 
	
	 /* Make new node as head if linked list is empty */
	if (*head_ref == NULL) 
	{ 
	   *head_ref = new_node; 
	   return; 
	}  
	
	/*Otherwise move new node to end of the linked list*/
	while (last->next != NULL) last = last->next; 
	
	last->next = new_node; 
	return;
}

int new_id (item_node_t* head)
{
	item_node_t* current = head;
	int unavailable_id = 1;
	
	 while (current != NULL) 
	    { 
	        if (((item_t*)(current->item_data))->ID == unavailable_id) 
	            return unavailable_id; 
	        
	        current = current->next; 
	    } 
	 
	 return -1;
}

void add_string (item_node_t* node, int i) {
	
	char str[256], reset[20];
	fgets(reset, sizeof reset, stdin);

	/*Reduces input to max size of str if over*/
	fgets(str, sizeof str, stdin);
	if(!strchr(str, '\n')) {    
		while(fgetc(stdin)!='\n');
	}
	
	switch (i)  {
		case 1 : 
				strcpy(((item_t*) (node->item_data))->title, str);
				break;
		case 2 : 
				strcpy(((item_t*) (node->item_data))->author, str); 
				break;
		case 3 : 
				strcpy(((item_t*) (node->item_data))->type, str); 
				break;
		case 4 : 
				strcpy(((item_t*) (node->item_data))->category, str); 
				break;

		default : 
			printf("Error Occurred\n");
			break;	
	}
}
