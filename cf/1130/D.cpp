#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=5010;
int qx[N],a[N];

int main(){
	int n,m;scanf("%d%d",&n,&m);
	memset(a,0x3f,sizeof a);
	fr(i,1,m){
		int x,y;scanf("%d%d",&x,&y);
		a[x]=min(a[x],(y-x+n)%n);
		qx[x]++;
	}
	fr(i,1,n){
		int pos=0;
		fr(j,1,n){
			if(!qx[j]) continue;
			int tt=(j-i+n)%n;
			pos=max(pos,tt+(qx[j]-1)*n+a[j]);
		}
		printf("%d ",pos);
	}
	return 0;
}
