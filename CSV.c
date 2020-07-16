#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define X 312
#define Y 350

// this function will deal with format and special cases
void format_string(char []);

int main(void)
{
	// declare file signal
	FILE * signal;
	
	// declare file mode
	FILE * mode;
	
	// print CSV File Report
	printf("CSV File Report:\n");
	
	// open interceptor file and set it to signal
	signal = fopen("interceptor-pin.csv", "rw");
	
	// if opening the interceptor file did not work 
	if (!signal)
	{
		
		// error message
		printf("Signal file failed to open!\n");
		
		// if error exits the code
		exit(1);
		
	}
	
	// opened target file and set it to mode
	mode = fopen("target-pin-edit.csv", "rw");
	
	// if opening the target file did not work 
	if (!mode)
	{
		
		// error message
		printf("Mode file failed to open!\n");
		
		// if error exits the code
		exit(2);
		
	}
	
	// declare char string signal_line 
	char signal_line[X][Y];
	
	// declare char string mode_line
	char mode_line[X][Y];
	
	// declare int k and initialize to zero
	int k = 0;
	
	// declare int signal_total and initialize to zero 
	int signal_total = 0;
	
	// declare int mode_total and initialize to zero
	int mode_total = 0;
	
	// goes line by line in the signal file
	while(fgets(signal_line[k], X, signal))
	{
		// keeps count of how many lines are in the signal file
		k++;
	}
	
	// saves total number of lines k to signal_total
	signal_total = k;
	
	// sets k back to 0
	k = 0;
	
	// goes line by line in the mode file
	while(fgets(mode_line[k], X, mode))
	{
		// keeps count of how many lines are in the mode file
		k++;
	}
	
	// saves total number of lines k to mode_total
	mode_total = k;
	
	// declare int counter_ball and initialize to zero 
	int counter_ball = 0;
	
	// declare int counter and initialize to zero 
	int counter = 0;
	
	// declare int z and initialize to zero 
	int z = 0;
	
	// declare char delim and initialize to , 
	char delim[] = ",";
	
	// declare string mode_part
	char * mode_part[5];
	
	// declare string mode_ptr
	char * mode_ptr;
	
	// declare string signal_part
	char * signal_part[4];
	
	// declare string signal_ptr
	char * signal_ptr;
	
	// declare string save_s
	char *save_s = malloc(60 * sizeof(char));
	
	// declare string save_m
	char *save_m = malloc(60 * sizeof(char)); 
  
  // declare int line_length_s and initialize to zero
  int line_length_s = 0;
  
  // declare int line_length_m and initialize to zero 
  int line_length_m = 0;
  	
  // declare int flag1 and initialize to zero 
  int flag1 = 0;
  	
  // declare int flag2 and initialize to zero 
  int flag2 = 0;
  	
  // declare int flag3 and initialize to zero 
  int flag3 = 0;
  	
  /* 
     The function goes through the signal file line by line and compares   				each line to every line in the mode file.
  */ 
	for(int i = 2; i < signal_total - 1; i++)
	{
		// sets counter back to zero
		counter = 0;
		
		// sets counter_ball back to zero
		counter_ball = 0;
		
		// finds the length of the signal line and saves it to line_length_s
		line_length_s = (sizeof(signal_line[i]));
	
		// saves signal_line[i] to save_s
		memcpy(save_s, signal_line[i], line_length_s);
		
		// saves part 0 of save_s to signal_ptr
		signal_ptr = strtok(save_s, delim);
		
		// sets each part of save_s to an array
		for(int y = 0; y <= 4; y++)
		{
			
			// sets signal_ptr to signal_part[y]
			signal_part[y] = signal_ptr;
			
			// sets the next part to signal_ptr and the origial to NULL
			signal_ptr = strtok(NULL, delim);
		}
		
		/*
		  Values being compared:
		  signal_part[0] is the ball name in interceptor
		  signal_part[1] is the signal in interceptor
		  mode_part[1] is the ball name in target
		  mode_part[4] is the mode signal in target
		*/
		
		/* 
     The function goes through the mode file and compares every line in the mode file to each line in the signal file.
  	*/
		for(int j = 2; j < mode_total ; j++)
		{
			// finds the length of the mode line and saves it to line_length_m
			line_length_m = (sizeof(mode_line[j]));		
		
			// saves mode_line[j] to save_m
			memcpy(save_m, mode_line[j], line_length_m);
			
			// save part zero of save_m to mode_ptr
			mode_ptr = strtok(save_m, delim);	
			
			// sets each part of save_m to an array
			for(int x = 0; x <= 5; x++)
			{
				// sets mode_ptr to mode_part[x]
				mode_part[x] = mode_ptr;
				
				// sets the next part to mode_ptr and the origial to NULL
				mode_ptr = strtok(NULL, delim);
			}
	
			 
			// checks that none of the values being compared are NULL
			if ((signal_part[0] != NULL) 
				&& (signal_part[1] != NULL) 
				&& (mode_part[1] != NULL) 
				&& (mode_part[4] != NULL))
			{
				// puts the values in the same format and deals with special cases
				format_string(signal_part[0]);
				format_string(signal_part[1]);
				format_string(mode_part[1]);
				format_string(mode_part[4]);
				
				// sets flag1 back to zero
				flag1 = 0;
				
				// goes through string character by character until NULL
				for(int loop = 0; (signal_part[0][loop] != '\0') || (mode_part[1][loop] != '\0'); loop++)
				{
					
					// checks that the strings are the same length
					if ((signal_part[0][loop] == '\0') 
						&& (mode_part[1][loop] != '\0')  
						|| (signal_part[0][loop] != '\0') 
						&& (mode_part[1][loop] == '\0'))
					{
						// sets flag1 to 1 which mean the strings are not equal
						flag1 = 1;
					}
					
					// make sure the char values are equal
					else if(signal_part[0][loop] != mode_part[1][loop])
					{
						// sets flag1 to 1 which mean the strings are not equal
						flag1 = 1;
					}	
				}
				
				// if the signal and mode ball match
				if (flag1 == 0)
				{
					// increment counter_ball
					counter_ball++;
					
					// sets flag2 back to zero
					flag2 = 0;
					
					// goes through string character by character until NULL
					for(int loop2 = 0; (signal_part[1][loop2] != '\0') && (mode_part[4][loop2] != '\0'); loop2++)
					{
						
						// makes sure char values are equal
						if(signal_part[1][loop2] != mode_part[4][loop2])
						{
							// sets flag2 to 1 which means the strings are not equal
							flag2 = 1;
						}
					}
					
					// if the signal and mode match
					if (flag2 == 0)
					{
						// increment counter
						counter++;	
					}
					
					// signal doesn't match mode
					else 
					{
						// prints out the incomplete match
						printf("Ball:%s Signal:%s doesn't match %s Mode:%s\n", signal_part[0], signal_part[1], mode_part[1], mode_part[4]);				
					}
					
				}
				
				// finished going through the mode file
				//if (j == (mode_total - 1))
				
				
				
			
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
			}
			
			// if values being compared are NULL
			else
			{
				// prints out "Hit NULL value"
			  printf("Hit NULL value.\n");
			}
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
	
	// declare int d and initialize to zero
	int d = 0;
	
	// declare int in and initialize to zero
	int in = 0;
	
	// declare string ball_match
	char * ball_match[X][Y];
	
	// declare string signal_match
	char * signal_match[X][Y];
	
	/* 
     The function goes through the mode file line by line and compares   				each line to every line in the signal file.
  */ 
  for(int i = 2; i < (mode_total); i++)
	{
		// sets counter back to zero
		counter = 0;
		
		//sets counter_ball back to zero
		counter_ball = 0;
		
		// saves mode_line[i] to save_m
		memcpy(save_m, mode_line[i], line_length_m);
		
		// save part zero of save_m to mode_ptr
		mode_ptr = strtok(save_m, delim);
		
		// sets each part of save_m to an array
		for(int y = 0; y <= 5; y++)
		{
			// sets mode_ptr to mode_part[y]
			mode_part[y] = mode_ptr;
			
			// sets the next part to mode_ptr and the origial to NULL
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
     The function goes through the signal file and compares every line in the mode file to each line in the mode file.
  	*/ 
		for(int q = 2; q <= signal_total - 1; q++)
		{
			// saves signal_line[q] to save_s
			memcpy(save_s, signal_line[q], line_length_s);
			
			// saves signal_line[q] to save_s, double check
			save_s = signal_line[q];
			
			// save part zero of save_s to signal_ptr
			signal_ptr = strtok(save_s, delim);
			
			// sets each part of save_s to an array
			for(int x = 0; x <= 4; x++)
			{
				// sets signal_ptr to signal_part[x]
				signal_part[x] = signal_ptr;
				
				// sets the next part to signal_ptr and the origial to NULL
				signal_ptr = strtok(NULL, delim);
			}
			
			// checks that none of the values being compared are NULL	
			if ((mode_part[1] != NULL) 
				&& (mode_part[4] != NULL) 
				&& (signal_part[0] != NULL) 
				&& (signal_part[1] != NULL))
			{
				// puts the values in the same format and deals with special cases
				format_string(signal_part[0]);
				format_string(signal_part[1]);
				format_string(mode_part[1]);
				format_string(mode_part[4]);
				
				//sets flag1 back to 0
				flag1 = 0;
				
				// goes through string character by characters until NULL
				for(int loop = 0; (signal_part[0][loop] != '\0') || (mode_part[1][loop] != '\0'); loop++)
				{
					// makes sure string are the same length
					if ((signal_part[0][loop] == '\0') 
						&& (mode_part[1][loop] != '\0')  
						|| (signal_part[0][loop] != '\0') 
						&& (mode_part[1][loop] == '\0'))
					{
						// sets flag1 to 1 which means the strings are not equal
						flag1 = 1;
					}
					if(signal_part[0][loop] != mode_part[1][loop])
					{
							// sets flag1 to 1 which means the strings are not equal
							flag1 = 1;
					}
					
				}
				
				// if the signal and mode ball match
				if (flag1 == 0)
				{
					
					// increments ball_counter
					counter_ball++;
					
					//sets flag2 back to zero
					flag2 = 0;
					
					// goes through string character by character until NULL
					for(int loop2 = 0; (signal_part[1][loop2] != '\0') || (mode_part[4][loop2] != '\0'); loop2++)
					{
						if ((signal_part[1][loop2] == '\0') 
							&& (mode_part[4][loop2] != '\0')  
							|| (signal_part[1][loop2] != '\0') 
							&& (mode_part[4][loop2] == '\0'))
						{
							// sets flag1 to 1 which means the strings are not equal
							flag2 = 1;
						}
						
						// check if char value match
						if(signal_part[1][loop2] != mode_part[4][loop2])
						{
							// sets flag1 to 1 which means the strings are not equal
							flag2 = 1;
						}
					}
					
					// goes in loop if mode and signal match
					if (flag2 == 0)
					{
			
						// increments counter
						counter++;
					}
					
					// signal doesn't match mode
					else 
					{	
						printf("Ball:%s Mode:%s doesn't match %s Signal:%s\n", mode_part[1], mode_part[4], signal_part[0], signal_part[1]);				
					}
				
				}
				
				// sets flag3 back to zero
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
								for(int loop3 = 0; (*ball_match[a][loop3] != '\0') || (*ball_match[b][loop3] != '\0'); loop3++)
								{
									// makes sure string are the same length
									if ((*ball_match[a][loop3] == '\0') 
										&& (*ball_match[b][loop3] != '\0')  
										|| (*ball_match[a][loop3] != '\0') 
										&& (*ball_match[b][loop3] == '\0'))
									{
										// sets flag1 to 1 which mean the strings are not equal
										flag3 = 1;
									}
									// makes sure char values match
									else if(ball_match[a][loop3] != ball_match[b][loop3])
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
				
				// mode ball couldn't find a matching ball in the signal file
				if ((q == (signal_total - 1)) && (counter == 0) && (counter_ball == 0))
				{
					if ((*mode_part[1] != '\0') && (*mode_part[4] != '\0'))
					{
						printf("Ball:%s Mode:%s couldn't find a matching ball or signal!\n", mode_part[1], mode_part[4]);
					}
				}
				
			}
			
			// if values are NULL
			else
			{
				// prints out Hit NULL value
			    printf("Hit NULL value.\n");
				
			}
		}
	}
}

// puts the values in the same format and deals with special cases
void format_string(char s[])
{
	// declare c and initialised c to zero
	int c = 0;
	
	// declare line and initialised line to _
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
		if(!(s[c] >= 'A' 
			&& s[c] <= 'Z') 
			&& !(isdigit(s[c])))
		{	
			// checks to see if char is [
			if(s[c] == '[');
			{
				// changes char from [ to _
				s[c] = line;
				
			}
			// if the end of the current string is _N
			if(((s[c] == '_') && (s[c + 1]) == 'N'))
			{
				// changes the current char to N
				s[c] = 'N';
				
				// changes the next char to blank
				s[c + 1] = '\0';
			}
		}
		// if the end of the current string is AZ
		if(!(s[c] >= 'A' 
			&& s[c] <= 'Z') 
			&& !(s[c] == line) 
			&& !(isdigit(s[c])))
		{
			// check to see that char is ]
			if(s[c] == ']');
			{
				// changes ] to blank
				s[c] = '\0';
			}
		}
		
		// if the end of the current string is 0N
		if((s[c] == '0') && (s[c + 1] == 'N'))
		{
			// changes 0 to N
			s[c] = 'N';
			
			// changes N to 0
			s[c + 1] = '0';
			
		}
		
		// if the end of the current string is 0n
		if((s[c] == '0') && (s[c + 1] == 'n'))
		{
			// changes 0 to N
			s[c] = 'N';
			
			// changes n to 0
			s[c + 1] = '0';
			
		}
		
		// if the end of the current string is 1N
		if((s[c] == '1') && (s[c + 1] == 'N'))
		{
			// changes 1 to N
			s[c] = 'N';
			
			// changes N to 1
			s[c + 1] = '1';
		}
		
		// if the end of the current string is 1_N
		if((s[c] == '1') 
			&& (s[c + 1] == '_') 
			&& (s[c + 2] == 'N'))
		{
			// changes 1 to N
			s[c] = 'N';
			
			// changes _ to 1
			s[c + 1] = '1';
			
			// changes N to blank
			s[c + 2] = '\0';
		}
		
		// if the end of the current string is 0_N
		if((s[c] == '0') 
			&& (s[c + 1] == '_') 
			&& (s[c + 2] == 'N'))
		{
			// changes 0 to n
			s[c] = 'N';
			
			// changes _ to 0
			s[c + 1] = '0';
			
			// changes N to blank
			s[c + 2] = '\0';
		}
		
		// if the end of the current string is _TMS 
		if((s[c] == '_') 
			&& (s[c + 1] == 'T') 
			&& (s[c + 2] == 'M') 
			&& (s[c + 3] == 'S') 
			&& (s[c + 4] == '\0'))
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
		// if the end of the current string is _TDI
		if((s[c] == '_') 
			&& (s[c + 1] == 'T') 
			&& (s[c + 2] == 'D') 
			&& (s[c + 3] == 'I') 
			&& (s[c + 4] == '\0'))
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
		
		// if the end of the current string is _TDO
		if((s[c] == '_') 
			&& (s[c + 1] == 'T') 
			&& (s[c + 2] == 'D') 
			&& (s[c + 3] == 'O') 
			&& (s[c + 4] == '\0'))
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
		
		// if the end of the current string is NNMI
		if((s[c] == 'N') 
			&& (s[c + 1] == 'N') 
			&& (s[c + 2] == 'M') 
			&& (s[c + 3] == 'I') 
			&& (s[c + 4] == '\0'))
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
		
		// if the end of the current string is _TCK
		if((s[c] == '_') 
			&& (s[c + 1] == 'T') 
			&& (s[c + 2] == 'C') 
			&& (s[c + 3] == 'K') 
			&& (s[c + 4] == '\0'))
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
		
		// if the end of the current string is ATA_P
		if((s[c] == 'A') 
			&& (s[c + 1] == 'T') 
			&& (s[c + 2] == 'A') 
			&& (s[c + 3] == '_') 
			&& (s[c + 4] == 'P') 
			&& (s[c + 5] == '\0'))
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
		
		// if the end of the current string is LK_P
		if((s[c] == 'L') 
			&& (s[c + 1] == 'K') 
			&& (s[c + 2] == '_') 
			&& (s[c + 3] == 'P') 
			&& (s[c + 4] == '\0'))
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
		
		// if the end of the current string is 1_DP
		if((s[c] == '1') 
			&& (s[c + 1] == '_') 
			&& (s[c + 2] == 'D') 
			&& (s[c + 3] == 'P') 
			&& (s[c + 4] == '\0'))
		{
			// change D to P
			s[c + 2] = 'P';
			
			// change P to blank
			s[c + 3] = '\0';
		}
		
		// if the end of the current string is 0_P
		if((s[c] == '0') 
			&& (s[c + 1] == '_') 
			&& (s[c + 2] == 'P') 
			&& (s[c + 3] == '\0'))
		{
			// change _ to blank
			s[c + 1] = '\0';
			
			// change P to blank
			s[c + 2] = '\0'; 
		}
		
		// if the end of the current string is DT0
		if((s[c] == 'D') 
			&& (s[c + 1] == 'T') 
			&& (s[c + 2] == '0') 
			&& (s[c + 3] == '\0'))
		{
			// change 0 to blank
			s[c + 2] = '\0';
		}
		
		// if the end of the current string is RTS
		if((s[c] == 'R') 
			&& (s[c + 1] == 'T') 
			&& (s[c + 2] == 'S') 
			&& (s[c + 3] == '\0'))
		{
			// change blank to N
			s[c + 3] = 'N';
			
			// change to blank
			s[c + 4] = '\0';
		}
		
		// if the end of the current string is _CLK_N
		if((s[c] == '_') 
			&& (s[c + 1] == 'C') 
			&& (s[c + 2] == 'L') 
			&& (s[c + 3] == 'K') 
			&& (s[c + 4] == '_') 
			&& (s[c + 5] == 'N') 
			&& (s[c + 6] == '\0'))
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
		
		// if the end of the current string is NTRST
		if((s[c] == 'N') 
			&& (s[c + 1] == 'T') 
			&& (s[c + 2] == 'R') 
			&& (s[c + 3] == 'S') 
			&& (s[c + 4] == 'T') 
			&& (s[c + 5] == '\0'))
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
		
		// if the end of the current string is _CLK_N
		if((s[c] == '_') 
			&& (s[c + 1] == 'C') 
			&& (s[c + 2] == 'L') 
			&& (s[c + 3] == 'K') 
			&& (s[c + 4] == '_') 
			&& (s[c + 5] == 'N') 
			&& (s[c + 6] == '\0'))
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
		
		// if the end of the current string is _nck
		if((s[c] == '_') 
			&& (s[c + 1] == 'n') 
			&& (s[c + 2] == 'c') 
			&& (s[c + 3] == 'k') 
			&& (s[c + 4] == '\0'))
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
		
		// if the end of the current string is S1_P
		if((s[c] == 'S') 
			&& (s[c + 1] == '1') 
			&& (s[c + 2] == '_') 
			&& (s[c + 3] == 'P') 
			&& (s[c + 4] == '\0'))
		{
			// change _ to blank
			s[c + 2] = '\0'; 
			// change P to blank
			s[c + 3] = '\0'; 
		}
		
		// if the end of the current string is 1_DM
		if((s[c] == '1') 
			&& (s[c + 1] == '_') 
			&& (s[c + 2] == 'D') 
			&& (s[c + 3] == 'M') 
			&& (s[c + 4] == '\0'))
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
		
		// if the end of the current string is 2_CTSN
		if((s[c] == '2') 
			&& (s[c + 1] == '_') 
			&& (s[c + 2] == 'C') 
			&& (s[c + 3] == 'T') 
			&& (s[c + 4] == 'S') 
			&& (s[c + 5] == 'N') 
			&& (s[c + 6] == '\0'))
		{
			// change N to blank
			s[c + 5] = '\0'; 
		}
		
		// if the end of the current string is DATA_N
		if((s[c] == 'D') 
			&& (s[c + 1] == 'A') 
			&& (s[c + 2] == 'T') 
			&& (s[c + 3] == 'A') 
			&& (s[c + 4] == '_') 
			&& (s[c + 5] == 'N') 
			&& (s[c + 6] == '\0'))
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
		
		// if the end of the current string is Zn
		if((s[c] == 'Z') 
			&& (s[c + 1] == 'n') 
			&& (s[c + 2] == '\0'))
		{
			// change n to blank
			s[c + 1] = '\0'; 
		}
		
		// if the end of the current string is _
		if((s[c] == '_') && (s[c + 1] == '\0'))
		{
			// changes _ to blank
			s[c] = '\0';
			
		}
		
		// increment c
		c++;
	}
	
}
