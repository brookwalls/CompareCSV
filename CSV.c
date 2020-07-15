#include "dbg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define X 312
#define Y 350

// this function will make the value being compare have the same format
				
void format_string(char []);

int main(void)
{
	// declaring file called signal
	FILE * signal;
	
	// declaring file called mode
	FILE * mode;
	
	printf("CSV File Report:\n");
	
	// opened signal file and set it to signal
	signal = fopen("interceptor-pin.csv", "rw");
	
	// if opening the signal file didn't work 
	if (!signal)
	{
		
		// error message
		printf("Signal file failed to open!\n");
		
		// if error exits the code
		exit(1);
		
	}
	
	else
	{
		
		// signal file opened correctly 
		//printf("Signal file was opened!\n");
		
	}
	
	
	// opened mode file and set it to mode
	mode = fopen("target-pin-edit.csv", "rw");
	
	// if opening the mode file didn't work 
	if (!mode)
	{
		
		// error message
		printf("Mode file failed to open!\n");
		
		// if error exits the code
		exit(2);
		
	}
	
	else
	{
		
		// mode file opened correctly
		//printf("Mode file was opened!\n");
		
	}
	
	// saved signal file to an array
	char signal_line[X][Y];
	
	// saved mode file to an array
	char mode_line[X][Y];
	
	// used to count total number of lines in the file
	int k = 0;
	
	// total number of lines in the signal file
	int signal_total = 0;
	
	// total number of lines in the mode file
	int mode_total = 0;
	
	// goes line by line, counts how many lines have imformation
	while(fgets(signal_line[k], X, signal))
	{
		k++;
	}
	
	// saves total number of lines to 313
	signal_total = k;
	
	// sets k back to 0
	k = 0;
	
	// will go throught the mode file and counter how many lines
	while(fgets(mode_line[k], X, mode))
	{
		k++;
	}
	
	// saves total number of lines to 253
	mode_total = k;
	
	// counter will be used to keep track of ball matches
	int counter_ball = 0;
	
	// counter will be used to keep track of whole matches
	int counter = 0;
	
	// used to seperate the information in each line
	int z = 0;
	
	// the , represents column dividers
	char delim[] = ",";
	
	// array holds information thats in a line in the mode file
	char * mode_part[5];
	
	// temporary holds the information in a line in the mode file
	char * mode_ptr;
	
	// array holds information thats in a line in the signal file
	char * signal_part[4];
	
	// temporary holds the information in a line in the signal file
	char * signal_ptr;
	
	// hold the information so the orginal stays the same
	char *save_s = malloc(60 * sizeof(char));
	
	// hold the information so the orginal stays the same
	char *save_m = malloc(60 * sizeof(char)); 
  
  	// length of signal file line
  	int line_length_s = 0;
  
  	// length of mode file line
  	int line_length_m = 0;
  	
  	// flag1 initialised to zero used for comparing both files
  	int flag1 = 0;
  	
  	// flag2 initialised to zero used for comparing both files
  	int flag2 = 0;
  	
  	// flag2 initialised to zero used for comparing both files
  	int flag3 = 0;
  	
  /* 
     It is going throught the signal file line by line and comparing    		 each line to every line in the mode file.
  */ 
	for(int i = 2; i < signal_total - 1; i++)
	{
		// counter is set back to 0
		counter = 0;
		
		// ball counter is set back to 0
		counter_ball = 0;
		
		// finds the length of signal file line
		line_length_s = (sizeof(signal_line[i]));
	
		// save the line information to save_s
		memcpy(save_s, signal_line[i], line_length_s);
		
		// save part 0 of the line to signal_ptr
		signal_ptr = strtok(save_s, delim);
		
		// this will set each column of inforation to an array
		for(int y = 0; y <= 4; y++)
		{
			
			// this sets the signal_ptr information to another array so it can used later
			signal_part[y] = signal_ptr;
			
			// sets the origial array to NULL
			signal_ptr = strtok(NULL, delim);
		}
		
		/*
		  Values being compared:
		  signal_part[0] is where the ball name is in interceptor
		  signal_part[1] is where the signal is in interceptor
		  mode_part[1] is where the ball name is in target
		  mode_part[4] is where the mode signal is in target
		*/
		

		/* 
		   go throught the mode file line by line 
		   trying to find the mode that is equal to the signal 
		*/
		for(int j = 2; j < mode_total ; j++)
		{
			
			// find the length of the mode file line
			line_length_m = (sizeof(mode_line[j]));		
		
			// saves the information of mode line to save_m
			memcpy(save_m, mode_line[j], line_length_m);
			
			// saves part 0 of mode line to mode_ptr
			mode_ptr = strtok(save_m, delim);	
			
			for(int x = 0; x <= 5; x++)
			{
				// this sets the signal_ptr information to another 					   array so it can used later
				mode_part[x] = mode_ptr;
			
				// sets part of the original array to NULL
				mode_ptr = strtok(NULL, delim);
			}
	
			/* 
			   this will make sure that none of the values that 					are being compared are NULL
			*/	
			if ((signal_part[0] != NULL) && (signal_part[1] != NULL) && (mode_part[1] != NULL) && (mode_part[4] != NULL))
			{
				// this makes the value being compare have the same format
				format_string(signal_part[0]);
				format_string(signal_part[1]);
				format_string(mode_part[1]);
				format_string(mode_part[4]);
				
				// sets flag1 to 0
				flag1 = 0;
				
				// goes through string character by character until null
				for(int loop = 0; (*((signal_part[0]) + loop) != '\0') || (*((mode_part[1]) + loop) != '\0'); loop++)
				{
					// makes sure string are the same length
					if ((*((signal_part[0]) + loop) == '\0') && (*((mode_part[1]) + loop) != '\0')  || (*((signal_part[0]) + loop) != '\0') && (*((mode_part[1]) + loop) == '\0'))
					{
						// sets flag1 to 1 which mean not equal
						flag1 = 1;
					}
					// make sure the char values are equal
					else if(*((signal_part[0]) + loop) != *((mode_part[1]) + loop))
					{
						// sets flag1 to 1 which mean not equal
						flag1 = 1;
					}
					
					
				}
				// goes in loop if same ball
				if (flag1 == 0)
				{
					counter_ball++;
					// sets flag2 to zero
					flag2 = 0;
					
					// goes through string by characters until null
					for(int loop2 = 0; (*((signal_part[1]) + loop2) != '\0') && (*((mode_part[4]) + loop2) != '\0'); loop2++)
					{
						// makes sure char values are equal
						if(*((signal_part[1]) + loop2) != *((mode_part[4]) + loop2))
						{
							// sets flag2 to 1, not equal
							flag2 = 1;
						}
					}
					// goes in loop if same signal mode 
					if (flag2 == 0)
					{
						// increment counter
						counter++;	
						
					}
					// signal doesn't match mode
					else 
					{
						// prints out that is was an incomplete match
						printf("Ball:%s Signal:%s doesn't match %s Mode:%s\n", signal_part[0], signal_part[1], mode_part[1], mode_part[4]);				
				
					}
					
				}
				
			    // went through mode file and multiple full matches
				if ((j == (mode_total - 1)) && (counter >= 2))
				{
					printf("Ball:%s Signal:%s found multiple matching modes\n", signal_part[0], signal_part[1]);
					
				}
				
				// went through mode file and multiple ball matches
				if ((j == (mode_total - 1)) && (counter_ball >= 2) && !(counter >= 2))
				{
					printf("Ball:%s Signal:%s found multiple matching balls with differnt modes\n", signal_part[0], signal_part[1]);
					
				}
				
				// signal only has one matching mode
				if ((j == (mode_total - 1)) && (counter == 1))
				{
					//printf("Ball: %s Signal: %s only found one match! The matching mode was printed out above.\n", signal_part[0], signal_part[1]);
				}
				
				// went through mode file and no matches
				if ((j == (mode_total - 1)) && (counter == 0) && (counter_ball == 0))
				{
					//printf("Ball: %s Signal: %s couldn't find a matching mode!\n", signal_part[0], signal_part[1]);
					
				}
				
			}
			
			// if values are NULL it will return "Hit NULL value."
			else
			{
				// prints out NULL value found
			    printf("Hit NULL value.\n");
				
			}
			
			// tells you if it finished going through the inner loop
			if (j == mode_total - 1)
			{
				//printf("Went throught innner loop mode!\n");
			}
			
			
		}
		
		// tells you if it finished going through the outter loop
		if (i == signal_total - 2)
		{
			//printf("Went all the way throught outter loop signal!\n");
		}
	
	}
	
		//sets flag1 back to zero
  	flag1 = 0;
  	
  	//sets flag2 back to zero
  	flag2 = 0;
  	
  	// skips a line
		printf("\n");
	
    // going through next file
		printf("NEXT FILE\n");
	
	// skips a line
	printf("\n");
	
	// initialize d to zero
	int d = 0;
	
	// initialize in to zero
	int in = 0;
	
	// saves the ball name of the onces who have multiple matches
	char * ball_match[X][Y];
	
	// saves the signal name of the onces who have multiple matches
	char * signal_match[X][Y];
	
	/* 
        It is going throught the mode file line by line and comparing    		     	each line to every line in the signal file
  */ 
  for(int i = 2; i < (mode_total); i++)
	{
		// sets counter back to zero
		counter = 0;
		
		//sets counter_ball back to zero
		counter_ball = 0;
		
		// saves mode line information to save_m so it dosen't change the original.
		memcpy(save_m, mode_line[i], line_length_m);
		
		// save part one of the mode line information to mode_ptr
		mode_ptr = strtok(save_m, delim);
		
		// this will set each column of inforation to an array
		for(int y = 0; y <= 5; y++)
		{
			// this sets the signal_ptr information to another array so it can used later
			mode_part[y] = mode_ptr;
			
			// sets the origial array to NULL
			mode_ptr = strtok(NULL, delim);
		}
			
		/*
		  Values being compared:
		  mode_part[1] is where the ball name is in target
		  mode_part[4] is where the mode signal is in target
		  signal_part[0] is where the ball name is in interceptor
		  signal_part[1] is where the signal is in interceptor
		*/
		
		
		
		/* 
		   go throught the mode file line by line 
		   trying to find the mode that is equal to the signal 
		*/
		for(int q = 2; q <= signal_total - 1; q++)
		{
			
			// save signal line information to save_s
			memcpy(save_s, signal_line[q], line_length_s);
			
			// save signal line information to save_s, double check
			save_s = signal_line[q];
			
			// save part zero signal line informationn to signal_ptr
			signal_ptr = strtok(save_s, delim);
			
			for(int x = 0; x <= 4; x++)
			{
				// this sets the signal_ptr information to another 					   array so it can used later
				signal_part[x] = signal_ptr;
				
				// sets part of the original array to NULL
				signal_ptr = strtok(NULL, delim);
			}
			
			/* 
			   this will make sure that none of the values that 					are being compared are NULL
			*/	
			if ((mode_part[1] != NULL) && (mode_part[4] != NULL) && (signal_part[0] != NULL) && (signal_part[1] != NULL))
			{
				// this makes the value being compare have the same format
				format_string(signal_part[0]);
				format_string(signal_part[1]);
				format_string(mode_part[1]);
				format_string(mode_part[4]);
				
				//sets flag1 back to 0
				flag1 = 0;
				
				// goes through string by characters until null
				for(int loop = 0; (*((signal_part[0]) + loop) != '\0') || (*((mode_part[1]) + loop) != '\0'); loop++)
				{
					// makes sure string are the same length
					if ((*((signal_part[0]) + loop) == '\0') && (*((mode_part[1]) + loop) != '\0')  || (*((signal_part[0]) + loop) != '\0') && (*((mode_part[1]) + loop) == '\0'))
					{
						// sets flag1 to 1 which mean not equal
						flag1 = 1;
					}
					if(*((signal_part[0]) + loop) != *((mode_part[1]) + loop))
					{
							// sets flag1 to 1 which mean not equal
							flag1 = 1;
					}
					// makes sure char values match
					
				}
				// goes in loop if same ball
				if (flag1 == 0)
				{
					
					// increments ball counter
					counter_ball++;
					//sets flag2 to zero
					flag2 = 0;
					
					// goes through string by characters until null
					for(int loop2 = 0; (*((signal_part[1]) + loop2) != '\0') || (*((mode_part[4]) + loop2) != '\0'); loop2++)
					{
						if ((*((signal_part[1]) + loop2) == '\0') && (*((mode_part[4]) + loop2) != '\0')  || (*((signal_part[1]) + loop2) != '\0') && (*((mode_part[4]) + loop2) == '\0'))
						{
							// sets flag1 to 1 which mean not equal
							flag2 = 1;
						}
						// check if char value match
						if(*((signal_part[1]) + loop2) != *((mode_part[4]) + loop2))
						{
							// sets flag1 to 1 which mean not equal
							flag2 = 1;
						}
					}
					
					// goes in loop if mode signal match
					if (flag2 == 0)
					{
			
						// increments ball counter
						counter++;
					}
					
					// signal doesn't match mode
					else 
					{
						
						printf("Ball:%s Mode:%s doesn't match %s Signal:%s\n", mode_part[1], mode_part[4], signal_part[0], signal_part[1]);				
						
					}
				
				}
				
				// sets flag3 to zero
				flag3 = 0;
			 
			  // went through signal file and check if actual multiple matches
				if ((q == (signal_total - 1)) && (counter >= 2) && (in == 0))
				{
					*ball_match[d] = signal_part[0];
					*signal_match[d] = signal_part[1];
					
					if (i == 123)
					{
						
						for (int a = 0; a <= d; a++)
						{
							for(int b = 1; b < a; b++)
							{
								for(int loop3 = 0; (*(*(ball_match[a]) + loop3) != '\0') || (*(*(ball_match[b]) + loop3) != '\0'); loop3++)
								{
									// makes sure string are the same length
									if ((*(*(ball_match[a]) + loop3) == '\0') && (*(*(ball_match[b]) + loop3) != '\0')  || (*(*(ball_match[a]) + loop3) != '\0') && (*(*(ball_match[b]) + loop3) == '\0'))
									{
										// sets flag1 to 1 which mean not equal
										flag3 = 1;
									}
									// makes sure char values match
									else if(*(*(ball_match[a]) + loop3) != *(*(ball_match[b]) + loop3))
									{
										// sets flag1 to 1 which mean not equal
										flag3 = 1;
									}
					
								}
								
								if (flag3 == 0)
								{
									//Do not print anything
								}
								else
								{
								printf("Ball:%s Mode:%s found multiple matching signals\n", *ball_match[a], *signal_match[a]);
								}
							}
							
						}
					}
					
				d++;
				in++;	
				}
				
				
				if ((q == (signal_total - 1)) && (counter_ball >= 2) && (counter == 0))
				{
					printf("Ball:%s Mode:%s found matching balls with different signals!\n", mode_part[1], mode_part[4]);
				}
				
				// went through mode file and no matches
				if ((q == (signal_total - 1)) && (counter == 0) && (counter_ball == 0))
				{
					if ((*(mode_part[1]) != '\0') && (*(mode_part[4]) != '\0'))
					{
						printf("Ball:%s Mode:%s couldn't find a matching ball or signal!\n", mode_part[1], mode_part[4]);
					}
				}
				
			}
			
			// if values are NULL it will move on to the next signal
			else
			{
				// prints out NULL value found
			    printf("Hit NULL value.\n");
				
			}
			
			// tells you if it finished going through the inner loop
			if (q == signal_total - 1)
			{
				
				//printf("Went throught innner loop mode!\n");
				
			}
			
			
		}
		
		// tells you if it finished going through the outter loop
		if (i == mode_total - 1)
		{
			
			//printf("Went all the way throught outter loop mode!\n");
			
		}
	
	}
	
	
}

// makes sure the value being compare are in the same format
void format_string(char s[])
{
	// initialised c to zero
	int c = 0;
	
	// initialised line to _
	char line = '_';
	
	// stays in loop untill char is black
	while(s[c] != '\0')
	{	
		// check to see if char is undercase
		if(s[c] >= 'a' && s[c] <= 'z')
		{
			// changes the value to uppercase
			s[c] = (s[c] - 32);
			
		}
		// check to see that char is not a letter or number
		if(!(s[c] >= 'A' && s[c] <= 'Z') && !(isdigit(s[c])))
		{	
			// checks to see if char is [
			if(s[c] == '[');
			{
				// changes char from [ to _
				s[c] = line;
				
			}
			// check to see if the current char is _ and the next one is N
			if(((s[c] == '_') && (s[c + 1]) == 'N'))
			{
				// changes the current char to N
				s[c] = 'N';
				
				// changes the next char to blank
				s[c + 1] = '\0';
			}
		}
		// check to see that char is not a letter number or _
		if(!(s[c] >= 'A' && s[c] <= 'Z') && !(s[c] == line) && !(isdigit(s[c])))
		{
			// check to see that char is ]
			if(s[c] == ']');
			{
				// changes ] to blank
				s[c] = '\0';
			}
		}
		
		// check to see if the current char is 0 and the next one is N
		if((s[c] == '0') && (s[c + 1] == 'N'))
		{
			// changes 0 to N
			s[c] = 'N';
			// changes N to 0
			s[c + 1] = '0';
			
		}
		
		// check to see if the current char is 0 and the next one is n
		if((s[c] == '0') && (s[c + 1] == 'n'))
		{
			// changes 0 to N
			s[c] = 'N';
			// changes n to 0
			s[c + 1] = '0';
			
		}
		
		// check to see if the current char is 1 and the next one is N
		if((s[c] == '1') && (s[c + 1] == 'N'))
		{
			// changes 1 to N
			s[c] = 'N';
			// changes N to 1
			s[c + 1] = '1';
			
		}
		
		// check to see if the current char is 1 and the next one is _ and the one after is N
		if((s[c] == '1') && (s[c + 1] == '_') && (s[c + 2] == 'N'))
		{
			// changes 1 to N
			s[c] = 'N';
			// changes _ to 1
			s[c + 1] = '1';
			// changes N to blank
			s[c + 2] = '\0';
			
		}
		
		// check to see if the current char is 0 and the next one is _ and the one after is N
		if((s[c] == '0') && (s[c + 1] == '_') && (s[c + 2] == 'N'))
		{
			// changes 0 to n
			s[c] = 'N';
			// changes _ to 0
			s[c + 1] = '0';
			// changes N to blank
			s[c + 2] = '\0';
			
		}
		if((s[c] == '_') && (s[c + 1] == 'T') && (s[c + 2] == 'M') && (s[c + 3] == 'S') && (s[c + 4] == '\0'))
		{
			// change to T
			s[0] = 'T';
			// change to M
			s[1] = 'M';
			// change to S
			s[2] = 'S';
			// change to blank
			s[3] = '\0';
			// change to blank
			s[4] = '\0';
			// change to blank
			s[c] = '\0'; 
			// change to blank
			s[c + 1] = '\0';
			// change to blank
			s[c + 2] = '\0'; 
			// change to blank
			s[c + 3] = '\0'; 
			// change to blank
			s[c + 4] = '\0'; 
		}
		
		if((s[c] == '_') && (s[c + 1] == 'T') && (s[c + 2] == 'D') && (s[c + 3] == 'I') && (s[c + 4] == '\0'))
		{
			// change to T
			s[0] = 'T';
			// change to M
			s[1] = 'D';
			// change to S
			s[2] = 'I';
			// change to blank
			s[3] = '\0';
			// change to blank
			s[4] = '\0';
			// change to blank
			s[c] = '\0'; 
			// change to blank
			s[c + 1] = '\0';
			// change to blank
			s[c + 2] = '\0'; 
			// change to blank
			s[c + 3] = '\0'; 
			// change to blank
			s[c + 4] = '\0'; 
		}
		
		if((s[c] == '_') && (s[c + 1] == 'T') && (s[c + 2] == 'D') && (s[c + 3] == 'O') && (s[c + 4] == '\0'))
		{
			// change to T
			s[0] = 'T';
			// change to M
			s[1] = 'D';
			// change to S
			s[2] = 'O';
			// change to blank
			s[3] = '\0';
			// change to blank
			s[4] = '\0';
			// change to blank
			s[c] = '\0'; 
			// change to blank
			s[c + 1] = '\0';
			// change to blank
			s[c + 2] = '\0'; 
			// change to blank
			s[c + 3] = '\0'; 
			// change to blank
			s[c + 4] = '\0'; 
		}
		
		if((s[c] == 'N') && (s[c + 1] == 'N') && (s[c + 2] == 'M') && (s[c + 3] == 'I') && (s[c + 4] == '\0'))
		{
			// change to T
			s[c] = 'A';
			// change to M
			s[c + 1] = 'M';
			// change to S
			s[c + 2] = '4';
			// change to blank
			s[c + 3] = '3';
			// change to blank
			s[c + 4] = '7';
			// change to blank
			s[c + 5] = 'X';
			// change to blank
			s[c + 6] = '_';
			// change to blank
			s[c + 7] = 'N'; 
			// change to blank
			s[c + 8] = 'M';
			// change to blank
			s[c + 9] = 'I'; 
			// change to blank
			s[c + 10] = 'N';  
		}
		
		if((s[c] == '_') && (s[c + 1] == 'T') && (s[c + 2] == 'C') && (s[c + 3] == 'K') && (s[c + 4] == '\0'))
		{
			// change to T
			s[0] = 'T';
			// change to M
			s[1] = 'C';
			// change to S
			s[2] = 'K';
			// change to blank
			s[3] = '\0';
			// change to blank
			s[4] = '\0';
			// change _ to blank
			s[c] = '\0'; 
			// change T to blank
			s[c + 1] = '\0';
			// change C to blank
			s[c + 2] = '\0'; 
			// change K to blank
			s[c + 3] = '\0'; 
	
		}
		
		if((s[c] == 'A') && (s[c + 1] == 'T') && (s[c + 2] == 'A') && (s[c + 3] == '_') && (s[c + 4] == 'P') && (s[c + 5] == '\0'))
		{
			// change A to P
			s[c] = 'P';
			// change to blank
			s[c + 1] = '\0';
			// change to blank
			s[c + 2] = '\0';
			// change to blank
			s[c + 3] = '\0';
			// change to blank
			s[c + 4] = '\0';
			
		}
		
		if((s[c] == 'L') && (s[c + 1] == 'K') && (s[c + 2] == '_') && (s[c + 3] == 'P') && (s[c + 4] == '\0'))
		{
			// change L to K
			s[c] = 'K';
			// change K to blank
			s[c + 1] = '\0';
			// change _ to blank
			s[c + 2] = '\0';
			// change P to blank
			s[c + 3] = '\0';
		}
		// ask if same
		if((s[c] == '1') && (s[c + 1] == '_') && (s[c + 2] == 'D') && (s[c + 3] == 'P') && (s[c + 4] == '\0'))
		{
			// change D to P
			s[c + 2] = 'P';
			// change P to blank
			s[c + 3] = '\0';
		}
		
		if((s[c] == '0') && (s[c + 1] == '_') && (s[c + 2] == 'P') && (s[c + 3] == '\0'))
		{
		
			// change _ to blank
			s[c + 1] = '\0';
			// change P to blank
			s[c + 2] = '\0'; 
			
		}
		
		if((s[c] == 'D') && (s[c + 1] == 'T') && (s[c + 2] == '0') && (s[c + 3] == '\0'))
		{
			// change 0 to blank
			s[c + 2] = '\0';
		}
		
		if((s[c] == 'R') && (s[c + 1] == 'T') && (s[c + 2] == 'S') && (s[c + 3] == '\0'))
		{
			// change blank to N
			s[c + 3] = 'N';
			// change to blank
			s[c + 4] = '\0';
		}
		
		if((s[c] == '_') && (s[c + 1] == 'C') && (s[c + 2] == 'L') && (s[c + 3] == 'K') && (s[c + 4] == '_') && (s[c + 5] == 'N') && (s[c + 6] == '\0'))
		{
			// change _ to N
			s[c] = 'N';
			// change C to blank
			s[c + 1] = '\0';
			// change L to blank
			s[c + 2] = '\0';
			// change K to blank
			s[c + 3] = '\0';
			// change _ to blank
			s[c + 4] = '\0';
			// change N to blank
			s[c + 5] = '\0';
		}
		
		if((s[c] == 'N') && (s[c + 1] == 'T') && (s[c + 2] == 'R') && (s[c + 3] == 'S') && (s[c + 4] == 'T') && (s[c + 5] == '\0'))
		{
			// change N to X
			s[c] = 'X';
			// change T to J
			s[c + 1] = 'J';
			// change R to T
			s[c + 2] = 'T';
			// change S to A
			s[c + 3] = 'A';
			// change T to G
			s[c + 4] = 'G';
			// change blank to _
			s[c + 5] = '_';
			// change blank to R
			s[c + 6] = 'R';
			// change blank to S
			s[c + 7] = 'S';
			// change blank to T
			s[c + 8] = 'T';
			// change blank to N
			s[c + 9] = 'N';
	
		}
		if((s[c] == '_') && (s[c + 1] == 'C') && (s[c + 2] == 'L') && (s[c + 3] == 'K') && (s[c + 4] == '_') && (s[c + 5] == 'N') && (s[c + 6] == '\0'))
		{
			// change _ to N
			s[c] = 'N';
			// change C to blank
			s[c + 1] = '\0';
			// change L to blank
			s[c + 2] = '\0';
			// change K to blank
			s[c + 3] = '\0';
			// change _ to blank
			s[c + 4] = '\0';
			// change N to blank
			s[c + 5] = '\0';
		}
		
		if((s[c] == '_') && (s[c + 1] == 'n') && (s[c + 2] == 'c') && (s[c + 3] == 'k') && (s[c + 4] == '\0'))
		{
			// change _ to N
			s[c] = 'N';
			// change n to blank
			s[c + 1] = '\0';
			// change c to blank
			s[c + 2] = '\0';
			// change k to blank
			s[c + 3] = '\0';
		}
		
		if((s[c] == 'S') && (s[c + 1] == '1') && (s[c + 2] == '_') && (s[c + 3] == 'P') && (s[c + 4] == '\0'))
		{
			// change _ to blank
			s[c + 2] = '\0'; 
			// change P to blank
			s[c + 3] = '\0'; 
		}
		
		if((s[c] == '1') && (s[c + 1] == '_') && (s[c + 2] == 'D') && (s[c + 3] == 'M') && (s[c + 4] == '\0'))
		{
			// change _ to blank
			s[c] = 'N'; 
			// change _ to blank
			s[c + 1] = '1'; 
			// change P to blank
			s[c + 2] = '\0'; 
			// change P to blank
			s[c + 3] = '\0'; 
		}
		
		if((s[c] == '2') && (s[c + 1] == '_') && (s[c + 2] == 'C') && (s[c + 3] == 'T') && (s[c + 4] == 'S') && (s[c + 5] == 'N') && (s[c + 6] == '\0'))
		{
			// change N to blank
			s[c + 5] = '\0'; 
		}
		//ME ME ME ME
		if((s[c] == 'D') && (s[c + 1] == 'A') && (s[c + 2] == 'T') && (s[c + 3] == 'A') && (s[c + 4] == '_') && (s[c + 5] == 'N') && (s[c + 6] == '\0'))
		{
			// change C to blank
			s[c + 1] = 'M';
			// change L to blank
			s[c + 2] = '\0';
			// change K to blank
			s[c + 3] = '\0';
			// change _ to blank
			s[c + 4] = '\0';
			// change N to blank
			s[c + 5] = '\0';
		}
		
		if((s[c] == 'Z') && (s[c + 1] == 'n') && (s[c + 2] == '\0'))
		{
			// change n to blank
			s[c + 1] = '\0'; 
		}
		if((s[c] == '_') && (s[c + 1] == '\0'))
		{
			// changes _ to blank
			s[c] = '\0';
			
		}
		// increment c
		c++;
	}
	
}


