ペア$(i,j)$を選択した時に出来る閉路の長さは$dist(i,j) + 1$です。

全$N(N - 1)/2$通りに対する閉路の長さの総和を$X$とするとき、明らかに

$2X = sum(dist(i,j) + 1　for　1 \le i \le N, 1\le j \le N, i \neq j)$

=$(iを始頂点としたときの、全頂点への距離 + 1 の総和)のiに対する総和$

と言い換えることができます。

この値は、全頂点からdfsやbfsを行うことで計算量$O(N^2)$で求めることができますが、$1 \le N \le 200000$の条件下では$2sec$で求めることは絶望的です。

今、ある頂点$S$(ここでは$1$とします)から($Sを始頂点とする全頂点への距離 + 1 の総和$)を求めましょう。

これはdfsやbfsを用いることで$O(N)$で求めることが可能です。これを$val$とします。

さらに、$S$を根に持つ木として、$child[node] := nodeを根に持つ部分木に含まれるノードの数$と定義します。

これも、dfsやbfsを用いることで$O(N)$で全頂点について求められます。

すると、$S$の子$v$を選び、グラフ上を移動したとすると、($vを始頂点とする全頂点への距離 + 1の総和$) は、

$val$より$child[v]$だけ減り、$n - child[v]$だけ増加することがわかります。

すなわち、($vを始頂点の前頂点への距離の総和 + 1$) = $val + n - 2child[v]$です。

この関係を用いグラフ上で$DP$を行うと、全頂点$i$に対する($iを始頂点とする全頂点への距離の総和 + 1$)を、計算量$O(N)$で求めることができます。

全体の時間計算量は$O(N)$です。

以下、$C{++}$と$Python3$による解答例です。

```C++での解答例(227ms)
#include<bits/stdc++.h>
#define ll long long
#define rep(i,n) for (int i = 0; i < n; i++)

using namespace std;

template <class T = int>T extgcd(T a,T b,T &x,T &y){T g = a;x = 1;y = 0;if (b != 0) {g = extgcd(b, a % b, y, x), y -= (a / b) * x;}return g;}
template<class T = int> T invMod(T a,T m){T x,y;if (extgcd(a, m, x, y) == 1) {return (x + m) % m;}else{return -1;}}

const ll MOD = 998244353;
const int inf = 1e9;

signed main(){
    int n;
    cin>>n;
    vector<vector<int>> g(n);
    rep(i,n - 1){
        int u,v;
        cin>>u>>v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> DIST(n,inf);
    vector<int> child(n);
    vector<int> par(n,-1);
    ll tot = 0;
    int S_Node = 0;
    DIST[S_Node] = 0;

    function<void(int)> dfs1 = [&](int S){
        for (int adj : g[S]){
            if (DIST[adj] == inf){
                par[adj] = S;
                DIST[adj] = DIST[S] + 1;
                dfs1(adj);
            }
        }
        child[S]++;
        for (int adj : g[S]){
            if (adj != par[S]){
                child[S] += child[adj];
            }
        }
    };

    dfs1(S_Node);

    ll val = 0;rep(i,n){val += DIST[i];}

    vector<int> trace_back;
    rep(i,n){if(i!= S_Node)DIST[i] = inf;}

    function<void(int)> dfs2 = [&](int S){
        tot = (tot + val + n - 1) % MOD;
        for (int adj : g[S]){
            if (DIST[adj] == inf){
                DIST[adj] = DIST[S] + 1;
                trace_back.push_back(val);
                val = (val + n - 2 * child[adj]) % MOD;
                dfs2(adj);
            }
        }
        if (S != S_Node){
            val = trace_back.back();
            trace_back.pop_back();
        }
    };

    dfs2(S_Node);

    ll ans = tot * invMod<ll>((ll)n*(n - 1),MOD) % MOD;
    if (ans < 0){ans += MOD;}
    cout << ans << endl;
    return 0;
}
```

```Python3での解答例(713ms)
import sys
sys.setrecursionlimit(1000000)
INF = 1 << 32
MOD = 998244353


def input():
    return sys.stdin.readline().rstrip()


n = int(input())
g = [[] for i in range(n)]

for i in range(n - 1):
    u, v = map(int, input().split())
    u -= 1
    v -= 1
    g[u].append(v)
    g[v].append(u)

DIST = [INF]*(n)
child = [0]*(n)
par = [-1]*(n)



def simple_dfs(S):
    for adj in g[S]:
        if DIST[adj] == INF:
            par[adj] = S
            DIST[adj] = DIST[S] + 1
            simple_dfs(adj)
    child[S] += 1
    for adj in g[S]:
        if adj != par[S]:
            child[S] += child[adj]


X = 0
DIST[X] = 0
simple_dfs(S=X)
tot = 0
val = sum(DIST[i] for i in range(n))


trace_back = []
for i in range(n):
    if i != X:
        DIST[i] = INF


def dfs(S):
    global val
    global tot
    tot += val + n - 1
    for adj in g[S]:
        if DIST[adj] == INF:
            tmp = val + n - 2 * child[adj]
            DIST[adj] = DIST[S] + 1
            trace_back.append(val)
            val = tmp
            dfs(adj)
    if S != X:
        val = trace_back.pop()


dfs(S=X)
ans = tot * pow(n * (n - 1), MOD - 2, MOD) % MOD
print(ans)
```