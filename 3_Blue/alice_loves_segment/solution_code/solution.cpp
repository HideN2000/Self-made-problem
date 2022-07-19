#include<bits/stdc++.h>

using namespace std;

#pragma GCC optimize("Ofast")

#define ll long long
#define ld long double

#define rep(i, a, b) for (int i = a; i < b; i++)
#define rep1(i, a, b) for (int i = (b) - 1; i >= a; i--)
#define endl '\n'

using Pii  = pair<int,int>;
using Pll = pair<ll,ll>;
const int inf = 1e9 + 10;

ll op(ll a,ll b){return a + b;}
ll e(){return 0ll;}
int ceil_pow2(int n) {
    int x = 0;
    while ((1U << x) < (unsigned int)(n)) x++;
    return x;
}

template <class S, S (*op)(S, S), S (*e)()> struct segtree {
  public:
    segtree() : segtree(0) {}
    segtree(int n) : segtree(std::vector<S>(n, e())) {}
    segtree(const std::vector<S>& v) : _n(int(v.size())) {
        log = ceil_pow2(_n);
        size = 1 << log;
        d = std::vector<S>(2 * size, e());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) {
        assert(0 <= p && p < _n);
        return d[p + size];
    }
    void inc(int p){
        assert(0 <= p && p < _n);
        auto v = get(p);
        set(p,v + 1);
        return;
    }
    void dec(int p){
        assert(0 <= p && p < _n);
        auto v = get(p);
        set(p,v - 1);
        return;
    }
    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        S sml = e(), smr = e();
        l += size;
        r += size;

        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() { return d[1]; }

    template <bool (*f)(S)> int max_right(int l) {
        return max_right(l, [](S x) { return f(x); });
    }
    template <class F> int max_right(int l, F f) {
        assert(0 <= l && l <= _n);
        if (l == _n) return _n;
        l += size;
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(op(sm, d[l]))) {
                while (l < size) {
                    l = (2 * l);
                    if (f(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <bool (*f)(S)> int min_left(int r) {
        return min_left(r, [](S x) { return f(x); });
    }
    template <class F> int min_left(int r, F f) {
        assert(0 <= r && r <= _n);
        if (r == 0) return 0;
        r += size;
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(op(d[r], sm))) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int _n, size, log;
    std::vector<S> d;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
};

struct que{
    int l1,l2,r1,r2;
    int index;
    que(){l1 = 0,l2 = 0,r1 = 1,r2 = 1;}
    que(int l1,int l2,int r1,int r2):l1(l1),l2(l2),r1(r1),r2(r2){};
    void set_index(int idx){
        index = idx;return;
    }
};

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,Q;
    cin >> n >> Q;
    assert(2 <= n && n <= 200000 && 1 <= Q && Q <= 200000);
    vector<Pii> A(n);
    vector<que> Que(Q);

    rep(i,0,n){
        int l,r;cin >> l >> r;
        assert(1 <= l && l <= r && r <= n);
        A[i] = {l,r};
    }
    rep(i,0,Q){
        int l1,l2,r1,r2;
        cin >> l1 >> l2 >> r1 >> r2;
        assert(1 <= l1 && l1 <= l2 && l2 < r1 && r1 <= r2 && r2 <= n);
        Que[i] = que(l1,l2,r1,r2);
        Que[i].set_index(i);
    }

    segtree<ll,op,e> segment(n + 5);
    vector<int> ans(Q,n);
    vector<ll> cntL(n + 5),cntR(n + 5);
    for (auto [L,R] : A){
        cntL[L]++;
        cntR[R]++;
    }
    rep(i,1,n + 5){
        cntL[i] += cntL[i - 1];
        cntR[i] += cntR[i - 1];
    }
    rep(i,0,Q){
        ans[Que[i].index] -= cntL[Que[i].l1 - 1];
        ans[Que[i].index] -= cntL[n + 4] - cntL[Que[i].l2];
        ans[Que[i].index] -= cntR[Que[i].r1 - 1];
        ans[Que[i].index] -= cntR[n + 4] - cntR[Que[i].r2];
    }
    sort(Que.begin(),Que.end(),[&](const que & lh,const que & rh){
        return lh.l1 < rh.l1;
    });
    sort(A.begin(),A.end());
    for (int i = 0,itr = 0;i < Q;i++){
        while(itr < n && A[itr].first < Que[i].l1){
            auto [L,R] = A[itr];
            segment.inc(R);
            itr++;
        }
        ans[Que[i].index] += segment.prod(0,Que[i].r1);
        ans[Que[i].index] += segment.prod(Que[i].r2 + 1,n + 5);
    }

    segtree<ll,op,e> segment1(n + 5);
    sort(Que.begin(),Que.end(),[&](const que & lh,const que & rh){
        return lh.l2 > rh.l2;
    });
    reverse(A.begin(),A.end());
    for (int i = 0,itr = 0;i < Q;i++){
        while(itr < n && A[itr].first > Que[i].l2){
            auto [L,R] = A[itr];
            segment1.inc(R);
            itr++;
        }
        ans[Que[i].index] += segment1.prod(0,Que[i].r1);
        ans[Que[i].index] += segment1.prod(Que[i].r2 + 1,n + 5);
    }
    rep(i,0,Q){
        cout << ans[i] << endl;
    }
    return 0;
}