#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define db double
#define LL long long
#define pb push_back
using namespace std;
const int N=210,M=20;
struct point{
	db x,y;
}a[N];
struct data{
	db r[N][N];
}JC[M];
db g[N],f[N];
vector<int>q[N*N];
LL jc[M]={1};
int n,res=0,vis[N],qwq[N];

db cross(point A,point B){
	return A.x*B.y-A.y*B.x;
}

data Mul(data A,data B){
	data tmp;
	fr(i,1,n) fr(j,1,n){
		tmp.r[i][j]=0;
		fr(k,1,n){
			tmp.r[i][j]+=A.r[i][k]*B.r[k][j];
		}
	}
	return tmp;
}

data Get(int w){
	data tmp;
	fr(i,1,n) fr(j,1,n) tmp.r[i][j]=(i==j);
	rf(i,19,0){
		if(w>=jc[i]){
			w-=jc[i];
			tmp=Mul(tmp,JC[i]);
		}
	}
	return tmp;
}

void init(){
	fr(i,1,n){
		memset(vis,0,sizeof vis);
		vis[i]=1;
		fr(j,1,n){
			if(vis[j]) continue;
			q[++res].pb(i),q[res].pb(j);
			vis[i]=vis[j]=1;
			fr(k,j+1,n){
				if(vis[k]) continue;
				if(!cross((point){a[j].x-a[i].x,a[j].y-a[i].y},(point){a[k].x-a[j].x,a[k].y-a[j].y})){
					q[res].pb(k),vis[k]=1;
				}
			}
		}
		db tmp=res-qwq[i-1];
		qwq[i]=res;
		fr(j,qwq[i-1]+1,qwq[i]){
			int len=q[j].size();
			fr(k,0,len-1){
				JC[0].r[i][q[j][k]]+=1.0/db(len)/tmp;
			}
		}
	}
}

void Go(data tmp){
	fr(i,1,n) g[i]=0;
	fr(i,1,n) fr(j,1,n){
		g[i]+=f[j]*tmp.r[i][j];
	}
	fr(i,1,n) f[i]=g[i];
}

int main(){
	scanf("%d",&n);
	fr(i,1,n) scanf("%lf%lf",&a[i].x,&a[i].y);
	init();
	fr(i,1,M-1) jc[i]=jc[i-1]*2LL,JC[i]=Mul(JC[i-1],JC[i-1]);
	int m;scanf("%d",&m);
	fr(o,1,m){
		int goal,w;
		scanf("%d%d",&goal,&w);
		w--;
		fr(i,1,n) f[i]=0;f[goal]=1;
		data tmp=Get(w);
		Go(tmp);
	//	fr(i,1,n) cout<<f[i]<<" ";
	//	puts("");
		db ans=0;
		fr(i,1,n){
			fr(j,qwq[i-1]+1,qwq[i]){
				int sz=q[j].size();
				db gg=0;
				fr(t,0,sz-1) gg+=f[q[j][t]];
				ans=max(ans,gg/db(sz));
			}
		}
		printf("%.20lf\n",ans);
	}
	return 0;
}
