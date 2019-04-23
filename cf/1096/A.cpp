#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;

int main(){
	int T;scanf("%d",&T);
	fr(o,1,T){
		int l,r;scanf("%d%d",&l,&r);
		printf("%d %d\n",l,l*2);
	}
	return 0;
}