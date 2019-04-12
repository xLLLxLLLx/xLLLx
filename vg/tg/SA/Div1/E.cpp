#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=4e5+10,LOG=20;
char lx[N];
int n=0;
int A[N],B[N];
int mk[N],id[N],a[N],rk[N],nm[N],sa[N],h[N],st[N][LOG+1];

template <class T>
void read(T &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void Sort(){
	memset(nm,0,sizeof nm);
	fr(i,1,n) nm[rk[i]]++;
	fr(i,1,max(n,26)) nm[i]+=nm[i-1];
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
	return rk[x]<rk[y];
}

void rmq(){
	fr(i,1,n) st[i][0]=h[i];
	fr(j,1,LOG){
		fr(i,1,n){
			if(i+(1<<j)>n+1) break;
			st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
		}
	}
}

int Get(int l,int r){
	if(l>r) return n-sa[r]+1;
	int t=log(double(r-l+1))/log(2.0);
	return min(st[l][t],st[r-(1<<t)+1][t]);
}

#define ls (x<<1)
#define rs (x<<1|1)

int sz[N<<2],tag[N<<2];
LL sum[N<<2];

void up(int x){
	sz[x]=sz[ls]+sz[rs];
	sum[x]=sum[ls]+sum[rs];
}

void down(int x){
	if(tag[x]){
		sum[ls]=sz[ls]=0;
		sum[rs]=sz[rs]=0;
		tag[ls]=tag[rs]=1;
		tag[x]=0;
	}
}

int Delet(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R){
		int pos=sz[x];
		tag[x]=1;
		sum[x]=sz[x]=0;
		down(x);
		return pos;
	}
	down(x);
	int mid=(l+r)>>1,ans=0;
	if(L<=mid) ans+=Delet(ls,l,mid,L,R);
	if(R>mid) ans+=Delet(rs,mid+1,r,L,R);
	up(x);
	return ans;
}

void change(int x,int l,int r,int L,int k){
	if(l==r){
		sz[x]+=k,sum[x]+=k*1LL*l;
		return ;
	}
	down(x);
	int mid=(l+r)>>1;
	if(L<=mid) change(ls,l,mid,L,k);
	else change(rs,mid+1,r,L,k);
	up(x);
}

void work(int lena,int lenb){
	sort(A+1,A+1+lena,Cmp);
	sort(B+1,B+1+lenb,Cmp);
	LL tot=0;
	for(int i=lena,j=lenb;i;--i){
		if(i!=lena){
			int pos=Get(rk[A[i]]+1,rk[A[i+1]]),tmp=Delet(1,0,n,pos+1,n);
			change(1,0,n,pos,tmp);
		}
		for(;rk[B[j]]>=rk[A[i]]&&j;--j)
			change(1,0,n,Get(rk[A[i]]+1,rk[B[j]]),1);
		tot+=sum[1];
	}
	Delet(1,0,n,0,n);
	for(int i=lenb,j=lena;i;--i){
		if(i!=lenb){
			int pos=Get(rk[B[i]]+1,rk[B[i+1]]),tmp=Delet(1,0,n,pos+1,n);
			change(1,0,n,pos,tmp);
		}
		for(;rk[A[j]]>rk[B[i]]&&j;--j)
			change(1,0,n,Get(rk[B[i]]+1,rk[A[j]]),1);
		tot+=sum[1];
	}
	Delet(1,0,n,0,n);
	printf("%lld\n",tot);
}

int main(){
	int m;
	read(n),read(m);
	scanf("%s",lx+1);
	fr(i,1,n) a[i]=lx[i]-'a'+1;
	fr(i,1,n) id[i]=i,rk[i]=a[i];
	Sort();
	for(int j=1,p=0;p<n;j<<=1){
		p=0;
		fr(i,n-j+1,n) id[++p]=i;
		fr(i,1,n) if(sa[i]>j) id[++p]=sa[i]-j;
		Sort(),swap(id,rk);
		p=0;
		fr(i,1,n) rk[sa[i]] = cmp(sa[i],sa[i-1],j) ? p : ++p;
	}
	Geth(),rmq();
	fr(o,1,m){
		int q1,q2;read(q1),read(q2);
		LL ans=0;int res=0;
		fr(i,1,q1) read(A[i]);
		fr(i,1,q2) read(B[i]);
		work(q1,q2);
	}
	return 0;
}