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
	QElemType *base;//��ʼ����̬����洢�ռ� 
	int front,rear;//βָ��ָ���βԪ�ص���һ�� 
}SqQueue;

Status InitQueue(SqQueue &Q); //����ն���
Status PrintQueue(SqQueue Q);//���ѭ������ 
int QueueLength(SqQueue Q); //����еĳ���
Status EnQueue (SqQueue &Q,QElemType e);//���β����Ԫ�� 
Status DeQueue(SqQueue &Q,QElemType &e);//�Ӷ�ͷɾ��Ԫ��
 
int main(int argc, char** argv) {
	SqQueue Q;
	int i,n;
	char c;
	QElemType e;
	InitQueue(Q);
	
	printf("������ѭ�������������ɵ������:\n");
	scanf("%d",&n);
	
	printf("������ѭ�����е�����:\n");
	for(i=0;i<n;i++)
	{
		scanf("%f",&e);
		EnQueue(Q,e);
	}
	PrintQueue(Q);
	
	printf("������Ҫ�����βԪ�ص�����:\n��������������������*\n");
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
	
	
	printf("ɾ����ͷԪ��:\n");
	printf("�����ɾ��������*���������ɾ��������#\n");
	while(1)
	{
		c=getchar();
		if(c=='*')
		{
			DeQueue(Q,e);
			PrintQueue(Q);
			printf("ɾ����Ԫ����%4.2f\n",e);		
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

