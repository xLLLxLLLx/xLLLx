#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e6+10;
char lx[N];

int main(){
	int n;scanf("%d",&n);
	scanf("%s",lx+1);
	LL ans=0;
	fr(i,1,n){
		int pos=lx[i]-'0';
		if(pos&1) continue;
		else ans+=i;
	}
	cout<<ans<<endl;
	return 0;
}