typedef struct _NODE{
	int nvalue;
	struct _NODE *next;
}node, *pnode; /* single link list */

/* not sorted, if you want sorted linklist, you should input sorted sequence */
/* don't have the virtual head node */
pnode insert(pnode L, int x)
{
	if( L == NULL )
	{
		L = (pnode) malloc( sizeof(node) );
		L->next = NULL;
		L->nvalue = x;
		return L;
	}
	else
	{
		pnode tmpnode = (pnode)malloc(sizeof(node));
		tmpnode->next = L;
		tmpnode->nvalue = x;
		return tmpnode;
	}
 }

pnode find_list_element(pnode L, int x)
{
	if( L == NULL )
		return NULL;

	for(; L != NULL ; L = L->next)
		if( L->nvalue == x)
			break;
	return L;
}

/* if add the virtual head node, this operation will be easyer */ 
void delete_elment(pnode *PL, int x)
{
	pnode pre, now ;
	if( PL == NULL || *PL == NULL )
		return  ;

	pre = now = (*PL);
	while( now != NULL )
	{
		if(now->nvalue == x )
		{
			if(pre == now ) /* delete the first node */
			{
				now = pre->next;
				free(pre);
				pre = now;
				*PL = now;
				return;
			}
			else
			{
				pre->next = now->next;
				free(now);
				now = pre->next;
			}
		}
		else 
		{
			pre = now;
			now = now->next;
		}
	}
 
}

void delete_list(pnode *PL)
{
	if( PL == NULL )
		return ;
	 
	pnode pnow, pnext;
	pnow = pnext = (*PL);
	while(pnow != NULL)
	{
		pnext = pnow->next;
		free(pnow);
		pnow = pnext;
	}
	*PL  =  NULL;

}

void print_list(pnode L, const char * suggest)
{
	printf("%s:\t", suggest);
	while(L != NULL)
	{
		printf("%d\t", L->nvalue);
		L= L->next;
	}
	printf("\n");
}


pnode reverse_list(pnode L)
{
	if( L == NULL || L->next == NULL)
		return L;
	pnode pend, pmid, phead;
	
	if( L->next->next == NULL )
	{
		pend = L->next;
 		L->next->next = L;
		L->next = NULL;
		return pend;
	}


	pend  = L;
	pmid = pend->next;
	phead = pmid->next;
	while( phead != NULL )
	{
		pmid->next = pend;
		pend  = pmid;
		pmid = phead;
		phead = phead->next;
	}
	pmid->next = pend;
	L->next = NULL;
 	return pmid;
	
}

/* Selection sort   */
void sort_list(pnode L)
{
	pnode pk;
	pnode pj;

	int  tmp;
	for(pk = L; pk != NULL; pk = pk->next)
	{
 		for(pj = pk->next; pj != NULL; pj = pj->next)
		{
			if( pj->nvalue < pk->nvalue)
			{
				tmp = pk->nvalue;	
				pk->nvalue = pj->nvalue;
				pj->nvalue = tmp;
			}
		}
	}

}

void compress_str(char *str, int len)
{
	if( *str == '\0' )
		return ;
	char *newstr = (char *) malloc(len*2 + 1);
	if( newstr == NULL )
	{
		printf("wrong\n");
		exit(-1) ;
	}

	char *pnew = newstr;
	char last = *str;
	int count = 1;
	
	int i;
 	for(i = 1; i <  len; ++i)
	{
		if(str[i] == last)
			count++;
		else
		{
			*pnew++ = last;
			if(*pnew == '\0')
				break;
			sprintf( pnew++ , "%d", count);
			while (count /= 10) 
				pnew++;
  			last = str[i];
			count = 1;
		}
	}
   	strcpy(str, newstr);
	free(newstr);
}

/* another way is hashtable */
static void delete_dups(pnode Head)
{
	pnode current=Head;
 	while( current != NULL)
	{
		pnode  runner = current->next;
		while(runner != NULL )
		{
			if(runner->nvalue == current->nvalue)
			{
				 pnode tmp  = runner;
				current->next = runner->next;
				runner = runner->next;
				free(tmp);
			}
			else
			{
				runner = runner->next;
			}
		}
		current = current->next;
	}
}


/* find the last k's node */
int  find_kth_node(pnode Head, int k , pnode *result )
{
 
	if(   Head == NULL )
		return 0;
  	int i = find_kth_node(Head->next,  k, result ) + 1;
 
  	if(  i == k+1 )
	{
		  *result =  Head;
 	}
	return i;

}

pnode nthTolast(pnode head, int k, int *i)
{
	if( head == NULL )
		return NULL;
	pnode nd = nthTolast(head->next, k, i);
	(*i) += 1;
	if( (*i) == k)
		return head;
	return nd;
}

int get_listlen(pnode head)
{
	int i = 0;
	while(head != NULL)
	{
		++i;
		head = head->next;
	}
	return i;
}
 
/* make the head to be  node.value < x, x , node.value > x */
void parvot(pnode head , int x )
{
	if( head == NULL ) 
		return ;
	pnode less_x  = NULL;
	pnode greater_x = NULL;
	
	pnode tmp = head;
	/* divide into two list */
	while(tmp != NULL)
	{
		if( tmp->nvalue <= x)
			less_x = insert(less_x, tmp->nvalue);
		else
			greater_x = insert(greater_x, tmp->nvalue);
		tmp = tmp->next;
	}

	/* merge two list */
	tmp = less_x;
	while(tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = greater_x;
	tmp = less_x;
	while( head != NULL && tmp != NULL)
	{
		head->nvalue = tmp->nvalue;
		head = head->next;
		tmp = tmp->next;
	}

	delete_list(&less_x);

}

		
pnode addlist(pnode L1, pnode L2)
{
	if(L1 == NULL || L2 ==NULL)
		return NULL;

	pnode result = NULL ;
	int carry = 0; /* 进位标记*/
	int sum = 0; 

	while( L1 != NULL && L2 != NULL )
	{
		sum = L1->nvalue + L2->nvalue + carry;
		carry = 0;
		if( sum >= 10)
		{
			carry = sum / 10;
			sum %= 10;
		}
		result = insert(result, sum);
		L1 = L1->next;
		L2 = L2->next;
	}
	if( L1 == NULL && L2 == NULL )
	{
		if(carry != 0)
			result = insert(result, carry);
	}

	while( L1 != NULL )
	{
		sum = carry + L1->nvalue;
		carry = 0;
		result = insert(result, sum);
		L1 = L1->next;
	}
	while( L2 != NULL )
	{
		sum = carry + L2->nvalue;
		result = insert(result, sum);
		L2 = L2->next;
	}
	
			
	return result;
}






int main()
{
	int i;
//#define STRNUM 8
//	char  str[STRNUM][50] = {"ab fggg", "   abb", "eeeeeeeeeeeff ", "  ", "\t", "eee", "jk\\","" };
//	
//	for(i = 0; i < STRNUM; ++i)
//	{
// 		compress_str(str[i], strlen(str[i])+1);
//		printf("%s\n", str[i]);
// 
//	}

#define TIMES 5
	srand((unsigned int)time(NULL));
	pnode L = NULL;
	pnode L2 = NULL;
 	for(i = 0; i < TIMES; ++i)
		L=insert(L,  rand()%10);
	for(i = 0; i < TIMES  ; ++i)
		L2=insert(L2,  rand()%10);

	pnode result = addlist(L, L2);
	print_list(L, "first");
	print_list(L2, "second");
	result = reverse_list(result);
	print_list(result, "sum");
 
	print_list(L, "before sort");
	sort_list(L);
	print_list(L, "after sort");
	delete_dups(L);
	print_list(L, "after delete_dups");

	parvot(L, 10);
	print_list(L, "after parvot");

	L = reverse_list(L);
	print_list(L, "after reverse");
 
	int want[] =  {0, 3, -11, 44};
	pnode tmp;
	for(i = 0; i < sizeof(want)/sizeof(want[0]); ++i)
	{
		  tmp =  find_list_element(L, want[i]);
		if( tmp == NULL )
			printf("%d not found\n", want[i]);
		else
			printf("input: %d\tfind: %d\n",want[i], tmp->nvalue);
	 
	}

	for(i = 1; i < 10; ++i)
	{
		delete_elment(&L, i);
		print_list(L, "delete element");
	}

	/*  test: null input, it's ok? */
	delete_list(&L);

	L=insert(L, 3);
	print_list(L, "insert element");
	delete_list(&L);


  	system("pause");
	return EXIT_SUCCESS;
}
