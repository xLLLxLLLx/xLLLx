#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define re register
#define gc getchar
#define pc putchar
#define cs const

inline
ll getint(){
	re ll num;
	re char c;
	while(!isdigit(c=gc()));num=c^48;
	while(isdigit(c=gc()))num=(num<<1)+(num<<3)+(c^48);
	return num;
}

inline
void outint(int a){
	static char ch[13];
	if(a==0)pc('0');
	while(a)ch[++ch[0]]=a-a/10*10,a/=10;
	while(ch[0])pc(ch[ch[0]--]^48);
}

cs int N=100005;

int last[N],nxt[N],to[N],ecnt;
inline
void addedge(int u,int v){
	nxt[++ecnt]=last[u],last[u]=ecnt,to[ecnt]=v;
}

map<ll,int> id;
int n;
ll d[N];
int siz[N];

int dist[N];
inline
void dfs(int u){
	for(int re e=last[u],v=to[e];e;v=to[e=nxt[e]]){
		dist[v]=dist[u]+1;
		dfs(v);
	}
}

vector<pair<int,int> > edge;

signed main(){
	n=getint();
	for(int re i=1;i<=n;++i)d[i]=getint(),id[d[i]]=i;
	sort(d+1,d+n+1);
	for(int re i=1;i<=n;++i)siz[i]=1;
	for(int re i=n;i>1;--i){
		int u=id[d[i]];
		int tmp=n-2*siz[u];
		if(tmp<=0)return puts("-1"),0; 
		ll t=d[i]-tmp;
		if(id.count(t)==0)return puts("-1"),0;
		int pos=id[t];
		addedge(pos,u);
		siz[pos]+=siz[u];
		edge.push_back(make_pair(pos,u));
	}
	ll sum=0;
	dfs(id[d[1]]);
	for(int re i=1;i<=n;++i){
		sum+=dist[i];
	}
	if(sum!=d[1])return puts("-1"),0;
	for(int re i=0;i<edge.size();++i)outint(edge[i].first),pc(' '),outint(edge[i].second),pc('\n');
	return 0;
}