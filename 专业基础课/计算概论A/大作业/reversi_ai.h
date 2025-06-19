#include <iostream>
#include <cstdio>
#include <cstring>
 
using namespace std;
 
template <typename T> T min(const T &x, const T &y) { return x < y ? x : y; }
template <typename T> T max(const T &x, const T &y) { return x > y ? x : y; }
 
const int weight[10][10] = 
{
    500,-25,10,5,5,10,-25,500,
    -25,-45,1,1,1,1,-45,-25,
    10,1,3,2,2,3,1,10,
    5,1,2,1,1,2,1,5,
    5,1,2,1,1,2,1,5,
    10,1,3,2,2,3,1,10,
    -25,-45,1,1,1,1,-45,-25,
    500,-25,10,5,5,10,-25,500,
};//黑白棋AI的权值表

const int d[8][2] = //搜索的8个方向
{
    -1, 0, 1, 0, 0, -1, 0, 1,
    -1, -1, -1, 1, 1, -1, 1, 1
};
int state[10][10], position;
//black:1 white:-1
int cur[10][10];
inline int alpha_beta(int dep, int player, int alpha, int beta, int cnt,int color) //0 for me 1 for it
{
    if(dep > 7 || cnt > 64) //dep是搜索的层数
    {
        int ret = 0;
        for (int i = 1; i <= 8; ++i)
            for(int j = 1; j <= 8; ++j)
            {
                if (state[i][j]==color) ret+=weight[i][j];
                if (state[i][j]==0-color) ret-=weight[i][j];
            }
        return ret;
    }
    int temp[10][10], tot = 0;
    memcpy(temp, state, sizeof state);
    if(!player)//己方落子情况
        for(int id = 1, x, y, i, j; id <= 64; ++id)
        {
            i = (id-1>>3)+1, j = (id-1)%8+1;//1-64转化为二维数组下标
            if(state[i][j] == 0)
            {
                int flag = 0, t;//flag是否是可落子点
                for(int k = 0; k < 8; ++k)//8向搜索
                {
                    t = 0, x = i+d[k][0], y = j+d[k][1];
                    while(state[x][y] == 0-color) t++, x += d[k][0], y += d[k][1];
                    if(t && state[x][y] == color)//返回，翻转旗子
                    {
                        do
                        {
                            x -= d[k][0], y -= d[k][1];
                            state[x][y] = color;
                        } while(x!=i||y!= j);
                        flag = 1;
                    }
                }
                if(flag)//可翻转，继续搜索
                {
                    tot++;
                    int v = alpha_beta(dep+1, player^1, alpha, beta, cnt+1,color);
                    if(v > alpha)
                    {
                        if(!dep) position=id, memcpy(cur, state, sizeof state);//选择该点落子，并更新棋盘
                        alpha = v;
                    }
                    memcpy(state, temp, sizeof temp);//还原state，回溯
                    if(beta <= alpha) break;//max点剪枝
                }
            }
        }
    if(!tot) player = 1;//没有可落子点，也进行下一次搜索
    if(player)//对方落子情况
    {
        for (int id = 1, x, y, tx, ty, i, j; id <= 64; ++id)
        {
            i = (id-1>>3)+1, j = (id-1)%8+1;
            if(state[i][j] == 0)
            {
                int flag = 0, t;
                for(int k = 0; k < 8; ++k)
                {
                    t = 0, x = i+d[k][0], y = j+d[k][1];
                    while(state[x][y] == color) t++, x += d[k][0], y += d[k][1];
                    if(t && state[x][y] == 0-color)
                    {
                        do
                        {
                            x -= d[k][0], y -= d[k][1];
                            state[x][y] = 0-color;
                        } while(x != i || y != j);
                        flag=1;
                    }
                }
                if(flag)
                {
                    int v = alpha_beta(dep+1, player^1, alpha, beta, cnt+1,color);
                    if(beta > v) beta = v;
                    memcpy(state, temp, sizeof temp);
                    if(beta <= alpha) break;//min点剪枝
                }
            }
        }
    }
    return !player ? alpha : beta;
}
 
int mainAI(int board[10][10],int color,int round)
{
    for (int i=1;i<=8;i++)
    {
        for (int j=1;j<=8;j++)
        {
            if (board[i][j]!=2) cur[i][j]=board[i][j];
        }
    }
    memcpy(state, cur, sizeof(cur));
    position=0;
    alpha_beta(0, 0, -1000000000, 1000000000, (round-1)*2,color);
    return position;
    //cout<<color;
}