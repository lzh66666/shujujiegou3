#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
#define TURE 1
#define FLASE 0
#define OVERFLOW -2

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef char SElemType;
typedef int Status;

typedef struct {
	SElemType *base,*top;
	int stacksize;
}Sqstack;

Status InitStack(Sqstack &S);
SElemType GetTop(Sqstack &S,SElemType c);
Status Push(Sqstack &S,SElemType &ch);
Status Pop(Sqstack &S,SElemType &ch);
Status StackEmpty(Sqstack S);//�ж��Ƿ�Ϊ�� 
Status Inn(SElemType c);//�ж��Ƿ�������� 
SElemType Operate(SElemType a,SElemType &theta,SElemType b);//������������
SElemType Precede(SElemType ch1,SElemType ch2);//�ж�����������ȼ� 

int main(int argc, char** argv) {
	SElemType theta,ch,x,c,m;
	SElemType a,b;
	Sqstack OPTR;
	Sqstack OPND;
	InitStack(OPTR);//��ʼ�������ջ 
	InitStack(OPND);//��ʼ��������ջ 
	c='#';
	
	Push(OPTR,c);
	printf("������һ����#��β�ı��ʽ:");
	ch=getchar();
	
	while(ch!='#' || GetTop(OPTR,c)!='#')
	{
		if(!Inn(ch))//������������ջ 
		{
			Push(OPND,ch);
			printf("��OPNDջ %d\n",ch-48);
			ch=getchar(); 
		}
		else
		{
			switch(Precede(GetTop(OPTR,c),ch))  //ͨ���ȽϽ��յ��ַ�����������
			{
				case'<':              //ջ��Ԫ������Ȩ�� 
				Push(OPTR,ch);
				printf("��OPTRջ %c\n",ch);
				ch=getchar();
				break;
				
				case'>':               //��ջ������������ջ 
				Pop(OPTR,theta);
				Pop(OPND,b);
				Pop(OPND,a);
				printf("��OPNDջǰ%d %d\n",b-48,a-48);
				Push(OPND,m=Operate(a,theta,b));
				printf("����� %d\n",m-48);
				break;
				
				case'=':                 //�����Ų�������һ���ַ� 
				Pop(OPTR,x);
				ch=getchar();
				break;
			}
		}
	}
	printf("\n\n\n");
    printf("������= %d",(GetTop(OPND,c)-48));
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

SElemType GetTop(Sqstack &S,SElemType c)
{
	if(S.top==S.base)
		return ERROR;
	c=*(S.top-1);
	return c;
}

Status Push(Sqstack &S,SElemType &ch)
{
	if(S.top-S.base>=S.stacksize)
	{
		S.base=(SElemType *)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(S.base==NULL)
			exit(OVERFLOW);
		S.top=S.base+S.stacksize;
		S.stacksize+=STACKINCREMENT;
	}
	*(S.top++)=ch;
	return OK;
}

Status Pop(Sqstack &S,SElemType &ch)
{
	if(S.top==S.base)
		return ERROR;
	ch=*(--S.top);
	return OK; 
}


Status Inn(SElemType c)
{
	if(c=='+' || c=='-' ||c=='*' ||c=='/' || c=='#' || c=='(' ||c==')')
		return OK;
	else
		return ERROR;
}


SElemType Operate(SElemType a,SElemType &theta,SElemType b)
{
	SElemType c;
	a=a-48;
	b=b-48;
	switch(theta)
	{
		case '+':c=a+b+48;
		break;
		case '-':c=a-b+48;
		break;
		case '*':c=a*b+48;
		break;
		case '/':c=a/b+48;
		break;
	}

	return c;
}

SElemType Precede(SElemType ch1,SElemType ch2)
{
	if(ch1=='+')
	{
		switch(ch2)
		{
			case '+':return '>';
			case '-':return '>';
			case '*':return '<';
			case '/':return '<';
			case '(':return '<';
			case ')':return '>';
			case '#':return '>';
		}
	}
	else if(ch1=='-')
	{
		switch(ch2)
		{
			case '+':return '>';
			case '-':return '>';
			case '*':return '<';
			case '/':return '<';
			case '(':return '<';
			case ')':return '>';
			case '#':return '>';
		}
	}
	
	else if(ch1=='*')
	{
		switch(ch2)
		{
			case '+':return '>';
			case '-':return '>';
			case '*':return '>';
			case '/':return '>';
			case '(':return '<';
			case ')':return '>';
			case '#':return '>';
		}
	}
	
	else if(ch1=='/')
	{
		switch(ch2)
		{
			case '+':return '>';
			case '-':return '>';
			case '*':return '>';
			case '/':return '>';
			case '(':return '<';
			case ')':return '>';
			case '#':return '>';
		}
	}
	
	else if(ch1=='(')
	{
		switch(ch2)
		{
			case '+':return '<';
			case '-':return '<';
			case '*':return '<';
			case '/':return '<';
			case '(':return '<';
			case ')':return '=';
		}
	}
	
	else if(ch1==')')
	{
		switch(ch2)
		{
			case '+':return '>';
			case '-':return '>';
			case '*':return '>';
			case '/':return '>';
			case ')':return '>';
			case '#':return '>';
		}
	}
	
	else if(ch1=='#')
	{
		switch(ch2)
		{
			case '+':return '<';
			case '-':return '<';
			case '*':return '<';
			case '/':return '<';
			case '(':return '<';
			case '#':return '=';
		}
	}
}
