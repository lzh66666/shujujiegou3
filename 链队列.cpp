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
	QueuePtr front;    //��ͷָ�� 
	QueuePtr rear;     //��βָ�� 
}LinkQueue;

Status InitQueue(LinkQueue &Q);   //����ն��� 
Status CreatQueue(LinkQueue &Q,int n);  //�����¶��� 
Status EnQueue(LinkQueue &Q,QElemType e);//���β����Ԫ��
Status PrintQueue(LinkQueue Q); //������� 
Status DeQueue(LinkQueue &Q,QElemType &e);//����ɾ�� 
Status DestroyQueue(LinkQueue &Q);   //�������� 

int main(int argc, char** argv) {
	LinkQueue Q;
	int n,i;
	char c;
	QElemType e;
	InitQueue(Q);//��ʼ������ 
	printf("����������������е�����:\n");
	scanf("%d",&n);
	printf("��������е�Ԫ��:\n");
	CreatQueue(Q,n);
	PrintQueue(Q);
	
	printf("���������β�����Ԫ��:\n������������������*\n");
	 
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
	
	
	printf("����ͷ����ɾ��Ԫ��:\n\n");
	printf("�����ɾ��������*\n����������ɾ��������#\n");
	while(1)
	{
		c=getchar();
		if(c=='*')
		{
			DeQueue(Q,e);
			PrintQueue(Q);
			printf("ɾ����Ԫ����:%4.2f\n",e);	
		}
		else if(c=='#')
			break;
	} 
	 
	n=DestroyQueue(Q);
	if(n==OK)
	{
		printf("�ö���������!");
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
  
