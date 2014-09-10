#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>


#define MAXLEN  30
/* hanoi tower */
void hanoi(int last, int src, int mid, int dst)
{
	if(last <= 0)
		return ;
	hanoi(last-1, src, dst, mid);
	printf("move the %d hanoi to %d position\n", last, dst);
	hanoi(last-1,  mid, src, dst);
}

/* find the max number of the int array */
int max_int(int *a, int i, int len)
{
	assert(i >= 0);
	if( i == len-1)
		return a[i];
	int temp  = max_int(a, i+1, len);
	if( a[i] < temp )
		return temp;
	else
		return a[i];
}


/* 分书问题，5本书，5个人，其阅读兴趣如二维数组like[i][j]= {1（i喜欢j书）， 0（i不喜欢j书）｝
*/

int like[5][5] = {  {0, 0, 1, 1, 0},
					{1, 1, 0, 0, 1},
					{0, 1, 1, 0, 1},
					{0, 0, 0, 1, 0},
					{0, 1, 0, 0, 1}
};
					
int booked[5] = {0};
int book_taken[5] = {0};

void try_allocate_book(int person)
{
	assert(person >= 0);
 
	if(person == 5)
	{
		int i;
		for(i = 0; i < 5; i++)
			printf("%d person---> %d book\n", i, book_taken[i]);
		printf("\n\n");
		return ;
	}
	int j ;
	for(j = 0; j < 5; j++)
	{
		if( booked[j] == 1 || like[person][j] == 0)
			continue;
		else
		{
			booked[j] = 1;
			book_taken[person] = j;
			try_allocate_book(person+1);
			booked[j] = 0;
			book_taken[person] = 0;
		}
		

	}
}


/* 走台阶， 从楼上走到楼下共有h个台阶，每一步有三种走法：
		走一个台阶
		走二个台阶
		走三个台阶
		问可以走多少种方案
	这是一个很明显的递归问题，既可以用分治法，也可以用回溯法，这里使用回溯法解题
*/
int steps[MAXLEN] = {0};
int step_num = 0;
void try_step(int init, int high)
{
	assert(high >= 0);
	int step ;
	for(step = 1; step <= 3; step++)
	{
		if(init  >  high)
			return ;
		else if(init == high)
		{
			int j = 0;
 
			for(j = 0; j <  step_num; ++j)
				printf("%d\t",  steps[j]);
			printf("\n");
			return;
		}
		else
		{
		 
			steps[step_num] = step;
			step_num++;
			try_step(init+step, high);
			steps[step_num] = 0;
			step_num--;
		}
	}
}

/* 八皇后问题，经典回溯习题 */
#define N 8
#define DIAGONAL (2*(N)-1)
int queen_row[N]  = {0}; /* 第i行的queen放在第几列 */
int column[N] = {0}; /* 用来判断第j列是否有元素, 0表示没有 */
int down[DIAGONAL] = {0};
int up[DIAGONAL] = {0};

void try_nqueens(int row)
{
	
	int  j;
	for( j = 0; j < N; j++)
	{
		if( column[j] || down[row-j+7] || up[row+j-2] )
			continue;
		int k;
		column[j] = 1;
		down[row-j+7] = 1;
		up[row+j-2] = 1;
		queen_row[row] = j;
		if(row == 7)
		{
			for(k = 0; k < 8; k++)
				printf("%d\t", queen_row[k]);
			printf("\n");
		}
		else
			try_nqueens(row+1);
		column[j] = 0;
		down[row-j+7] = 0;
		up[row+j-2] = 0;
		queen_row[row] = 0;
	}
}

/* 单词全排列， 这个代码从清华大学谌(chen)卫军老师的ppt转载过来
	输入boy, 输出boy, byo ....
	输入bob,输出bob, bbo,obb
	*/
#define MAXSIZE 20
void TryChar(char *word, int i, int length);
int CharFlag[MAXSIZE] = {0};
int CharTaken[MAXSIZE] = {0};

void TryChar(char *word, int i, int length)
{
	int j, k;
	for(j = 1; j <= length; j++)
	{
		if(CharFlag[j] ) continue;
		for(k = 1; k < j; k++)
		{
			if(!CharFlag[k])
				if(word[k-1] == word[j-1]) 
					break;
		}
		if( k < j) continue;
		CharTaken[i] = j;
		CharFlag[j] = 1;
		if(i == length)
		{
			for(k=1; k <= length; k++)
				printf("%c", word[CharTaken[k]-1]);
			printf("\n");
		}
		else
			TryChar(word, i+1, length);
		CharTaken[i] = 0;
		CharFlag[j] = 0;
	}
}

int main()
{

	srand((unsigned int)time(NULL));
	// hanoi(5, 1, 2, 3);

	//int i;
	//int a[MAXLEN];
	//int times = 0;
	//scanf("%d", &times);
	//if( times <= 0)
	//	return EXIT_FAILURE;
	//while(times--)
	//{
	//	for( i = 0; i < MAXLEN; ++i)
	//		a[i]  =  rand()%(MAXLEN*10);

	//	for(i = 0; i  < MAXLEN; ++i)
	//		printf("%d\t", a[i]);
	//	printf("\t: max %d\n", max_int(a, 0, MAXLEN));
	//}

	// try_allocate_book(0);

	//int i;
	//for(i = 0; i < 6; ++i)
	//{
	//	printf("when %d steps:\n", i);
	//	try_step(0, i);
	//	printf("end\n");
	//}

	// try_nqueens(0);

	char word[MAXSIZE];
	int length;
	printf("请输入一个单词: ");
	scanf("%s", word);
	length = strlen(word);
	TryChar(word, 1, length);
	

	return EXIT_SUCCESS;
}