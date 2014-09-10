/* stack */
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <limits.h>
#include <stddef.h>


/* use array to release stack */
#define MAXLEN 150
#define ELEMENT_TYPE double 

typedef struct _NODE
{
	ELEMENT_TYPE nvalue;
	struct _NODE * next;
}NODE, *STACK;

typedef NODE * LIST;


LIST insert(LIST head, ELEMENT_TYPE x)
{
	if( head == NULL )
	{
		head = (NODE *) malloc( sizeof(NODE));
		if( head == NULL)
		{
			printf("error in malloc for insert()\n");
			return NULL;
		}
		head->nvalue = x;
		head->next = NULL;
		return head;
	}

	NODE *newp = (NODE*) malloc (sizeof(NODE));
	if(newp == NULL )
	{
		printf("error in malloc for insert() \n");
		return NULL;
	}
	newp->next = head;
	newp->nvalue = x;

	return newp;
}
void push_list(STACK *stk, ELEMENT_TYPE x)
{
	*stk = insert(*stk, x);
}
int get_list_len(LIST head)
{
	int len = 0;
	while( head != NULL )
	{
		++len;
		head = head->next;
	}
	return len;
}

#define YES 1
#define NO 0
int isempty_list(STACK stk)
{
	return 0 == get_list_len(stk) ? YES : NO;
}




ELEMENT_TYPE pop_list(STACK *stk)
{
	if( isempty_list(*stk) == YES )
	{
		printf("stack is empty, cannot pop\n");
		return -1.0; /* INF */
	}

	NODE * tmp = *stk;
	ELEMENT_TYPE value =  tmp->nvalue;
	(*stk) = (*stk)->next;
	free(tmp);
	return value;
}






typedef struct _stack{
	int top;
	ELEMENT_TYPE ary[MAXLEN];
}stack;

 void make_empty_stack(stack *a)
{
	assert(a != NULL);
 	a->top = 0;
 }

/* array stack */
void push_v1(stack *a, ELEMENT_TYPE x)
{
	assert(a != NULL);
	if(a->top >= MAXLEN  )
	{
		printf("stack full\n");
		exit(-1);
	}
	(a->ary)[(a->top)++] = x;
}

ELEMENT_TYPE pop_v1(stack *a)
{
	assert(a != NULL);
	if(a->top <= 0)
	{
		printf("stack empty\n");
		exit(-1);
	}
	return (a->ary)[--(a->top)];
}

ELEMENT_TYPE top_v1(stack *a)
{
	assert(a != NULL);
	return (a->ary)[a->top - 1 ];
}





#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if( bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}




#define NUMBER '0'
#define MAXOP 100
int getop(char *s)
{
	int i,  c ; /* int c, for EOF */
	
	while( (s[0] = c = getch( )) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if( !isdigit(c) && c != '.')
		return c;
	i = 0;
	if( isdigit(c))
		while(isdigit(s[++i] = c = getch( )))
			;
	if( c == '.')
		while( isdigit(s[++i] = c = getch( )))
			;

	s[i] = '\0';
 
	if( (c=getch( )) != EOF)
		ungetch(c  );

	return NUMBER;
}
 
enum {RIGHT = 1, WRONG = -1};
/* success return RIGHT, otherwise return WRONG */
int  get_repolish_expr(char *s, stack *T)
{
	return 0;
}

int main()
{
	//STACK stk = NULL;
	//push_list(&stk, 10.0);
	//push_list(&stk, 9.0);
	//push_list(&stk, 9.4);
	//printf("%d\n", get_list_len(stk));
	//printf("%lf\n", pop_list(&stk));
	//printf("%lf\n", pop_list(&stk));


	//printf("%d\n", get_list_len(stk));

	stack mystk;
	make_empty_stack(&mystk);
 

	//char expr[MAXOP] = {0};
	//fgets(expr, MAXOP, stdin);
	//stack repolish;
	//make_empty_stack(&repolish);
	//get_repolish_expr(expr, &repolish);
	//int i = 0;
	//char s[MAXOP]={0};
	//int type;
	//double op1;
	//double op2;

	//while((type = getop(s)) != EOF)
	//{
	//	switch(type)
	//	{
	//	case NUMBER:
	//		printf("%lf\n", atof(s));
	//		push_v1(&mystk, atof(s));
	//		break;
	//	case '+':
	//		push_v1( &mystk, pop_v1(&mystk) + pop_v1(&mystk) );
	//		printf("+\n");
	//		break;
	//	case '-':
	//		op1 =  pop_v1(&mystk);
	//		op2 =  pop_v1(&mystk);
	//		push_v1(&mystk, op2 - op1);
	//		printf("-\n");
	//		break;
	//	case '*':
	//		push_v1(&mystk, pop_v1(&mystk) *pop_v1(&mystk));
	//		break;
	//	case '/':
	//		op1 =  pop_v1(&mystk);
	//		if( op1 == 0.0)
	//			printf("error: zero divisor\n");
	//		else
	//			push_v1(&mystk,  pop_v1(&mystk)/op1);
	//		break;
	//	case '\n':
	//		printf("\t%.8g\n", pop_v1(&mystk));
	//		break;
	//	default:
	//		printf("error: unknown command %s\n", s);
	//		break;
	//	}
	//}
	//


	system("pause");
	return 0;
}