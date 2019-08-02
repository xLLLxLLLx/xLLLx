#include<bits/stdc++.h>
#define mp make_pair
#define pii pair<int,int>
#define inf 0x3f3f3f3f
using namespace std;
const int N=3e3,M=2e4;
bitset<M> b[N];
pii p[2][N];
int n,k,sz[N];
char s[N][M],ans[M];
int main(){
	scanf("%d%d",&n,&k);
	int i,j;
	for(i=1;i<=n;++i){
		scanf("%s",s[i]);
		sz[i]=strlen(s[i]);
	}
	b[n+1][0]=1;
	for(i=n;i;--i) b[i]=b[i+1]|(b[i+1]<<sz[i]);
	int t=0,c=0,tc=0;
	for(i=1;i<=n;++i) if(b[i+1][k-sz[i]]) p[t][++c]=mp(i,0);
	int mn;
	for(i=0;i<k;++i,c=tc,t^=1){
		char mc='z';
		for(j=1;j<=c;++j) mc=min(mc,s[p[t][j].first][p[t][j].second]);
		ans[i]=mc;
		tc=0,mn=inf;
		for(j=1;j<=c;++j){
			int x=p[t][j].first,y=p[t][j].second;
			if(s[x][y]!=mc) continue;
			if(y==sz[x]-1) mn=min(mn,x);
			else p[t^1][++tc]=mp(x,y+1);
		}
		if(mn^inf) for(j=mn+1;j<=n;++j) if(k-sz[j]-i-1>=0 and b[j+1][k-sz[j]-i-1]) p[t^1][++tc]=mp(j,0);
	}
	for(i=0;i<k;++i) putchar(ans[i]);
	return 0;
}
