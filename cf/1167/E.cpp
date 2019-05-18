#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#include<cmath>
#include<set>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=1e6+10;
set<int>q;
set<int> :: iterator L,R;
int a[N],tot=0,num=0;
vector<int>g[N];

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

int js(int pos,int v){
	int cnt=0,flg=1;
	if(!q.size()) return 0;
	R=q.upper_bound(pos),L=q.lower_bound(pos);
	if(L==q.begin()) flg=0;
	else L--;
	if(flg&&R!=q.end()) cnt-=(a[*L]<=a[*R]);
	if(flg) {
		if(a[*L]<=v) cnt++;
	}
	if(R!=q.end()) {
		if(v<=a[*R]) cnt++;
	}
	return cnt;
}

inline void put(int x){
	int len=g[x].size();
	for (int i = 0; i < len; i++) {
		int pos=g[x][i];
		num++;
		tot+=js(pos,x);
		q.insert(pos);
	}
}

inline void cut(int x){	
	int len=g[x].size();
	for (int i = 0; i < len; i++) {
		q.erase(g[x][i]);
		tot-=js(g[x][i],x);
		num--;
	}
}

inline bool check(){
	return tot==num-1;
}

int main(){
	int n,x;
	read(n);read(x);
	fr(i,1,n) {
		scanf("%d", &a[i]);
		//read(a[i]);
		g[a[i]].push_back(i);
	}
	ll ans=0;
	for (int i = 1; i <= n; i++) {
		q.insert(i),num++;
		if(i<n) {
			tot+=(a[i]<=a[i+1]);
		}
	}
	int r=0;
	for(int i = 1; i <= x; i++) {
		if(r<i) cut(i),r=i;
		if(!check()) {
			for(int j=r+1;j<=x+1;++j){
				if(j==x+1) {
					r=x+1;
					break;
				}
				cut(j);
				if(check()) {
					r=j;
					break;
				}
			}
		}
		ans+=x-r+1;
		put(i);
	}
	printf("%lld\n",ans);
	return 0;
}