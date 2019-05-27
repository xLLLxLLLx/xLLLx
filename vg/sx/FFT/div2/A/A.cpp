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
const int N=(1<<20)+1,M=1e5+10;
const double PI=acos(-1);
int rev[N],nm[N],c[M];
ll gg[N];

struct C {
	double r,i;
	C(){}
	C(double _r,double _i){ r=_r,i=_i; }
	C operator + (C x){ return C(r+x.r,i+x.i); }
	C operator - (C x){ return C(r-x.r,i-x.i); }
	C operator * (C x){ return C(r*x.r-i*x.i,r*x.i+i*x.r); }
}a[N],w[N];

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

int main(){
	int T;
	scanf("%d",&T);
	fr(o,1,T) {
		int A;
		scanf("%d",&A);
		int maxn=0;
		fr(i,1,A) {
			scanf("%d",&c[i]);
			nm[c[i]]++;
			maxn=max(maxn,c[i]);
		}
		int n=1,L=0;
		for(;n<=2*maxn;n<<=1,L++) ;
		fr(i,1,maxn) {
			a[i].r=nm[i];
		}
		frl(i,0,n) {
			w[i]=C(cos(2.0*i*PI/n),sin(2.0*i*PI/n));
			rev[i]=(rev[i>>1]>>1)+((i&1)<<(L-1));
		}
		fft(a,n);
		frl(i,0,n) {
			a[i]=a[i]*a[i];
			w[i].i=-w[i].i;
		}
		fft(a,n);
		frl(i,0,n) {
			gg[i]=(long long)(a[i].r/n+0.5);
			if(i%2==0) gg[i]-=nm[i>>1];
			gg[i]>>=1;
		}
		ll ans=0,tot=1ll*A*(A-1)*(A-2)/6;
		frl(i,1,n) {
			gg[i]+=gg[i-1];
		}
		ll cut=0,pos=0;
		sort(c+1,c+1+A);
		fr(i,1,A) {
			ans+=gg[n-1]-gg[c[i]];
			ans-=(A-i)*1ll*i;
			ans-=i-1;
			ans-=(A-i)*1ll*(A-i-1)/2;
		}
		frl(i,0,n) {
			a[i]=C(0,0),w[i]=C(0,0);
			rev[i]=0,gg[i]=0,nm[i]=0;
		}
		printf("%.7f\n",double(ans)/double(tot));
	}
	return 0;
}