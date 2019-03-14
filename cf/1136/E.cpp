#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds;   
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update> 
#define ll long long int
#define ld double
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define all(a) a.begin(),a.end()
#define sz(a) (ll)(a.size())
const ll M=1e5+5;
ll a[M],k[M],s1[M],s2[M];
ll lazy[4*M],seg[4*M],flazy[4*M];
void build(ll i,ll s,ll e)
{
	if(s==e)
	{
		seg[i]=a[s];
		return;
	}
	ll m=(s+e)/2;
	build(2*i,s,m);
	build(2*i+1,m+1,e);
	seg[i]=seg[2*i]+seg[2*i+1];
}
void split(ll i,ll s,ll e)
{
	if(flazy[i]!=0)
		seg[i]=(e-s+1)*lazy[i]+s2[e-1]-s2[s-1]-(e-s)*s1[s-1];
	if(flazy[i]==0)
		return;
	if(s==e)
		return;
	if(flazy[2*i]==0)
	{
		flazy[2*i]=1;
		lazy[2*i]=lazy[i];
	}
	else
	{
		lazy[2*i]=max(lazy[2*i],lazy[i]);
	}
	if(flazy[2*i+1]==0)
	{
		flazy[2*i+1]=1;
		lazy[2*i+1]=lazy[i]+s1[(s+e)/2]-s1[s-1];
	}
	else
	{
		lazy[2*i+1]=max(lazy[2*i+1],lazy[i]+s1[(s+e)/2]-s1[s-1]);
	}
	flazy[i]=0;
}
ll query(ll i,ll s,ll e,ll l,ll r)
{
	split(i,s,e);
	if(s>r || l>e)
		return 0;
	if(s>=l && e<=r)
	{
		// cout<<s<<" "<<e<<" "<<seg[i]<<"\n";
		return seg[i];
	}
	ll m=(s+e)/2;
	return query(2*i,s,m,l,r)+query(2*i+1,m+1,e,l,r);
}
void update(ll i,ll s,ll e,ll l,ll r,ll z)
{
	split(i,s,e);
	if(s>r || l>e)
		return;
	if(s>=l && e<=r)
	{
		if(flazy[i]==0)
		{
			flazy[i]=1;
			lazy[i]=z+s1[s-1]-s1[l-1];
		}
		else
			lazy[i]=max(lazy[i],z+s1[s-1]-s1[l-1]);
		seg[i]=(e-s+1)*lazy[i]+s2[e-1]-s2[s-1]-(e-s)*s1[s-1];
		// cout<<s<<" "<<e<<" "<<seg[i]<<"\n";
		return;
	}
	ll m=(s+e)/2;
	update(2*i,s,m,l,r,z);
	update(2*i+1,m+1,e,l,r,z);
	seg[i]=seg[2*i+1]+seg[2*i];
	flazy[i]=0;
	// cout<<s<<" "<<e<<" "<<seg[i]<<"\n";
}
int main()
{
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	ll n;
	cin>>n;
	for(ll i=1;i<=n;i++)
		cin>>a[i];
	for(ll i=1;i<n;i++)
	{
		cin>>k[i];
		s1[i]=s1[i-1]+k[i];
		s2[i]=s2[i-1]+s1[i];
	}
	build(1,1,n);
	ll q;
	cin>>q;
	while(q--)
	{
		char c;
		cin>>c;
		if(c=='s')
		{
			// cout<<"fuck"<<"\n";
			ll l,r;
			cin>>l>>r;
			cout<<query(1,1,n,l,r)<<"\n";
		}
		else
		{
			ll i,x;
			cin>>i>>x;
			ll l=i,r=n,mid,p=-1;
			ll z = query(1,1,n,i,i);
			// cout<<z<<"\n";
			while(l<r)
			{
				mid=(l+r)/2;
				if(mid==p)
					mid++;
				p=mid;
				ll y=query(1,1,n,p,p);
				if(y>z+x+s1[p-1]-s1[i-1])
					r=mid-1;
				else
					l=mid;
			}
			// cout<<i<<" "<<l<<"\n";
			update(1,1,n,i,l,z+x);
		}
	}
	return 0;
}
