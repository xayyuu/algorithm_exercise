
 
#include <stdio.h>
#include <stdlib.h>
typedef struct _NODE
{
	int n;
	struct _NODE * next;
}node, *pnode;

void create_list_head(pnode *L, int a[], int len)
{
	*L = (pnode ) malloc(sizeof( node ));
	(*L)->next = NULL;

	pnode tmp = *L;

	int i = 0;
	while(i < len)
	{
		pnode pnew = (pnode)malloc( sizeof(node) );
		pnew->n = a[i];
		pnew->next = tmp->next;
		tmp->next =pnew;
		i++;
	}
}

void  create_list_rear(pnode *L, int a[], int len)
{
	*L = (pnode) malloc (sizeof(node));
	(*L)->next = NULL;

	pnode tmp = *L;

	int i = 0; 
	while( i < len )
	{
		pnode pnew = (pnode) malloc( sizeof(node) );
		pnew->n = a[i];
		pnew->next = NULL;

		tmp->next = pnew;
		tmp = tmp->next;
		i++;
	}

}

void print_list(pnode *L)
{
	pnode tmp = (*L)->next;
	while( tmp != NULL )
	{
		printf("%d\t", tmp->n);
		tmp = tmp->next;
	}
	printf("\n");
}

void free_list(pnode *L)
{
	pnode tmp = (*L)->next ;
	 

	while( tmp != NULL)
	{
		(*L)->next = tmp->next;
		free(tmp);
		tmp = (*L)->next;
	}

	free(*L);
	L = NULL;
}
		


int main()
{
	int a[] = {3, 4, 2, 1, 9, 6, 5};
	pnode L = NULL;
	create_list_head(&L, a, sizeof(a)/sizeof(int));
	print_list(&L);
	free_list(&L);
	create_list_rear(&L, a, sizeof(a)/sizeof(int));
	print_list(&L);
	free_list(&L);

	system("pause");
	return 0;

}
 