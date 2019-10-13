#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
typedef long double ldb;
typedef long long ll;
const int maxn = 55;
int n, m;
char s[maxn][30];
ldb ans;
ldb F[(1 << 20) + 5];//F[j]猜到j状态的概率有多少
ll Choice[(1 << 20) + 5];
 //__builtin_popcount()用这个函数来统计位数
int main(){
    //freopen("programmer.in", "r", stdin);
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%s", s[i]);
    if(n == 1){
        printf("0\n");
        return 0;
    }
    //for(int i = 1; i <= n; i++)
    //    printf("%s\n", s[i]);
    m = strlen(s[1]);
    //cerr << m << endl;
    F[0] = 1;
    for(int i = 1; i <= n; i++)
        for(int j = i+1; j <= n; j++){
            int stat = 0;
            for(int k = 0; k <= m-1; k++)
                if(s[i][k] == s[j][k]) stat |= (1 << k);
            Choice[stat] |= (1LL << i) | (1LL << j);
            //int stat = 0;
            //if(s[])
        }
    for(int j = (1 << m) - 1; j >= 0; j--){
        for(int k = 0; k <= m-1; k++){
            if((j >> k) & 1){
                Choice[j^(1 << k)] |= Choice[j];
            }
        }
        //cerr << "#: " << j << endl;
        //cerr << Choice[j] << endl;
        printf("f[%d] = %lld\n", j, Choice[j] / 2);
    }
//    /*
    for(register int j = 0; j <= (1 << m) - 1; j++){
        int len = __builtin_popcount(j);
        len = m - len;
        for(register int k = 0; k < m; k++){
            if(!((j >> k) & 1)){
                int stat = j ^ (1 << k);
            //    if(__builtin_popcount(Choice[stat]) == 0) continue;
                F[stat] += F[j] * 1.0/(ldb)len;
            }
        }
        //cerr << j << endl;
        //cerr << F[j] << endl;
    }
//    */
    /*
    for(int j = 1; j <= (1 << m) - 1; j++){
        int len = __builtin_popcount(j);
        len = m - len + 1;
        for(int k = 0; k <= m-1; k++){
            if((j >> k) & 1){
                int stat = j ^ (1 << k);
                if(__builtin_popcount(Choice[stat]) == 0) continue;
                F[j] += 1.0 / (ldb)len * F[stat];
            }
        }
        //cerr << j << endl;
        //cerr << F[j] << endl;
    }*/

    for(int i = 0; i <= (1 << m) - 1; i++){
        int len = __builtin_popcount(Choice[i] & ((1 << 30) - 1));

        len += __builtin_popcount(Choice[i] >> 30);
        //cif(len == 0)
        //cerr << len << endl;
        //cerr << i << ": " << endl;
        //cerr << len << endl;
        ans += F[i] * (ldb)len / (ldb)n;//这步基于期望的可加性
        printf("%d\n", len);
        //cerr << ans << endl;
    }

    printf("%.15Lf\n", ans);
}