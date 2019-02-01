#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1010;
struct data{
	int x,y;
}a[N],bz;
int vis[N];

bool check(data A,data B){
	return (B.y-A.y)*(A.x-bz.x)==(A.y-bz.y)*(B.x-A.x);
}

int main(){
	int n;scanf("%d%d%d",&n,&bz.x,&bz.y);
	fr(i,1,n) scanf("%d%d",&a[i].x,&a[i].y);
	int ans=0;
	fr(i,1,n) {
		if(vis[i]) continue;
		ans++;
		fr(j,i+1,n){
			if(vis[j]) continue;
			if(check(a[i],a[j])) vis[j]=1;
		}
	}
	printf("%d\n",ans);
	return 0;
}
