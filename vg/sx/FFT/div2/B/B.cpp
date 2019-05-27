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
using namespace std;

const int N=(1<<20)+1;
const double PI=acos(-1.0);
char lx[N],ll[N];
int rev[N],gg[N];

struct C {
	double r,i;
	C(){}
	C(double _r,double _i){ r=_r,i=_i; }
	C operator + (C x){ return C(r+x.r,i+x.i); }
	C operator - (C x){ return C(r-x.r,i-x.i); }
	C operator * (C x){ return C(r*x.r-i*x.i,i*x.r+r*x.i); }
}a[N],b[N],w[N];

void fft(C a[],int n){
	frl(i,0,n)
		if(rev[i]>i) {
			swap(a[i],a[rev[i]]);
		}
	for(int t=n>>1,d=1;d<n;d<<=1,t>>=1)
		for(int i=0;i<n;i+=(d<<1)) {
			frl(j,0,d) {
				C tmp=w[t*j]*a[i+j+d];
				a[i+j+d]=a[i+j]-tmp;
				a[i+j]=a[i+j]+tmp;
			}
		}
}

int main(){
	while(scanf("%s%s",lx,ll)==2) {
		int A=strlen(lx),B=strlen(ll);
		frl(i,0,A) {
			a[i].r=lx[A-i-1]-'0';
		}
		frl(i,0,B) {
			b[i].r=ll[B-i-1]-'0';
		}
		int n=1,L=0;
		for(;n<=A+B;n<<=1,L++) ;
		frl(i,0,n) {
			rev[i]=(rev[i>>1]>>1)+((i&1)<<(L-1));
			w[i]=C(cos(2.0*i*PI/n),sin(2.0*i*PI/n));
			// printf("%d %lf %lf\n",rev[i],w[i].r,w[i].i);
		}
		// printf("%d\n",n);
		fft(a,n),fft(b,n);
		frl(i,0,n) {
			a[i]=a[i]*b[i];
			w[i].i=-w[i].i;
		}
		fft(a,n);
		frl(i,0,n) {
			gg[i]+=int(a[i].r/n+0.5);
			gg[i+1]+=gg[i]/10;
			gg[i]%=10;
		}
		frl(i,0,n) {
			a[i]=C(0,0),b[i]=C(0,0),w[i]=C(0,0),rev[i]=0;
		}
		for(;!gg[n]&&n;n--) ;
		rf(i,n,0) {
			printf("%d",gg[i]);
			gg[i]=0;
		}
		puts("");
	}
	return 0;
}