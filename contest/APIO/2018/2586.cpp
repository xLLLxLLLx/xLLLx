#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<cmath>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define frl(i,x,y) for(int i=x;i<y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=3e5+10;
struct data{
	int x,t,a,b;
}q[N];
struct node{
	int x,t;
}Q[N];
int all[N*5],c[N*5],d[N];

void Min(int &x,int y){
	if(x==-1) x=y;
	else x=min(x,y);
}

int main(){
	int n,k,T;
	scanf("%d%d%d",&n,&k,&T);
	int flg=1;
	fr(i,1,n) {
		scanf("%d%d%d%d",&q[i].x,&q[i].t,&q[i].a,&q[i].b);
		// if(q[i].x!=1) flg=0;
	}
	// int res=0;
	// if(k<=400) {
	// 	fr(o,1,T) {

	// 	}
	// }
	// else {
		fr(o,1,T) {
			int x,t;
			scanf("%d%d",&x,&t);
			memset(d,-1,sizeof d);
			fr(i,1,n) {
				if(q[i].a<=t&&t<=q[i].b) {
					Min(d[q[i].t],abs(x-q[i].x));
				}
			}
			int maxn=0,flg=0;
			fr(i,1,k) {
				if(d[i]==-1) flg=1;
				else maxn=max(maxn,d[i]);
			}
			if(flg) printf("-1\n");
			else printf("%d\n",maxn);
		}
	// }
	return 0;
}