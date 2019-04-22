#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define frl(i,x,y) for(int i=x;i<y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=1e6+10;

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

struct hsh{
	int a[8];
	hsh(){ memset(a,0,sizeof a); }
	hsh(int x) { rf(i,7,0) a[i]=x%5,x/=5;}
	hsh(int *_a) { frl(i,0,8) a[i]=_a[i]; }
	void st() { sort(a,a+8); }
	void rd() {
		frl(i,0,8) read(a[i]);
		st();
	}
	int cal(){
		int res=0;
		frl(i,0,8) res*=5,res+=a[i];
		return res;
	}
};
struct data{
	int nt,to;
}ed[N<<6];
int d[N],head[N],ys[N],sy[N],v[N];
queue<int>q;
int cnt=0,tot=0;

void add(int x,int y){
	d[y]++;
	ed[++cnt].to=y,ed[cnt].nt=head[x],head[x]=cnt;
}

void dfs(int dep,int lt,int val){
	if (dep==8) sy[++tot]=val,ys[val]=tot;
	 else frl(i,lt,5) dfs(dep+1,i,val*5+i);
}

int cal(int x,int y){
	return (x-1)*tot+y-1;
}

void init(){
	dfs(0,0,0);
	fr(i,1,tot) fr(j,1,tot){
		hsh pos(sy[i]),tmp(sy[j]);
		frl(k,0,8) if(pos.a[k]){
			frl(t,0,8) if(tmp.a[t]) {
				hsh gg(pos.a);
				gg.a[k]=(pos.a[k]+tmp.a[t])%5,gg.st();
				int qwq=ys[gg.cal()];
				add(cal(j,qwq),cal(i,j));
			}
		}
	}
	fr(i,2,tot) v[cal(i,1)]=1,q.push(cal(i,1));
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=ed[i].nt){
			if(!v[ed[i].to]){
				if(v[u]==1) v[ed[i].to]=-1,q.push(ed[i].to);
				else if(--d[ed[i].to] == 0){
					q.push(ed[i].to);
					v[ed[i].to]=1;
				}
			}
		}
	}
	//fr(i,1,tot*tot) printf("%d\n",v[i]);
}

int c[8];

int main(){
	init();
	int T;read(T);
	fr(o,1,T){
		int f;read(f);
		hsh A,B;
		A.rd(),B.rd();
		if (f) swap(A,B);
		int gg=v[cal(ys[A.cal()],ys[B.cal()])];
		//printf("%d %d %d\n",A.cal(),B.cal(),cal(ys[A.cal()],ys[B.cal()]));
		if (!gg) printf("Deal\n");
		else if (gg==1) 
			if (f) printf("Alice\n");
			 else printf("Bob\n");
		else if (f) printf("Bob\n");
		else printf("Alice\n");
	}
	return 0;
}