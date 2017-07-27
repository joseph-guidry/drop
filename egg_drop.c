#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
	if ( (argc < 3) || (atoi(argv[1]) < 1) || (atoi(argv[2]) < 1))
	{
		fprintf(stderr, "usage error|%s [# of Floors] [# of Eggs]\nFloors greater than zero\nEggs greater than zero\n", argv[0]);
		exit(1);
	}
	
	unsigned int start_floor = 1;
	unsigned int max_floor = atoi(argv[1]);
	unsigned int num_eggs = atoi(argv[2]);
	
	
	
	printf("here\neggs: %d\nfloors: %d\n", num_eggs, max_floor);
	
	
}
