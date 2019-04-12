#include<bits/stdc++.h>
#define LL long long
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
const int N=4e5+10;
struct data{
	int nt,to;
	LL w;
}qx[N<<1];
LL dia=0,dis[N],qz[N];
int cnt=0,head[N],b[N],n,m;

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) 2333;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void read(LL &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) 2333;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void add(int x,int y,LL w){
	qx[++cnt].to=y,qx[cnt].w=w,qx[cnt].nt=head[x],head[x]=cnt;
	qx[++cnt].to=x,qx[cnt].w=w,qx[cnt].nt=head[y],head[y]=cnt;
}

void rd(){
	freopen("track.in","r",stdin);
	freopen("track.out","w",stdout);
}

LL Getdia(int u,int fa){
	LL maxn=0;
	for(int i=head[u];i;i=qx[i].nt){
		int to=qx[i].to;
		if(to==fa) continue;
		LL pos=Getdia(to,u)+qx[i].w;
//		printf("u=%d fa=%d to=%d pos=%lld maxn=%lld\n",u,fa,to,pos,maxn);
		dia=max(dia,maxn+pos);
		maxn=max(maxn,pos);
	}
	return maxn;
}

void dfs(int u,int fa){
	for(int i=head[u];i;i=qx[i].nt){
		int to=qx[i].to;
		if(to==fa) continue;
		dis[u]=dis[u]+qx[i].w;
		dfs(to,u);
	}
}

bool check(LL w){
	int lt=0,res=0;
	fr(i,1,n) {
		if(qz[i]-qz[lt]>=w) lt=i,res++; 
	}
	return res>=m;
}

void subtask1(){
	Getdia(1,0);
	printf("%lld\n",dia);
	exit(0);
}

void subtask2(){
	dfs(1,0);
	fr(i,1,n) qz[i]=qz[i-1]+dis[i];
	LL l=0,r=1e9,ans=0;
	while(l<=r){
		LL mid=(l+r)>>1;
		if(check(mid)) ans=mid,l=mid+1;
		else r=mid-1;
	}
	printf("%lld\n",ans);
	exit(0);
}

int main(){
	rd();
	read(n),read(m);
	LL minn=1e18;
	fr(i,1,n-1){
		int x,y;LL w;
		read(x),read(y),read(w);
		b[x]++,b[y]++;
		add(x,y,w);
		minn=min(minn,w);
	}
	int flg=1;
	fr(i,1,n) if(b[i]>2) flg=0;
	if(m==1) subtask1();
	else if(flg) subtask2();
	else printf("%lld\n",minn);
	return 0;
}
