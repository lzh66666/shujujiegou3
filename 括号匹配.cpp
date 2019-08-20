#include <stdio.h>
#include <stdlib.h>

#define INIT_SIZE 10
#define INCREMENT 5

#define OVERFLOW -2
#define FALSE 0 
#define OK 1
#define TRUE 1
#define ERROR 0

typedef char SElemType; 
typedef int Status;

typedef struct stack{
    SElemType *base;
    SElemType *top;
    int stacksize; 
}Stack;

Status InitStack(Stack &S){
    //��ʼ��ջ 
    S.base=(SElemType *)malloc(INIT_SIZE*sizeof(SElemType));
    if(!S.base)
		exit(OVERFLOW);
    S.top=S.base;
    S.stacksize=INIT_SIZE;
    return OK;
}

Status Push(Stack &S,char e){
    //��ջ 
    if(S.top-S.base>=S.stacksize){    //ջ�������·����ڴ� 
        S.base=(SElemType *)realloc(S.base,(INIT_SIZE+INCREMENT)*sizeof(SElemType));
        if(!S.base)
			exit(OVERFLOW);
        S.top=S.base+S.stacksize;
        S.stacksize+=INCREMENT;
    }
    *S.top++=e;
    return OK;
}

char Pop(Stack &S){
    //��ջ 
    char e;
    
    if(S.top==S.base)
	    return ERROR;    //ջ�գ����� 
    e=*(--S.top);
    return e;
}

Status judge(Stack &S){
    //���б��ʽ��������ж� 
    SElemType *p;
    char n;
    
    scanf("%c",&n);            		//��һ�����ŵļ��
    while(n!='(' && n!='[')        //�������ֵ��������ţ�ֱ����������
    {
        if(n==')' || n==']' || n=='#')
		    return FALSE;    //��Ϊ')'��']'���������ƥ�䡣'#'���ڽ�������
        scanf("%c",&n);    
    }
    
    if(n=='(' || n=='[')
	    Push(S,n);    //��⵽�����ţ���ջ
    scanf("%c",&n);
    while(n!='#')    //'#'���ڽ�������
    {    
        if(n=='(' || n==')' || n=='[' || n==']')
        {
            p=S.top;
            Push(S,n);
            if(*(p-1)=='(')        //��ǰһ�����űȽ�
            {
                if(*p==')')    
                {
                    printf("%c\n",Pop(S));
                    printf("%c\n",Pop(S));
                }
                else if(*p==']')    return FALSE;
            }
            else if(*(p-1)=='[')
            {
                if(*p==']')    
                {
                    printf("%c\n",Pop(S));
                    printf("%c\n",Pop(S));
                }
                else if(*p==')')    return FALSE;
            }
        }
        scanf("%c",&n);
    }
    if(S.top==S.base)
	    return TRUE; //ջ��û��Ԫ��ʱ��˵��ƥ�� 
    else 
		return FALSE;
}

int main(int argc,char **argv){
    Stack S;
    
    if(InitStack(S)) 
		printf("��ʼ��ջ�ɹ�\n");
		
    printf("������һ�������ŵı��ʽ(��#����):\n");
    
    if(judge(S))
	    printf("ƥ��ɹ�\n");
    else 
		printf("ƥ��ʧ��\n");
    
    return 0;
}
