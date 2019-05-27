#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;

int main(){
	int n,m;scanf("%d%d",&n,&m);
	int minn=1e9,res=-1;
	fr(i,1,n){
		int x,y;scanf("%d%d",&x,&y);
		if(x<=m){
			int pos=(m-x)/y;
			if((m-x)%y) pos++;
			int gg=pos*y+x;
			if(minn>gg) minn=gg,res=i;
 		}
		else if(minn>x) minn=x,res=i;
	}
	cout<<res<<endl;
	return 0;
}