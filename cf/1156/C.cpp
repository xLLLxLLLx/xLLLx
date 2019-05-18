#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#include<vector>
#include<cmath>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=2e5+10;
int a[N],vis[N];
int n;

int main(){
	int x;
	scanf("%d%d",&n,&x);
	int ans=0,lt=n/2+1;
	fr(i,1,n) scanf("%d",&a[i]);
	sort(a+1,a+1+n);
	fr(i,1,n){
		if(vis[i]) continue;
		lt=max(lt,i+1);
		while(lt<=n&&a[lt]-a[i]<x) lt++;
		if(lt>n||a[lt]-a[i]<x) break;
		vis[lt]=1,ans++;
		lt++;
	}
	printf("%d\n",ans);
	return 0;
}