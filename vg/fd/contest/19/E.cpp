#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define Fr(i,x,y) for(int i=x;i<y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define Rf(i,x,y) for(int i=x;i>y;--i)
#define LL long long
using namespace std;
const int N=1e5+10,M=1e6+10,LOG=19;
struct data{
	int nt,to;
}a[N<<1];
queue<int>Q;
int n,m;
int q[N],d[N];
int v[1<<LOG+1][LOG],mk[N];
int head[N],dep[N],c[M],res=0,cnt=0;

void add(int x,int y){
	a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].nt=head[y],head[y]=cnt;
}

void Min(int &x,int y){
	x=min(x,y);
}

void dfs(int u,int fa){
	dep[u]=dep[fa]+1;
	c[++res]=u;
	for(int i=head[u];i;i=a[i].nt){
		if(a[i].to!=fa){
			dfs(a[i].to,u);
			c[++res]=u;
		}
	}
}

void Gao(){
	memset(mk,-1,sizeof mk);
	//fr(i,1,res) printf("%d ",c[i]);
	//puts("");
	fr(i,1,res)
		if(mk[c[i]]==-1) mk[c[i]]=i;
	fr(i,1,res) v[i][0]=dep[c[i]];
	Fr(i,1,LOG) fr(j,1,res){
		if(j+(1<<i)>res+1) continue;
		int len=1<<(i-1);
		v[j][i]=min(v[j][i-1],v[j+len][i-1]);
	}
}

int zx(int l,int r){
	if(l>r) swap(l,r);
	int kk=log(double(r-l+1))/log(2.0);
	int pos=min(v[l][kk],v[r-(1<<kk)+1][kk]);
	//printf("%d %d %d\n",l,r,pos);
	return pos;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,x,y;i<n;++i){
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	dfs(1,0),Gao();
	int kk=sqrt(m),qq=m/kk;
	if(m%kk) qq++;
	fr(i,1,n) d[i]=dep[i]-1;
	Fr(o,0,qq){
		q[0]=0;
		fr(j,o*kk+1,min(o*kk+kk,m)){
			int x,y;scanf("%d%d",&x,&y);
			if(x==1) q[++q[0]]=y,d[y]=0;
			else {
				fr(i,1,q[0]) Min(d[y],dep[q[i]]+dep[y]-2*zx(mk[y],mk[q[i]]));
				printf("%d\n",d[y]);
			}
		}
		fr(i,1,q[0]) Q.push(q[i]);
		while(!Q.empty()){
			int u=Q.front();Q.pop();
			for(int i=head[u];i;i=a[i].nt){
				if(d[a[i].to]>1+d[u]) d[a[i].to]=1+d[u],Q.push(a[i].to);
			}
		}
	}
	return 0;
}
