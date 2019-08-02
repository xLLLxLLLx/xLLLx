#include<cstdio>
#include<cstdlib>
#include<algorithm>
#define read(x) scanf("%d",&(x))
using namespace std;
typedef long long ll;

const int N=21;
int n,m,t,lv[N],rv[N];
int lw[1<<N],rw[1<<N];
int lf[1<<N],rf[1<<N];

int cnt[1<<N];
int x[1<<N],y[1<<N],totx,toty;

int main(){
  char s[N];
  read(n); read(m);
  for (int i=0;i<n;i++){
    while (getchar()!='\n');
    scanf("%s",s);
    for (int j=0;j<m;j++) if (s[j]=='1') lw[1<<i]|=1<<j,rw[1<<j]|=1<<i;
  }
  for (int i=0;i<n;i++) read(lv[i]);
  for (int j=0;j<m;j++) read(rv[j]);
  read(t);
  for (int i=1;i<max(1<<n,1<<m);i++) cnt[i]=cnt[i>>1]+(i&1);

  for (int s=0;s<(1<<n);s++){
    lf[s]=1; int sum=0;
    for (int i=0;i<n;i++)
      if (s>>i&1)
    lf[s]&=lf[s^(1<<i)],lw[s]|=lw[s^(1<<i)],sum+=lv[i];
    if (lf[s]&=cnt[s]<=cnt[lw[s]]) x[++totx]=sum;
  }
  for (int s=0;s<(1<<m);s++){
    rf[s]=1; int sum=0;
    for (int j=0;j<m;j++)
      if (s>>j&1)
    rf[s]&=rf[s^(1<<j)],rw[s]|=rw[s^(1<<j)],sum+=rv[j];
    if (rf[s]&=cnt[s]<=cnt[rw[s]]) y[++toty]=sum;
  }
  // for(int i = 1; i <= totx; ++i) {
  //   printf("x[%d]=%d\n", i, x[i]);
  // }
  sort(x+1,x+totx+1);
  ll ans=0;
  for (int i=1;i<=toty;i++)
    ans+=totx-(lower_bound(x+1,x+totx+1,t-y[i])-x)+1;
  printf("%lld\n",ans);
  return 0;
}