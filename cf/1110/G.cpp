#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i<=y;++i)
#define ll long long
#define wh printf("White\n")
#define dr printf("Draw\n")
using namespace std;
const int N=5e5+10;
struct data{
	int nt,to;
}a[N<<4];
char lx[N];
int head[N<<2],d[N<<2],cnt=0,sz=0;

void add(int x,int y){
	d[x]++,d[y]++;
	a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
	a[++cnt].to=x,a[cnt].nt=head[y],head[y]=cnt;
}

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void init(){
	fr(i,1,sz) head[i]=d[i]=0;
	cnt=sz=0;
}

int main(){
	int T;read(T);
	fr(o,1,T){
		int n;read(n);
		for(int i=1,x,y;i<n;++i){
			read(x),read(y);
			add(x,y);
		}
		sz=n;
		scanf("%s",lx+1);
		fr(i,1,n) if(lx[i]=='W') add(i,++sz),add(sz,sz+1),add(sz,sz+2),sz+=2;
		int flg=0,tmp=0;
		fr(i,1,sz) {
			int res=0;
			for(int j=head[i];j;j=a[j].nt){
				if(d[a[j].to]>=2) res++;
			}
			tmp+=(d[i]>=3);
			if(d[i]>=4||(d[i]>=3&&res>=2)) flg=1;
		}
		if(flg) wh;
		else if(!tmp) dr;
		else if(tmp==1) dr;
		else {
			if(sz&1) wh;
			else dr;
		}
		init();
	}
	return 0;
}