#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=3e5+10;
struct node{
	int x,y;
}b[N];
int a[10];

void fail(){
	printf("NO\n");
	exit(0);
}

int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	fr(i,1,m) {
		scanf("%d%d",&b[i].x,&b[i].y);
	}
	a[1]=b[1].x,a[2]=b[1].y;
	int FF=0;
	fr(i,2,m) {
		int flg=0;
		fr(j,1,2) {
			if(b[i].x==a[j]) flg=1;
			if(b[i].y==a[j]) flg=1;
		}
		if(!flg) {
			a[3]=b[i].x;
			a[4]=b[i].y;
			FF=1;
			break;
		}
	}
	if(!FF) return printf("YES\n"),0;
	else {
		fr(k,1,2) fr(t,3,4) {
			int pos=a[k],tmp=a[t];
			int pd=1;
			fr(j,1,m) {
				if(b[j].x==pos||b[j].x==tmp||b[j].y==pos||b[j].y==tmp) continue;
				else {
					pd=0;break;
				}
			}
			if(pd) return printf("YES\n"),0;
		}
	}
	fail();
	return 0;
}