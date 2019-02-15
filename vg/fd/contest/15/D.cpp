#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long 
using namespace std;
const int N=55,M=110;
int k,x,n,m;
int a[M],b[M];
LL f[N];

LL Go(int i,int j,int z,int t){
	int I=i,J=j,Z=z,T=t;
	LL tmp=0,pos=0;
	fr(i,3,k){
		LL zz=tmp+pos;
		if(J==1&&Z==3) zz++;
		tmp=pos,pos=zz;
		int Q=Z,W=T;
		Z=I;I=Q,J=W;
	}
	return pos;
}

void GG(){
	fr(i,1,n){
		if(a[i]==1) printf("A");
		if(a[i]==2) printf("Z");
		if(a[i]==3) printf("C");
	}
	puts("");
	fr(i,1,m){
		if(b[i]==1) printf("A");
		if(b[i]==2) printf("Z");
		if(b[i]==3) printf("C");
	}
	exit(0);
}

void check(int s1,int t1,int s2,int t2,int A,int B){
	if(!A) {
		a[1]=s1;a[n]=t1;
		fr(i,2,n-1) a[i]=2;
	} else {
		if(s1!=1){
			if(t1==3){
				if(A*2+1<=n){
					a[1]=s1;
					fr(i,0,A-1) a[2+i*2]=1,a[3+i*2]=3;
					fr(i,A*2+2,n) a[i]=t1;
				}
				else return ;
			} else {
				if(A*2+2<=n){
					a[1]=s1;
					fr(i,0,A-1) a[2+i*2]=1,a[3+i*2]=3;
					fr(i,A*2+2,n) a[i]=t1;
				}else return ;
			}
		}
		else {
			if(t1==3){
				if(A*2<=n){
					fr(i,0,A-1) a[i*2+1]=1,a[i*2+2]=3;
					fr(i,A*2+1,n) a[i]=t1;
				}
				else return ;
			}else{
				if(A*2+1<=n){
					fr(i,0,A-1) a[i*2+1]=1,a[i*2+2]=3;
					fr(i,A*2+1,n) a[i]=t1;
				} else return ;
			}
		}
	}
	if(!B){
		b[1]=s2,b[m]=t2;
		fr(i,2,m-1) b[i]=2;
	} else {
		if(s2!=1){
			if(t2==3){
				if(B*2+1<=m){
					b[1]=s2;
					fr(i,0,B-1) b[2+i*2]=1,b[3+i*2]=3;
					fr(i,B*2+2,m) b[i]=t2;
				}
				else return ;
			} else {
				if(B*2+2<=m){
					b[1]=s2;
					fr(i,0,B-1) b[2+i*2]=1,b[3+i*2]=3;
					fr(i,B*2+2,m) b[i]=t2;
				}else return ;
			}
		}
		else {
			if(t2==3){
				if(B*2<=m){
					fr(i,0,B-1) b[i*2+1]=1,b[i*2+2]=3;
					fr(i,B*2+1,m) b[i]=t2;
				}
				else return ;
			}else{
				if(B*2+1<=m){
					fr(i,0,B-1) b[i*2+1]=1,b[i*2+2]=3;
					fr(i,B*2+1,m) b[i]=t2;
				} else return ;
			}
		}
	}
	GG();
}

int main(){
	scanf("%d%d%d%d",&k,&x,&n,&m);
	f[1]=1,f[2]=1;
	fr(i,3,k) f[i]=f[i-1]+f[i-2];
	fr(i,1,3) fr(j,1,3) fr(z,1,3) fr(t,1,3){
		if(n==1&&(i!=j)) continue;
		if(m==1&&(z!=t)) continue;
		LL pos=Go(i,j,z,t);
	//	printf("%d %d %d %d %lld\n",i,j,z,t,pos);
		fr(Q,0,n/2) fr(W,0,m/2) {
			//printf("%lld\n",Q*1LL*f[k-2]+W*1LL*f[k-1]+pos);
			if(Q*1LL*f[k-2]+W*1LL*f[k-1]+pos==x) check(i,j,z,t,Q,W);
		}
	}
	printf("Happy new year!\n");
	return 0;
}
