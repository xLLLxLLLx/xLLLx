#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=30;
struct data{
	int nt,to,w;
}a[N*N];
int b[N],head[N];
int n,m,cnt=0;

void add(int x,int y,int w){
	a[++cnt].to=y,a[cnt].w=w,a[cnt].nt=head[x],head[x]=cnt;
}

int main(){
	int L;scanf("%d",&L);
	int n=0,tmp=L;
	for(;L;L>>=1) n++;
	L=tmp;
	fr(i,1,n-1) add(i,i+1,1<<(i-1)),add(i,i+1,0);
	int gg=1<<(n-1);
	rf(i,n-1,1) if((L>>(i-1))&1) add(i,n,gg),gg+=(1<<(i-1));
	printf("%d %d\n",n,cnt);
	fr(u,1,n) for(int i=head[u];i;i=a[i].nt){
		printf("%d %d %d\n",u,a[i].to,a[i].w);
	}
	return 0;
}