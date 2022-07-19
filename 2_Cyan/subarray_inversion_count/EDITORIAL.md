通常の転倒数を求めるアルゴリズムの内部を理解していれば恐らく易しいはずです。

$P_i$の大きい順から見てゆき、転倒数を構成するペアが左に何個あるかを確認しながらそのペアを含みうる部分列の個数を数えれば良いです。

これは$SegmentTree$や$FenwickTree$を用いれば$O(N logN)$で解決できます。

```C++での解答例
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using P = pair<ll,ll>;

const ll MOD = 1e18;


struct FenwickTree {
    vector<ll> bit;  // binary indexed tree
    ll n;

    FenwickTree(ll n) {
        this->n = n;
        bit.assign(n, 0);
    }

    FenwickTree(vector<ll> a) : FenwickTree(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }

    ll sum(ll r) {
        ll ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    ll sum(ll l, ll r) {
        return sum(r) - sum(l - 1);
    }

    void add(ll idx, ll delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};

signed main(){
    int N;cin>>N;
    ll X;
    vector<P> A;
    for (int i = 0; i < N;i++){
        cin>>X;
        A.emplace_back(P{-X,i});
    }
    sort(A.begin(),A.end());
    FenwickTree fen = FenwickTree(N);
    ll ans = 0;
    for (auto [_,idx] : A){
        ans += (N - idx) * fen.sum(0,idx);
        ans %= MOD;
        fen.add(idx,idx + 1);
    }
    cout << ans << endl;
    return 0;
}
```

```Pythonでの解答例(https://github.com/not522/ac-library-pythonの導入が必要)
from atcoder.segtree import SegTree

N = int(input())
perm = list(map(int, input().split()))
segment = SegTree(lambda x, y: x + y, 0, N)

events = [(perm[i], i) for i in range(N)]
events.sort(key=lambda x: -x[0])

ans = 0
MOD = int(1e18)

for val, idx in events:
    r = N - idx
    ans += r * segment.prod(0, idx + 1)
    segment.increment(idx, idx + 1)

print(ans % MOD)

```