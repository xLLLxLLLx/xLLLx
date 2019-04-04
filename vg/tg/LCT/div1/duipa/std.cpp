#include<iostream>
#include<cstdio>
#define maxn 30000
using namespace std;
const int p=10007;
struct data{
    int k,b;
    data(){k=1,b=0;}
    data(int k,int b):k(k),b(b){}
    int cal(int x){return (k*x+b)%p;}
    //void print(){ printf("%d %d\n",k,b);}
};
data operator + (data a,data b){
    data ret;
    ret.k=a.k*b.k%p;
    ret.b=(a.b*b.k%p+b.b)%p;
    return ret;
}
void exgcd(int a,int b,int &x,int &y){
    if(!b) x = 1, y = 0;
    else{
        exgcd(b,a%b,y,x);
        y-=a/b*x;
    }
}
struct linkcuttree{
    int ch[maxn+10][2],fa[maxn+10],sfa[maxn+10];
    data val[maxn+10],sum[maxn+10];
    int rc(int fa,int o){return ch[fa][1]==o;}
    int top(int o){return ch[fa[o]][0]!=o&&ch[fa[o]][1]!=o;}
    void pushup(int o){sum[o]=sum[ch[o][0]]+val[o]+sum[ch[o][1]];}
    int vis[maxn+10],ins[maxn+10];
    void dfs(int u){
        ins[u]=vis[u]=1;
        int v=fa[u];
        if(ins[v]){
            fa[u]=0;
            sfa[u]=v;       
        }
        if(!vis[v])dfs(v);
        ins[u]=0;
    }
    void init(int n){
        for(int i=1;i<=n;i++){
            int k,b;
            scanf("%d%d%d",&k,&fa[i],&b);
            val[i]=sum[i]=data(k,b);
        }
        for(int i=1;i<=n;i++)if(!vis[i])dfs(i);
        //for(int i=1;i<=n;++i) printf("%d\n",sfa[i]);
    }
    void rot(int o){
        int f=fa[o],r=rc(f,o);
        if(!top(f))fa[ch[fa[f]][rc(fa[f],f)]=o]=fa[f];
        else fa[o]=fa[f];
        fa[ch[f][r]=ch[o][r^1]]=f;
        fa[ch[o][r^1]=f]=o;
        pushup(f);
        pushup(o);
    }
    void splay(int o){
        while(!top(o)){
            if(!top(fa[o])&&rc(fa[fa[o]],fa[o])==rc(fa[o],o))rot(fa[o]);
            rot(o);
        }
    }
    void access(int u){
        int v=0;
        while(u){
            splay(u);
            ch[u][1]=v;
            pushup(u);
            v=u;
            u=fa[u];
        }
    }
    int findroot(int u){
        access(u);
        splay(u);
        while(ch[u][0])u=ch[u][0];
        splay(u);
        return u;
    }
    int query(int u){
        access(u);
        splay(u);
        data v1=sum[u];
        int ro=findroot(u),f=sfa[ro];
        access(f);
        splay(f);
        data v2=sum[f];
        if(v2.k==1)return v2.b?-1:-2;
        if(v2.k==0)return v1.cal(v2.b);
        int x,y;
        exgcd(v2.k-1,p,x,y);
    //    v1.print(),v2.print();
        return v1.cal((p-x)%p*v2.b%p);
    }
    void cut(int u){
        access(u);
        splay(u);
        fa[ch[u][0]]=0;
        ch[u][0]=0;
        pushup(u);
    }
    void join(int u,int f){
        access(u);
        splay(u);
        fa[u]=f;
    }
    int oncirclr(int u,int ro){
        int f=sfa[ro];
        if(u==f)return 1;
        access(f);
        splay(f);
        splay(u);
        return !top(f);
    }
    void update(int u,int f,int k,int b){
        access(u);
        splay(u);
        val[u]=data(k,b);
        pushup(u);
        int ro=findroot(u);
        if(u==ro){
            int rf=findroot(f);
            if(rf==ro)sfa[u]=f;
            else{
                sfa[u]=0;
                join(u,f);
            }
        }else{
            if(oncirclr(u,ro)){
                cut(u);
                join(ro,sfa[ro]);
                sfa[ro]=0;
                int rf=findroot(f);
                if(rf==u)sfa[u]=f;
                else join(u,f);
            }else{
                cut(u);
                int rf=findroot(f);
                if(rf==u)sfa[u]=f;
                else join(u,f);
            }   
        }
       // for(int i=1;i<=5;++i) printf("%d\n",sfa[i]);
    }
}lct;
int main(){
    int n;
    scanf("%d",&n);
    lct.init(n);
    int q;
    scanf("%d",&q);
    char e[2];
    int x,k,b,f;
    while(q--){
        scanf("%s%d",e,&x);
        if(e[0]=='A')printf("%d\n",lct.query(x));
        else{
            scanf("%d%d%d",&k,&f,&b);
            lct.update(x,f,k,b);
        }
    }
    return 0;
}
