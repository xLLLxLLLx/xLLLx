#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#include<vector>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=2e5+10;
int c[N],a,b,n;

int main(){
	cin>>n>>a>>b;
	int l=b;
	fr(i,1,n) scanf("%d",&c[i]);
	int maxn=0;
	fr(i,1,n){
		//printf("%d %d\n",a,b);
		maxn=max(maxn,min(n,i+b));
		if(c[i]){
			maxn=max(maxn,min(n,i+min(l,b+1)));
			if(b==l) b--;
			else if(a>1){
				a--;
				b++,b=min(b,l);
			} else if(b) b--;
			else a--;
		} else {
			if(b) b--;
			else a--;
		}
		maxn=max(maxn,i);
		if(!a) maxn=max(maxn,min(n,i+b));
		if(!a) break;
	}
	printf("%d\n",maxn);
	return 0;
}