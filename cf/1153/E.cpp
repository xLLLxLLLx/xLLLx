#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=2010;
int w[N],n,res=0,tmp=0,co[N],ro[N];

int Ask(int x1,int y1,int x2,int y2){
    printf("? %d %d %d %d\n",x1,y1,x2,y2);
    fflush(stdout);
    int x;scanf("%d",&x);
    return x;
}

int main(){
    scanf("%d",&n);
    fr(i,1,n-1){
        w[i]=Ask(1,1,n,i);
        if((w[i]^w[i-1])&1) co[res++]=i;
    }
    if((w[n]^w[n-1])&1) co[res++]=n;
    fr(i,1,n-1){
        w[i]=Ask(1,1,i,n);
        if((w[i]^w[i-1])&1) ro[tmp++]=i;
    }
    if((w[n]^w[n-1])&1) ro[tmp++]=n;
    if(res>=2&&tmp>=2){
    		int pos=0;
        fr(i,0,1) fr(j,0,1){
            if(Ask(ro[i],co[j],ro[i],co[j])==1) w[++pos]=ro[i],w[++pos]=co[j];
        }
        printf("!");
        fr(i,1,4) printf(" %d",w[i]);
        fflush(stdout);
    } else if(res>=2){
        int l=1,r=n,ans=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if(Ask(1,co[0],mid,co[0])&1) ans=mid,r=mid-1;
            else l=mid+1;
        }
        printf("! %d %d %d %d\n",ans,co[0],ans,co[1]);
        fflush(stdout);
    } else if(tmp>=2){
        int l=1,r=n,ans=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if(Ask(ro[0],1,ro[0],mid)&1) ans=mid,r=mid-1;
            else l=mid+1;
        }
        printf("! %d %d %d %d\n",ro[0],ans,ro[1],ans);
        fflush(stdout);
    } 
    return 0;
}