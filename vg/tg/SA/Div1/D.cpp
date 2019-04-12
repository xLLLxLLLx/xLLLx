#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long 
using namespace std;
const int N=3e5+10,mod=1e9+7;
char lx[N];
int n=0;
LL q[N][4],d[N];
int c[N],f[N],a[N],mk[N],id[N],rk[N],nm[N],sa[N],h[N];

void Mul(LL &x,LL y){
	x=(x*y)%mod;
}

void Add(LL &x,LL y){
	x=(x+y+mod)%mod;
}

void Sort(){
	fr(i,1,max(n,29)) nm[i]=0;
	fr(i,1,n) nm[rk[i]]++;
	fr(i,1,max(n,29)) nm[i]+=nm[i-1];
	rf(i,n,1) sa[nm[rk[id[i]]]--]=id[i];
}

void Geth(){
	int H=0;
	fr(i,1,n){
		if(H) H--;
		int j=sa[rk[i]-1];
		while(a[i+H]==a[j+H]) H++;
		h[rk[i]]=H;
	}
	//fr(i,2,n) printf("%d ",h[i]);
}

bool cmp(int x,int y,int j){
	return id[x]==id[y] && id[x+j]==id[y+j];
}

bool Cmp(int x,int y){
	return h[x]>h[y];
}

int find(int k){
	return f[k]==k ? f[k] : f[k]=find(f[k]);
}

int main(){
	int minn=N;
	fr(o,1,3){
		scanf("%s",lx+1);
		int len=strlen(lx+1);
		minn=min(minn,len);
		fr(i,1,len) a[++n]=lx[i]-'a'+1,mk[n]=o;
		a[++n]=o+26;
	}
	fr(i,1,n) id[i]=i,rk[i]=a[i],c[i]=i,f[i]=i;
	Sort();
	for(int j=1,p=0;p<n;j<<=1){
		p=0;
		fr(i,n-j+1,n) id[++p]=i;
		fr(i,1,n) if(sa[i]>j) id[++p]=sa[i]-j;
		Sort(),swap(id,rk);
		p=0;
		fr(i,1,n) rk[sa[i]] = cmp(sa[i],sa[i-1],j) ? p : ++p;
	}
	Geth();
	fr(i,1,n) if(mk[sa[i]]) q[i][mk[sa[i]]]++;
	sort(c+1,c+1+n,Cmp);
	int j=1;LL ans=0;
	// fr(i,1,n) printf("%d ",h[c[i]]);
	// puts("");
	rf(i,minn,1){
		while(j<=n&&h[c[j]]>=i){
			int fx=find(c[j]-1),fy=find(c[j]);
			LL pos=1;
			fr(o,1,3) Mul(pos,q[fy][o]);
			Add(ans,-pos),pos=1;
			fr(o,1,3) Mul(pos,q[fx][o]),q[fx][o]+=q[fy][o];
			Add(ans,-pos),pos=1;
			fr(o,1,3) Mul(pos,q[fx][o]);
			Add(ans,pos);
			f[fy]=fx;
			j++;
		}
		d[i]=ans;
	}
	fr(i,1,minn) printf("%lld ",d[i]);
	return 0;
}