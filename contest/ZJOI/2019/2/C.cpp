struct num{
    ll a,b,c;
    num(){a=b=0,c=1;}
    num(register ll x,register ll y)
    {
        if(y<0) 
            x=-x,y=-y;
        a=x/y;
        b=x%y;
        c=y;
        if(b<0)
            b+=c,--a;
    }
    inline ll floor(){return a;}
    inline ll ceil(){return a+(b>0);}
    inline bool operator<(const num &x)const{return a==x.a?b*x.c<x.b*c:a<x.a;}
    inline bool operator<=(const num &x)const{return a==x.a?b*x.c<=x.b*c:a<x.a;}
}p[N];
int n,m,id[N],s[N],top,tot,ans[N];
ll a[N],b[N];
pair<ll,int> S[N<<1];
inline num cross(register int x,register int y)
{
    return num(b[y]-b[x],a[x]-a[y]);
}
inline void work(register int k)
{
    p[top=tot=0]=num(0,1);
    for(register int i=1;i<=n;++i)
        if(ans[id[i]]==-1&&a[id[i]]>a[s[top]])
        {
            while(top&&cross(id[i],s[top]).floor()<p[top].ceil())
                --top;
            s[++top]=id[i];
            if(top>1)
                p[top]=cross(s[top-1],id[i]);
        }
    p[top+1]=num(1ll<<60,1);
    for(register int i=1;i<=n;++i)
        if(ans[i]>0)
        {
            int l=1,r=top-1,res=top;
            while(l<=r)
            {
                int mid=l+r>>1;
                if(a[s[mid]]>=a[i]||cross(s[mid],i)<=p[mid+1])
                    res=mid,r=mid-1;
                else
                    l=mid+1;
            }
            S[++tot]=make_pair(a[s[res]]>=a[i]?0ll:cross(s[res],i).floor()+1,1);
            l=2,r=top,res=1;
            while(l<=r)
            {
                int mid=l+r>>1;
                if(a[s[mid]]<=a[i]||p[mid]<=cross(s[mid],i))
                    res=mid,l=mid+1;
                else
                    r=mid-1;
            }
            if(a[s[res]]>a[i])
                S[++tot]=make_pair(cross(s[res],i).ceil(),-1);
        }
    sort(S+1,S+1+tot);
    for(register int i=1,j=1,x=0;i<=top;++i)
    {
        while(j<=tot&&S[j].first<=p[i].ceil())
            x+=S[j++].second;
        if(x<k)
            ans[s[i]]=k;
        while(j<=tot&&S[j].first<=p[i+1].floor())
        {
            int l=j;
            while(l<=tot&&S[l].first==S[j].first)
                x+=S[l++].second;
            if(x<k)
                ans[s[i]]=k;
            j=l;
        }
    }
}
inline bool cmp(register int x,register int y) {
    return a[x]<a[y]||a[x]==a[y]&&b[x]>b[y];
}
int main() {
    n=read(),m=read();
    for(register int i=1;i<=n;++i)
        a[i]=read(),b[i]=read(),id[i]=i,ans[i]=-1;
    sort(id+1,id+1+n,cmp);
    for(register int i=1;i<=m;++i)
        work(i);
    for(register int i=1;i<=n;++i)
        write(ans[i]),putchar(' ');
    return 0;
}