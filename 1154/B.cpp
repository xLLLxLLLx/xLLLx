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
const int N=110;
int a[N];

int main(){
	int n;cin>>n;
	fr(i,1,n) cin>>a[i];
	int maxn=110;
	fr(i,1,100){
		int pos=-1,flg=1;
		fr(j,1,n){
			int gg=abs(i-a[j]);
			if(!gg) continue;
			if(pos==-1) pos=gg;
			else if(pos!=gg) flg=0;
		}
		if(pos==-1) maxn=0;
		else if(flg) maxn=min(maxn,pos);
	}
	if(maxn!=110) cout<<maxn<<endl;
	else cout<<"-1\n";
	return 0;
}