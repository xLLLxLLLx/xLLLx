#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#include<vector>
#include<cmath>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=2e5+10;
int a[N],st[N],be[N],ed[N],mk[N];

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) scanf("%d",&a[i]);
	int head=1,tail=0;
	fr(i,1,n){
		while(tail>=head&&a[st[tail]]<a[i]) tail--;
		if(tail>=head) be[i]=st[tail]+1;
		else be[i]=1;
		st[++tail]=i;
	}
	head=1,tail=0;
	rf(i,n,1){
		while(tail>=head&&a[st[tail]]<a[i]) tail--;
		if(tail>=head) ed[i]=st[tail]-1;
		else ed[i]=n;
		st[++tail]=i;
	}
	//fr(i,1,n) printf("%d %d\n",be[i],ed[i]);
	int ans=0;
	fr(i,1,n) mk[a[i]]=i;
	fr(i,1,n){
		int l=(i-be[i]),r=(ed[i]-i);
		if(l>=r){
			fr(j,i+1,ed[i]){
				if(a[i]!=a[j]*2&&mk[a[i]-a[j]]>=be[i]&&mk[a[i]-a[j]]<i) ans++;
			}
		} else {
			fr(j,be[i],i-1){
				if(a[i]!=a[j]*2&&mk[a[i]-a[j]]>i&&mk[a[i]-a[j]]<=ed[i]) ans++;
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}