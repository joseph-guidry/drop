#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "egg.h"

int get_next_floor(int current, int max, int eggs)
{
	unsigned int next_drop = 0;
	
	next_drop = (max - current) / eggs;
	printf("next_drop = %u \n", next_drop);
	return next_drop;
}



int main(int argc, char ** argv)
{
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
	
	
	
	//printf("here1 %d \neggs: %d\nfloors: %d\n\n",curr_floor, num_eggs, max_floor);
	
	while ( num_eggs > 0)
	{
		egg *new_egg = lay_egg();
		
		if ( num_eggs == 1 )
		{//DO BRUTEFORCE FUNCTION?
			printf("Lets go floor by floor\n");
			do
			{
				curr_floor++;
				num_guess++; 
				egg_drop_from_floor(new_egg, curr_floor);
				printf("Were on floor: %d throwing egg #%d \n", curr_floor, atoi(argv[2]));
				 
			}while ( !egg_is_broken(new_egg) );
			
			printf("We are safe from floor %d after %d\n", (curr_floor - 1), num_guess);
			destroy_egg(new_egg);
			break;
		}
		else 
		{
			printf("We have a few eggs to work with\n");
			while ( !egg_is_broken(new_egg) )
			{
				next_drop = get_next_floor(curr_floor, max_floor, num_eggs);
				egg_drop_from_floor(new_egg, (curr_floor + next_drop));
			
				if ( egg_is_broken(new_egg) )
				{
					printf("Egg == CRACKED! \n");
					max_floor = next_drop;
				}
				else
				{
					curr_floor += next_drop;
					printf("Safe to move up to floor %d \n", curr_floor);
				}
				
				num_guess++; 
			}
			num_eggs--;
			destroy_egg(new_egg);
		}
	}
}
