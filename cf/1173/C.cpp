#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int vis[N];
int a[N], b[N];

int main() {
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i) {
		scanf("%d",&a[i]);
		vis[a[i]]=1;
	}
	for(int i=1;i<=n;++i) {
		scanf("%d",&b[i]);
	}
	int now=b[n],lt=0;
	for(int i=n-1;i>=n-now;--i) {
		if(b[i]!=now-(n-i)) {
			now=-1;
			break;
		}
	}
	// printf("%d\n",now);
	if(now!=-1){
		int lt=0,flg=1;
		for(int i=now+1;i<=n;++i){
			if(vis[i]) {
				lt++;
				vis[b[lt]]=1;
			} else {
				flg=0;
				break;
			}
		}
		if(flg) {
			return printf("%d\n",n-now),0;
		}
	}
	int maxn=0,tmp=0;
	lt=0;
	memset(vis,0,sizeof vis);
	for(int i=1;i<=n;++i){
		vis[a[i]]=1;
	}
	int ans=0;
	for(int i=1;i<=n;++i){
		if(vis[i]) {
			lt++;
			vis[b[lt]]=1;
		} else {
			for(;b[lt]!=i;){
				lt++;
				vis[b[lt]]=1;
			}
			maxn=lt,tmp=i;
		}
	}
	printf("%d\n",maxn+(n-tmp+1));
	return 0;
}