#include <stdio.h>
#include <stdlib.h>

#define FLASE 0
#define TRUE 1
#define MAX 3

typedef struct Node   //����
{
    int number;
    int time;
}Node;

typedef struct QueueNode1   //���н��
{
    Node infom;
    struct QueueNode1 * next;
}*QueueNode;

typedef struct LinkQueue    //������
{
    struct QueueNode1 * front;
    struct QueueNode1 * rear;
}LinkQueue;

typedef struct stack         //ջ���
{
    struct Node data;
    struct stack *next;
}*StackNode;

typedef struct LinkStack     //��ջ
{
    StackNode top;
    int count;
}LinkStack;

//����ʵ��

void menu(LinkQueue *wait,LinkQueue *park,LinkStack *giveway,int num,int t);//�˵�
int init(LinkQueue *wait,LinkQueue *park,LinkStack *giveway);//��ʼ��
int linklength(LinkQueue q);//�鿴����
int enqueue(LinkQueue *q,int num,int t);//�����
int dequeue(LinkQueue *q,int *num,int *t);//������
void park1(LinkQueue *wait,LinkQueue *park);//ͣ������
int push(LinkStack *s,int num,int t);//��ջ
int pop(LinkStack *s,int *num,int *t);//��ջ
void leave2(LinkQueue *wait,LinkQueue *park,LinkStack *giveway,int num,int t);//�뿪����
void view3(LinkQueue wait,LinkQueue park);//�鿴ͣ����״̬

int main()
{
    LinkQueue wait;
    LinkQueue park;
    LinkStack giveway;
    int num = 0;
    int t = 0;
    init(&wait,&park,&giveway);
    menu(&wait,&park,&giveway,num,t);
    return 0;
}

int init(LinkQueue *wait,LinkQueue *park,LinkStack *giveway)
{
    QueueNode newnode1 = (QueueNode)malloc(sizeof(struct QueueNode1));
    if(!newnode1)
    {
        return FLASE;
    }
    newnode1->next = NULL;
    wait->front = newnode1;
    wait->rear = newnode1;

    QueueNode newnode2 = (QueueNode)malloc(sizeof(struct QueueNode1));
    if(NULL == newnode2)
    {
        return FLASE;
    }
    newnode2->next = NULL;
    park->front = newnode2;
    park->rear = newnode2;

    giveway->top = NULL;
    giveway->count = 0;
}

void menu(LinkQueue *wait,LinkQueue *park,LinkStack *giveway,int num,int t)
{
    printf("******************��ӭ��ͣ��!******************\n");
    printf("****************��ѡ����Ҫ�Ĺ���****************\n");
    printf("**********         1 : ͣ��.          **********\n");
    printf("**********         2 : �뿪.         **********\n");
    printf("**********         3 : ״��.          **********\n");
    printf("**********         4 : ף����.        **********\n");
    int option;
    scanf("%d",&option);
    switch(option)
    {
        case 1:{
            park1(wait,park);
            printf("ͣ����ɣ�\n");
            menu(wait,park,giveway,num,t);
            break;
        }
        case 2:{
            leave2(wait,park,giveway,num,t);
            menu(wait,park,giveway,num,t);
            break;
        }
        case 3:{
            view3(*wait,*park);
            menu(wait,park,giveway,num,t);
            break;
        }
        case 4:{
            printf("**********     ��ӭ�ٴ�ʹ�ã�лл��   **********\n");
            break;
        }
        default:{
            printf("**********      ��������ȷ��ָ�    **********\n");
            menu(wait,park,giveway,num,t);
            break;
        }
    }

}

int linklength(LinkQueue q)
{
    int i = 0;
    while(q.front != q.rear)
    {
        i++;
        q.front = q.front->next;
    }
    return i;
}

int enqueue(LinkQueue *q,int num,int t)
{
    QueueNode newnode = (QueueNode)malloc(sizeof(struct QueueNode1));
    if(NULL == newnode)
    {
        return FLASE;
    }
    newnode->infom.number = num;
    newnode->infom.time = t;
    newnode->next = NULL;
    q->rear->next = newnode;
    q->rear = newnode;
    return TRUE;
}

int dequeue(LinkQueue *q,int *num,int *t)
{
    if(q->front == q->rear)
    {
        printf("��ͣ����û�˳�!\n");
        return FLASE;
    }
    *num = q->front->next->infom.number;
    *t = q->front->next->infom.time;
    QueueNode temp = q->front->next;
    q->front->next = temp->next;
    if(temp->next == NULL)
    {
        q->rear = q->front;
    }
    free(temp);
    return TRUE;
}

void park1(LinkQueue *wait,LinkQueue *park)
{
    printf("�����복�ź�ͣ��ʱ��\n");
    int num,t;
    scanf("%d%d",&num,&t);
    if(linklength(*park) >= MAX)
    {
        printf("ͣ��������������ȴ�����\n");
        enqueue(wait,num,t);
    }
    else
    {
        enqueue(park,num,t);
    }
}

int push(LinkStack *s,int num,int t)
{
    StackNode newnode = (StackNode)malloc(sizeof(struct stack));
    if(NULL == newnode)
    {
        return FLASE;
    }
    newnode->data.number = num;
    newnode->data.time = t;
    newnode->next = s->top;
    s->top = newnode;
    s->count++;
    return TRUE;
}

int pop(LinkStack *s,int *num,int *t)
{
    if(s->count==0)
    {
        printf("��ͣ����û��!\n");
        return FLASE;
    }
    *num = s->top->data.number;
    *t = s->top->data.time;
    StackNode temp = s->top;
    s->top = s->top->next;
    free(temp);
    s->count--;
    return TRUE;
}

void leave2(LinkQueue *wait,LinkQueue *park,LinkStack *giveway,int num,int t)
{
    printf("������Ҫ�뿪���ĳ���\n");
    int leavenumber;
    scanf("%d",&leavenumber);
    int i = 0;
    QueueNode head = park->front;
    while(head != park->rear)
    {
        if(head->next->infom.number != leavenumber)
        {
            head = head->next;
            i++;
        }
        else
            break;
    }
    int j = 0;
    if(i <= MAX-1)
    {
        while(j != i)
        {
            dequeue(park,&num,&t);
            push(giveway,num,t);
            j++;
        }
        dequeue(park,&num,&t);
    }
    else
    {
        printf("���޴˳���\n");
    }
    while(giveway->top != NULL)
    {
        pop(giveway,&num,&t);
        enqueue(park,num,t);
    }
    if(linklength(*wait) != 0)
    {
        dequeue(wait,&num,&t);
        enqueue(park,num,t);
    }
}

void view3(LinkQueue wait,LinkQueue park)
{
    printf("********************    Ŀǰͣ����״��    ********************\n");
    printf("ͣ������%d����λ����ǰͣ��������%d�������ȴ�������%d����\n",
        MAX,linklength(park),linklength(wait));
    printf("**************************************************************\n");
    printf("��    �ţ�");
    QueueNode head1 = park.front;
    QueueNode head2 = park.front;
    while(head1 != park.rear)
    {
        printf("%d  ",head1->next->infom.number);
        head1 = head1->next;
    }
    printf("\n");
    printf("ͣ��ʱ�䣺");
    while(head2 != park.rear)
    {
        printf("%d ",head2->next->infom.time);
        head2 = head2->next;
    }
    printf("\n");
}

