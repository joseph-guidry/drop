#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "egg.h"

#define SMALL_GAP 1

int get_next_floor(int current, int max, int eggs)
{
	unsigned int next_drop = 0;
	printf("eggs: %d max: %d \n", eggs, max);
	if (eggs == max)
		return 1;
	next_drop = (max - current) / eggs;
	printf("next drop %d\n", next_drop);
	return next_drop;
}

int get_max(int a, int b)
{
	if ( a < b)
		return b;
}

int main(int argc, char ** argv)
{
	//Ensure proper input including
	//that both floors and eggs are greater than 0
	if ( (argc < 3) || (atoi(argv[1]) < 1) || (atoi(argv[2]) < 1))
	{
		fprintf(stderr, "usage error|%s [# of Floors] [# of Eggs]\n \
						Floors greater than zero\nEggs greater than zero\n", argv[0]);
		exit(1);
	}
	
	unsigned int num_guess = 0, next_drop;
	unsigned int curr_floor = 0;
	unsigned int max_floor = atoi(argv[1]);
	unsigned int num_eggs = atoi(argv[2]);
	
	printf("\nWere going to throw some eggs out the window!\n\nLets start from the ground floor\n\n");
	
	while ( num_eggs > 0 && (curr_floor < max_floor) )
	{
		egg *new_egg = lay_egg();
		//Start the brute force stepping once a single egg remains
		if ( num_eggs == 1 )
		{
			printf("Lets go floor by floor\n");
			do
			{
				curr_floor++;
				num_guess++; 
				egg_drop_from_floor(new_egg, curr_floor);
				if (curr_floor <= max_floor && !egg_is_broken(new_egg) )
					printf("Were on floor: %3.0d throwing egg #%d \n", curr_floor, atoi(argv[2]));
				else
				{
					printf("Egg == CRACKED! at floor %d\n", curr_floor--);
					break;
				}
			}while ( (curr_floor < max_floor));
			
			//Decrement curr_floor to represent secret floor.
			
			
			//Once here it'll be on the secret floor and we need to clean up the broken egg.
			destroy_egg(new_egg);
			break;
		}
		else if ( (num_eggs > 1) )
		{
			printf("We have a few eggs to work with\n\n");
			while ( !egg_is_broken(new_egg) && (curr_floor <= max_floor) )
			{
				//Print the current egg number.
				printf("Throwing egg #%d from curr_floor: %d\tmax_floor: %d \n",
										 (atoi(argv[2]) - num_eggs + 1), curr_floor, max_floor);
				next_drop = get_next_floor(curr_floor, max_floor, num_eggs);
				egg_drop_from_floor(new_egg, (curr_floor + next_drop));
				
				if ( egg_is_broken(new_egg) )
				{
					printf("Egg == CRACKED! at floor %d\n", curr_floor + next_drop);
					//If egg is broken, and step is one, therefore it is the secret floor. 
					if(next_drop < 1)
					{
						//This allows loop to exit if on secret floor with eggs remaining.
						num_eggs = 1;
						curr_floor--;
						break;
					}
					max_floor = curr_floor + next_drop;
				}
				else
				{
					
					//If the number of eggs prevents the division for next drop to be less than 1.
					printf("curr %d | max %d \n", curr_floor, max_floor);
					curr_floor += next_drop;
					
					printf("curr %d | max %d \n", curr_floor, max_floor);
					
					if (next_drop < 1 && (curr_floor < max_floor))
						curr_floor += get_max( ((max_floor - curr_floor)/2), 1);
					
				}
				
				num_guess++; 
			}
			//There is a broken egg, clean up is required.
			printf("here\n");
			
			num_eggs--;
			destroy_egg(new_egg);
		}
	}
	
	printf("We are safe from the secret floor: %d after %d %s\n",
				  curr_floor, num_guess, num_guess > 1? "guesses":"guess");
}
