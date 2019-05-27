#include<algorithm>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<iostream>
#include<complex>
#define ll long long
#define N 150005
typedef std::complex<double> cd;
int mark[200005],p[200005];
int son[200005],F[200005],first[200005],next[200005],tot,go[200005];
int lc,n,sum,dis[200005],root,vis[200005],mxdis;
ll a[200005],b[200005],c[200005],A[200005],B[200005];
ll ans1=0,ans2=0;
int read(){
    char ch=getchar();int t=0,f=1;
    while (ch<'0'||ch>'9'){
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while ('0'<=ch&&ch<='9'){
        t=t*10+ch-'0';
        ch=getchar();
    }
    return t*f;
}
int bitrev(int t,int n){
    int res=0;
    for (int i=0;i<n;i++) res|=((t>>(n-i-1))&1)<<i;//括号要多加 
    return res;
}
void fft(cd *a,int n,int rev){
    int len=1<<n;
    static cd y[N];double Pi=acos(-1);
    for (int i=0;i<len;i++) y[i]=a[bitrev(i,n)];
    for (int d=1;d<len;d<<=1){
        cd wn(exp(cd(0,Pi*rev/d)));
        for (int k=0;k<len;k+=2*d){
            cd w(1,0);
            for (int i=k;i<k+d;i++,w*=wn){
                cd u=y[i],v=w*y[i+d];
                y[i]=u+v;
                y[i+d]=u-v;
            }
        }
    }
    if (rev==-1)
    for (int i=0;i<len;i++) y[i]/=len;
    for (int i=0;i<len;i++) a[i]=y[i];
}
void mul(ll *a,int la,ll *b,int lb,ll *c,int &lc){
    int len=1,n=0;
    static cd t1[N],t2[N];
    for (;len<la*2||len<lb*2;len<<=1,n++);
    for (int i=0;i<la;i++) t1[i]=cd(a[i],0);
    for (int i=0;i<lb;i++) t2[i]=cd(b[i],0);
    for (int i=la;i<len;i++) t1[i]=cd(0,0);
    for (int i=lb;i<len;i++) t2[i]=cd(0,0);
    fft(t1,n,1);fft(t2,n,1);
    for (int i=0;i<len;i++) t1[i]*=t2[i];
    fft(t1,n,-1);
    for (int i=0;i<len;i++) c[i]=(ll)(t1[i].real()+0.5);
    lc=len;
}
void insert(int x,int y){
    tot++;
    go[tot]=y;
    next[tot]=first[x];
    first[x]=tot;
}
void add(int x,int y){
    insert(x,y);
    insert(y,x);
}
void prework(){
    mark[0]=mark[1]=1;
    for (int i=2;i<=50000;i++){
        if (!mark[i]){
            p[++p[0]]=i;
        }
        for (int j=1;j<=p[0]&&p[j]*i<=50000;j++){
            mark[p[j]*i]=1;
            if (i%p[j]==0) break;
        }
    }
}
void findroot(int x,int fa){
    son[x]=1;
    F[x]=0;
    for (int i=first[x];i;i=next[i]){
        int pur=go[i];
        if (vis[pur]||pur==fa) continue;
        findroot(pur,x);
        son[x]+=son[pur];
        F[x]=std::max(F[x],son[pur]);
    }
    F[x]=std::max(F[x],sum-son[x]);
    if (F[x]<F[root]) root=x;
}
void pre(int x,int fa){
    dis[x]=dis[fa]+1;
    mxdis=std::max(mxdis,dis[x]);
    for (int i=first[x];i;i=next[i]){
        int pur=go[i];
        if (pur==fa||vis[pur]) continue;
        pre(pur,x);
    }
}
void dfs(int x,int fa){
    b[dis[x]]++;
    for (int i=first[x];i;i=next[i]){
        int pur=go[i];
        if (pur==fa||vis[pur]) continue;
        dis[pur]=dis[x]+1;
        dfs(pur,x);
    }
}
void work(int x){
    dis[0]=-1;mxdis=0;
    int all=sum;
    pre(x,0);
    for (int i=0;i<=mxdis+1;i++) a[i]=b[i]=0; 
    a[0]=1;
    for (int i=first[x];i;i=next[i]){
        int pur=go[i];
        if (vis[pur]) continue;
        dis[pur]=1;
        for (int j=0;j<=mxdis;j++) b[j]=0;
        dfs(pur,x);
        for (int j=0;j<=mxdis;j++) A[j]=a[j],B[j]=b[j];
        mul(A,mxdis+1,B,mxdis+1,c,lc);
        int lim=std::min(mxdis*2,50000);
        for (int i=1;i<=p[0]&&p[i]<=lim;i++){
          ans1+=c[p[i]];
        }
        for (int i=0;i<=mxdis;i++)
         a[i]+=b[i];
    }
    vis[x]=1;
    for (int i=first[x];i;i=next[i]){
        int pur=go[i];
        if (vis[pur]) continue;
        if (son[pur]>son[x]) sum=all-son[x];
        else sum=son[pur];
        root=0;
        findroot(pur,x);
        work(root);
    }
}
int main(){
    prework();
    while (scanf("%d",&n)!=EOF){
     if (n==0) break;
     tot=0;
     for (int i=1;i<=n;i++) first[i]=vis[i]=0;    
     for (int i=1;i<n;i++){
        int x,y;
        x=read();y=read();
        add(x,y);
     }
     root=0;sum=n;
     F[0]=99999999;
     ans1=ans2=0;
     findroot(1,0);
     work(root);
     ans2=(ll)(((ll)n)*((ll)(n-1))/2);
     double tmp=((double)(ans1))/((double)(ans2));
     printf("%.10lf\n",tmp);
    }
}