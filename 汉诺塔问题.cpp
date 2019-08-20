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
	if (S.base==S.top)//�ж��Ƿ�ǿ�
		return ERROR;
	S.top--;//ջ��Ԫ�ؽ���
	e=*S.top;//���
	return OK;
}
Status Push(Stack &S,ElemType e)
{
	if ((S.top-S.base)>=S.stacksize)//ջ��׷������Ԫ��
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
 
int c=0;//ȫ�ֱ�����¼���˴���
 
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
		hanoi(n-1,x,z,y);//��x�ϱ��Ϊ1��n-1��Բ���Ƶ�y,z��Ϊ������
		Move(x,n,z);//�����Ϊn��Բ�̴�x�Ƶ�z
		hanoi(n-1,y,x,z);//��y�ϱ��Ϊ1��n-1��Բ���Ƶ�z,x��Ϊ������
	}
}
int main(int argc,char **argv){
	int n;
	Stack x,y,z;
	char tagx='x';//��ջ���ǩ
	char tagy='y';//��ջ���ǩ
	char tagz='z';//��ջ���ǩ
	ElemType e;
	
	InitStack(x,tagx);
	InitStack(y,tagy);
	InitStack(z,tagz);
	
	printf("������Hanoi���ĸ߶�\n");
	scanf("%d",&n);
	hanoi(n,x,y,z);
	printf("���˽����������޺���Z��\n");
	while(!StackEmpty(z))
	{
		Pop(z,e);
		printf("%d\n",e);
	}
	getch();
	return 0;
}

