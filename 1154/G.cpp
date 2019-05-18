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
const int N=2e5+10;
struct data{
	int x,y;
}q[N];
int a[N];

bool cmp(data A,data B){
	if(A.x!=B.y) return A.y>B.y;
	else return A.x>B.x;
}

int main(){
	int n,m,k;scanf("%d%d%d",&n,&m,&k);
	fr(i,1,n) scanf("%d",&a[i]);
	fr(i,1,m) scanf("%d%d",&q[i].x,&q[i].y);
	sort(a+1,a+1+n);
	sort(q+1,q+1+m,cmp);
	
	return 0;
}