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
const int N=2e5+10;
struct data{
	int w,id;
}a[N];

bool cmp(data xx,data yy){
	return xx.w<yy.w;
}

int main(){
	int n;scanf("%d",&n);
	int sum=0;
	fr(i,1,n) scanf("%d",&a[i].w),sum+=a[i].w,a[i].id=i;
	sort(a+1,a+1+n,cmp);
	int flg=sum&1;
	fr(i,1,n){
		if(a[i].w%2!=flg) continue;
		
	}
	return 0;
}