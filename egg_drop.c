#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "egg.h"

int get_next_floor(int current, int max, int eggs)
{
	unsigned int next_drop = 0;
	next_drop = (max - current) / eggs;
	return next_drop;
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
	
	printf("Were going to throw some eggs out the window!\nLets start from the ground floor\n\n");
	
	while ( num_eggs > 0 )
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
				printf("Were on floor: %d throwing egg #%d \n", curr_floor, atoi(argv[2]));
				 
			}while ( !egg_is_broken(new_egg) && (curr_floor < max_floor)  );
			//Once loop breaks it'll be on the secret floor
			destroy_egg(new_egg);
			break;
		}
		else if (num_eggs > 1)
		{
			printf("We have a few eggs to work with\n\n");
			while ( !egg_is_broken(new_egg) )
			{
				printf("Throwing egg #%d\n", (atoi(argv[2]) - num_eggs + 1));
				next_drop = get_next_floor(curr_floor, max_floor, num_eggs);
				egg_drop_from_floor(new_egg, (curr_floor + next_drop));
				
				if ( egg_is_broken(new_egg) )
				{
					printf("Egg == CRACKED! at floor %d\n", curr_floor + next_drop);
					//If egg is broken, and step is one, therefore it is the secret floor. 
					if(next_drop <= 1)
					{
						//This allows loop to exit if on secret floor with eggs remaining.
						num_eggs = 1;
						break;
					}
					max_floor = curr_floor + next_drop + 1;
				}
				else
				{
					curr_floor += next_drop;
					//If the number of eggs prevents the division for next drop to be at least 1.
					if (next_drop < 1)
						curr_floor += 1;
					printf("Safe to move up to floor %d \n", curr_floor);
				}
				
				num_guess++; 
			}
			num_eggs--;
			destroy_egg(new_egg);
		}
	}
	printf("We are safe from floor %d after %d\n",
				  (curr_floor != 1)? curr_floor - 1: curr_floor, num_guess);
}
