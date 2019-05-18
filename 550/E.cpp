//#include<bits/stdc++.h>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>
#include<vector>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=2e5+10;
struct data{
	int to,id,z;
};
int b[N],mk[N];
queue<int>q;
vector<data>g[N];

int main(){
	int n,m;scanf("%d%d",&n,&m);
	fr(i,1,m){
		int x,y;scanf("%d%d",&x,&y);
		g[x].push_back((data){y,i,1});
		g[y].push_back((data){x,i,0});
	}
	memset(mk,-1,sizeof mk);
	q.push(1);
	while(!q.empty()){
		int i=q.front();q.pop();
		int len=g[i].size();
		if(mk[i]==-1) mk[i]=0;
		fr(j,0,len-1){
			b[g[i][j].id]=mk[i]^g[i][j].z;
			if(mk[g[i][j].to]==-1) mk[g[i][j].to]=mk[i]^1,q.push(g[i][j].to);
			else if(mk[g[i][j].to]==(mk[i]^1)) ;
			else return printf("NO\n"),0;
		}
	}
	printf("YES\n");
	fr(i,1,m) printf("%d",b[i]);
	return 0;
}