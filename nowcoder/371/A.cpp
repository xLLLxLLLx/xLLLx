#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long 
using namespace std;
const int N=15,M=5e7+10;
int b[M],jc[N]={1},a[N]={6,2,5,5,4,5,6,3,7,6};
int n,k;

void dfs(int dep,int nw,int nm){
	if(dep>7) return ;
	fr(i,0,9){
		int now=nw+i*jc[dep];
		if(now>n) break;
		if(i) b[now]=nm+a[i];
		dfs(dep+1,now,nm+a[i]);
	}
}

int main(){
	scanf("%d%d",&n,&k);
	fr(i,1,7) jc[i]=jc[i-1]*10;
	fr(i,0,9) b[i]=a[i],dfs(1,i,b[i]);
	int ans=0,cnt=n/k;
	fr(i,0,n/2) {
	//	printf("%d %d\n",i,b[i]);
		if(b[i]+b[n-i]+4+b[n]==cnt) ans++;
	}
	printf("%d\n",ans);
	return 0;
}
