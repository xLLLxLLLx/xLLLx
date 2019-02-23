#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e4+10,mod=1e9+7,MK=(1<<3);
int dx[5][2]={{-1,-2},{0,0},{1,2},{0,0}};
int dy[5][2]={{0,0},{1,2},{0,0},{-1,-2}};
int mk[N],g[N],tr[5],bx,by,n;
LL dp[N][MK],as[MK];

void Add(LL &x,LL y){
	x=(x+y)%mod;
}

LL add(LL x,LL y){
	return (x+y)%mod;
}

LL DP(){
	memset(dp,0,sizeof dp);
	dp[0][7]=1;
	fr(i,0,n) fr(j,0,7){
		if(!dp[i][j]) continue;
		if(j==7) Add(dp[i+1][g[i+1]],dp[i][j]);
		else {
			fr(t,0,1){
				int pos=(1<<t)|(1<<(t+1));
				if((j&pos)==0) Add(dp[i][j|pos],dp[i][j]);
			}
			fr(t,0,2){
				int pos=(1<<t);
				if((j|pos)==7&&(pos&g[i+1])==0) {
					Add(dp[i+1][g[i+1]|pos],dp[i][j]);
				}
			}
			if(j==0&&g[i+1]==0) Add(dp[i+1][7],dp[i][j]);
			fr(t,0,2) fr(k,t+1,2){
				int pos=(1<<t)|(1<<k);
				if((pos&j)!=0) continue;
				if((pos|j)!=7) continue;
				if((pos&g[i+1])!=0) continue;
				Add(dp[i+1][g[i+1]|pos],dp[i][j]);
			}
		}
	}
	return dp[n+1][0];
}

int main(){
	scanf("%d",&n);
	fr(i,0,2) fr(j,1,n){
		char ch;cin>>ch;
		if(ch=='O') bx=i,by=j;
		mk[j]|=((ch!='.')<<i);
	}
	LL ans=0;
	fr(i,0,3){
		int flg=1;
		fr(j,0,1){
			int xx=bx+dx[i][j],yy=by+dy[i][j];
			if(xx<0||xx>2||yy<1||yy>n) {flg=0;break;}
			if((mk[yy]>>xx)&1) {flg=0;break;}
		}
		if(flg) tr[++tr[0]]=i;
	}
	int tot=(1<<tr[0])-1;
	fr(i,1,tot){
		fr(j,1,n) g[j]=mk[j];
		int res=0;
		fr(j,1,tr[0]){
			if((i>>(j-1))&1){
				res++;
				int J=tr[j];
				fr(k,0,1){
					int xx=bx+dx[J][k],yy=by+dy[J][k];
					g[yy]|=(1<<xx);
				}
			}
		}
		//fr(j,1,n) printf("g[%d]=%d\n",j,g[j]);
		if(res&1) Add(ans,DP());
		else Add(ans,add(-DP(),mod));
	}
	printf("%lld\n",ans);
	return 0;
}
