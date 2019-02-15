#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=210;
int n,cnt=-1,ans=0,flg=0,res=0;
int head[N],a[N],g[N],vis[N];
struct data{
	int to,nt,f,c;
}A[N*N];
vector<int>B[N],qx[N];
queue<int>q;

void add(int x,int y,int c){
	A[++cnt].to=y,A[cnt].c=c,A[cnt].f=0,A[cnt].nt=head[x],head[x]=cnt;
	A[++cnt].to=x,A[cnt].c=0,A[cnt].f=0,A[cnt].nt=head[y],head[y]=cnt;
}

bool check(int x){
	int len=sqrt(x);
	fr(i,2,len) if(x%i==0) return false;
	return true;
}

int mf[N],p[N];

bool bfs(){
	memset(mf,0,sizeof mf),memset(p,0,sizeof p);
	mf[0]=10000,p[0]=-1;
	q.push(0);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i!=-1;i=A[i].nt) {
			int pos=A[i].c-A[i].f,to=A[i].to;
			if(!mf[to]&&pos>0){
				mf[to]=min(pos,mf[u]);
				p[to]=i;q.push(to);
				if(to==n+1) {
					while(!q.empty()) q.pop();
					break;
				}
			}
		}
	}
	int be=n+1;
	if(!mf[n+1]) return false;
	for(;be;) {
		A[p[be]].f+=mf[n+1];
		A[p[be]^1].f-=mf[n+1];
		be=A[p[be]^1].to;
	}
	ans+=mf[n+1];
	return mf[n+1];
}

void pd(){
	int res=0;
	for(int i=head[0];i!=-1;i=A[i].nt) if(A[i].f==2) res++;
	for(int i=head[n+1];i!=-1;i=A[i].nt) if(A[i].f==-2) res++;
	if(res==n) return ;
	printf("Impossible\n");
	exit(0);
}

void dfs(int u){
	qx[res].push_back(u);vis[u]=1;
	int len=B[u].size();
	fr(i,0,len-1){
		int to=B[u][i];
		if(!vis[to]) g[to]=u,dfs(to);
		else if(to!=g[u]) flg=1;
		else continue;
		return ;
	}
}

int main(){
	memset(head,-1,sizeof head);
	scanf("%d",&n);
	fr(i,1,n) scanf("%d",&a[i]);
	fr(i,1,n){
		if(a[i]&1) {
			add(0,i,2);
			fr(j,1,n) if(check(a[i]+a[j])) add(i,j,1);
		} else add(i,n+1,2);
	}
	bfs();
	for(;bfs(););
	pd();
	fr(u,1,n) for(int i=head[u];i;i=A[i].nt) {
		if(A[i].c==A[i].f&&A[i].f==1) {
			B[u].push_back(A[i].to);
			B[A[i].to].push_back(u);
		}
	}
	fr(i,1,n) {
		if(a[i]%2&&!vis[i]) g[i]=i,++res,flg=0,dfs(i);
	}
	printf("%d\n",res);
	fr(i,1,res){
		int len=qx[i].size();
		printf("%d ",len);
		fr(j,0,len-1) printf("%d ",qx[i][j]);
		puts("");
	}
	return 0;
}
