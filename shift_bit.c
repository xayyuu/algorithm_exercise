#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
 

//  shift the rightest n'th bit to the leftest bit
void rightrot(int *x, int n)
{
	// get number like "0111 1111 1111 1111 ...."
	unsigned tmp = 0;
	unsigned left = 01;
	left = ~left;
	unsigned maxf = ~0;
  	while ( left != maxf )
	{
  		tmp = left;
 		left = (left << 1) | 0x1;
 	}
	left = tmp;
 
	unsigned right ;
	while( n-- ){
		// get the rightest bit of x
		right  = 01;
		right = right & (*x);
 
		(*x) = (*x) >> 1;
		if( right )
			(*x) = (*x) | ( left + 1);
		else
			(*x) = (*x) & left;
 
	}

}

unsigned get_bits_num(void)
{
	 // get os's bits
	unsigned bits_num = 1;
	unsigned tmp = ~0;
	while( (tmp = tmp << 1) )
		bits_num++;
	//printf("%u\n", bits_num);

	return bits_num;
}

void rightrot_new(int* x, unsigned n)
{
	unsigned bits_num = get_bits_num();

	(*x) = ((*x) << (bits_num - n )) | ((*x)>> n);
}
 
void leftrot_new(int *x, unsigned n)
{
	unsigned bits_num = get_bits_num();
	(*x) = ( ( (*x) >> (bits_num -n ))  & (~( ~0 << n)) ) | ((*x) << n);  
}

int main()
{

	int   x = 8;
	unsigned   n  = 3;
	leftrot_new(&x, n);
	printf("%x\n", x);

	system("pause");
	return 0;
}
 
