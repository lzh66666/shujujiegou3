#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define TRUE 1
#define FALSE 0

#define STACK_INIT_SIZE 100   //�洢�ռ��ʼ��������
#define STACKINCREMENT 10
#define MAXLEN 10

typedef int Status;

typedef struct  {
	
	int r;  //λ�õĺ�����
	int c;  //λ�õ�������
	
}PosType;

typedef struct  {
	
	int ord;  //ͨ������·���ϵ����
	PosType seat;  //ͨ�������Թ��е�����λ��
	int di;   //�Ӵ�ͨ����������һͨ����ķ���
	
}SElemType;  //ջ��Ԫ������

typedef struct {
	
	int r;  //�Թ�����������ȥ��ǽ
	int c;  //�Թ�����������ȥ��ǽ
	char adr[MAXLEN][MAXLEN];
	
}MazeType;  //�Թ�����

typedef struct  
{
	SElemType *base;  //��ջ����֮ǰ������֮��base��ֵΪNULL
	SElemType *top;  //ջ��ָ��
	int stackSize;   //��ǰ�ѷ���Ĵ洢�ռ�
}SqStack;
 
Status InitStack(SqStack &S){
	//����һ����ջ
	S.base = (SElemType *)malloc(sizeof(SElemType) * STACK_INIT_SIZE);
	if(!S.base)
		exit(OVERFLOW);
	S.top = S.base;
	S.stackSize = STACK_INIT_SIZE;
	return OK;
}
 
 
Status StackEmpty(const SqStack &S){
	//�ж�ջ�Ƿ�Ϊ��
	if(S.top == S.base)  
		return TRUE;  //ջ��
	return FALSE;
}
 
 
 
Status Push(SqStack &S, const SElemType &e){
	//����Ԫ��eΪ�µ�ջ��Ԫ��
	if(S.top - S.base >= S.stackSize)
	{
		//ջ��
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
	//��ջ���գ���ɾ��S��ջ��Ԫ��
	if(S.top == S.base )
		return ERROR;
	e = *--S.top;
	return OK;
}
 
Status InitMaze(MazeType &maze){
	//��ʼ��һ���Թ�
	maze.c = 8;  //�Թ�������
	maze.r = 8;  //�Թ�������
	int i, j;
	for(i= 0; i < 10; ++i)
	{
		//��ʼ����ǽ
		maze.adr[0][i] = '#';
		maze.adr[9][i] = '#';
		maze.adr[i][0] = '#';
		maze.adr[i][9] = '#';
	}
	srand(time(NULL));
	for(i = 1; i < 9; ++i)  //�����Թ�
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
	//�жϵ�ǰλ���Ƿ��ͨ
	if(M.adr[curpos.r][curpos.c] == '1')
		return TRUE;
	else
		return FALSE;
}
 
PosType NextPos(PosType curpos, int i){
	//̽����һλ�ò�������һλ�õ�����
	PosType nextPos = curpos;
	switch(i){
		
		case 1:nextPos.c += 1;break;//��һ��
		case 2:nextPos.r += 1;break;//����һ��
		case 3:nextPos.c -= 1;break;//����һ��
		case 4:nextPos.r -= 1;break;//��һ��
		default:
			exit(ERROR);
	}
	return nextPos;
}
 
Status MarkPrint(MazeType &M, PosType curpos){
	//���߹�����ͨ���±�ǲ�����OK;
	M.adr[curpos.r][curpos.c] = 'x'; //@��ʾ�߹�����ͨ
	return OK;
}
 
 
Status FootPrint(MazeType &M, PosType curpos){
	//�߹��ĵط������㼣
	M.adr[curpos.r][curpos.c] = 3;//��ʾ��ͨ,��Ц����ʾ
	return OK;
}
 
 
Status MazePath(MazeType &M,PosType start, PosType end){
	//���Թ�M�д��ڴ����start������end��ͨ���������һ�������ջ�У�
	//������TRUE,���򷵻�FALSE;
	SqStack S;
	InitStack(S);
	SElemType e;
	PosType curpos = start;  //�趨��ǰλ��Ϊ���λ��
	int curstep = 1; //̽����һ��
	do
	{
		if(Pass(M,curpos))
		{
			//��ǰλ�ÿ���ͨ������δ���߹���ͨ����
			FootPrint(M,curpos);//�����㼣
			e.ord = curstep;
			e.seat = curpos;
			e.di = 1;
			Push(S,e);//����·��
			if(curpos.r == end.r && curpos.c == end.c) 
				return TRUE;//�������
			curpos = NextPos(curpos,1);  //��һλ���ǵ�ǰλ�õĶ���
			++curstep;  //̽����һ��
		}
		else
		{
			//��ǰλ�ò���ͨ��
			if(!StackEmpty(S))
			{
				Pop(S,e);  
				while(e.di == 4 && !StackEmpty(S))//ջ���գ����ܾ���ͨ
				{
					//���²���ͨ���ı�ǣ����˻�һ��
					MarkPrint(M,e.seat);
					Pop(S,e);
				}
				if(e.di < 4){
					
					++e.di;//����һ������̽��
					Push(S,e);
					curpos = NextPos(e.seat,e.di);//�趨��ǰλ���Ǹ��·����ϵ����ڿ�
				}
			}
		}
	}while(!StackEmpty(S));
	return FALSE;
}
 
 
Status PrintMaze(const MazeType &M){
	//����Թ�
	int i,j;
	for(i = 0; i < 11; ++i)
	{
		if(0 == i)
			printf("  ");
		else
			printf("%2d",i-1);//��ӡ����
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
		
		printf("�Թ�Ϊ��\n");
		printf("����'#'������ǽ��'1'��ʾͨ��,'0'��ʾ������\n");
		PrintMaze(M);
		
		PosType In,Out;
		printf("������������꣺");
		scanf("%d %d",&In.r,&In.c);
		printf("�������������:");
		scanf("%d %d",&Out.r,&Out.c);
		
		if(MazePath(M,In,Out))
		{
			printf("�������α�ʾ·����x��ʾ��·��ͨ:\n");
			PrintMaze(M);
		}
		else
		printf("û��ͨ��\n");
		system("pause");
	}
	
	return 0;
}
