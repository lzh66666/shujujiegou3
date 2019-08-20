#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define STACK_INIT_SIZE 20
#define STACKINCREMENT 10
#define MAXBUFFER 10

typedef float ElemType;

typedef struct
{
    ElemType *base;
    ElemType *top;
    int stackSize;
}sqStack;



void InitStack(sqStack *s)
{
    s->base=(ElemType *)malloc(STACK_INIT_SIZE*sizeof(ElemType));
    if(!s->base)
        exit(0);
    s->top=s->base;
    s->stackSize=STACK_INIT_SIZE;
}

/*
入栈操作
*/
void Push(sqStack *s,ElemType e)
{
    if(s->top-s->base==s->stackSize)
    {
        s->base=(ElemType *)realloc(s->base,(STACKINCREMENT+s->stackSize)*sizeof(ElemType));
        if(!s->base)
            exit(0);

        s->top=s->base+s->stackSize;
        s->stackSize=s->stackSize+STACKINCREMENT;
    }
    *(s->top)=e;
    s->top++;
}

void Pop(sqStack *s,ElemType *e)
{
    if(s->top==s->base)
        return;
    *e=*--(s->top);
}

int StackLen(sqStack *s)
{
    return (s->top-s->base);
}

int main()
{
    sqStack s;
    char c;
    float d,e;
    char str[MAXBUFFER];
    int i=0;

    InitStack(&s);
    printf("请输入逆波兰表达式输入待计算数据，数据与运算符之间用空格隔开，以$作为结束标志：\n");

    scanf("%c",&c);
    while(c!='$')
    {
        while(isdigit(c)||c=='.')
        {
            str[i++]=c;
            str[i]='\0';
            if(i>=10)
            {
                printf("error");
                return -1;
            }

            scanf("%c",&c);
            if(c==' ')
            {
                d=atof(str);
                Push(&s,d);
                i=0;
                break;
            }
        }
        switch(c){
	        case '+':
	            Pop(&s,&e);
	            Pop(&s,&d);
	            Push(&s,d+e);
	            break;
	        case '-':
	            Pop(&s,&e);
	            Pop(&s,&d);
	            Push(&s,d-e);
	            break;
	        case '*':
	            Pop(&s,&e);
	            Pop(&s,&d);
	            Push(&s,d*e);
	            break;
	        case '/':
	            Pop(&s,&e);
	            Pop(&s,&d);
	            if(e!=0){
	                Push(&s,d/e);
	            }
	            else
	            {
	                printf("error!");
	                return -1;
	            }
	            break;
        }
        scanf("%c",&c);
    }
    Pop(&s,&d);
    printf("the final result:%5.3f",d);
    return 0;
}

