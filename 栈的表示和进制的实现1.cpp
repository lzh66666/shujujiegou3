#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define N 16
#define MAXSIZE 1024

typedef int datatype;

typedef struct{
	datatype data[MAXSIZE];
	int top;
}SeqStack;

SeqStack *Init_SeqStack(); //置空栈 
int Empty_SeqStack(SeqStack *s); //判空栈 
int Push_SeqStack(SeqStack *s,datatype x);//入栈 
int Pop_SeqStack(SeqStack *s,datatype &x);//出栈 
datatype Top_SeqStack(SeqStack *s);//返回栈顶元素 
void conversion();
 
int main(int argc, char** argv) {
	conversion();
	return 0;
} 

SeqStack *Init_SeqStack()
{
	SeqStack *s;
	s=(SeqStack *)malloc(sizeof(SeqStack));
	s->top=-1;
	return s;
}

int Empty_SeqStack(SeqStack *s)
{
	if(s->top==-1)
		return 1;
	else
		return 0;
}

int Push_SeqStack(SeqStack *s,datatype x)
{
	if(s->top==MAXSIZE-1)
		return 0;
	else
	{
		s->top++;
		s->data[s->top]=x;
		return 1;
	} 
}

int Pop_SeqStack(SeqStack *s,datatype &x)
{
	if(Empty_SeqStack(s))
		return 0;
	else
	{
		x=s->data[s->top];
		s->top--;
		return 1;
	}
}

datatype Top_SeqStack(SeqStack *s)
{
	if(Empty_SeqStack(s))
		return 0;
	else
		return s->data[s->top];
}

void conversion()
{
	SeqStack *s;
	datatype x,n;
	s=Init_SeqStack();
	printf("请输入一个十进制整数：");
	scanf("%d",&x);
	n=x;
	while(x)
	{
		Push_SeqStack(s,x%N);
		x=x/N;
	}
	printf("%d的%d进制数是：",n,N);
	while(!Empty_SeqStack(s))
	{
		Pop_SeqStack(s,x);
		printf("%d",x);
	}
}
