#include<bits/stdc++.h>

using namespace std;

#pragma GCC optimize("Ofast")

#define ll long long
#define ld long double
#define rep(i, a, b) for (int i = a; i < b; i++)
#define rep1(i, a, b) for (int i = (b) - 1; i >= a; i--)
#define endl '\n'

template <class T>bool chmax(T &a, T b){if (a < b){a = b;return true;}return false;}
template <class T>bool chmin(T &a, T b){if (a > b){a = b;return true;}return false;}

int popcount(int x) { return __builtin_popcount(x); }
ll popcount(ll x) { return __builtin_popcountll(x); }

using Pii  = pair<int,int>;
using Pll = pair<ll,ll>;
const int inf = 1e6;

int tens[100];
int M,R;

void setup(){
    tens[0] = 1;
    rep(i,1,100){
        tens[i] = 10 * tens[i - 1] % M;
    }
    return;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S;
    cin >> S;
    cin >> M >> R;
    setup();
    int n = S.size();
    vector<int> a(n);
    rep(i,0,n){
        a[i] = S[i] - '0';
    }
    vector<vector<int>> dp(1 << n,vector<int>(M,inf));
    dp[0][0] = 0;
    rep(S,1,1 << n){
        int small_bit = 0;
        int d = a[popcount(S) - 1];
        rep1(bit,0,n){
            if (d == 0 && bit == 0){
                continue;
            }
            if (S >> bit & 1){
                int val = d * tens[n - 1 - bit] % M;
                rep(m,0,M){
                    chmin(dp[S][(val + m) % M],dp[S & ~(1 << bit)][m] + small_bit);
                }
                small_bit++;
            }
        }
    }
    int ans = dp[(1 << n) - 1][R];
    if (ans == inf){
        ans = -1;
    }
    printf("%d\n",ans);
    
    return 0;
}