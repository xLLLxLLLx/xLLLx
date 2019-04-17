#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=5210;
int n;
char lx[N];
int a[N][N],c[10],qz[N][N];

void cal(int x,int b,int pos){
  int zz=0;memset(c,0,sizeof c);
  for(;pos;pos>>=1) c[++zz]=pos%2;
  reverse(c+1,c+1+4);
  fr(i,1,4) a[x][b+i-1]=c[i];
}

int Get(int x1,int x2,int y1,int y2){
  return qz[x2][y2]-qz[x1-1][y2]-qz[x2][y1-1]+qz[x1-1][y1-1];
}

bool check(int x){
  fr(i,1,n/x) fr(j,1,n/x){
    int xl=(i-1)*x+1,xr=i*x;
    int yl=(j-1)*x+1,yr=j*x;
    int pos=Get(xl,xr,yl,yr);
    if(pos&&pos!=x*x) return false;
  }
  return true;
}

int main(){
  scanf("%d",&n);
  fr(o,1,n){
    scanf("%s",lx+1);
    fr(i,1,n/4) {
      int pos;
      if(lx[i]>='0'&&lx[i]<='9') pos=lx[i]-'0';
      else pos=lx[i]-'A'+10;
      cal(o,(i-1)*4+1,pos);
    }
  }
  /*fr(i,1,n){
    fr(j,1,n) printf("%d",a[i][j]);
    puts("");
  }*/
  fr(i,1,n) fr(j,1,n) qz[i][j]=qz[i][j-1]+qz[i-1][j]-qz[i-1][j-1]+a[i][j];
  //fr(i,1,n) fr(j,1,n) printf("qz[%d][%d]=%d\n",i,j,qz[i][j]);
  int maxn=0,len=sqrt(n);
  fr(i,1,len){
    if(n%i) continue;
    if(check(i)) maxn=max(maxn,i);
    if(check(n/i)) maxn=max(maxn,n/i);
  }
  cout<<maxn<<endl;
  return 0;
}