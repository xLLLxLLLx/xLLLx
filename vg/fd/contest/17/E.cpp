#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
#define db double
using namespace std;
const int N=25,mod=1e9+7;
struct data{
	LL r[N][N];
}chu;
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
int vis[N*N];
LL dp[N*N],g[N*N];
int n,m,tot,q;

void Mul(LL &x,LL y){
	x=(x*y)%mod;
}

LL mul(LL x,LL y){
	return x*y%mod;
}

void Add(LL &x,LL y){
	x=(x+y)%mod;
}

LL add(LL x,LL y){
	return (x+y)%mod;
}

data juzhen(data A,data B){
	data C;
	fr(i,1,tot) fr(j,1,tot){
		C.r[i][j]=0;
		fr(k,1,tot)
			Add(C.r[i][j],mul(A.r[i][k],B.r[k][j]));
	}
	return C;
}

data q_pow(int y,data tmp){
	data ans;
	fr(i,1,tot) fr(j,1,tot) ans.r[i][j]=(i==j);
	for(;y;y>>=1){
		if(y&1) ans=juzhen(ans,tmp);
		tmp=juzhen(tmp,tmp);
	}
	return ans;
}

int zh(int x,int y){
	return (x-1)*m+y;
}

void Get(int y){
	data zz=q_pow(y,chu);
	fr(i,1,tot) {
		g[i]=0;
		fr(j,1,tot)
			Add(g[i],mul(dp[j],zz.r[j][i]));
	}
	fr(i,1,tot) dp[i]=g[i];
}

void UPD(){
	fr(i,1,tot) fr(j,1,tot) chu.r[i][j]=0;
	fr(i,1,n) fr(j,1,m) {
		int be=zh(i,j);
		if(vis[be]) continue;
		chu.r[be][be]=1;
		fr(k,0,3){
			int xx=i+dx[k],yy=j+dy[k];
			if(xx<=0||xx>n||yy<=0||yy>m) continue;
			int pos=zh(xx,yy);
			if(!vis[pos]) chu.r[be][pos]=1;
		}
	}
}

int main(){
	scanf("%d%d%d",&n,&m,&q);
	tot=n*m;
	int lt=2;
	dp[1]=1;
	UPD();
	fr(i,1,q){
		int tp,x,y,t;
		scanf("%d%d%d%d",&tp,&x,&y,&t);
		if(tp==1){
			Get(t-lt+1);lt=t+1;
			printf("%lld\n",dp[zh(x,y)]);
		}
		else if(tp==2){
			Get(t-lt+1),lt=t+1;
			vis[zh(x,y)]=1,UPD();
		}
		else {
			Get(t-lt+1),lt=t+1;
			vis[zh(x,y)]=0,UPD();
		}
	}
	return 0;
}
