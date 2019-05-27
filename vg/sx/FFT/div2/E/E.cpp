#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<cmath>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define frl(i,x,y) for(int i=x;i<y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=3e5+10;
const double PI=acos(-1.0);
struct block {
	int l,r;
}bl[N];
int rev[N],pre[N],bac[N],now[N],mk[N];
ll gg[N],nm[N],c[N];

struct C {
	double r,i;
	C(){}
	C(double _r,double _i){ r=_r,i=_i; }
	C operator + (C x){ return C(r+x.r,i+x.i); }
	C operator - (C x){ return C(r-x.r,i-x.i); }
	C operator * (C x){ return C(r*x.r-i*x.i,r*x.i+i*x.r); }
}a[N],b[N],w[N];

void fft(C a[],int n) {
	frl(i,0,n)
		if(rev[i]>i) 
			swap(a[i],a[rev[i]]);
	for(int t=n>>1,d=1;d<n;t>>=1,d<<=1) 
		for(int i=0;i<n;i+=(d<<1)) {
			frl(j,0,d) {
				C tmp=w[t*j]*a[i+j+d];
				a[i+j+d]=a[i+j]-tmp;
				a[i+j]=a[i+j]+tmp;
			}
		}
}


int mul(C a[],C b[],int A,int B){
	int L=0,n=1;
	for(;n<=A+B;n<<=1,L++) ;
	frl(i,0,n) {
		w[i]=C(cos(2.0*i*PI/n),sin(2.0*i*PI/n));
		rev[i]=(rev[i>>1]>>1)+((i&1)<<(L-1));
	}
	fft(a,n),fft(b,n);
	frl(i,0,n) {
		a[i]=a[i]*b[i];
		w[i].i=-w[i].i;
	}
	fft(a,n);
	frl(i,0,n) {
		gg[i]=(long long)(a[i].r/n+0.5);
		// if(gg[i]) printf("gg %d %lld\n",i,gg[i]);
		a[i]=C(0,0),b[i]=C(0,0),w[i]=C(0,0),rev[i]=0;
	}
	return n;
}

ll ans=0;

int main(){
	int len,maxn=30000;
	scanf("%d",&len);
	fr(i,1,len) {
		scanf("%d",&c[i]);
		bac[c[i]]++;
	}
	int bk=5*sqrt(len),num=len/bk+1;
	fr(i,1,len) {
		mk[i]=(i/bk);
		if(i%bk) mk[i]++;
		bl[mk[i]].r=i;
		if(!bl[mk[i]].l) bl[mk[i]].l=i;
	}
	fr(i,1,num) {
		fr(j,bl[i].l,bl[i].r) {
			bac[c[j]]--;
			// printf("%d ",c[j]);
		}
		// puts("");
		fr(j,bl[i].l,bl[i].r) {
			fr(k,j+1,bl[i].r) now[c[k]]++;
			fr(k,j+1,bl[i].r) {
				now[c[k]]--;
				int pos=c[k]*2-c[j];
				int tmp=c[j]*2-c[k];
				if(pos>0) ans+=bac[pos]+now[pos];
				if(tmp>0) ans+=pre[tmp];
			}
		}
		fr(j,1,maxn) {
			// if(pre[j]) printf("pre%d %d\n",j,pre[j]);
			// if(bac[j]) printf("bac%d %d\n",j,bac[j]);
			a[j].r=pre[j];
			b[j].r=bac[j];
		}
		int n=mul(a,b,maxn,maxn);
		// printf("ans=%lld\n",ans);
		fr(j,bl[i].l,bl[i].r) {
			ans+=gg[c[j]*2];
			pre[c[j]]++;
		}
		frl(j,0,n) gg[j]=0;
	}
	printf("%lld\n",ans);
	return 0;
}