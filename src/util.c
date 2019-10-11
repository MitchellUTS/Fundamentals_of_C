/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * 
 * Author(s):      Mitchell Lee, ...
 *  
 * Date of creation: 18/09/2019
 * 
 * Purpose: Provide a variety of core/basic functions
 * 
*******************************************************************************/

#include "core.h"

/*******************************************************************************
 * This provides a boolean answer that determines if a value is 
 * between (inclusive) a specified range.
 * inputs:
 * - char value: this is the value to test
 * - char min: this is the minium value that <value> can be and stil have the 
 *              function return true
 * - char max: this the maxium value that <value> can be and still have the 
 *              function return true
 * outputs:
 * - int: this will be true or false


 login function- Helps the system to be secure by asking the user for an username and a password.
If they are correct the system can be used and the other fuctions which are available are visible. 
*******************************************************************************/
int between(int value, int min, int max) {
    return (value >= min && value <= max);
}

int loginFunction()
{
  
  char username[20];
  char userpwd[10]; 
  
  printf("Enter your username for the IMS : ");

  scanf("%19s",username);
  
  printf("Enter your password : ");

 
/*  int i=0;
  for(i=0;i<10;i++)
  {
   userpwd[i]=getchar();
   printf("*");   	
  }
  userpwd[i]='\0';*/

  scanf("%9s", userpwd);
 
  /*printf("\n\nPress any key to continue");
  getchar();*/
 
 /* add users with their passwords here*/
 if((!strcmp(username,"admin") && !strcmp(userpwd,"fundaC")) || 
  (!strcmp(username,"student") && !strcmp(userpwd,"fundaC")) || 
  (!strcmp(username,"lecturer") && !strcmp(userpwd,"fundaC")))
 {
    printf("\nSuccessful Login\n");
    return true;
 }
  else
 {
    printf("\nIncorrect username or password\n");
    return false;
 }
}