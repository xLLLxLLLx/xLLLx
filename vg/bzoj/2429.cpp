#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e3+10;
struct node{
	int x,y;
}b[N];
struct data{
	int nt,to,w;
}a[N*N];
int s[N],f[N];

void read(int &x){
	char ch=getchar();x=0;bool q=0;
	for(;ch<'0'||ch>'9';ch=getchar()) q|=(ch=='-');
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
	if(q) x=-x;
}

bool cmp(data xx,data yy){
	return xx.w<yy.w;
}

int find(int k){
	return f[k]==k ? k : f[k]=find(f[k]);
}

int pf(int x){ return x*x; }

int dis(int x,int y){
	return pf(b[x].x-b[y].x)+pf(b[x].y-b[y].y);
}

int main(){
	int n,m;
	read(m);
	fr(i,1,m) read(s[i]);
	int res=0;
	read(n);
	fr(i,1,n) read(b[i].x),read(b[i].y);
	fr(i,1,n) fr(j,i+1,n){
		a[++res].nt=i,a[res].to=j,a[res].w=dis(i,j);
	}
	sort(a+1,a+1+res,cmp);
	int pos=0,cnt=0;
	fr(i,1,n) f[i]=i;
	fr(i,1,res){
		int fx=find(a[i].nt),fy=find(a[i].to);
	//	printf("%d %d %d %d\n",a[i].nt,fx,a[i].to,fy);
		if(fx==fy) continue;
	//	printf("xxx%d %d %d\n",a[i].nt,a[i].to,a[i].w);
		cnt++;
		pos=a[i].w;
		f[fx]=fy;
		//if(cnt==n-1) break;
	}
	int ans=0;
	fr(i,1,m) if(pf(s[i])>=pos) ans++;
	printf("%d\n",ans);
	return 0;
}