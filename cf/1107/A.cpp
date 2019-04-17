#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1010;
char lx[N];

int main(){
	int q;scanf("%d",&q);
	fr(o,1,q){
		int n;scanf("%d",&n);
		scanf("%s",lx+1);
		if(n==2){
			if(lx[1]>=lx[2]) printf("NO\n");
			else printf("YES\n2\n%d %d\n",lx[1]-48,lx[2]-48);
		} else {
			printf("YES\n2\n");
			printf("%d ",lx[1]-48);
			fr(i,2,n) printf("%d",lx[i]-48);
			puts("");
		}
	}
	return 0;
}