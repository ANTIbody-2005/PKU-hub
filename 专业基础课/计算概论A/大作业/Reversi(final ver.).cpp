#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <Windows.h>
#include <setjmp.h>
#include <fstream>
#include "reversi_ai.h"
using namespace std;

int Board[10][10]={0},color,tempcolor,yourcolor,roundnum,mode=0,mem=0,pvp=0;
int tempBoard[10][10]={0};
//1为黑，-1为白，0为空，2为能下，3为边界 
int flag[2]={0,1};//记忆连续2回合的落子情况，当连续两回合无法落子时游戏结束，0存白，1存黑

//初始化棋盘（完成） 
void initialize(void) 
{
	memset(Board,0,sizeof(Board));
	Board[4][4]=-1;Board[5][5]=-1;
	Board[4][5]=1;Board[5][4]=1;
	for (int i=0;i<=9;i++)
	{
		Board[0][i]=3;
		Board[9][i]=3;
		Board[i][0]=3;
		Board[i][9]=3;
	}
}

//画棋盘（完成） 
void printBoard(int b[10][10])
{        
	printf("     A   B   C   D   E   F   G   H\n");
	printf("  ---------------------------------\n");
	for (int i=1;i<=8;i++)
	{
		printf("%d ", i);
		for (int i1=1;i1<=8;i1++)
		{
			printf("| ");
			switch (b[i][i1])
			{
				case 0:cout<<" ";break;
				case 1:cout<<"○";break;
				case -1:cout<<"●";break;
				case 2:cout<<"·";
			}
			printf(" ");
		}
		printf("|\n");
		printf("  ---------------------------------\n");
	}
	cout<<endl;
}

// //输出原始数字棋盘(for test only)
// void printori(int a[10][10])
// {
// 	for (int i=0;i<=10;i++)
// 	{
// 		for (int i1=0;i1<=10;i1++)
// 		{
// 			cout<<" "<<a[i][i1]<<" ";
// 			if (i1==10) cout<<endl;
// 		}
// 	}
// }

//检测是否可落子 （完成） 
bool judge(int a,int b,int color)
{
	if (Board[a][b]!=0) return false;
	else
	{
		for (int dx=-1;dx<=1;dx++)
		{
			for (int dy=-1;dy<=1;dy++)
			{
				if (Board[a+dx][b+dy]+color!=0) continue;
				else
				{
					int x=a+dx,y=b+dy;
					while (Board[x][y]+color==0)
					{
						x+=dx;
						y+=dy;
					}
					if (Board[x][y]==color)
					{
						return true;
					}
				}
			}
		}
		return false;
	}
} 

//寻找可落子点并标记之，有返回1，无返回0 （完成） 
int search(int color)
{
	for (int i=1;i<=8;i++)
	{
		for (int i1=1;i1<=8;i1++)
		{
			if (Board[i][i1]==2) Board[i][i1]=0;
		}
	}
	int exist=0;
	memset(tempBoard,0,sizeof(tempBoard));
	for (int i=1;i<=8;i++)
	{
		for (int i1=1;i1<=8;i1++)
		{
			if (judge(i,i1,color))
			{
				exist=1;
				tempBoard[i][i1]=2;
			}
		}
	}
	for (int i=1;i<=8;i++)
	{
		for (int i1=1;i1<=8;i1++)
		{
			if (tempBoard[i][i1]==2) Board[i][i1]=2;
		}
	}
	if (exist) return 1;
	else return 0;
}

//翻转旗子操作，并清除可落子标记（完成） 
void reverse(int a,int b,int color)
{
	Board[a][b]=color;
	int reBoard[10][10]={};
	for (int dx=-1;dx<=1;dx++)
	{
		for (int dy=-1;dy<=1;dy++)
		{
			if (Board[a+dx][b+dy]+color!=0) continue;
			else
			{
				int x=a+dx,y=b+dy;
				while (Board[x][y]+color==0)
				{
					x+=dx;y+=dy;
				}
				if (Board[x][y]==color)
				{
					x-=dx;y-=dy;
					while (Board[x][y]+color==0)
					{
						Board[x][y]=color;
						x-=dx;y-=dy;
					}
				}
			}
		}
	}
	for (int i=1;i<=8;i++)
	{
		for (int i1=1;i1<=8;i1++)
		{
			if (Board[i][i1]==2) Board[i][i1]=0;
		}
	}
} 

//某方落子操作，落子返回位置（1-64），暂停返回0 ,其他返回-1（完成） 
int place(int color)
{
	char ch[10]={};
	while (true)
	{
		printf("请%s方输入落子位置，或输入P暂停游戏\n",color==1?"黑":"白");
		cin.getline(ch,10);
		if (strlen(ch)==1&&ch[0]=='P')
		{
			return 0;
		}
		else if (strlen(ch)==2&&(ch[0]>='A'&&ch[0]<='H')&&(ch[1]>='1'&&ch[1]<='8'))
		{
			if (Board[ch[1]-'0'][ch[0]-'A'+1]==2) return 8*(ch[1]-'1')+(ch[0]-'A'+1);
			else if (Board[ch[1]-'0'][ch[0]-'A'+1]==1||Board[ch[1]-'0'][ch[0]-'A'+1]==-1) 
			{
				printf("该处已有棋子\n");
				system("pause");
				return -1;
			}
			else 
			{
				printf("该处不可落子\n");
				system("pause");
				return -1;
			}
		}
		else
		{
			printf("非法输入！请重新落子，或输入P暂停游戏\n");
			system("pause");
			return -1;
		}
	}
} 

//黑子计数（完成） 
int countBlack(void)
{
	int count=0;
	for (int i=1;i<=8;i++)
	{
		for (int i1=1;i1<=8;i1++)
		{
			if (Board[i][i1]==1) count++;
		}
	}
	return count;
} 
//白子计数（完成） 
int countWhite(void)
{
	int count=0;
	for (int i=1;i<=8;i++)
	{
		for (int i1=1;i1<=8;i1++)
		{
			if (Board[i][i1]==-1) count++;
		}
	}
	return count;
} 
//输出旗子数（完成） 
void printcount(void) 
{
	printf("○黑棋数： %d\n", countBlack());
	printf("●白棋数： %d\n", countWhite());
}


//规则介绍（完成）
void rule(void)
{
	system("cls");
	printf("[游戏规则介绍]\n");
	printf("黑白棋，又叫翻转棋（Reversi）、奥赛罗棋（Othello）\n");
	printf("黑白棋的棋盘大小为8×8；棋局开始时，棋盘中心存在黑白各2颗子，黑方先手\n");
	printf("在回合内，棋手需要下在对方的一颗棋旁边，使对方的部分棋子在横、竖或斜向上被本回合所下的棋和自己的其他棋子相夹；一旦落下符合条件的棋子，被夹的对方棋子会转换为己方棋子\n");
	printf("当一方没有地方可以落子时，跳过其回合，由对方继续落子，直到再次出现可以落子的点；如果一方存在可以落子的点，其必须落子\n");
	printf("当双方都没有地方可以落子时，游戏结束，以棋盘上棋子数量多的一方获胜，数量相同则为平局\n\n");
	system("pause");
} 

//存档，成功返回1，失败返回0
int save(int num,int roundnum1,int temp1,int temp2)
{
	switch (num)
	{
		case 1:
		{
			ofstream outfile("saves/save1.txt");
            if (!outfile) {cerr<<"存档失败!"<<endl;return 0;}
			outfile<<roundnum1<<" "<<temp1<<" "<<temp2<<" ";
			for (int i=0;i<=9;i++) {for (int j=0;j<=9;j++) {outfile<<((Board[i][j]!=2)?Board[i][j]:0)<<" ";}}
			outfile.close();
			break;
		}
		case 2:
		{
			ofstream outfile("saves/save2.txt");
            if (!outfile) {cerr<<"存档失败!"<<endl;return 0;}
			outfile<<roundnum1<<" "<<temp1<<" "<<temp2<<" ";
			for (int i=0;i<=9;i++) {for (int j=0;j<=9;j++) {outfile<<((Board[i][j]!=2)?Board[i][j]:0)<<" ";}}
			outfile.close();
			break;
		}
		case 3:
		{
			ofstream outfile("saves/save3.txt");
            if (!outfile) {cerr<<"存档失败!"<<endl;return 0;}
			outfile<<roundnum1<<" "<<temp1<<" "<<temp2<<" ";
			for (int i=0;i<=9;i++) {for (int j=0;j<=9;j++) {outfile<<((Board[i][j]!=2)?Board[i][j]:0)<<" ";}}
			outfile.close();
			break;
		}
		case 4:
		{
			ofstream outfile("saves/save4.txt");
            if (!outfile) {cerr<<"存档失败!"<<endl;return 0;}
			outfile<<roundnum1<<" "<<temp1<<" "<<temp2<<" ";
			for (int i=0;i<=9;i++) {for (int j=0;j<=9;j++) {outfile<<((Board[i][j]!=2)?Board[i][j]:0)<<" ";}}
			outfile.close();
			break;
		}
		case 5:
		{
			ofstream outfile("saves/save5.txt");
            if (!outfile) {cerr<<"存档失败!"<<endl;return 0;}
			outfile<<roundnum1<<" "<<temp1<<" "<<temp2<<" ";
			for (int i=0;i<=9;i++) {for (int j=0;j<=9;j++) {outfile<<((Board[i][j]!=2)?Board[i][j]:0)<<" ";}}
			outfile.close();
			break;
		}
		case 6:
		{
			ofstream outfile("saves/save6.txt");
            if (!outfile) {cerr<<"存档失败!"<<endl;return 0;}
			outfile<<roundnum1<<" "<<temp1<<" "<<temp2<<" ";
			for (int i=0;i<=9;i++) {for (int j=0;j<=9;j++) {outfile<<((Board[i][j]!=2)?Board[i][j]:0)<<" ";}}
			outfile.close();
			break;
		}
		case 7:
		{
			ofstream outfile("saves/save7.txt");
            if (!outfile) {cerr<<"存档失败!"<<endl;return 0;}
			outfile<<roundnum1<<" "<<temp1<<" "<<temp2<<" ";
			for (int i=0;i<=9;i++) {for (int j=0;j<=9;j++) {outfile<<((Board[i][j]!=2)?Board[i][j]:0)<<" ";}}
			outfile.close();
			break;
		}
		case 8:
		{
			ofstream outfile("saves/save8.txt");
            if (!outfile) {cerr<<"存档失败!"<<endl;return 0;}
			outfile<<roundnum1<<" "<<temp1<<" "<<temp2<<" ";
			for (int i=0;i<=9;i++) {for (int j=0;j<=9;j++) {outfile<<((Board[i][j]!=2)?Board[i][j]:0)<<" ";}}
			outfile.close();
			break;
		}
		case 9:
		{
			ofstream outfile("saves/save9.txt");
            if (!outfile) {cerr<<"存档失败!"<<endl;return 0;}
			outfile<<roundnum1<<" "<<temp1<<" "<<temp2<<" ";
			for (int i=0;i<=9;i++) {for (int j=0;j<=9;j++) {outfile<<((Board[i][j]!=2)?Board[i][j]:0)<<" ";}}
			outfile.close();
			break;
		}
	}
	return 1;
}


//主界面，返回：1新游戏 2读档 3查看规则 0退出 （完成） 
int menu(void)
{
	while (true)
	{
		system("cls");
		printf("欢迎来到 [黑白棋游戏Reversi] !\n\n");
	    printf("[请选择模式]\n");
    	printf("输入N 以开始新游戏\n");
    	printf("输入R 以进行存档读取\n");
    	printf("输入H 以查看游戏规则\n");
    	printf("输入Q 以退出游戏\n");
    	char c[3];
    	cin.getline(c,3);
    	if (strlen(c)==1&&(c[0]=='N'||c[0]=='R'||c[0]=='H'||c[0]=='Q'))
    	{
    		if (c[0]=='N') return 1;
    		if (c[0]=='R') return 2;
    		if (c[0]=='H') return 3;
    		if (c[0]=='Q') return 0;
		}
    	else printf("非法输入！\n");system("pause");
	}
} 
//暂停时的主界面，返回：1新游戏 2读档 3查看规则 4返回暂停 0退出 （完成） 
int pausemenu(void)
{
	while (true)
	{
		system("cls");
		printf("欢迎来到 [黑白棋游戏Reversi] !\n\n");
	    printf("[请选择模式]\n");
    	printf("输入N 以开始新游戏\n");
    	printf("输入B 以返回暂停界面\n");
    	printf("输入R 以进行存档读取\n");
    	printf("输入H 以查看游戏规则\n");
    	printf("输入Q 以退出游戏\n");
    	char c[3];
    	cin.getline(c,3);
    	if (strlen(c)==1&&(c[0]=='N'||c[0]=='B'||c[0]=='R'||c[0]=='H'||c[0]=='Q'))
    	{
    		if (c[0]=='N') return 1;
    		if (c[0]=='B') return 4;
    		if (c[0]=='R') return 2;
    		if (c[0]=='H') return 3;
    		if (c[0]=='Q') return 0;
		}
    	else printf("非法输入！\n");system("pause");
	}
}

//暂停界面，返回：1返回游戏 2存档 3返回首页 0退出 （完成） 
int pause(void) 
{
	while (true)
	{
		system("cls");
	    printf("[游戏暂停中]\n");
    	printf("输入B 以返回游戏\n");
    	printf("输入S 以进行存档\n");
    	printf("输入M 以返回主界面\n");
    	printf("输入Q 以退出游戏\n");
    	char c[3];
    	cin.getline(c,3);
    	if (strlen(c)==1&&(c[0]=='B'||c[0]=='S'||c[0]=='M'||c[0]=='Q'))
    	{
    		if (c[0]=='B') return 1;
    		if (c[0]=='S') return 2;
    		if (c[0]=='M') return 3;
    		if (c[0]=='Q') return 0;
		}
		printf("非法输入！\n");
		system("pause");
	}
}

//退出游戏，返回：0返回（完成） 
int quit(void)
{
	system("cls");
	printf("确定直接关闭游戏吗？未保存的棋局将会丢失！\n");
	printf("输入Q 以确认退出\n");
	printf("输入其他字符以返回\n");
	char c[3];
	cin.getline(c,3);
	if (strlen(c)==1&&c[0]=='Q') exit(0);
	else return 0;
} 

//



//游戏的一个循环，如果落子返回落子位置，如果无法落子返回0，新游戏返回-1，读档返回-2 （完成）
int round(int color)
{
	if (search(color)==0)//无法落子
	{
		system("cls");
		printBoard(Board);
		printcount();
		printf("%s方无法落子，该回合跳过\n",(color==1)?"黑":"白");
		return 0;
	}
	else//可以落子
	{
		while(true)
		{
			system("cls");
			printBoard(Board);
		    printcount();
		    if (mem)
		    {
		    	printf("上一回合%s方在%c%d处落子\n",(color==1)?"白":"黑",'A'-1+((mem%8==0)?8:mem%8),(mem%8==0)?mem/8:mem/8+1);
			}
			int pos;
			if (pvp==0)
			{
			    if (color==yourcolor)
			    {
				    pos=place(color);
			    }
			    else
			    {
				    printf("电脑正在落子……\n");
				    pos=mainAI(Board,color,1);
				    system("pause");
			    }
			}
			else
			{
				pos=place(color);
			}
			if (pos>0)//落子
			{
				reverse((pos%8==0)?pos/8:pos/8+1,(pos%8==0)?8:pos%8,color);
				return pos;
			}
			else if (pos==0)//暂停
			{
				while(true)
				{
					switch (pause())
				    {
				    	case 0: quit();break;
				    	case 1: break;
				    	case 2: 
						{
							while (true)//写的真是史山啊！！！！！！！
							{
								system("cls");
							    printf("选择你要保存的存档序号(1-9)\n");
							    int flag[9];
							    ifstream infile1("saves/save1.txt");
							    infile1>>flag[0];
							    if (flag[0]) printf("[存档1]\n");
							    else printf("[空]\n");
							    infile1.close();
							    ifstream infile2("saves/save2.txt");
							    infile2>>flag[1];
							    if (flag[1]) printf("[存档2]\n");
							    else printf("[空]\n");
							    infile2.close();
						    	ifstream infile3("saves/save3.txt");
							    infile3>>flag[2];
							    if (flag[2]) printf("[存档3]\n");
							    else printf("[空]\n");
							    infile3.close();
							    ifstream infile4("saves/save4.txt");
							    infile4>>flag[3];
							    if (flag[3]) printf("[存档4]\n");
							    else printf("[空]\n");
							    infile4.close();
							    ifstream infile5("saves/save5.txt");
							    infile5>>flag[4];
							    if (flag[4]) printf("[存档5]\n");
							    else printf("[空]\n");
							    infile5.close();
							    ifstream infile6("saves/save6.txt");
							    infile6>>flag[5];
							    if (flag[5]) printf("[存档6]\n");
							    else printf("[空]\n");
							    infile6.close();
							    ifstream infile7("saves/save7.txt");
							    infile7>>flag[6];
							    if (flag[6]) printf("[存档7]\n");
							    else printf("[空]\n");
							    infile7.close();
							    ifstream infile8("saves/save8.txt");
							    infile8>>flag[7];
							    if (flag[7]) printf("[存档8]\n");
							    else printf("[空]\n");
							    infile8.close();
							    ifstream infile9("saves/save9.txt");
							    infile9>>flag[8];
							    if (flag[8]) printf("[存档9]\n");
							    else printf("[空]\n");
							    infile9.close();
								printf("\n输入N 以返回\n");
							    char c[10];
							    cin.getline(c,10);
							    if (strlen(c)==1&&c[0]>='1'&&c[0]<='9')
							    {
									if (flag[c[0]-'1'])
									{
										printf("确定覆盖该存档吗?\n");
										printf("输入Y 以确定覆盖存档\n");
										printf("输入其他字符以取消\n");
										char c1[10];
										cin.getline(c1,10);
										if (strlen(c1)==1&&c1[0]=='Y')
										{
											save(c[0]-'0',roundnum,flag[0],flag[1]);
											break;
										}
									}
									else 
									{
										save(c[0]-'0',roundnum,flag[0],flag[1]);
									    break;
									}
							    }
								else if (strlen(c)==1&&c[0]=='N')
								{
									break;
								}
							    else
								{
									printf("非法输入！\n");
									system("pause");
								}
							}
							break;
						}
				    	case 3: 
				    	{
				    		switch (pausemenu())
				    		{
							    case 0: quit();break;
							    case 1: 
							    {
							    	printf("确定开始新游戏吗？现有的棋局将不会保存！\n");
							    	printf("输入N 以确认开始新游戏\n");
							    	printf("输入其他字符以返回主界面\n");
							    	char c[3];
							    	cin.getline(c,3);
							    	if (strlen(c)==1&&c[0]=='N') 
									{
										return -1;
										break;
									}
									else break;
								}
								case 2: 
								{
									while (true)//不是我100行的读档函数怎么忘了调用啊啊啊！！！
							        {
								        system("cls");
							            printf("选择你要读取的存档序号(1-9)\n");
							            int flag[9];
							            ifstream infile1("saves/save1.txt");
							            infile1>>flag[0];
							            if (flag[0]) printf("[存档1]\n");
							            else printf("[空]\n");
							            infile1.close();
							            ifstream infile2("saves/save2.txt");
							            infile2>>flag[1];
							            if (flag[1]) printf("[存档2]\n");
							            else printf("[空]\n");
							            infile2.close();
						    	        ifstream infile3("saves/save3.txt");
							            infile3>>flag[2];
							            if (flag[2]) printf("[存档3]\n");
							            else printf("[空]\n");
							            infile3.close();
							            ifstream infile4("saves/save4.txt");
							            infile4>>flag[3];
							            if (flag[3]) printf("[存档4]\n");
					        		    else printf("[空]\n");
							            infile4.close();
							            ifstream infile5("saves/save5.txt");
							            infile5>>flag[4];
							            if (flag[4]) printf("[存档5]\n");
							            else printf("[空]\n");
							            infile5.close();
							            ifstream infile6("saves/save6.txt");
							            infile6>>flag[5];
							            if (flag[5]) printf("[存档6]\n");
							            else printf("[空]\n");
							            infile6.close();
							            ifstream infile7("saves/save7.txt");
							            infile7>>flag[6];
							            if (flag[6]) printf("[存档7]\n");
							            else printf("[空]\n");
							            infile7.close();
							            ifstream infile8("saves/save8.txt");
							            infile8>>flag[7];
							            if (flag[7]) printf("[存档8]\n");
							            else printf("[空]\n");
							            infile8.close();
							            ifstream infile9("saves/save9.txt");
							            infile9>>flag[8];
							            if (flag[8]) printf("[存档9]\n");
							            else printf("[空]\n");
							            infile9.close();
										printf("\n输入N 以返回\n");
							            char c[10];
							            cin.getline(c,10);
							            if (strlen(c)==1&&c[0]>='1'&&c[0]<='9')
							            {
								        	if (flag[c[0]-'1'])
									        {
										        system("cls");
												int readBoard[10][10];
												int roundnum1,mycolor,temp1,temp2;
												switch (c[0]-'0')
												{
													case 1:
													{
														ifstream infile("saves/save1.txt");infile>>roundnum1>>temp1>>temp2;mycolor=(roundnum1%2==0)?1:-1;
														for (int i=0;i<=9;i++){for (int j=0;j<=9;j++){infile>>readBoard[i][j];}}
														break;
													}
													case 2:
													{
														ifstream infile("saves/save2.txt");infile>>roundnum1>>temp1>>temp2;mycolor=(roundnum1%2==0)?1:-1;
														for (int i=0;i<=9;i++){for (int j=0;j<=9;j++){infile>>readBoard[i][j];}}
														break;
													}
													case 3:
													{
														ifstream infile("saves/save3.txt");infile>>roundnum1>>temp1>>temp2;mycolor=(roundnum1%2==0)?1:-1;
														for (int i=0;i<=9;i++){for (int j=0;j<=9;j++){infile>>readBoard[i][j];}}
														break;
													}
													case 4:
													{
														ifstream infile("saves/save4.txt");infile>>roundnum1>>temp1>>temp2;mycolor=(roundnum1%2==0)?1:-1;
														for (int i=0;i<=9;i++){for (int j=0;j<=9;j++){infile>>readBoard[i][j];}}
														break;
													}
													case 5:
													{
														ifstream infile("saves/save5.txt");infile>>roundnum1>>temp1>>temp2;mycolor=(roundnum1%2==0)?1:-1;
														for (int i=0;i<=9;i++){for (int j=0;j<=9;j++){infile>>readBoard[i][j];}}
														break;
													}
													case 6:
													{
														ifstream infile("saves/save6.txt");infile>>roundnum1>>temp1>>temp2;mycolor=(roundnum1%2==0)?1:-1;
														for (int i=0;i<=9;i++){for (int j=0;j<=9;j++){infile>>readBoard[i][j];}}
														break;
													}
													case 7:
													{
														ifstream infile("saves/save7.txt");infile>>roundnum1>>temp1>>temp2;mycolor=(roundnum1%2==0)?1:-1;
														for (int i=0;i<=9;i++){for (int j=0;j<=9;j++){infile>>readBoard[i][j];}}
														break;
													}
													case 8:
													{
														ifstream infile("saves/save8.txt");infile>>roundnum1>>temp1>>temp2;mycolor=(roundnum1%2==0)?1:-1;
														for (int i=0;i<=9;i++){for (int j=0;j<=9;j++){infile>>readBoard[i][j];}}
														break;
													}
													case 9:
													{
														ifstream infile("saves/save9.txt");infile>>roundnum1>>temp1>>temp2;mycolor=(roundnum1%2==0)?1:-1;
														for (int i=0;i<=9;i++){for (int j=0;j<=9;j++){infile>>readBoard[i][j];}}
														break;
													}
												}
												printf("[存档%d预览]\n",c[0]-'0');
												printBoard(readBoard);
												printf("\n是否读取该存档?现有的棋局将被覆盖\n");
												printf("输入Y 以确认读取存档\n");
												printf("输入其他字母以取消\n");
												char c[10];
												cin.getline(c,10);
												if (strlen(c)==1&&c[0]=='Y')
												{
													roundnum=roundnum1;
													tempcolor=mycolor;
													flag[0]=temp1;flag[1]=temp2;
													mem=0;
													for (int i=0;i<=9;i++)
													{
														for (int j=0;j<=9;j++)
														{
															Board[i][j]=readBoard[i][j];
														}
													}
													return -2;
												}
									        }
									        else 
									        {
										        printf("这是一个空存档！\n");
									            system("pause");
									        }
							            }
										else if (strlen(c)==1&&c[0]=='N')
										{
											break;
										}
							            else
								        {
								        	printf("非法输入！\n");
									        system("pause");
								        }
							        }
									break;
								}
								case 3: rule();break;
								case 4: continue;
				    		}
				    	} 
				    }
					break;
				}
			}
			else
			{
				continue;
			}
		}
	}
} 

//新游戏，游戏结束返回0，新游戏返回1，读档游戏返回2
int newgame(void)//mode:0新游戏，1读档游戏
{
	while (true)
	{
		system("cls");
	    printf("[请选择游戏模式]\n");
	    printf("输入1 为玩家对战模式(pvp)\n");
	    printf("输入2 为人机对战模式(pve)\n");
		char c[10];
		cin.getline(c,10);
		if (strlen(c)==1&&c[0]=='1')//pvp
		{
			pvp=1;
		}
		else if (strlen(c)==1&&c[0]=='2')//pve
		{
			pvp=0;
		}
		else
		{
			printf("非法输入！");
			system("pause");
			continue;
		}
		break;
	}
	if (mode==0)
	{
		initialize();
		while (pvp==0)
		{
			system("cls");
		    printf("[请选择执棋颜色]\n");
		    printf("输入1 执黑(先手)\n输入2 执白(后手)\n");
		    char c0[10];cin.getline(c0,10);
		    if (strlen(c0)==1&&c0[0]=='1')
			{
				yourcolor=1;
			}
			else if (strlen(c0)==1&&c0[0]=='2')
			{
				yourcolor=-1;
			}
			else 
			{
				printf("非法输入！\n");
				system("pause");
				continue;
			}
	        color=1;//黑方先下 
	        flag[0]=1;flag[1]=1;
	        roundnum=0;
		    mem=0;
		    mode=1;
		    //cout<<"初始化！"<<endl;
		    //system("pause");
			break;
		}
		while (pvp==1)
		{
			color=1;//黑方先下 
	        flag[0]=1;flag[1]=1;
	        roundnum=0;
		    mem=0;
		    mode=1;
		    //cout<<"初始化！"<<endl;
		    //system("pause");
			break;
		}
	}
	else
	{
		while (pvp==0)
		{
			system("cls");
		    printf("[请选择执棋颜色]\n");
		    printf("输入1 执黑\n输入2 执白\n");
		    char c0[10];cin.getline(c0,10);
		    if (strlen(c0)==1&&c0[0]=='1')
		    {
		    	yourcolor=1;
		    }
		    else if (strlen(c0)==1&&c0[0]=='2')
		    {
			    yourcolor=-1;
		    }
			else
			{
				printf("非法输入！\n");
				system("pause");
				continue;
			}
			break;
		}
	}
	while (true)
	{
		if (flag[0]==0&&flag[1]==0) break;
		flag[(color==1)?1:0]=round(color);
		if (flag[(color==1)?1:0]==-1) 
		{
			return 1;
		}
		if (flag[(color==1)?1:0]==-2)
		{
			color=tempcolor;
			return 2;
		}
		mem=flag[(color==1)?1:0];
		color=0-color;
		roundnum++;
	}
	if (countBlack()>countWhite())
	{
		printf("游戏结束！恭喜黑方以%d:%d获胜！\n",countBlack(),countWhite());
	}
	else if (countBlack()<countWhite())
	{
		printf("游戏结束！恭喜白方以%d:%d获胜！\n",countWhite(),countBlack());
	}
	else
	{
		printf("游戏结束！双方%d:%d平局！\n",countWhite(),countBlack());
	}
	printf("按任意键回到主界面\n");
	system("pause");
	return 0;
} 

//主程序 
int main()
{
	system("chcp 65001");
	while (true)
	{
		switch (menu())
	    {
		    case 0: quit();continue;
		    case 1: 
			{
				while (true)
				{
					mode=0;
					int n=newgame(),nn=0;
					switch (n)
					{
						case 0: break;
						case 1: 
						{
							mode=0;
							continue;
						}
						case 2: 
						{
							while (true)
							{
								mode=1;
								int n1=newgame();
								if (n1==0) break;
								else if (n1==1) 
								{
									nn=1;break;
								}
								else continue;
							}
							break;
						}
					}
					if (nn)
					{
						continue;
					}
					else break;
				}
				continue;
			}
		    case 2: 
			{
				int ex=0;
				while (true)
				{
					system("cls");
					printf("选择你要读取的存档序号(1-9)\n");
					int flag[9];
					ifstream infile1("saves/save1.txt");
					infile1>>flag[0];
					if (flag[0]) printf("[存档1]\n");
					else printf("[空]\n");
		            infile1.close();
					ifstream infile2("saves/save2.txt");
					infile2>>flag[1];
					if (flag[1]) printf("[存档2]\n");
					else printf("[空]\n");
					infile2.close();
					ifstream infile3("saves/save3.txt");
					infile3>>flag[2];
					if (flag[2]) printf("[存档3]\n");
					else printf("[空]\n");
					infile3.close();
					ifstream infile4("saves/save4.txt");
					infile4>>flag[3];
					if (flag[3]) printf("[存档4]\n");
					else printf("[空]\n");
					infile4.close();
					ifstream infile5("saves/save5.txt");
					infile5>>flag[4];
					if (flag[4]) printf("[存档5]\n");
					else printf("[空]\n");
					infile5.close();
					ifstream infile6("saves/save6.txt");
					infile6>>flag[5];
					if (flag[5]) printf("[存档6]\n");
					else printf("[空]\n");
					infile6.close();
					ifstream infile7("saves/save7.txt");
					infile7>>flag[6];
					if (flag[6]) printf("[存档7]\n");
				     else printf("[空]\n");
					infile7.close();
					ifstream infile8("saves/save8.txt");
					infile8>>flag[7];
					if (flag[7]) printf("[存档8]\n");
					else printf("[空]\n");
					infile8.close();
					ifstream infile9("saves/save9.txt");
					infile9>>flag[8];
					if (flag[8]) printf("[存档9]\n");
					else printf("[空]\n");
					infile9.close();
					printf("\n输入N 以返回\n");
					char c[10];
					cin.getline(c,10);		            		            
					if (strlen(c)==1&&c[0]>='1'&&c[0]<='9')		            
					{
						if (flag[c[0]-'1'])
						{
							system("cls");
							int readBoard[10][10];
							int roundnum1,mycolor,temp1,temp2;
							switch (c[0]-'0')
							{
								case 1:
								{
									ifstream infile("saves/save1.txt");infile>>roundnum1>>temp1>>temp2;mycolor=(roundnum1%2==0)?1:-1;
									for (int i=0;i<=9;i++){for (int j=0;j<=9;j++){infile>>readBoard[i][j];}}
									break;
								}
								case 2:
								{
									ifstream infile("saves/save2.txt");infile>>roundnum1>>temp1>>temp2;mycolor=(roundnum1%2==0)?1:-1;
									for (int i=0;i<=9;i++){for (int j=0;j<=9;j++){infile>>readBoard[i][j];}}
									break;
								}
								case 3:
								{
									ifstream infile("saves/save3.txt");infile>>roundnum1>>temp1>>temp2;mycolor=(roundnum1%2==0)?1:-1;
									for (int i=0;i<=9;i++){for (int j=0;j<=9;j++){infile>>readBoard[i][j];}}
									break;
								}
								case 4:
								{
									ifstream infile("saves/save4.txt");infile>>roundnum1>>temp1>>temp2;mycolor=(roundnum1%2==0)?1:-1;
									for (int i=0;i<=9;i++){for (int j=0;j<=9;j++){infile>>readBoard[i][j];}}
									break;
								}
								case 5:
								{
									ifstream infile("saves/save5.txt");infile>>roundnum1>>temp1>>temp2;mycolor=(roundnum1%2==0)?1:-1;
									for (int i=0;i<=9;i++){for (int j=0;j<=9;j++){infile>>readBoard[i][j];}}
									break;
								}
								case 6:
								{
									ifstream infile("saves/save6.txt");infile>>roundnum1>>temp1>>temp2;mycolor=(roundnum1%2==0)?1:-1;
									for (int i=0;i<=9;i++){for (int j=0;j<=9;j++){infile>>readBoard[i][j];}}
									break;
								}
								case 7:
								{
									ifstream infile("saves/save7.txt");infile>>roundnum1>>temp1>>temp2;mycolor=(roundnum1%2==0)?1:-1;
									for (int i=0;i<=9;i++){for (int j=0;j<=9;j++){infile>>readBoard[i][j];}}
									break;
								}
								case 8:
								{
									ifstream infile("saves/save8.txt");infile>>roundnum1>>temp1>>temp2;mycolor=(roundnum1%2==0)?1:-1;
									for (int i=0;i<=9;i++){for (int j=0;j<=9;j++){infile>>readBoard[i][j];}}
									break;
								}
								case 9:
								{
									ifstream infile("saves/save9.txt");infile>>roundnum1>>temp1>>temp2;mycolor=(roundnum1%2==0)?1:-1;
									for (int i=0;i<=9;i++){for (int j=0;j<=9;j++){infile>>readBoard[i][j];}}
									break;
								}
							}
							printf("[存档%d预览]\n",c[0]-'0');
							printBoard(readBoard);
							printf("\n是否读取该存档?\n");
							printf("输入Y 以确认读取存档\n");
							printf("输入其他字母以取消\n");
							char c[10];
							cin.getline(c,10);
							if (strlen(c)==1&&c[0]=='Y')
							{
								roundnum=roundnum1;
								color=mycolor;
								flag[0]=temp1;flag[1]=temp2;
								mem=0;
								for (int i=0;i<=9;i++)
								{
									for (int j=0;j<=9;j++)
									{
										Board[i][j]=readBoard[i][j];
									}
								}
								break;
							}
						}
						else 
						{
							printf("这是一个空存档！\n");
							system("pause");
						}
					}
					else if (strlen(c)==1&&c[0]=='N')
					{
						ex=1;break;
					}
					else
					{
						printf("非法输入！\n");
						system("pause");
					}
				}
				if (ex==1)
				{
					break;
				}
				while (true)
				{
					mode=1;
				    int n=newgame();
				    if (n==0)
				    {
				    	continue;
				    }
				    else if (n==1)
				    {
				        while (true)
				        {
						    mode=0;
						    int n=newgame(),nn=0;
						    switch (n)
						    {
							    case 0: break;
							    case 1: continue;
							    case 2: 
							    {
								    while (true)
								    {
									    mode=1;
									    int n1=newgame();
									    if (n1==0) break;
									    else if (n1==1) 
									    {
									    	nn=1;break;
									    }
									    else continue;
								    }
								    break;
							    }
						    }
						    if (nn)
						    {
						    	continue;
						    }
						    else break;
				    	}
					    continue;	
				    }
				    else continue;
				    break;
				}
				
			}
		    case 3: rule();continue;
	    }
	}
	return 0;
}


