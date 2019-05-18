#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
#include<cstring>
#include<set>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=1e5+10;
int a[N],nm[20];
multiset<int>q;

int main(){
	int n;cin>>n;
	fr(i,1,n) scanf("%d",&a[i]);
	int maxn=1;
	fr(j,1,n){
		nm[a[j]]++;
		int mx=0,res=0,mn=15,tmp=0;
		fr(i,1,10){
			if(!nm[i]) continue;
			if(nm[i]>mx) mx=nm[i],res=1;
			else if(nm[i]==mx) res++;
			if(nm[i]<mn) mn=nm[i],tmp=1;
			else if(nm[i]==mn) tmp++;
		}
		printf("%d %d %d %d\n",mx,mn,res,tmp);
		if(mx==mn){
			if(mx==1) maxn=j;
			if(res==1) maxn=j;
		}
		if(mx-1==mn&&res==1) maxn=j;
		if(tmp==1&&mn==1) maxn=j;
	}
	printf("%d\n",maxn);
	return 0;
}