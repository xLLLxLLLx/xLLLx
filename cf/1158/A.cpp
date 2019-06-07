#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=100002;
int n,m,a[N],b[N],s[N];

void read(int &x){ scanf("%d",&x); }

int main(){
	read(n);read(m);
	ll sum=0;
	int mx=0,mn=1e9;
	fr(i,1,n) read(a[i]),mx=max(mx,a[i]),sum+=a[i];
	sort(a+1,a+1+n);
	fr(i,1,m) read(b[i]),mn=min(mn,b[i]);
	sort(b+1,b+1+m);
	if (mx>mn) return printf("-1\n"),0;
	ll ans=sum*m;
	if (233){
		int s1=0,s2=0;
		//rf(i,n,1) if (a[i]==a[n]) s1++;else break;
		//fr(i,1,m) if (b[i]==b[1]) s2++;else break;
		int w=n;
		fr(i,1,m){
			if (b[i]>a[w]){
				s[w]++;
				ans+=b[i]-a[w];
				if (s[w]==m-1) w--;
			}
		}
		cout<<ans<<endl;
	}
	//cout<<ans<<endl;
	return 0;
}