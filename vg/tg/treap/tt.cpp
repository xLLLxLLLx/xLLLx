#include<bits/stdc++.h>
#define MAXN 5000010
using namespace std;
const int inf=0x3f3f3f3f;
int k,sum1,val;
char ch[10];
int n,m,rt,cnt;
int a[MAXN],num[MAXN],fa[MAXN],f[MAXN][2];
int sum[MAXN],size[MAXN],v[MAXN],mx[MAXN],l[MAXN],r[MAXN];
bool tf[MAXN],pf[MAXN];
queue<int> q;
// inline int read() {
//     char ch;
//     bool f=false;
//     int res=0;
//     while (((ch=getchar())<'0'||ch>'9')&&ch!='-');
//     if (ch=='-')
//         f=true;
//     else 
//         res=ch-'0';
//     while ((ch=getchar())>='0'&&ch<='9')
//         res=(res<<3)+(res<<1)+ch-'0';
//     return f?~res+1:res;
// }
inline void update(int x){
    sum[x]=sum[f[x][0]]+sum[f[x][1]]+v[x];
    size[x]=size[f[x][0]]+size[f[x][1]]+1;
    mx[x]=max(mx[f[x][0]],max(mx[f[x][1]],r[f[x][0]]+v[x]+l[f[x][1]]));
    l[x]=max(l[f[x][0]],sum[f[x][0]]+v[x]+l[f[x][1]]);
    r[x]=max(l[f[x][1]],sum[f[x][1]]+v[x]+r[f[x][0]]);
} 
inline void s1(int t,int w,int x){
    tf[t]=1,v[t]=v[x],sum[t]=v[x]*size[t];
}
inline void s2(int t){
    l[t]=r[t]=mx[t]=sum[t];
}
inline void s3(int t,int x){
    l[t]=r[t]=0,mx[t]=v[x];
}
inline void s4(int x){
    int t=f[x][0],w=f[x][1];
    if (tf[x]){
        pf[x]=tf[x]=0;
        if (t) s1(t,w,x);
        if (w) s1(w,t,x);
        /*if (v[x]>=0&&t) s2(t);
        if (v[x]>=0&&w) s2(w);
        if (v[x]<0&&t) s3(t,x);
        if (v[x]<0&&w) s3(w,x); */
        if (v[x]>=0){
            if(t)
                s2(t);
            if (w)
                s2(w);
        }
        else {
            if (t)
                s3(t,x);
            if (w)
                s3(w,x);
        }
    }
    if(pf[x]){
        pf[x]=0;
        pf[t]^=1;
        pf[w]^=1;
        swap(l[t],r[t]);
        swap(l[w],r[w]);
        swap(f[t][0],f[t][1]);
        swap(f[w][0],f[w][1]);
    }
}
inline void rotate(int x,int &k){
    int y=fa[x],z=fa[y],t,w;
    /*if (f[y][1]==x)
        t=1;
    else 
        t=0;
    w=t^1;
    k=(y==k)?x:k;
    if (y!=k)
        //f[z][1]=y,f[z][y]=x;
        f[z][f[z][1]==y]=x;*/
    t=(f[y][1]==x);
    w=t^1;
    if (y==k)
        k=x;
    else 
        f[z][f[z][1]==y]=x;
    fa[f[x][w]]=y,fa[y]=x,fa[x]=z;
    f[y][t]=f[x][w];
    f[x][w]=y;
    update(y);
    update(x);
}
inline void splay(int x,int &k){
    while (x!=k){
        int y=fa[x],z=fa[y];
        if (y!=k){
            //rotate(((f[y][0]==x^f[z][0]==y)?x:y),k);
            if (f[z][0]==y^f[y][0]==x)rotate(x,k);
                else rotate(y,k);
        }
        rotate(x,k);
    }
    if(k==rt){
        rt=x;
    }
}
inline int find (int x,int rk){
    s4(x);
    int t=f[x][0],w=f[x][1];
    if (size[t]+1==rk)
        return x;
    if (size[t]>=rk)
        return find(t,rk);
    else 
        return find(w,rk-size[t]-1);
}
inline void clean(int x){
    q.push(x);
    fa[x]=f[x][0]=f[x][1]=0;
    tf[x]=pf[x]=0; 
}
inline void rec(int x){
    /*if (!x)
        return;
    int t=f[x][0],w=f[x][1];
    rec(t);
    rec(w);
    //clean(x);*/
    int &t=f[x][0],&w=f[x][1];
    if (t)
        rec(t);
    if (w)
        rec(w);
    q.push(x);
    fa[x]=t=w=tf[x]=pf[x]=0;
}
inline int split(int t,int sum1){
    int x=find(rt,t),y=find(rt,t+sum1+1);
    splay(x,rt);
    splay(y,f[x][1]);
    return f[y][0];
}
inline void query(int k,int sum1){
    int x=split(k,sum1);
    printf("%d\n",sum[x]);
}
inline void modify(int k,int sum1,int val){
    int x=split(k,sum1),y=fa[x];
    v[x]=val,tf[x]=1,sum[x]=size[x]*val;
    /*l[x]=r[x]=((val>=0)?sum[x]:0);
    mx[x]=((val>=0)?sum[x]:val);*/
    if (val>=0)
        l[x]=r[x]=mx[x]=sum[x];
    else l[x]=r[x]=0,mx[x]=val;
    update(y);
    update(fa[y]);
}
inline void pfer(int k,int sum1){
    int x=split(k,sum1),y=fa[x];
    if (!tf[x]){
        pf[x]^=1;
        swap(f[x][0],f[x][1]);
        swap(l[x],r[x]);
        update(y);
        update(fa[y]);
    }
}
inline void erase(int k,int sum1){
    int x=split(k,sum1),y=fa[x];
    rec(x);
    f[y][0]=0;
    update(y);
    update(fa[y]);
}
inline void build(int t,int w,int k){
    int mid=(t+w)>>1;
    int now=num[mid],last=num[k];
    if (t==w){
        mx[now]=sum[now]=a[t];
        tf[now]=pf[now]=0;
        l[now]=r[now]=max(a[t],0);
        size[now]=1;
    }
    if (t<mid)build(t,mid-1,mid);
    if (mid<w)build(mid+1,w,mid);
    v[now]=a[mid];
    fa[now]=last;
    //printf("error: %d\n",now);
    update(now);
    f[last][mid>=k]=now;
}
inline void insert(int k,int sum1){
    for (int i=1;i<=sum1;++i)
        //a[i]=read();
        scanf("%d",&a[i]);
    for (int i=1;i<=sum1;++i)
        if (!q.empty())
            num[i]=q.front(),q.pop();
        else 
            num[i]=++cnt;
    build(1,sum1,0);
    int z=num[(1+sum1)>>1],x=find(rt,k+1),y=find(rt,k+2);
    splay(x,rt);
    splay(y,f[x][1]);
    fa[z]=y;
    f[y][0]=z;
    update(y);
    update(x);
}
void liblibal(int x){
    if(!x)return;
    s4(x);
    liblibal(f[x][0]);
    printf("%d ",a[x]);
    liblibal(f[x][1]);
}
int main(){
    //freopen("","r",stdin);
    //freopen("","w",stdout);
    /*n=read(),m=read(),*/scanf("%d%d",&n,&m);
    mx[0]=a[1]=a[n+2]=-inf,rt=(n+3)>>1,cnt=n+2;
    for (int i=1;i<=n;++i)
        scanf("%d",&a[i+1]);
        //a[i+1]=read();
    for (int i=1;i<=n+2;++i)
        num[i]=i;
    build(1,n+2,0);
    while(m--){
        scanf("%s",ch);
        if(ch[0]!='M'||ch[2]!='X')
            /*k=read()*/scanf("%d%d",&k,&sum1)/*,sum1=read()*/;
        if(ch[0]=='I')
            insert(k,sum1);
        if(ch[0]=='D')
            erase(k,sum1);
        if(ch[0]=='M'){
            if(ch[2]=='X')
                printf("%d\n",mx[rt]);
            else {
                /*val=read()*/scanf("%d",&val);
                modify(k,sum1,val);
            }
        }
        if(ch[0]=='R')
            pfer(k,sum1);
        if(ch[0]=='G')
            query(k,sum1);
        //liblibal(rt);
    }
    return 0;
} 
