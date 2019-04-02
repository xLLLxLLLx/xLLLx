#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=110;
struct data{
	int b,nm;
}q[N];
char lx[N];

bool pd(char ch){
	return ch=='>';
}

int main(){
	int T,n;scanf("%d",&T);
	fr(o,1,T){
		scanf("%d",&n);
		scanf("%s",lx+1);
		int lt=1,res=0;
		fr(i,2,n){
			if(lx[i]!=lx[i-1]){
				q[++res].b=pd(lx[i-1]),q[res].nm=i-lt;
				lt=i;
			}
		}
		q[++res].b=pd(lx[n]),q[res].nm=n+1-lt;
		if(q[1].b||!q[res].b||n==1) printf("0\n");
		else if(res==1) printf("%d\n",q[1].nm-1);
		else {
			int gg=min(q[1].nm,q[res].nm);
			printf("%d\n",gg);
		}
	}
	return 0;
}