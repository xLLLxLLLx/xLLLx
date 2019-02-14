#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10;
struct data{
	int fr,to,rk,w;
}a[N];
vector<int>qx[N],B[N];
map<int,int>mp[N];
map<int,int> :: iterator sit;
int n,m,cnt=0;
LL v[N];
int gg[N],vis[N],f[N],b[N],c[N];

int find(int k){
	return f[k]==k?k:f[k]=find(f[k]);
}

bool cmp(data xx,data yy){
	return xx.w<yy.w;
}

void luangao(){
	int lt=1,now=1,nm=0;
	fr(i,1,m){
		if(i>1&&a[i].w!=a[i-1].w){
			now++;
			fr(j,1,nm){
				int len=qx[j].size();
				if(len==1) b[a[qx[j][0]].rk]=2;
				else {
					fr(k,0,len-1) b[a[qx[j][k]].rk]=1;
				}
				qx[j].clear();
			}
			fr(j,lt,i-1){
				int x=a[j].fr,y=a[j].to;
				int fx=find(x),fy=find(y);
				/*
				if(fx==fy)
				*/
				f[fx]=fy;
			}
			fr(j,1,gg[0]) mp[gg[j]].clear();
			lt=i;c[0]=0;nm=0;gg[0]=0;
		}
		int x=a[i].fr,y=a[i].to;
		int fx=find(x),fy=find(y);
		if(fx==fy) continue;
		if(fx>fy) swap(fx,fy);
		if(vis[fx]!=now) gg[++gg[0]]=fx,vis[fx]=now;
		if(mp[fx].count(fy)) qx[mp[fx][fy]].push_back(i);
		else mp[fx][fy]=++nm,qx[nm].push_back(i);
	}
	fr(j,1,nm){
		int len=qx[j].size();
		if(len==1) b[a[qx[j][0]].rk]=2;
		else {
			fr(k,0,len-1) b[a[qx[j][k]].rk]=1;
		}
	}
	fr(j,lt,n){
		int x=a[j].fr,y=a[j].to;
		int fx=find(x),fy=find(y);
		/*
		if(fx==fy)
		*/
		f[fx]=fy;
	}
}

int main(){
	scanf("%d%d",&n,&m);
	fr(i,1,m){
		int x,y,w;
		scanf("%d%d%d",&x,&y,&w);
		a[i]=(data){x,y,i,w};
	}
	fr(i,1,n) f[i]=i;
	sort(a+1,a+1+m,cmp);
	luangao();
	int kk=0;
	fr(i,1,m) if(b[i]==2) kk++;
	if(kk==m&&m>=n) fr(i,1,m) b[i]=1;
	fr(i,1,m){
		if(!b[i]) printf("none\n");
		else if(b[i]==1) printf("at least one\n");
		else printf("any\n");
	}
	return 0;
}
