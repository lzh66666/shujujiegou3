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
Status StackEmpty(Sqstack S);//判断是否为空 
Status Inn(SElemType c);//判断是否是运算符 
SElemType Operate(SElemType a,SElemType &theta,SElemType b);//对数进行运算
SElemType Precede(SElemType ch1,SElemType ch2);//判断运算符的优先级 

int main(int argc, char** argv) {
	SElemType theta,ch,x,c,m;
	SElemType a,b;
	Sqstack OPTR;
	Sqstack OPND;
	InitStack(OPTR);//初始化运算符栈 
	InitStack(OPND);//初始化运算数栈 
	c='#';
	
	Push(OPTR,c);
	printf("请输入一个带#结尾的表达式:");
	ch=getchar();
	
	while(ch!='#' || GetTop(OPTR,c)!='#')
	{
		if(!Inn(ch))//不是运算符则进栈 
		{
			Push(OPND,ch);
			printf("入OPND栈 %d\n",ch-48);
			ch=getchar(); 
		}
		else
		{
			switch(Precede(GetTop(OPTR,c),ch))  //通过比较接收的字符来进行运算
			{
				case'<':              //栈顶元素优先权低 
				Push(OPTR,ch);
				printf("入OPTR栈 %c\n",ch);
				ch=getchar();
				break;
				
				case'>':               //退栈并将运算结果入栈 
				Pop(OPTR,theta);
				Pop(OPND,b);
				Pop(OPND,a);
				printf("入OPND栈前%d %d\n",b-48,a-48);
				Push(OPND,m=Operate(a,theta,b));
				printf("运算后 %d\n",m-48);
				break;
				
				case'=':                 //脱括号并接收下一个字符 
				Pop(OPTR,x);
				ch=getchar();
				break;
			}
		}
	}
	printf("\n\n\n");
    printf("运算结果= %d",(GetTop(OPND,c)-48));
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
