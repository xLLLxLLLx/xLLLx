#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<cmath>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=1010,MASK=65540;
int ans=0,n,tot;
int g[10][N],a[N],f[N][MASK];

void Max(int &x,int y){
	if(x==-1) x=y;
	else x=max(x,y);
}

int find(int x,int y){
	int l=1,r=g[x][0],ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(g[x][mid]<=y) ans=mid,l=mid+1;
		else r=mid-1;
	}
	return ans;
}

bool check(int i){
	memset(f,-1,sizeof f);
	f[0][0]=0;
	fr(j,0,n) fr(k,0,tot) {
		if(f[j][k]==-1) continue;
		Max(f[j+1][k],f[j][k]);
		if(j!=n) {
			int pos=a[j+1];
			if((1<<(pos-1))&k) continue;
			int ss=find(pos,j+1);
			if(!ss) continue;
			if(ss+i-2<=g[pos][0]) {
				int sit=g[pos][ss+i-2];
				Max(f[sit][k|(1<<(pos-1))],f[j][k]+i-1);
			}
			if(ss+i-1<=g[pos][0]) {
				int sit=g[pos][ss+i-1];
				Max(f[sit][k|(1<<(pos-1))],f[j][k]+i);
			}
		}
	}
	ans=max(ans,f[n][tot]);
	if(f[n][tot]==-1) return false;
	else return true;
}

int main(){
	scanf("%d",&n);
	fr(i,1,n) {
		scanf("%d",&a[i]);
		g[a[i]][++g[a[i]][0]]=i;
	}
	tot=(1<<8)-1;
	fr(i,1,8) {
		if(g[i][0]) ans++;
	}
	int l=2,r=n;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(check(mid)) l=mid+1;
		else r=mid-1;
	}
	printf("%d\n",ans);
	return 0;
}