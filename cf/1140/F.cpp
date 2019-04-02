#define Pir pair<int,int>
#define fir first
#define sec second
#define LL long long
const int N=300000+10;

int q;
map<Pir,int> mp;

vector<Pir> Q[N<<2];

void Append(int ql,int qr,Pir p,int o=1,int l=1,int r=q)
{
	if(ql<=l&&r<=qr)
	{
		Q[o].push_back(p);
		return;
	}
	int mid=(l+r)>>1,lc=o<<1,rc=lc^1;
	if(ql<=mid)Append(ql,qr,p,lc,l,mid);
	if(qr>mid)Append(ql,qr,p,rc,mid+1,r);
}

struct Data{int *p,x;}stk[N<<2];
int tp;

int fa[N<<1],sz[N<<1],szx[N<<1];

void F(int &x,int y)
{
	stk[++tp]=(Data){&x,x};
	x=y;
}

void G()
{
	*stk[tp].p=stk[tp].x;
	--tp;
}

int Find(int x){return fa[x]?Find(fa[x]):x;}

LL ans;
void Hb(int x,int y)
{
	x=Find(x);y=Find(y);
	if(x==y)return;
	if(sz[x]<sz[y])swap(x,y);
	F(fa[y],x);
	ans+=(LL)szx[x]*(sz[y]-szx[y])+(LL)szx[y]*(sz[x]-szx[x]);
	F(sz[x],sz[x]+sz[y]);
	F(szx[x],szx[x]+szx[y]);
}

void Solve(int o=1,int l=1,int r=q)
{
	int ntp=tp;LL lastans=ans;
	for(int i=0;i<(int)Q[o].size();++i)Hb(Q[o][i].fir,N+Q[o][i].sec);
	if(l==r)printf("%lld ",ans);
	else
	{
		int mid=(l+r)>>1;
		Solve(o<<1,l,mid);
		Solve((o<<1)^1,mid+1,r);
	}
	for(ans=lastans;ntp!=tp;G());
}

int main()
{
	for(int i=0;i<(N<<1);++i)
	{
		sz[i]=1;
		szx[i]=(i<N);
	}
	scanf("%d",&q);
	for(int i=1;i<=q;++i)
	{
		Pir p;scanf("%d%d",&p.fir,&p.sec);
		if(mp[p])
		{
			Append(mp[p],i-1,p);
			mp[p]=0;
		}
		else mp[p]=i;
	}
	for(map<Pir,int>::iterator it=mp.begin();it!=mp.end();++it)
		if(it->sec)
			Append(it->sec,q,it->fir);
	Solve();
	return 0;
}