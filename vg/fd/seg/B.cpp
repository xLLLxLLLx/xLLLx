#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define lson x<<1
#define rson x<<1|1
#define LL long long
using namespace std;
const int N=35010;
int n,k;
int a[N];
vector<int>qx[N];
LL v[N<<2];

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void change(int x,int l,int r,int L,int R,int k){
	
}

int main(){
	read(n),read(k);
	fr(i,1,n) read(a[i]),qx[a[i]].push_back(a[i]),all[i]=a[i];
	sort(all+1,all+1+n);
	int m=unique(all+1,all+1+n)-all-1;
	fr(o,1,k){
		fr(i,1,m){
			int len=qx[all[i]].size();
			fr(j,0,len-1){
				change(qx[all[i]][j])
			}
		}
	}
	printf("%lld\n",v[1]);
	return 0;
}
