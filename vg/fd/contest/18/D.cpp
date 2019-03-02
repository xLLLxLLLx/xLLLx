#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e4+10;
int sz[N],hx[N],zz[N*10],bx,by;

void solve(int l,int r){
	if(l>r) return ;
	int mid=(l+r)>>1,dis;
	printf("0 %d %d\n",mid,mid),fflush(stdout);
	scanf("%d",&dis);
	if(dis){
		bx=mid,by=mid;
		if(mid+dis<=1e8) zz[++zz[0]]=mid+dis;
		if(mid-dis>=-1e8) zz[++zz[0]]=mid-dis;
		solve(l,mid-dis-1),solve(mid+dis+1,r);
	} else {
		solve(l,mid-dis-1),solve(mid+dis+1,r);
		zz[++zz[0]]=mid;
	}
}

int main(){
	solve(-1e8,1e8);
	sort(zz+1,zz+1+zz[0]);
	zz[0]=unique(zz+1,zz+1+zz[0])-zz-1;
	fr(i,1,zz[0]){
		int pos;
		printf("0 %d %d\n",bx,zz[i]),fflush(stdout);
		scanf("%d",&pos);
		if(!pos) sz[++sz[0]]=zz[i];
		printf("0 %d %d\n",zz[i],by),fflush(stdout);
		scanf("%d",&pos);
		if(!pos) hx[++hx[0]]=zz[i];
	}
	printf("1 %d %d\n",hx[0],sz[0]),fflush(stdout);
	fr(i,1,hx[0]) printf("%d ",hx[i]),fflush(stdout);
	puts("");
	fr(i,1,sz[0]) printf("%d ",sz[i]),fflush(stdout);
	return 0;
}
