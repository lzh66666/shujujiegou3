#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
 
typedef int ElemType;
typedef int Status;

#define STACK_SIZE 10
#define STACK_INCREMENT 10
#define OK   1
#define ERROR  -1

typedef struct{
	ElemType *base;
	ElemType *top;
	int stacksize;
	char tag;
}Stack;
 
Status InitStack(Stack &S,char tag)
{
	S.base=(ElemType*)malloc(STACK_SIZE*sizeof(ElemType));
	if (!S.base)
		return ERROR;
	S.top=S.base;
	S.tag=tag;
	S.stacksize=STACK_SIZE;
	return OK;
}
 
Status Pop(Stack &S,ElemType &e)
{
	if (S.base==S.top)//判断是否非空
		return ERROR;
	S.top--;//栈顶元素降低
	e=*S.top;//输出
	return OK;
}
Status Push(Stack &S,ElemType e)
{
	if ((S.top-S.base)>=S.stacksize)//栈满追加数据元素
	{
		S.base=(ElemType *)realloc(S.base,(S.stacksize+STACK_INCREMENT)*sizeof(ElemType));
		if (!S.base)
			exit(ERROR);
		S.top=S.base+S.stacksize;
		S.stacksize+=STACK_INCREMENT;
	}
	*S.top=e;
	S.top++;
	return OK;
}
 
Status StackEmpty(Stack &S)
{
	if (S.base==S.top)
		return 1;
	else
		return 0;
}
 
int c=0;//全局变量记录搬运次数
 
void Move(Stack &x,ElemType n,Stack &z)
{
	Pop(x,n);
	Push(z,n);
}
 
void hanoi(ElemType n,Stack &x,Stack &y,Stack &z)
{
	printf("%d:Move disk %d from %c to %c\n",++c,n,x.tag,z.tag);
	if (n==1)
		Move(x,1,z);
	else
	{
		hanoi(n-1,x,z,y);//将x上编号为1至n-1的圆盘移到y,z作为补助塔
		Move(x,n,z);//将编号为n的圆盘从x移到z
		hanoi(n-1,y,x,z);//将y上编号为1至n-1的圆盘移到z,x作为补助塔
	}
}
int main(int argc,char **argv){
	int n;
	Stack x,y,z;
	char tagx='x';//给栈打标签
	char tagy='y';//给栈打标签
	char tagz='z';//给栈打标签
	ElemType e;
	
	InitStack(x,tagx);
	InitStack(y,tagy);
	InitStack(z,tagz);
	
	printf("请输入Hanoi塔的高度\n");
	scanf("%d",&n);
	hanoi(n,x,y,z);
	printf("搬运结束，输入罗汉塔Z：\n");
	while(!StackEmpty(z))
	{
		Pop(z,e);
		printf("%d\n",e);
	}
	getch();
	return 0;
}

