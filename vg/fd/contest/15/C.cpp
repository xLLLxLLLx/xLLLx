#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=3e5+10;
struct data{
	int x,rk;
}a[N];
int b[N];

bool cmp(data xx,data yy){
	return xx.x<yy.x;
}

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) scanf("%d",&a[i].x),a[i].rk=i;
	sort(a+1,a+1+n,cmp);
	int lt=1,res=a[1].x;
	fr(i,2,n){
		if(a[i].x!=a[i-1].x){
			fr(j,lt,i-1) b[a[j].rk]=res++;
			lt=i;res=max(res,a[i].x);
		}
	}
	fr(i,lt,n) b[a[i].rk]=res++;
	fr(i,1,n) printf("%d ",b[i]);
	return 0;
}
