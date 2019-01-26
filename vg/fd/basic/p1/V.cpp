#include<iostream>
#include<cstdio>
#include<cstring>
#define fr(z,x,y) for(int z=x;z<=y;++z)
#define rf(z,x,y) for(int z=x;z>=y;--z)
#define LL long long
using namespace std;
const int N=35;
string ll;
int n,m;
int a[N][N],c[N];

int zh(char ch){
	return (ch-'A'+1);
}

void Get(int nw){
	fr(i,nw,m) cin>>ll;
}

bool check(int x,int y){
	a[y][x]=1;
	fr(k,1,n)
	 fr(i,1,n)
	  fr(j,1,n){	  	
	  	a[i][j]=a[i][j]|(a[i][k]&a[k][j]);
	  }
	fr(i,1,n) if(a[i][i]) return 1;
	return 0;
}

int main(){
	while(scanf("%d%d",&n,&m)==2&&(n||m)){
		int flg=0;memset(a,0,sizeof a);
		fr(i,1,m){
			int x,y;
			char ch;cin>>ch;
			x=zh(ch);cin>>ch;
			cin>>ch;y=zh(ch);
			if(a[x][y]||check(x,y)) {
				flg=1;Get(i+1);
				printf("Inconsistency found after %d relations.\n",i);
				break;
			}
			int ff=0;
			memset(c,0,sizeof c);
			fr(p,1,n){
			 fr(j,1,n){
			  int pos=0;
			  fr(k,1,n){
			  	if(a[j][k]) pos++;
			  }
			  if(pos==n-p) c[p]=j;
			 }
			 if(!c[p]) ff=1;
			}
			if(!ff) {
				flg=1;
				printf("Sorted sequence determined after %d relations: ",i);
				rf(j,n,1) cout<<char(c[j]+'A'-1);
				printf(".\n");
				Get(i+1);break;
			}
		}
		if(!flg) printf("Sorted sequence cannot be determined.\n");
	}
	return 0;
}
