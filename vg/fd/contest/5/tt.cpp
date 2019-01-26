#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main(){
    ll n;
    while (cin >> n){
        map <ll, string> mp;
        string tmp;
        for (ll i = 2; i * i <= n; ++i){
            for (ll k = 2, j = i * i; j <= n; ++k, j *= i){
                tmp = to_string(i) + "^" + to_string(k); // j = i ^ k
                if (mp.count(j) == 0) mp[j] = to_string(j); // 预处理出所有小于等于 n 的 i ^ k 形式
                if (mp[j].length() > tmp.length()) mp[j] = tmp;
            }
        }
        string ans = to_string(n);
        for (auto& p : mp){
            tmp.clear();
            ll a = n / p.first, b = n % p.first; // a * i ^ k + b
            if (a > 1){
                if (mp.count(a) == 0)
                    tmp = to_string(a) + "*";
                else
                    tmp = mp[a] + "*";
            }
            tmp += p.second;
            if (b > 0){
                if (mp.count(b) == 0)
                    tmp += "+" + to_string(b);
                else
                    tmp += "+" + mp[b];
            }
            if (tmp.length() < ans.length()) ans = tmp;
        }
        cout << ans << endl;
    }
	return 0;
}
