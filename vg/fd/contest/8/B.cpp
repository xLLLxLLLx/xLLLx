#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10;
int a[N],b[N];

int main(){
	int n;scanf("%d",&n);
	int res=0,FLG=0,flg=0;
	fr(i,1,n){
		char ch=getchar();
		for(;ch<'0'||ch>'9';ch=getchar()) ;
		if(!flg) b[0]=0;
		int flg1=0,zz=0,nm=0,nm1=0;
		for(;ch>='0'&&ch<='9';ch=getchar()) {
			int pos=ch-'0';
			if(!flg1&&!pos) return printf("0\n"),0;
			if(!pos) nm++;
			if(pos==1) nm1++;
			if(!flg) b[++b[0]]=pos;
			if(pos>1||nm1>1) zz=1;
			flg1=1; 
		} 
		if(zz) flg=1;
		else res+=nm;
	}
	if(flg) {
		fr(i,1,b[0]) printf("%d",b[i]);
	} else printf("1");
	fr(i,1,res) printf("0");
	return 0;
}
