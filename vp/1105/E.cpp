#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e4+10,Q=2e6+10,M=30,K=45;
char lx[K];
int ch[N][M],a[K][K],vis[N],size=0,res=-1;
int qx[N*10],f[Q],g[Q];

void insert(){
	int fa=0,len=strlen(lx+1),flg=0;
	fr(i,1,len){
		int pos=lx[i]-'a'+1;
		if(!ch[fa][pos]) ch[fa][pos]=++size;
		fa=ch[fa][pos];
	}
	if(vis[fa]==-1) vis[fa]=++res;
	qx[++qx[0]]=vis[fa];
}

int ck[K];

int main(){
	int n,m;cin>>n>>m;
	memset(vis,-1,sizeof vis);
	fr(o,1,n+1){
		int p=1;
		if(o!=n+1) cin>>p;
		if(p==1){
			sort(qx+1,qx+1+qx[0]);
			int t=unique(qx+1,qx+1+qx[0])-qx-1;
			fr(i,1,t) fr(j,i+1,t) a[qx[i]][qx[j]]=a[qx[j]][qx[i]]=1;
			qx[0]=0;
		} else {
			scanf("%s",lx+1);
			insert();
		}
	}
	int l=m/2,r=m-l,maxn=0;
	int ml=(1<<l)-1,mr=(1<<r)-1;
	fr(i,0,ml){
		ck[0]=0;maxn=max(maxn,f[i]);
		fr(j,0,l-1) if((i>>j)&1) ck[++ck[0]]=j;
		fr(j,0,l-1){
			int flg=1;
			if((i>>j)&1) continue;
			fr(o,1,ck[0]) if(a[j][ck[o]]) flg=0;
			f[i|(1<<j)]=max(f[i|(1<<j)],f[i]+flg);
		}
	}
	fr(i,0,mr){
		ck[0]=0;maxn=max(maxn,g[i]);
		fr(j,0,r-1) if((i>>j)&1) ck[++ck[0]]=j+l;
		fr(j,0,r-1){
			int flg=1;
			if((i>>j)&1) continue;
			fr(o,1,ck[0]) if(a[j+l][ck[o]]) flg=0;
			g[i|(1<<j)]=max(g[i|(1<<j)],g[i]+flg);
		}
	}
	fr(i,0,ml){
		int pos=0;
		fr(j,0,l-1){
			if((i>>j)&1) 
				fr(k,0,r-1) if(a[j][k+l]) pos|=(1<<k);
		}
		pos=mr^pos;
		maxn=max(maxn,f[i]+g[pos]);
	}
	cout<<maxn<<endl;
	return 0;
}
