/*
	binary search algrithom 
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define RETURN_UNFOUND -1
#define RAND_MAX_  100

#define DEBUG(i) {printf("DEBUG ....%d\n", (i));}

int bisearch(int *ary, int begin, int end, int val);
int test_bisearch(void);


int main()
{
	int times = 10;
	
	while (times-- > 0)
	{
		test_bisearch();
	}
	printf("my bisearch is SUCCESS.\n");
	
	return 0;
	
}

int test_bisearch(void)
{
	srand((unsigned)time(NULL));
	int max = rand()%(RAND_MAX_+1);
	int i ;
	
	/* allocate  mem for array[] */
	int *ary = (int *) malloc (sizeof(int)*max);
	if (ary == NULL)
	{
		printf("error in malloc\n");
		exit(-1);
	}
	
	for (i = 0; i < max; i++)
	{
		ary[i] = i+1;
	}
	
	for (i = 0; i < max; i++)
	{
		assert( bisearch(ary, 0, max-1, i+1) == i ); 
		assert( bisearch(ary, 0, max-1, i) != i ); 
		assert( bisearch(ary, 0, max-1, max+1+i) == RETURN_UNFOUND);
	}
	
	free (ary);
}

int bisearch(int *ary, int begin, int end, int val)
{
	if (ary == NULL)
		return RETURN_UNFOUND;
	if (begin < 0 || end < 0)
		return RETURN_UNFOUND;
	
 	int mid;
 	
	while (begin <= end)
	{
		/* DEBUG(1); */
		mid = begin + (end-begin)/2;
		if (ary[mid] == val)
		{
			return mid;
		}
		else if (val > ary[mid])
		{
			/* DEBUG(2); */
			begin = mid+1;
		}
		else
		{
			/*DEBUG(3);*/
			end = mid-1;
		}
	}
	
	return RETURN_UNFOUND;
	
}
