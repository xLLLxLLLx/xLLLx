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
int a[N],nm[N],mk[N];
multiset<int>q;

int main(){
	int n;cin>>n;
	fr(i,1,n) scanf("%d",&a[i]);
	int maxn=1,mx=0,res=0,tot=0;
	fr(i,1,n){
		if(nm[a[i]]) mk[nm[a[i]]]--;
		else tot++;
		if(nm[a[i]]) q.erase(q.find(nm[a[i]]));
		nm[a[i]]++,mk[nm[a[i]]]++;
		q.insert(nm[a[i]]);
		int mn=*q.begin(),mx=*q.rbegin();
		if(mx==mn)
			if(mk[mx]==1||mx==1) maxn=i;
		if(mx-1==mn&&mk[mx]==1) maxn=i;
		if(mn==1&&mk[mn]==1&&mk[mx]==tot-1) maxn=i; 
	}
	printf("%d\n",maxn);
	return 0;
}