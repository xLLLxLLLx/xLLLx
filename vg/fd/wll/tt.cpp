#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <queue>
using namespace std;
int n,m;//n个点，m条边 
int head[100010];//这是邻接表的标志，head[i]表示以i为顶点的第一条边 
struct edge
{
    int cap,flow;//cap为容量，flow为流量 
    int from,to;//一条边的起点终点 
    int next;//和这条边起点相同的下一条边（邻接表标志） 
}mp[100010];
int cnt=-1;//邻接表输入数组 
int flag=0;//退出的标记 
void build_edge(int a,int b,int c)//构造邻接表，插入连接表 
{
    cnt++;
    mp[cnt].from=a;
    mp[cnt].to=b;
    mp[cnt].cap=c;
    mp[cnt].flow=0;
    mp[cnt].next=head[a];
    head[a]=cnt;
    cnt++;
    mp[cnt].from=b;//插入相反边 
    mp[cnt].to=a;
    mp[cnt].cap=0;
    mp[cnt].flow=0;
    mp[cnt].next=head[b];
    head[b]=cnt;
    return ;
}
int bfs(){//运用bfs找到増广路 
    int min_flow[100010];//min_flow[i]代表到第i好点时，当前所走过变的容量-流量的最小值 
    memset(min_flow,0,sizeof(min_flow));
    queue<int> Q;//用队列 维护 
    min_flow[1]=999999;//开始为无限大 
    int p[100010];//这个很重要，构造增光路时，记录当前点是由那条边找到的，以此找到増广路时能从终点以此到起点的边的流量加上最小值 
    p[1]=-1;
    Q.push(1);//起点入队 
    while(!Q.empty()){
        int now=Q.front();
        Q.pop();
        for(int e=head[now];e!=-1;e=mp[e].next){//邻接表枚举当前点的所有连边 
            int v=mp[e].cap-mp[e].flow;//v就是为当前边容量-流量 
            if(v>0 && !min_flow[mp[e].to])//当v>0 并且这个点没有访问过时 
            {
                p[mp[e].to]=e;//记录到达这个点的边的序号 
                min_flow[mp[e].to]=min(min_flow[now],v);//维护最小值 
                Q.push(mp[e].to);//维护bfs 
            }
        }
        if(min_flow[n]!=0)//如果终点得到更新，说明找到増广路，直接break 
            break;
    }
    if(min_flow[n]==0)//当没有更新到终点，也就是重点最小增加值为0时，说明没有増广路了，直接完事 
        flag=1;
    for(int e=n;p[e]!=-1;e=mp[p[e]].from)//从终点开始，以此倒着走増广路，把沿途上边的流量都加上终点最小更新值 
    {
         mp[p[e]].flow+=min_flow[n];//流量加上最小更新至 
         mp[p[e]^1].flow-=min_flow[n];//反向边减去 
    }
    printf("xx%d\n",min_flow[n]);
    return min_flow[n];//返回最小更新至，加到答案当中 
}
int max_flow(){
    int flow=0;//这就是神圣的答案 
    while(1){
        flow+=bfs();//循环搜索 
        if(flag==1)//没有増广路，就直接跳出 
            break;
    }
    return flow;//返回答案 
}
int main(){
    cin>>n>>m;
    for(int i=0;i<=m;i++){//初始化，很重要，制胜之点 
        mp[i].next=-1; 
        head[i]=-1;
    }
    for(int i=1;i<=m;i++){//读入，构造邻接表 
        int a,b,c,d;
        cin>>a>>b>>c;
        build_edge(a,b,c);
    }
    cout<<max_flow();//输出答案 
}
/*
测试数据 
4
2 2
4 2
3 3
4 1
*/ 
