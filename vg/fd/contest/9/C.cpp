#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=55;

int main(){
	int n,k;scanf("%d%d",&n,&k);
	int res=0,cnt=0,sum=0;	
	fr(i,1,n){
		int x;scanf("%d",&x);
		if(x==50) res++;
		else cnt++;
		sum+=x;
	}
	LL ans=0;
	if(sum<=k) return printf("1\n1\n"),0;
	if(!res){
		int pos=k/100;
		
	}
	return 0;
}
