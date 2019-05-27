#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=1e5+10,mod=(1<<30);
struct data{
	int a[2];
	ll dp,cnt;
	void clear(){
		dp=cnt=0;
		a[0]=a[1]=0;
	}
}s[N];
struct node{
	int a[3];
}w[N];
int mx[N],ch[N][2],up[N][2],down[N][2],pd;
ll nm[N];

#define ls ch[x][0]
#define rs ch[x][1]

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void Min(int &x,int y){
	x=min(x,y);
}

void Max(int &x,int y){
	x=max(x,y);
}

bool cmp(data A,data B){
	return A.a[pd]<B.a[pd] || (A.a[pd]==B.a[pd]&&A.a[pd^1]<B.a[pd^1]);
}

bool comp(node A,node B){
	if(A.a[0]!=B.a[0]) return A.a[0]<B.a[0];
	if(A.a[1]!=B.a[1]) return A.a[1]<B.a[1];
	return A.a[2]<B.a[2];
}

void upd(int x){
	if(ls) {
		fr(i,0,1) {
			Min(down[x][i],down[ls][i]);
			Max(up[x][i],up[ls][i]);
		}
	}
	if(rs) {
		fr(i,0,1) {
			Min(down[x][i],down[rs][i]);
			Max(up[x][i],up[rs][i]);
		}
	}
}

void work(int now,int x){
	// printf("now=%d x=%d\n",now,x);
	// fr(i,0,1) {
	// 	printf("down[%d]=%d\n",i,down[x][i]);
	// 	printf("up[%d]=%d\n",i,up[x][i]);
	// }
	if(up[x][0]<=s[now].a[0]&&up[x][1]<=s[now].a[1]) {
		// printf("WAI!!!\n");
		if(mx[now]<mx[x]) mx[now]=mx[x],nm[now]=nm[x];
		else if(mx[now]==mx[x]) nm[now]+=nm[x],nm[now]%=mod;
		return ;
	}
	if(s[x].a[0]<=s[now].a[0]&&s[x].a[1]<=s[now].a[1]) {
		if(mx[now]<s[x].dp) mx[now]=s[x].dp,nm[now]=s[x].cnt;
		else if(mx[now]==s[x].dp) nm[now]+=s[x].cnt,nm[now]%=mod;
	}
	int tmp=ls ? mx[ls] : 0;
	int pos=rs ? mx[rs] : 0;
	if(down[ls][0]>s[now].a[0]||down[ls][1]>s[now].a[1]) tmp=0;
	if(down[rs][0]>s[now].a[0]||down[rs][1]>s[now].a[1]) pos=0;
	if(mx[now]<=pos) work(now,rs);
	if(mx[now]<=tmp) work(now,ls);
}

void insert(int now,int x,int pos){
	if(s[now].a[pos]<s[x].a[pos]) {
		if(ls) insert(now,ls,pos^1);
		else {
			ls=now;
		}
	} else {
		if(rs) insert(now,rs,pos^1);
		else {
			rs=now;
		}
	}
	// printf("now=%d x=%d",now,x);
	if(mx[x]<mx[now]) mx[x]=mx[now],nm[x]=nm[now];
	else if(mx[x]==mx[now]) nm[x]+=nm[now],nm[x]%=mod;
	upd(x);
	// fr(i,0,1) {
	// 	printf("down[%d]=%d\n",i,down[x][i]);
	// 	printf("up[%d]=%d\n",i,up[x][i]);
	// }
	// printf("%d %lld\n",mx[x],nm[x]);
	// puts("yyyyy!");
}

int main(){
	int T;read(T);
	fr(o,1,T){
		int n;read(n);
		fr(i,1,n) fr(j,0,2) {
			read(w[i].a[j]);
		}
		sort(w+1,w+1+n,comp);
		int maxn=1;
		ll cnt=1;
		int root=1;
		s[1].a[0]=w[1].a[1],s[1].a[1]=w[1].a[2];
		s[1].dp=1,s[1].cnt=1;
		mx[1]=1,nm[1]=1;
		down[1][0]=up[1][0]=w[1].a[1];
		down[1][1]=up[1][1]=w[1].a[2];
		fr(i,2,n) {
			// printf("x=%d y=%d z=%d\n",w[i].a[0],w[i].a[1],w[i].a[2]);
			fr(j,0,1) {
				s[i].a[j]=w[i].a[j+1];
				down[i][j]=up[i][j]=s[i].a[j];
			}
			mx[i]=0,nm[i]=1;
			work(i,root);
			mx[i]++;
			// printf("ff%d %lld\n",mx[i],nm[i]);
			s[i].dp=mx[i],s[i].cnt=nm[i];
			insert(i,root,0);
		}
		printf("%d %lld\n",mx[1],nm[1]);
		fr(i,1,n) {
			ch[i][0]=ch[i][1]=0;
			mx[i]=nm[i]=0;
			s[i].clear();
		}
	}
	return 0;
}