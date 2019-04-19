#include<iostream>
#include<stdio.h>
#include<algorithm>
using namespace std;
 
const int N = 50000;
bool prime[N];
int u[N], su[N];//su是u的前缀和
 
void getu()
{
	for (int i = 0; i < N; i++)prime[i] = true, u[i] = 1;
	prime[1] = false;
	for (int i = 2; i < N; i++)if (prime[i])for (int j = 1; i* j < N; j++)
		prime[i*j] = false, u[i*j] *= -1 * (j%i != 0);
	su[0] = u[0];
	for (int i = 1; i < N; i++)su[i] = su[i - 1] + u[i];
}
 
int f(int n, int m)//有多少个数对(x,y)满足1<=x<=n,1<=y<=m且gcd(x,y)=1
{
	int res = 0;
	for (int i = 1, key; i <= n && i <= m; i = key + 1)
	{
		key = min(n / (n / i), m / (m / i));
		res += (n / i)*(m / i)*(su[key] - su[i - 1]);
	}
	return res;
}
 
int main()
{
	int n, a, b, c, d, k;
	scanf("%d", &n);
	getu();
	while (n--)
	{
		scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
		a--, c--;
		a /= k, b /= k, c /= k, d /= k;
		printf("%d\n", f(b, d) - f(a, d) - f(b, c) + f(a, c));
	}
	return 0;
}