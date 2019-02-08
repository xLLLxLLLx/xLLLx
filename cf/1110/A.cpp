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

int main(){
	int b,k;cin>>b>>k;
	int flg=0;
	fr(i,1,k-1) {
		int x;cin>>x;
		int pos=(x&1)&(b&1);
		if(pos) flg=1^flg;
	}
	int x;cin>>x;
	if(x&1) flg=1^flg;
	if(!flg) printf("even\n");
	else printf("odd\n");
}