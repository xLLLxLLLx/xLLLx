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
	int n;cin>>n;
	fr(i,1,n) {
		int x;scanf("%d",&x);
		int flg=1,y=x,cnt=0;
		for(;y;) {
			int pos=y%2;
			cnt++;
			if(!pos) flg=0;
			y>>=1;
		} 
		if(!flg) printf("%d\n",(1<<cnt)-1);
		else {
			int len=sqrt(x),ans=1;
			fr(i,2,len) {
				if(x%i==0) {
					ans=x/i;
					break;
				}
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}