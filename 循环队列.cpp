#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXQSIZE 100

typedef int Status;
typedef float QElemType;

typedef struct{
	QElemType *base;//初始化动态分配存储空间 
	int front,rear;//尾指针指向队尾元素的下一个 
}SqQueue;

Status InitQueue(SqQueue &Q); //构造空队列
Status PrintQueue(SqQueue Q);//输出循环队列 
int QueueLength(SqQueue Q); //求队列的长度
Status EnQueue (SqQueue &Q,QElemType e);//向队尾插入元素 
Status DeQueue(SqQueue &Q,QElemType &e);//从队头删除元素
 
int main(int argc, char** argv) {
	SqQueue Q;
	int i,n;
	char c;
	QElemType e;
	InitQueue(Q);
	
	printf("请输入循环队列所能容纳的最大数:\n");
	scanf("%d",&n);
	
	printf("请输入循环队列的数据:\n");
	for(i=0;i<n;i++)
	{
		scanf("%f",&e);
		EnQueue(Q,e);
	}
	PrintQueue(Q);
	
	printf("请输入要插入队尾元素的数据:\n如果不想继续插入请输入*\n");
	while(1)
	{
		c=getchar();
		if(c!='*')
		{
			scanf("%f",&e);
			EnQueue(Q,e);
			PrintQueue(Q);		
		}
		else if(c=='*')
			break;
	}
	
	
	printf("删除队头元素:\n");
	printf("如果想删除请输入*，不想继续删除请输入#\n");
	while(1)
	{
		c=getchar();
		if(c=='*')
		{
			DeQueue(Q,e);
			PrintQueue(Q);
			printf("删除的元素是%4.2f\n",e);		
		}
		else if(c=='#')
			break;
	} 
	
	return 0;
}

Status InitQueue(SqQueue &Q)
{
	Q.base=(QElemType *)malloc(MAXQSIZE*sizeof(QElemType));
	if(Q.base==NULL)
		exit(OVERFLOW);
	Q.front=Q.rear=0;
	return OK;
}

Status PrintQueue(SqQueue Q)
{
	SqQueue q; 
	if(Q.front==Q.rear)
	{
		return ERROR;
	} 
	while(Q.front!=Q.rear)
	{
		printf("%4.2f ",Q.base[Q.front]);
		Q.front=(Q.front+1)%MAXQSIZE;
	}
	printf("\n");
	return OK;
} 

int QueueLength(SqQueue Q)
{
	return (Q.rear-Q.front+MAXQSIZE)%MAXQSIZE;
}

Status EnQueue (SqQueue &Q,QElemType e)
{
	if((Q.rear+1)%MAXQSIZE == Q.front)
		return ERROR;
	Q.base[Q.rear]=e;
	Q.rear=(Q.rear+1)%MAXQSIZE;
	return OK;
 } 

Status DeQueue(SqQueue &Q,QElemType &e)
{
	if(Q.front==Q.rear)
		return ERROR;
	e=Q.base[Q.front];
	Q.front=(Q.front+1)%MAXQSIZE;
	return OK;
 } 

