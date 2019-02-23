#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10;
struct data{
	int nt,to;
}a[N<<1];
int head[N],dep[N],cnt=0;

void add(int x,int y){
	a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].nt=head[y],head[y]=cnt;
}

int main(){
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1,x,y;i<n;++i){
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	fr(i,1,m){
		
	}
	return 0;
}
