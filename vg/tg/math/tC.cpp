void exgcd(int a,int b,int &x,int &y)
{
    if(b==0){ x=1; y=0; return;}
    exgcd(b,a%b,x,y);
    int tp=x;
    x=y; y=tp-a/b*y;
}

int china()
{
    int ans=0,lcm=1,x,y;
    for(int i=1;i<=k;++i) lcm*=b[i];
    for(int i=1;i<=k;++i)
    {
        int tp=lcm/b[i];
        exgcd(tp,b[i],x,y);
        x=(x%b[i]+b[i])%b[i];
        ans=(ans+tp*x*a[i])%lcm;
    }
    return (ans+lcm)%lcm;
}
