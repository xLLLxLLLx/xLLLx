#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e4+10;
int a[N];

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) scanf("%d",&a[i]);
	int ans=0,pos=0;
	fr(i,1,n){
		ans++;
		if(a[i]>pos){
			pos=a[i];
			fr(j,i,pos) pos=max(pos,a[j]);
			i=pos;
		}
	}
	cout<<ans<<endl;
	return 0;
}