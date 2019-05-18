#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#include<cmath>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=16;
int c[N],d[N],q[N],a[N],b[N][N];
int cnt=0,res=0;

void js(){
	int x;cin>>x;
	q[++res]=x;
	fr(i,1,6) fr(j,i+1,6){
		if(b[i][j]==x){
		//	printf("xx%d %d\n",i,j);
			c[++cnt]=i,c[++cnt]=j;
			break;
		}
	}
}

int main(){
	a[1]=4,a[2]=8,a[3]=15,a[4]=16,a[5]=23,a[6]=42;
	fr(i,1,6) fr(j,1,6) b[i][j]=a[i]*a[j];
	printf("? 1 3\n"),fflush(stdout);
	js();
	printf("? 3 5\n"),fflush(stdout);
	js();
	sort(c+1,c+1+4);
	fr(i,2,4){
		if(c[i]==c[i-1]){
			d[3]=a[c[i]];
			break;
		}
	}
	d[1]=q[1]/d[3],d[5]=q[2]/d[3];
	res=cnt=0;
	printf("? 2 4\n"),fflush(stdout);
	js();
	printf("? 4 6\n"),fflush(stdout);
	js();
	sort(c+1,c+1+4);
	fr(i,2,4){
		if(c[i]==c[i-1]){
			d[4]=a[c[i]];
			break;
		}
	}
	d[2]=q[1]/d[4],d[6]=q[2]/d[4];
	printf("! %d %d %d %d %d %d\n",d[1],d[2],d[3],d[4],d[5],d[6]),fflush(stdout);
	return 0;
}