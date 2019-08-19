#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TURE 1
#define FLASE 0
#define OVERFLOW -2

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define N 8

typedef int SElemType;
typedef int Status;

typedef struct {
	SElemType *base,*top;
	int stacksize;
}Sqstack;

Status InitStack(Sqstack &S);
Status GetTop(Sqstack S,SElemType &e);
Status Push(Sqstack &S,SElemType e);
Status Pop(Sqstack &S,SElemType &e);
Status StackEmpty(Sqstack S);
void conversion(Sqstack S);

int main(int argc, char** argv) {
	Sqstack S;
	conversion(S);
	return 0;
}

Status GetTop(Sqstack S,SElemType &e)
{
	if(S.top==S.base)
		return ERROR;
	e=*(S.top-1);
	return OK;
}

Status InitStack(Sqstack &S)
{
	S.base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!S.base)
		exit(OVERFLOW);
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
	return OK;
}



Status Push(Sqstack &S,SElemType e)
{
	if(S.top-S.base>=S.stacksize)
	{
		S.base=(SElemType *)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(S.base==NULL)
			exit(OVERFLOW);
		S.top=S.base+S.stacksize;
		S.stacksize+=STACKINCREMENT;
	}
	*(S.top++)=e;
	return OK;
}

Status Pop(Sqstack &S,SElemType &e)
{
	if(S.top==S.base)
		return ERROR;
	e=*(--S.top);
	return OK; 
}

Status StackEmpty(Sqstack S)
{
	if(S.top==S.base)
		return TURE;
	else
		return FLASE;
}

void conversion(Sqstack S)
{
	int n,m,e;
	InitStack(S);
	printf("请输入一个十进制数:\n");
	scanf("%d",&n);
	m=n;
	while(n)
	{
		Push(S,n%N);
		n=n/N;
	}
	printf("%d的%d进制是：",m,N);
	while(!StackEmpty(S))
	{
		Pop(S,e);
		printf("%d",e);
	}
	
}
