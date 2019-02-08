#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<map>
#include<stack>
#include<vector>
#include<queue>
#include<set>
#include<algorithm>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;

int gcd(int a,int b){
	return b?gcd(b,a%b):a; 
}

int main(){
	int x;cin>>x;
	int pos=(1<<x)-1,maxn=0;
	printf("%d\n",pos);
	fr(i,1,pos-1) {
		int x=max(pos^i,i&pos);
		int y=min(pos^i,i&pos);
		//printf("%d %d\n",x,y);
		maxn=max(maxn,gcd(x,y));
	}
	printf("%d\n",maxn);
	return 0;
}