#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<cmath>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=1e5+10,M=30;
char lx[N];
int nm[M],mk[N];

int main(){
	int n,k,res=0;
	cin>>n>>k;
	scanf("%s",lx+1);
	fr(i,1,n){
		int pos=lx[i]-'A'+1;
		if(pos>k) res++;		
		else nm[pos]++;
	}
	int minn=1e5;
	fr(i,1,k) minn=min(minn,nm[i]),nm[i]=0;
	res+=minn*k;
	printf("%d\n",res);
	return 0;
}