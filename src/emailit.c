/*************************************/
/**  ***************/
/*** Author : Abdul Mateen ***********/

/** The Program is released under GPLv2 License ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define cknull(x) if((x)==NULL) {perror(""); exit(EXIT_FAILURE);}
#define cknltz(x) if((x)<0) {perror(""); exit(EXIT_FAILURE);}
#define LIST_LEN 4

/******************************* 
* email_it() -
*  emails the contents of a file
*  parms 
*	char *filename - file to email
*  	email recipients are in the array email_list[][] 
*   which has to be terminated with a zero-length element
********************************/

void email_it(char *filename)                                           
{                                                                       
	char tmp[256]={0x0};                                                
	char fpBuffer[512]={0x0};                                           
	char email_list[LIST_LEN][256]={  {0x0},             
							   {0x0},             
					  {0x0},         
							   {0x0}};                                  
	int i=0;                                                            
																		
	for(i=0;*email_list[i]>0x0;i++)                                
	{		                                                            
		cknull(strcpy(tmp, email_list[i]));                             
		cknltz(sprintf (fpBuffer,                                       
			"/usr/bin/mailx -s '%s %s' %s < %s",                        
			"Please Review:",                                           
			filename,                                                   
			tmp,                                                        
			filename)); 	                                            
		if(system (fpBuffer)==(-1))                                     
		{                                                               
			perror("email failure");                                    
			exit(EXIT_FAILURE);	                                        
		}                                                               
	}	                  
}
