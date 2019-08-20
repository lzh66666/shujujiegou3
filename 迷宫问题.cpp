#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define TRUE 1
#define FALSE 0

#define STACK_INIT_SIZE 100   //存储空间初始化分配量
#define STACKINCREMENT 10
#define MAXLEN 10

typedef int Status;

typedef struct  {
	
	int r;  //位置的横坐标
	int c;  //位置的纵坐标
	
}PosType;

typedef struct  {
	
	int ord;  //通道块在路径上的序号
	PosType seat;  //通道块在迷宫中的坐标位置
	int di;   //从此通道块走向下一通道块的方向
	
}SElemType;  //栈的元素类型

typedef struct {
	
	int r;  //迷宫的行数，除去外墙
	int c;  //迷宫的列数，除去外墙
	char adr[MAXLEN][MAXLEN];
	
}MazeType;  //迷宫类型

typedef struct  
{
	SElemType *base;  //在栈构造之前和销毁之后，base的值为NULL
	SElemType *top;  //栈顶指针
	int stackSize;   //当前已分配的存储空间
}SqStack;
 
Status InitStack(SqStack &S){
	//构造一个空栈
	S.base = (SElemType *)malloc(sizeof(SElemType) * STACK_INIT_SIZE);
	if(!S.base)
		exit(OVERFLOW);
	S.top = S.base;
	S.stackSize = STACK_INIT_SIZE;
	return OK;
}
 
 
Status StackEmpty(const SqStack &S){
	//判断栈是否为空
	if(S.top == S.base)  
		return TRUE;  //栈空
	return FALSE;
}
 
 
 
Status Push(SqStack &S, const SElemType &e){
	//插入元素e为新的栈顶元素
	if(S.top - S.base >= S.stackSize)
	{
		//栈满
		S.base = (SElemType *)realloc(S.base, sizeof(SElemType) * (S.stackSize + STACKINCREMENT));
		if(!S.base)
			exit(OVERFLOW);
		S.top = S.base + S.stackSize;
		S.stackSize += STACKINCREMENT;
	}
	*S.top++ = e;
	return OK;
}
 
Status Pop(SqStack &S,SElemType &e){
	//若栈不空，则删除S的栈顶元素
	if(S.top == S.base )
		return ERROR;
	e = *--S.top;
	return OK;
}
 
Status InitMaze(MazeType &maze){
	//初始化一个迷宫
	maze.c = 8;  //迷宫的行数
	maze.r = 8;  //迷宫的列数
	int i, j;
	for(i= 0; i < 10; ++i)
	{
		//初始化外墙
		maze.adr[0][i] = '#';
		maze.adr[9][i] = '#';
		maze.adr[i][0] = '#';
		maze.adr[i][9] = '#';
	}
	srand(time(NULL));
	for(i = 1; i < 9; ++i)  //生成迷宫
	{
		for(j = 1; j < 9; ++j)
		{
			int i_rand = rand()%2;
			if(i_rand == 1)
				maze.adr[i][j] = '1';
			else
				maze.adr[i][j] = '0';
		}
	}
	/*for(i = 0; i < 10; ++i)
	{
		for(j = 0; j < 10; ++j)
		{
			printf("%2c",maze.adr[i][j]);
		}
		printf("\n");
	}*/
	return OK;
}
 
Status Pass(const MazeType &M, PosType curpos){
	//判断当前位置是否可通
	if(M.adr[curpos.r][curpos.c] == '1')
		return TRUE;
	else
		return FALSE;
}
 
PosType NextPos(PosType curpos, int i){
	//探索下一位置并返回下一位置的坐标
	PosType nextPos = curpos;
	switch(i){
		
		case 1:nextPos.c += 1;break;//向东一步
		case 2:nextPos.r += 1;break;//向南一步
		case 3:nextPos.c -= 1;break;//向西一步
		case 4:nextPos.r -= 1;break;//向北一步
		default:
			exit(ERROR);
	}
	return nextPos;
}
 
Status MarkPrint(MazeType &M, PosType curpos){
	//曾走过但不通留下标记并返回OK;
	M.adr[curpos.r][curpos.c] = 'x'; //@表示走过但不通
	return OK;
}
 
 
Status FootPrint(MazeType &M, PosType curpos){
	//走过的地方留下足迹
	M.adr[curpos.r][curpos.c] = 3;//表示可通,用笑脸表示
	return OK;
}
 
 
Status MazePath(MazeType &M,PosType start, PosType end){
	//若迷宫M中存在从入口start到出口end的通道，则求得一条存放在栈中，
	//并返回TRUE,否则返回FALSE;
	SqStack S;
	InitStack(S);
	SElemType e;
	PosType curpos = start;  //设定当前位置为入口位置
	int curstep = 1; //探索第一步
	do
	{
		if(Pass(M,curpos))
		{
			//当前位置可以通过，是未曾走过的通道块
			FootPrint(M,curpos);//留下足迹
			e.ord = curstep;
			e.seat = curpos;
			e.di = 1;
			Push(S,e);//加入路径
			if(curpos.r == end.r && curpos.c == end.c) 
				return TRUE;//到达出口
			curpos = NextPos(curpos,1);  //下一位置是当前位置的东邻
			++curstep;  //探索下一步
		}
		else
		{
			//当前位置不能通过
			if(!StackEmpty(S))
			{
				Pop(S,e);  
				while(e.di == 4 && !StackEmpty(S))//栈不空，四周均不通
				{
					//留下不能通过的标记，并退回一步
					MarkPrint(M,e.seat);
					Pop(S,e);
				}
				if(e.di < 4){
					
					++e.di;//换下一个方向探索
					Push(S,e);
					curpos = NextPos(e.seat,e.di);//设定当前位置是该新方向上的相邻块
				}
			}
		}
	}while(!StackEmpty(S));
	return FALSE;
}
 
 
Status PrintMaze(const MazeType &M){
	//输出迷宫
	int i,j;
	for(i = 0; i < 11; ++i)
	{
		if(0 == i)
			printf("  ");
		else
			printf("%2d",i-1);//打印列名
	}
	printf("\n");
	for(i = 0; i < 10; ++i)
	{
		printf("%2d",i);
		for(j = 0; j < 10; ++j)
		{
			printf("%2c",M.adr[i][j]);
		}
		printf("\n");
	}
	return OK;
}
int main(int argc,char **argv){
	MazeType M;
	
	while(1)
	{
		InitMaze(M);
		
		printf("迷宫为：\n");
		printf("其中'#'代表外墙，'1'表示通道,'0'表示不可走\n");
		PrintMaze(M);
		
		PosType In,Out;
		printf("请输入入口坐标：");
		scanf("%d %d",&In.r,&In.c);
		printf("请输入出口坐标:");
		scanf("%d %d",&Out.r,&Out.c);
		
		if(MazePath(M,In,Out))
		{
			printf("其中心形表示路径，x表示此路不通:\n");
			PrintMaze(M);
		}
		else
		printf("没有通道\n");
		system("pause");
	}
	
	return 0;
}
