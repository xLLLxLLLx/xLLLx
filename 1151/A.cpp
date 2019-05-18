#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
#include<cmath>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=55;
char lx[N],ll[5]={'A','C','T','G'};

int main(){
	int n;scanf("%d",&n);
	scanf("%s",lx+1);
	int maxn=1e9;
	fr(i,1,n-3){
		int res=0;
		fr(j,0,3){
			int pos=lx[i+j]-'A'+1;
			int tmp=ll[j]-'A'+1;
			int gg=pos-tmp;
			if(gg<0) gg=-gg;
			res+=min(gg,26-gg);
			//printf("%d\n",res);
		}
		maxn=min(maxn,res);
	}
	cout<<maxn<<endl;
	return 0;
}