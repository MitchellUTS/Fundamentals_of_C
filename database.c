/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * 
 * Author(s):      Mitchell Lee, ...
 *  
 * Date of creation: 18/09/2019
 * 
 * Purpose: Create a database file and some interfacing tools.
 * 
*******************************************************************************/
#include "core.h"

/*******************************************************************************
 * This function saves all items in memory to the database file as plain text.
 * inputs:
 * - item_t* items: This is an array of size MAX_NUM_itemS which will be
 *                      saved to the database. 
 * - int items_size: This is the number of items currently in the array.
 * outputs:
 * - none
*******************************************************************************/
void save_items(item_node_t* item_list) {
	FILE* file_stream;

    char format_string[] = "%-6s %-3s %02d-%02d %02d:%02d %-3s %02d-%02d %02d:%02d\n";

    /* Open/Create the file for writing text data */ 
    file_stream = fopen(DB_NAME, "w");

    /* Check if opening the file was successful */
    if (file_stream == NULL)
    	return;

    int i;
    for (i = 0; i < items_size; i++) {

        /* Print each item to the database in the same format that is used
        in the display function. */
    	fprintf(file_stream, format_string, items[i].itemcode, "SYD", 
    		items[i].departure_dt.month, items[i].departure_dt.day, 
            items[i].departure_dt.hour, items[i].departure_dt.minute,
    		items[i].arrival_city,
    		items[i].arrival_dt.month, items[i].arrival_dt.day, 
            items[i].arrival_dt.hour, items[i].arrival_dt.minute);
    }
    
    /* Always close the file after you have finished using it. */ 
    fclose(file_stream);
}

/*******************************************************************************
 * This function loads all items from the database file to memory.
 * inputs:
 * - item_t* items: This is an array of size MAX_NUM_itemS which will be
 *                      populated with records from the database. 
 * - int* items_size: This is the number of items currently in the array,
 *                      this value will be updated when the database contents
 *                      have been loaded.
 * outputs:
 * - none
*******************************************************************************/
void load_items(item_node_t* item_list) {
	FILE* file_stream;
    char format_string[] = "%6s %3s %02d-%02d %02d:%02d %3s %02d-%02d %02d:%02d\n";

    /* This is used the hold the "SYD" text from the file which is not used in
        memory*/
    char temp[MAX_CITYCODE_LEN + 1];

    /* Open the file for reading text data */
    file_stream = fopen(DB_NAME, "r");

    /* Check if opening the file was successful */
    if (file_stream == NULL) {
        printf("Read error\n");
    	return;
    }

    int i = 0;

    /* Keep reading records from the file until an invalid line is read
        or memory has been filled*/
    while (fscanf(file_stream, format_string, items[i].itemcode, temp, 
    		&items[i].departure_dt.month, &items[i].departure_dt.day, 
            &items[i].departure_dt.hour, &items[i].departure_dt.minute,
    		items[i].arrival_city,
    		&items[i].arrival_dt.month, &items[i].arrival_dt.day, 
            &items[i].arrival_dt.hour, &items[i].arrival_dt.minute) == 11 &&
            i < MAX_NUM_itemS) {
            i++;
    }

    /* Update the number of items currently in use as part of the array */
    *items_size = i;    
    
    /* Always close the file once you are no longer using it */
    fclose(file_stream);
}




void getNoOfRecords()
{
  int recordcount=0;
  for (i=0; i<sizeof(struct Book),i++)
  {
    recordcount++;
  }
  return recordcount;
}



void deleteRecord()
{
  int BookID;
  int count=0;
  
  FILE *ptr2 = fopen("c:\\database1.h","a");
  int records = getNoOfRecords();
  refresh();
  fflush(stdin);
  printf("Enter BookID:\n");
  scanf("%d",&BookID);
  while(count!=records)
  {
    fread(&var,sizeof(struct Book),1,ptr);
    if(var.BookID==BookID)
    {
    }
    else
    {
      fwrite(&var,sizeof(struct Book),1,ptr2);
    }
    count++;
  }
  fcloseall();
  remove("c:\\database.h");
  rename("c:\\database1.h","c:\\database.h");
  printf("Press any key to continue..");
  getch();
}
