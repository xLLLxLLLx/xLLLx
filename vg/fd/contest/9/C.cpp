#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=55,mod=1e9+7;
struct data{
	int n5,n1,nw;
};
int res=0,cnt=0;
int vis[N][N][2];
LL f[N][N][2],yh[N][N];
queue<data>q;

void Add(LL &x,LL y){
	x=(x+y)%mod;
}

LL add(LL x,LL y){
	return (x+y)%mod;
}

LL mul(LL x,LL y){
	return (x*y)%mod;
}

void init(){
	fr(i,0,50) yh[i][i]=yh[i][0]=1;
	fr(i,1,50)
	 fr(j,1,i-1) yh[i][j]=add(yh[i-1][j-1],yh[i-1][j]);
}

int main(){
	init();
	int n,k;scanf("%d%d",&n,&k);
	fr(i,1,n) {
		int x;scanf("%d",&x);
		if(x==50) res++;
		else cnt++;
	}
	memset(f,0,sizeof f);
	memset(vis,-1,sizeof vis);
	vis[res][cnt][0]=0,f[res][cnt][0]=1;
	q.push((data){res,cnt,0});
	//n5,n1,nw
	while(!q.empty()){
		data h=q.front();q.pop();
		int nc=vis[h.n5][h.n1][h.nw]+1;
		//printf("%d %d %d\n",h.n5,h.n1,h.nw);
		if(!h.n5&&!h.n1) break;
		if(h.nw) {
			int kk=res-h.n5,tt=cnt-h.n1;
			fr(i,0,kk){
				int yu=k-50*i;
				if(yu<0) break;
				int pos=min(tt,yu/100);
				fr(j,0,pos){
					if(!i&&!j) continue;
					int w5=h.n5+i,w1=h.n1+j;
					if(vis[w5][w1][0]!=-1&&vis[w5][w1][0]<nc) continue;
					LL tmp=mul(yh[kk][i],yh[tt][j]);
					Add(f[w5][w1][0],mul(tmp,f[h.n5][h.n1][1]));
					if(vis[w5][w1][0]==-1) q.push((data){w5,w1,0});
					vis[w5][w1][0]=nc;
					//printf("w5=%d w1=%d 0\n",w5,w1);
				}
			}
		} else {
			fr(i,0,h.n5){
				int yu=k-50*i;
				if(yu<0) break;
				int pos=min(h.n1,yu/100);
				fr(j,0,pos) {
					if(!i&&!j) continue;
					int w5=h.n5-i,w1=h.n1-j;
					if(vis[w5][w1][1]!=-1&&vis[w5][w1][1]<nc) continue;
					LL tmp=mul(yh[h.n5][i],yh[h.n1][j]);
					Add(f[w5][w1][1],mul(f[h.n5][h.n1][0],tmp));
					if(vis[w5][w1][1]==-1) q.push((data){w5,w1,1});
					vis[w5][w1][1]=nc; 
					//printf("w5=%d w1=%d 1\n",w5,w1);
				}		
			}
		} 
	}
	if(vis[0][0][1]==-1) printf("-1\n0\n");
	else printf("%d\n%lld\n",vis[0][0][1],f[0][0][1]);
	return 0;
}
