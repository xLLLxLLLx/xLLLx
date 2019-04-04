#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e6+10;
int a[N];

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

int main(){
	int n,res=0,tmp=0;
	read(n);
	fr(i,1,n){
		read(a[i]);
		if(a[i]) res++;
		else tmp++;
	}
	if(n==1&&!a[n]) printf("YES\n0\n");
	else if(a[n]) printf("NO\n");
	else {
		if(a[n-1]||tmp>2){
			printf("YES\n");
			printf("(");
			fr(i,1,n-1){
				if(i!=n-1) printf("(");
				printf("%d",a[i]);
				if(i!=n-1) printf("->");
			}
			fr(i,1,n-2) printf(")");
			printf("->%d)",a[n]);
		} else printf("NO\n");
	}
	return 0;
}