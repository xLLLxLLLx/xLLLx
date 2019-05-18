#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cmath>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10,LOG=19;
struct data{
	int l,r;
}xd[N];
int a[N],f[N],vis[N];
LL qz[N],sz=0,tot=0;
vector<int>g[N];

int find(int k){
	return f[k]==k ? f[k] : f[k]=find(f[k]);
}

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) scanf("%d",&a[i]),g[a[i]].push_back(i);
	LL ans=0,sum=0;
	fr(i,1,n){
		int len=g[i].size();
		if(!len) {
			qz[i]=qz[i-1];
			continue;
		}
		qz[i]++;
		fr(j,0,len-1){
			int nw=g[i][j];
			int pos=find(nw-1),tmp=find(nw+1);
			if(tmp){
				if(pos){
					f[nw]=tmp;
					xd[tmp].l=nw;
				} else {
					f[nw]=f[pos]=f[tmp];
					tot-=2;
					xd[tmp].l=xd[pos].l;
				}
			} else if(pos) f[nw]=pos,xd[pos].r=nw; 
			else xd[++sz]=(data){nw,nw},tot++,f[nw]=nw;
		}
		fr(j,0,len-1){
			int nw=g[i][j];
			int fx=find(nw);
			if(vis[fx]!=i) vis[nw]=i,ans+=qz[a[xd[fx].l]-1]+qz[a[xd[fx].r]-1];
		}
		ans+=sum;
		sum+=tot;
	}
	cout<<ans<<endl;
	return 0;
}