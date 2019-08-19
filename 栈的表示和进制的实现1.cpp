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

SeqStack *Init_SeqStack(); //�ÿ�ջ 
int Empty_SeqStack(SeqStack *s); //�п�ջ 
int Push_SeqStack(SeqStack *s,datatype x);//��ջ 
int Pop_SeqStack(SeqStack *s,datatype &x);//��ջ 
datatype Top_SeqStack(SeqStack *s);//����ջ��Ԫ�� 
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
	printf("������һ��ʮ����������");
	scanf("%d",&x);
	n=x;
	while(x)
	{
		Push_SeqStack(s,x%N);
		x=x/N;
	}
	printf("%d��%d�������ǣ�",n,N);
	while(!Empty_SeqStack(s))
	{
		Pop_SeqStack(s,x);
		printf("%d",x);
	}
}
