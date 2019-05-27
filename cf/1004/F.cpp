#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define frl(i,x,y) for(int i=x;i<y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ls (x<<1)
#define rs (x<<1|1)
#define fi first
#define se second
#define mp make_pair
#define ll long long
using namespace std;
const int N=1e5+10;
struct data{
	ll sum;
	vector<pair<ll,int> >  pre,bac;
	data(){
		sum=0;
		pre.clear();
		bac.clear();
	}
}tr[N<<2];
int n,m,bz;
int a[N];

ll get(data A,data B){
	ll ans=0;
	int lena=A.bac.size(),lenb=B.pre.size();
	frl(i,0,lena) frl(j,0,lenb) {
		if((A.bac[i].se|B.pre[j].se)>=bz) {
			ans+=A.bac[i].fi*B.pre[j].fi;
		}
	}
	return ans;
}

data up(data A,data B){
	// printf("Asum=%lld\n",A.sum);
	// frl(i,0,A.pre.size()) printf("pre%lld %d\n",A.pre[i].fi,A.pre[i].se);
	// frl(i,0,A.bac.size()) printf("bac%lld %d\n",A.bac[i].fi,A.bac[i].se);
	// printf("Bsum=%lld\n",B.sum);
	// frl(i,0,B.pre.size()) printf("pre%lld %d\n",B.pre[i].fi,B.pre[i].se);
	// frl(i,0,B.bac.size()) printf("bac%lld %d\n",B.bac[i].fi,B.bac[i].se);
	data res;
	res.sum=A.sum+B.sum;
	res.sum+=get(A,B);
	int lena=A.pre.size(),lenb=B.pre.size();
	frl(i,0,lena) {
		res.pre.push_back(A.pre[i]);
	}
	frl(i,0,lenb) {
		pair<ll,int> ss=res.pre.back();
		int pos=A.pre[lena-1].se|B.pre[i].se;
		ll tmp=B.pre[i].fi;
		if(pos==ss.se) {
			res.pre.back().fi+=tmp;
		} else {
			res.pre.push_back(mp(tmp,pos));
		}
	}
	//hb hz
	lena=A.bac.size(),lenb=B.bac.size();
	frl(i,0,lenb) {
		res.bac.push_back(B.bac[i]);
	}
	frl(i,0,lena) {
		pair<ll,int> ss=res.bac.back();
		int pos=B.bac[lenb-1].se|A.bac[i].se;
		ll tmp=A.bac[i].fi;
		if(pos==ss.se) {
			res.bac.back().fi+=tmp;
		} else {
			res.bac.push_back(mp(tmp,pos));
		}
	}
	// printf("ressum=%lld\n",res.sum);
	// frl(i,0,res.pre.size()) printf("pre%lld %d\n",res.pre[i].fi,res.pre[i].se);
	// frl(i,0,res.bac.size()) printf("bac%lld %d\n",res.bac[i].fi,res.bac[i].se);
	return res;
}

void build(int x,int l,int r){
	if(l==r) {
		scanf("%d",&a[l]);
		if(a[l]>=bz) tr[x].sum=1;
		tr[x].pre.push_back(mp(1,a[l]));
		tr[x].bac.push_back(mp(1,a[l]));
		return ;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid),build(rs,mid+1,r);
	tr[x]=up(tr[ls],tr[rs]);
	// printf("x=%d l=%d r=%d sium=%lld\n",x,l,r,tr[x].sum);
}

void Change(int x,int l,int r,int L,int v){
	if(l==r) {
		if(v>=bz) tr[x].sum=1;
		else tr[x].sum=0;
		tr[x].pre.clear();
		tr[x].bac.clear();
		tr[x].pre.push_back(mp(1,v));
		tr[x].bac.push_back(mp(1,v));
		return ;
	}
	int mid=(l+r)>>1;
	if(L<=mid) Change(ls,l,mid,L,v);
	else Change(rs,mid+1,r,L,v);
	tr[x]=up(tr[ls],tr[rs]);
	// printf("x=%d l=%d r=%d sium=%lld\n",x,l,r,tr[x].sum);
}

data Ask(int x,int l,int r,int L,int R){
	// printf("x=%d l=%d r=%d L=%d R=%d\n",x,l,r,L,R);
	if(L<=l&&r<=R) {
		return tr[x];
	}
	int mid=(l+r)>>1;
	if(R<=mid) return Ask(ls,l,mid,L,R);
	else if(L>mid) return Ask(rs,mid+1,r,L,R);
	else {
		// printf("haha\n");
		return up(Ask(ls,l,mid,L,R),Ask(rs,mid+1,r,L,R));
	}
}

int main(){
	scanf("%d%d%d",&n,&m,&bz);
	build(1,1,n);
	fr(i,1,m) {
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		if(x==2) {
			printf("%lld\n",Ask(1,1,n,y,z).sum);
		} else {
			Change(1,1,n,y,z);
		}
	}
	return 0;
}