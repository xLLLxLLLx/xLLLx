#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10;
vector<int> g[N];
int f[N],c[N],z[N];

int main(){
	int n,rt;scanf("%d",&n);
	fr(i,1,n){
		scanf("%d%d",&f[i],&c[i]);
		if(f[i]==-1) rt=i;
		else g[f[i]].push_back(i);
	}
	int flg=0;
	fr(i,1,n){
		z[i]=0;
		if(!c[i]) continue;
		int len=g[i].size();
		z[i]=1;
		fr(j,0,len-1){
			if(!c[g[i][j]]) z[i]=0;
		}
		if(z[i]) flg=1,printf("%d ",i);
	}
	if(!flg) puts("-1");
	return 0;
}