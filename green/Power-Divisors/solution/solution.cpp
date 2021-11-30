/* 
    C++(GNU++17) Template for Programming-Contest.
*/
#include<bits/stdc++.h>

using namespace std;

#pragma GCC optimize("Ofast")

#define ll long long
#define ld long double
#define rep(i, a, b) for (int i = a; i < b; i++)
#define rep1(i, a, b) for (int i = (b) - 1; i >= a; i--)
#define endl '\n'

template<class T> ostream& operator << (ostream &s, vector<T> &P)
{ for (int i = 0; i < P.size(); ++i) { if (i > 0) { s << " "; } s << P[i]; } return s; }

template<class T,class U> ostream& operator << (ostream &s, pair<T,U> &P)
{ s << " { " << P.first << " " << P.second << " } "; return s; }

template <class T>bool chmax(T &a, T b){if (a < b){a = b;return true;}return false;}
template <class T>bool chmin(T &a, T b){if (a > b){a = b;return true;}return false;}
template <typename T>using heapq = priority_queue<T, vector<T>, greater<T>>;

template <class T = int>T gcd(T a, T b){return (b == 0) ? a : gcd(b, a % b);}
template <class T = int>T lcm(T a, T b){return a / gcd(a, b) * b;}
template<class T = int>T powMod(T x, T k, T m) {if (k == 0){return (T)1;}if (k % 2 == 0) {return powMod(x*x % m, k/2, m);}else{return x*powMod(x, k-1, m) % m;}}
template <class T = int>T extgcd(T a,T b,T &x,T &y){T g = a;x = 1;y = 0;if (b != 0) {g = extgcd(b, a % b, y, x), y -= (a / b) * x;}return g;}
template<class T = int> T invMod(T a,T m){T x,y;if (extgcd(a, m, x, y) == 1) {return (x + m) % m;}else{return -1;}}
template<class T = int>int bisect_right(const vector<T> & V, T val){if (V.size() == 0){return 0;}auto it = lower_bound(V.begin(), V.end(), val + 1);int index = it - V.begin();return index;}
template<class T = ll>void UniqueVector(vector<T> & V){sort(V.begin(),V.end());auto result = std::unique(V.begin(), V.end());V.erase(result,V.end());return;}

map<ll,int> compress(const vector<ll> & a){int n = (int)a.size();vector<ll> copy_a(n);copy(a.begin(),a.end(),copy_a.begin());sort(copy_a.begin(),copy_a.end());
        int itr = 0;map<ll,int> retval;for (ll elem : copy_a){if (retval.find(elem) == retval.end()){retval[elem] = itr;itr++;}}return retval;}
vector<ll> compressVector(const vector<ll> & a){auto d = compress(a);int n = (int)a.size();vector<ll> ans(n);rep(i,0,n){ans[i] = d[a[i]];}return ans;}
int popcount(int x) { return __builtin_popcount(x); }
ll popcount(ll x) { return __builtin_popcountll(x); }

using Pii  = pair<int,int>;
using Pll = pair<ll,ll>;
const ll mod = 998244353;
const int inf = 1e9 + 10;
const ll linf = 1e18 + 10;

struct Eratos
{
    vector<int> primes;
    vector<bool> isprime;
    vector<int> mebius;
    vector<int> min_factor;
 
    Eratos(int MAX) : primes(),
                    isprime(MAX + 1, true),
                    mebius(MAX + 1, 1),
                    min_factor(MAX + 1, -1)
    {
        isprime[0] = isprime[1] = false;
        min_factor[0] = 0, min_factor[1] = 1;
        for (int i = 2; i <= MAX; ++i)
        {
            if (!isprime[i])
                continue;
            primes.push_back(i);
            mebius[i] = -1;
            min_factor[i] = i;
            for (int j = i * 2; j <= MAX; j += i)
            {
                isprime[j] = false;
                if ((j / i) % i == 0)
                    mebius[j] = 0;
                else
                    mebius[j] = -mebius[j];
                if (min_factor[j] == -1)
                    min_factor[j] = i;
            }
        }
    }

    // prime factorization
    vector<pair<int, int>> prime_factors(int n)
    {
        vector<pair<int, int>> res;
        while (n != 1)
        {
            int prime = min_factor[n];
            int exp = 0;
            while (min_factor[n] == prime)
            {
                ++exp;
                n /= prime;
            }
            res.push_back(make_pair(prime, exp));
        }
        return res;
    }

    // enumerate divisors
    vector<int> divisors(int n)
    {
        vector<int> res({1});
        auto pf = prime_factors(n);
        for (auto p : pf)
        {
            int n = (int)res.size();
            for (int i = 0; i < n; ++i)
            {
                int v = 1;
                for (int j = 0; j < p.second; ++j)
                {
                    v *= p.first;
                    res.push_back(res[i] * v);
                }
            }
        }
        return res;
    }
};



Eratos Primes(1000);
const ll maxn = 1e12;


signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> good_ords;
    for (int i = 1; i < 40;i *= 2){
        if (i > 1){
            good_ords.emplace_back(i - 1);
        }
    }
    vector<int> primes = Primes.primes;
    int n = primes.size();
    vector<vector<ll>> dp(n + 1,vector<ll>{});
    dp[0].emplace_back(1);

  	n = 7;
    for (int i = 0; i < n; i++){
        ll p = primes[i];
        for (auto e : dp[i]){
            //dp[i] -> dp[i + 1]
            for (auto ord : good_ords){
                ll val = e;
                rep(j,0,ord){
                    val = val * p;
                    if (val > maxn){break;}
                }
                if (val <= maxn){
                    dp[i + 1].emplace_back(val);
                }
            }
        }
        if (i > 0){
            for (auto & e : dp[i]){
                dp[i + 1].emplace_back(e);
            }
        }
        //if (i > 4)cout << i << "->" << dp[i] << endl;
    }
    cout << dp[n].size() << endl;
    return 0;
}