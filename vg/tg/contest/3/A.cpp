#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10,M=1e5;
int a[N];
struct data{
	int id,w;
}b[N],zz[5];
int vis[N];

bool cmp(data x,data y){
	return x.w>y.w;
}

int main(){
	int n;scanf("%d",&n);
	int ans=0,res=0;
	fr(i,1,n) scanf("%d",&a[i]);
	for(int i=1;i<=n;i+=2) vis[a[i]]++;
	fr(i,1,M) b[++res].id=i,b[res].w=vis[i];
	sort(b+1,b+1+res,cmp);
	zz[1]=b[1],zz[2]=b[2];
	memset(vis,0,sizeof vis);
	for(int i=2;i<=n;i+=2) vis[a[i]]++;
	res=0;
	fr(i,1,M) b[++res].id=i,b[res].w=vis[i];
	sort(b+1,b+1+res,cmp);
	zz[3]=b[1],zz[4]=b[2];
	int maxn=0;
	fr(i,1,2) fr(j,3,4){
		if(zz[i].id!=zz[j].id) maxn=max(maxn,zz[i].w+zz[j].w);
	}
	cout<<n-maxn<<endl;
	return 0;
}