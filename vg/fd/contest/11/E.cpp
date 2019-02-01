#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=310;
struct data{
	int nt,to;
}a[N*N*2];
int v[N],head[N],cnt=0;

void add(int x,int y){
	a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].nt=head[y],head[y]=cnt;
}

bool check(int x){
	int len=sqrt(x);
	fr(i,2,len) if(x%i==0) return false;
	return true;
}

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) scanf("%d",&a[i]);
	fr(i,1,n) fr(j,i+1,n) {
		if(check(v[i]+v[j])) add(i,j);
	}
	return 0;
}
