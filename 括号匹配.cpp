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
    //初始化栈 
    S.base=(SElemType *)malloc(INIT_SIZE*sizeof(SElemType));
    if(!S.base)
		exit(OVERFLOW);
    S.top=S.base;
    S.stacksize=INIT_SIZE;
    return OK;
}

Status Push(Stack &S,char e){
    //入栈 
    if(S.top-S.base>=S.stacksize){    //栈满，重新分配内存 
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
    //出栈 
    char e;
    
    if(S.top==S.base)
	    return ERROR;    //栈空，出错 
    e=*(--S.top);
    return e;
}

Status judge(Stack &S){
    //进行表达式的输入和判断 
    SElemType *p;
    char n;
    
    scanf("%c",&n);            		//第一个括号的检测
    while(n!='(' && n!='[')        //忽略数字等其他符号，直到输入括号
    {
        if(n==')' || n==']' || n=='#')
		    return FALSE;    //若为')'或']'，则表明不匹配。'#'用于结束输入
        scanf("%c",&n);    
    }
    
    if(n=='(' || n=='[')
	    Push(S,n);    //检测到左括号，进栈
    scanf("%c",&n);
    while(n!='#')    //'#'用于结束输入
    {    
        if(n=='(' || n==')' || n=='[' || n==']')
        {
            p=S.top;
            Push(S,n);
            if(*(p-1)=='(')        //与前一个括号比较
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
	    return TRUE; //栈内没有元素时，说明匹配 
    else 
		return FALSE;
}

int main(int argc,char **argv){
    Stack S;
    
    if(InitStack(S)) 
		printf("初始化栈成功\n");
		
    printf("请输入一个带括号的表达式(以#结束):\n");
    
    if(judge(S))
	    printf("匹配成功\n");
    else 
		printf("匹配失败\n");
    
    return 0;
}
