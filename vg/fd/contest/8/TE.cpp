#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=30;
string lx[2];
int c[N];

int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}

int main(){
	int n;scanf("%d",&n);
	int sum=0,qaq=0;
	fr(i,1,n) {
		scanf("%d",&c[i]),sum+=c[i];
		if(c[i]&1) qaq++;
	}
	if(qaq>1) {
		printf("0\n");
		fr(i,1,n)
		 fr(j,1,c[i]) printf("%c",char(i+'a'-1));
		return 0;
	}
	int gg=c[1];
	fr(i,2,n) gg=gcd(max(gg,c[i]),min(gg,c[i]));
	fr(i,1,n) c[i]/=gg;
	printf("%d\n",gg);
	lx[0]="",lx[1]="";
	string ll="";
	if(gg&1) {
		fr(i,1,n)
		 fr(j,1,c[i]/2) lx[0]+=char(i+'a'-1);
		fr(i,1,n) if(c[i]&1) lx[0]+=char(i+'a'-1);
		rf(i,n,1)
		 fr(j,1,c[i]/2) lx[0]+=char(i+'a'-1);
		int len=lx[0].length();
		rf(i,len-1,0) lx[1]+=lx[0][i];
		fr(i,1,gg) ll+=lx[i%2];
		cout<<ll<<endl;
	} else {
		fr(i,1,n)
		 fr(j,1,c[i]) lx[0]+=char(i+'a'-1);
		int len=lx[0].length();
		rf(i,len-1,0) lx[1]+=lx[0][i];
		fr(i,1,gg) ll+=lx[i%2];
		cout<<ll<<endl; 
	}
	return 0;
}
