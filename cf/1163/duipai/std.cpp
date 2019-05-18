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
const int N=1e5+10;
int a[N],nm[20];
multiset<int>q;

int main(){
	int n;cin>>n;
	fr(i,1,n) scanf("%d",&a[i]);
	int maxn=1;
	fr(j,1,n){
		nm[a[j]]++;
		fr(i,1,10){
			if(!nm[i]) continue;
			nm[i]--;
			int flg=1,p1=-1;
			fr(k,1,10){
				if(!nm[k]) continue;
				if(p1==-1) p1=nm[k];
				else if(p1!=nm[k]) {flg=0;break;}
			}
			nm[i]++;
			if(flg) maxn=j;
		}
	}
	printf("%d\n",maxn);
	return 0;
}