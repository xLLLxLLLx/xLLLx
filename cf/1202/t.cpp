#include<bits/stdc++.h>
 
using namespace std;
 
int main()  {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
 
    int a, b;   cin >> a >> b;
    int n = a + b;
 
    int ans = 0;
 
    for(int per = 1 ; per <= n ;)   {
        int fre = n / per;
        int nxt = n / fre;
        if (a >= fre && b >= fre)   {
            int l1 = (a + fre) / (fre + 1);
            int r1 =  a / fre;
            int l2 = (b + fre) / (fre + 1);
            int r2 =  b / fre;
            if (l1 <= r1 && l2 <= r2)
                ans += max(0,min(nxt,r1 + r2) - max(per,l1 + l2) + 1);
        }
        printf("%d %d\n", per, ans);
        per = nxt + 1;
	}
 
	cout << ans << endl;
}