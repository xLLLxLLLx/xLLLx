#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
#include<cstring>
#include<set>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=1e3+10;
struct node{
	int x,y;
}a[N];
struct data{
	int x,y,z;
}b[N*N],c[N*N];

int gcd(int A,int B){
	return B ? gcd(B,A%B) : A;
}

bool check(data A,data B){
	if(A.x!=B.x) return false;
	else if(A.y!=B.y) return false;
	else return true;
}

bool cmp(data A,data B){
	if(A.x!=B.x) return A.x<B.x;
	if(A.y!=B.y) return A.y<B.y;
	return A.z<B.z;
}

bool pd(data A,data B){
	if(A.x!=B.x) return false;
	else if(A.y!=B.y) return false;
	else if(A.z!=B.z) return false;
	return true;
}

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) {
		scanf("%d%d",&a[i].x,&a[i].y);
	}
	int res=0;
	fr(i,1,n) fr(j,i+1,n) {
		int k1=a[i].x-a[j].x,k2=a[i].y-a[j].y,k3=a[i].x*a[j].y-a[i].y*a[j].x;
		if(k1<0) {
			k1=-k1,k2=-k2,k3=-k3;
		} else if(k1==0&&k2<0) {
			k1=-k1,k2=-k2,k3=-k3;
		}
		int pos=gcd(gcd(k1,k2),k3);
		pos=abs(pos);
		k1/=pos,k2/=pos,k3/=pos;
		b[++res].x=k1,b[res].y=k2,b[res].z=k3;
	}
	sort(b+1,b+1+res,cmp);
	ll ans=0;
	int tot=0;
	c[++tot]=b[1];
	fr(i,2,res) {
		if(!pd(b[i],b[i-1])) c[++tot]=b[i];
	}
	int lt=1;
	// fr(i,1,tot) {
	// 	printf("%d %d %d\n",c[i].x,c[i].y,c[i].z);
	// }
	fr(i,2,tot+1) {
		if(!check(c[i],c[i-1])) {
			int pos=i-lt;
			ans+=(tot-pos)*pos;
			lt=i;
		}
	}
	// ans+=tot*(tot-lt+1);
	printf("%lld\n",ans/2);
	return 0;
}