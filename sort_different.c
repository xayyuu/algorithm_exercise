#ifdef _WIN32 || _WIN64

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include  <cmath >
#include <time.h>
#include <Windows.h>

// 堆排序 http://zh.wikipedia.org/wiki/堆排序
//  不稳定会带来什么坏处？当key为多级数据时，前一级的不稳定排序可能导致后面几级的数据顺序发生变化，引入误差
int parent(int);
int left(int);
int right(int);
void Max_Heapify(int [], int, int);
void Build_Max_Heap(int [], int);
 void HeapSort(int [], int);
 
/*父結點*/
int parent(int i)
{
    return (int)floor((i - 1) / 2);
}
 
/*左子結點*/
int left(int i)
{
    return (2 * i + 1);
}
 
/*右子結點*/
int right(int i)
{
    return (2 * i + 2);
}
 
/*單一子結點最大堆積樹調整*/
void Max_Heapify(int A[], int i, int heap_size)
{
    int l = left(i);
    int r = right(i);
    int largest;
    int temp;
    if(l < heap_size && A[l] > A[i])
    {
        largest = l;
    }
    else
    {
        largest = i;
    }
    if(r < heap_size && A[r] > A[largest])
    {
        largest = r;
    }
    if(largest != i)
    {
        temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;
        Max_Heapify(A, largest, heap_size);
    }
}
 
/*建立最大堆積樹*/
void Build_Max_Heap(int A[],int heap_size)
{
    for(int i = (heap_size-2)/2; i >= 0; i--)
    {
        Max_Heapify(A, i, heap_size);
    }
}
 
 
 
/*堆積排序程序碼*/
void HeapSort(int A[], int heap_size)
{
    Build_Max_Heap(A, heap_size);
    int temp;
    for(int i = heap_size - 1; i >= 0; i--)
    {
        temp = A[0];
        A[0] = A[i];
        A[i] = temp;
        Max_Heapify(A, 0, i);
    }
 }

void print_array(int a[], int len)
{
	int i;
	for(i = 0; i < len; i++)
		printf("%d\t", a[i]);
	printf("\n");
}





int find_center(int a[], int left, int right)
{
	int i = left;
	int j = right;

	int pivot = a[i];
	while(i < j)
	{
		while( i < j && a[j] >= pivot )
			j--;
		a[i] = a[j];
		while(i < j && a[i] < pivot )
			i++;
		a[j] = a[i];
	}

	a[i] = pivot;
	return i;

}

// 当数据量太大的时候，递归会导致栈溢出，最好用非递归的形式实现快排
void quick_sort(int a[], int left,  int right)
{
	if( left < right)
	{
		int center = find_center(a, left, right);
		quick_sort(a, left, center);
		quick_sort(a, center+1, right);
		
	}
}

// o(nlog(n))
void merge_array(int *list1, int list1_size, int *list2, int list2_size)
{
    int i, j, k;
    i = j = k = 0;
 
    // 声明临时数组用于存储归并结果
    int *list = (int *) malloc((list1_size + list2_size)*sizeof(int));
 
    // note: 只要有一个数组到达了尾部就要跳出
    // 也就是说只有两个都没有到达尾部的时候才执行这个循环
    while (i < list1_size && j < list2_size)
    {
        // 把较小的那个数据放到结果数组里， 同时移动指针
        list[k++] = list1[i] > list2[j] ? list1[i++] : list2[j++];
    }
 
    // 如果 list1 还有元素，把剩下的数据直接放到结果数组
    while (i < list1_size)
    {
        list[k++] = list1[i++];
    }
 
    // 如果 list2 还有元素，把剩下的数据直接放到结果数组
    while (j < list2_size)
    {
        list[k++] = list2[j++];
    }
 
    // 把结果数组 copy 到 list1 里
    for (int ii = 0; ii < (list1_size + list2_size); ++ii)
    {
        list1[ii] = list[ii];
    }
    free(list);
 
}
 
void merge_sort(int *a, int len)
{
	 if( len > 1 )
	 {
		 int *a1 = a;
		 int len1 = len/2;
		 int *a2 = a+len1;
		 int len2 = len - len1;
		 merge_sort(a1, len1);
		 merge_sort(a2, len2);

		 merge_array( a1, len1,  a2, len2);
	 }

}

void merge_array_v2(int *a, int left, int middle, int right, int *temp)
{
 
	int i = left;
	int j = middle+1;

	int k = 0;
	while( i <= middle && j <= right )
	{
		temp[k++] = a[i] < a[j] ? a[i++] : a[j++];
	}

	while( i <= middle )
		temp[k++]  = a[i++];
	while(j <= right )
		temp[k++] = a[j++];

	
	for(i = 0; i < k ; i++)
		a[left+i] = temp[i];  //  write like that is wrong: for(i =0 ; i < right; i++)  a[i] = temp[i]; 

}

void merge_sort_v2(int *a, int left, int right, int *temp)
{
	if( left  <  right )
	{
		
		int middle = (left+right)/2;
 
		merge_sort_v2(a, left, middle, temp);
		merge_sort_v2(a, middle+1, right, temp);
 		merge_array_v2(a, left, middle, right, temp);
	}
}

void swap_by_point(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
 
void select_sort(int a[], int len)
{
	int i,j;
	int min;
	for(i = 0; i < len; i++)
	{
		min = i;
		for(j = i+1; j < len; j++)
			if( a[j] < a[min] )
				min = j;
		swap_by_point(&(a[min]), &(a[i]));
	}
}

 
void insert_sort(int a[], int len)
{
	int i, j ;

	int temp;

	// o(n^2), 第一种方法
	// int k;
	//for(i = 0; i < len; i++)
	//{
	//	for(j = 0; j < i ; j++)
	//	{
	//		if( a[i] < a[j] )
	//		{
	//			temp = a[i];
	//			for(k = i; k > j && k > 0; k-- )
	//				a[k] = a[k-1];
	//			swap_by_point(&(a[j]), &(temp));
	//		}
	//	}
	//}

	// o(n^2)， 第二种方法
	for(i = 1; i < len; i++)
	{
		j  = i - 1;
		temp = a[i];
		while( j >= 0 && a[j] > temp )
		{
				a[j+1] = a[j];
				j--;
		}
		a[j+1] = temp;
 
	}
}


void shell_sort(int a[], int len)
{
	int step = len/2;
	int i, j, k;

	int temp;
	while( step >= 1 )
	{

		// sort by step
		for(i = 0; i < step ; i++)
		{
			for(j = 1; j < len/step ; j++ )
			{
				k = j -1;
				temp = a[ i + j*step ];
				while( k >= 0 && a[i+k*step] > temp )
				{
					a[i+(k+1)*step] = a[i+k*step];
					k--;
				}
				a[i+(k+1)*step] = temp;
			}
		}
 
		step /= 2;
	}



}


void bubble_sort(int a[], int len )
{
	int i, j;

	// o(n^2)
	for(i = 0; i < len; i++)
		for(j = i+1; j < len; j++)
			if( a[j] < a[i] )
				swap_by_point(&(a[j]), &(a[i]));

}


#define N 3000
#define MAX_NUM 30000
int ar1[N]={0};
int ar2[N] = {0};
int  copy_array(int *dst, int dst_len, int *src, int src_len)
{
	 
	if( dst_len != src_len ) return -1;
	int i ;
	for(i  = 0; i < dst_len; i++)
		dst[i] = src[i];

	return 0;
}


double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
	printf("QueryPerformanceFrequency failed!\n");

    PCFreq = double(li.QuadPart)/1000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}
double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-CounterStart)/PCFreq;
}


double get_sort_time(int *pa, int len, void (fsort)(int * , int   ))
{
# if 0 //  计时方法1
	const clock_t begin = clock();
	 fsort(pa, len);
	 const clock_t end = clock();
	 return  (double)(end-begin)/CLOCKS_PER_SEC  ;
#endif
#if 0 // 计时方法2
	 DWORD begin = GetTickCount();
	 fsort(pa, len);
	 DWORD end = GetTickCount();

	 return end - begin;
#endif

	 StartCounter();
     fsort(pa, len);
     return  GetCounter() ;
 
}

// 最后对所有排序做个时间测评，并且做时间复杂度分析，对它们做个比较，在大数据上试验一下各种排序算法
int main()
{
	srand((unsigned int)time(NULL));

	int i;
	for(i = 0; i < N; i++)
	{
		ar2[i]=  rand()%MAX_NUM;
	}


	int len = sizeof(ar1) / sizeof(int);
	int * temp = (int *) malloc( sizeof(int) *len );

	  print_array(ar2, len);

	  copy_array(ar1, len, ar2, len);
	  printf("heap sort:  %lf\n", get_sort_time(ar1, len,  HeapSort));
	  // print_array(ar1, len);
 

	  copy_array(ar1, len, ar2, len);
	  printf("bubble sort:\t%lf\n", get_sort_time(ar1, len,  bubble_sort));
	  // print_array(ar1, len);
 

	  copy_array(ar1, len, ar2, len);
	  printf("shell_sort:\t%lf\n", get_sort_time(ar1, len,  shell_sort));
	  // print_array(ar1, len);
	 
	   copy_array(ar1, len, ar2, len);
	  printf("merge_sort:\t%lf\n", get_sort_time(ar1, len,  merge_sort));
	  // print_array(ar1, len);
	 
	   copy_array(ar1, len, ar2, len);
	  printf("inset sort:\t%lf\n", get_sort_time(ar1, len,  insert_sort));
	  // print_array(ar1, len);
	 

	  copy_array(ar1, len, ar2, len);
	  printf("select sort:\t%lf\n", get_sort_time(ar1, len,  select_sort));
	  // print_array(ar1, len);
	   
 
	  // quick sort， 当N太大了，会造成堆栈溢出的问题
	// StartCounter();
	//quick_sort(ar1, 0, len-1);
	//printf("quick sort:\t%lf\n", GetCounter());


	 // print_array(ar1, len);
 	 free(temp);
	system("pause");
	return 0;
}
 
#endif