#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define bug(x) cout<<#x<<"="<<x<<endl;
#define LL long long
using namespace std;
const int N=1e3+10,M=1e6+10;
int n,m,k,p;
LL a[N][N],c[N],r[N],val[M];

bool cmp(int x,int y){
	return x>y;
}

bool check(LL zd,int nm){
	LL kk=0;
	fr(i,1,n){
		LL tmp=(r[i]-zd+p*m)/(p*m);
		kk+=tmp;
		if(!tmp) break;
		if(kk>=nm) return 1;
	}
	return kk>=nm;
}

LL Get(int nm){
	LL l=-1e11,r=1e3,ans=-1;
	while(l<=r){
		LL mid=(l+r)>>1;
		if(check(mid,nm)) ans=mid,l=mid+1;
		else r=mid-1;
	}
	return ans;
}

bool judge(LL zd,int nm){
	LL kk=0;
	fr(i,1,m){
		LL tmp=(c[i]-zd+p*n)/(p*n);
		kk+=tmp;
		if(!tmp) break;
		if(kk>=nm) return 1;
	}
	return kk>=nm;
}

LL get(int nm){
	LL l=-1e11,r=1e3,ans=-1;
	while(l<=r){
		LL mid=(l+r)>>1;
		if(judge(mid,nm)) ans=mid,l=mid+1;
		else r=mid-1;
	}
	return ans;
}

LL js(LL w,int nm){
	LL pos=0;LL kk=0;
	fr(i,1,m) {
		LL tmp=(c[i]-w+p*n)/(p*n);
		tmp=min(tmp,nm-kk);
		LL tt=c[i]-(tmp-1)*p*n;
		pos+=(c[i]+tt)*(tmp)/2;
		kk+=tmp;
		if(kk>=nm) break;
	}
	return pos;
}

LL sj(LL v,int nm){
	LL pos=0;LL kk=0;
	fr(i,1,n){
		LL tmp=(r[i]-v+p*m)/(p*m);
		tmp=min(tmp,nm-kk);
		LL tt=r[i]-(tmp-1)*p*m;
		pos+=(r[i]+tt)*tmp/2;
		kk+=tmp;
		if(kk>=nm) break;
	}
	return pos;
}

int main(){
	cin>>n>>m>>k>>p;
	fr(i,1,n) fr(j,1,m) cin>>a[i][j];
	fr(i,1,n) fr(j,1,m) c[j]+=a[i][j],r[i]+=a[i][j];
	sort(c+1,c+1+m,cmp),sort(r+1,r+1+n,cmp);
	LL maxn=-1e17;
	fr(tr,1,k-1) {
		LL pos=-(k-tr)*1LL*tr*1LL*p;
		LL v=Get(tr),w=get(k-tr);
		pos+=js(w,k-tr),pos+=sj(v,tr);
		val[tr]=pos;
		maxn=max(maxn,pos);
//		if(tr>1&&val[tr]<val[tr-1]) break;
	}
	LL v=Get(k),w=get(k);
	maxn=max(maxn,js(w,k));
	maxn=max(maxn,sj(v,k));
	cout<<maxn<<endl;
	return 0;
}
