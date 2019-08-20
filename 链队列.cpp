#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef float QElemType;
typedef int Status;

typedef struct QNode{
	QElemType data;
	struct QNode *next;
}QNode,*QueuePtr;

typedef struct{
	QueuePtr front;    //队头指针 
	QueuePtr rear;     //队尾指针 
}LinkQueue;

Status InitQueue(LinkQueue &Q);   //构造空队列 
Status CreatQueue(LinkQueue &Q,int n);  //创建新队列 
Status EnQueue(LinkQueue &Q,QElemType e);//向队尾插入元素
Status PrintQueue(LinkQueue Q); //队列输出 
Status DeQueue(LinkQueue &Q,QElemType &e);//队列删除 
Status DestroyQueue(LinkQueue &Q);   //队列销毁 

int main(int argc, char** argv) {
	LinkQueue Q;
	int n,i;
	char c;
	QElemType e;
	InitQueue(Q);//初始化队列 
	printf("请输入你想输入队列的总数:\n");
	scanf("%d",&n);
	printf("请输入队列的元素:\n");
	CreatQueue(Q,n);
	PrintQueue(Q);
	
	printf("输入向队列尾插入的元素:\n如果想结束插入请输入*\n");
	 
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
	
	
	printf("队列头进行删除元素:\n\n");
	printf("如果想删除请输入*\n如果不想继续删除请输入#\n");
	while(1)
	{
		c=getchar();
		if(c=='*')
		{
			DeQueue(Q,e);
			PrintQueue(Q);
			printf("删除的元素是:%4.2f\n",e);	
		}
		else if(c=='#')
			break;
	} 
	 
	n=DestroyQueue(Q);
	if(n==OK)
	{
		printf("该队列已销毁!");
	}
	return 0;
}

Status InitQueue(LinkQueue &Q)
{
	Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
	if(Q.front==NULL)
		exit(OVERFLOW);
	Q.front->next=NULL;
	return OK;
}

Status CreatQueue(LinkQueue &Q,int n)
{
	int i;
	QElemType e;
	for(i=0;i<n;i++)
	{
		scanf("%f",&e);
		EnQueue(Q,e);
	}
	return OK;
} 

Status PrintQueue(LinkQueue Q)
{ 
	Q.front=Q.front->next;
	while(Q.front!=Q.rear->next)
	{
		printf("%4.2f ",Q.front->data);
		Q.front=Q.front->next;
	}
	printf("\n");
	return OK;
}

Status EnQueue(LinkQueue &Q,QElemType e)
{
	QueuePtr p;
	p=(QueuePtr)malloc(sizeof(QNode));	
	if(p==NULL)
		exit(OVERFLOW);
	p->data=e;
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
	return OK;
} 
 
Status DeQueue(LinkQueue &Q,QElemType &e)
{
	QueuePtr p;
	if(Q.front==Q.rear)
		return ERROR;
	p=Q.front->next;
	e=p->data;
	Q.front->next=p->next;
	if(Q.rear==p)
		Q.rear=Q.front;
	free(p);
	return OK;
} 

Status DestroyQueue(LinkQueue &Q)
{
	while(Q.front)
	{
		Q.rear=Q.front->next;
		free(Q.front);
		Q.front=Q.rear;
	}
	return OK;
} 
  
