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

using Pii  = pair<int,int>;
using Pll = pair<ll,ll>;
const ll inf = 1e18;

template <class S, S (*op)(S, S), S (*e)()> struct segtree {
  public:
        segtree() : segtree(0) {}
        segtree(int n) : segtree(std::vector<S>(n, e())) {}
        segtree(const std::vector<S>& v) : _n(int(v.size())) {log = _ceil_pow2(_n);size = 1 << log;d = std::vector<S>(2 * size, e());for (int i = 0; i < _n; i++) d[size + i] = v[i];for (int i = size - 1; i >= 1; i--) {update(i);}}
        void set(int p, S x) {assert(0 <= p && p < _n);p += size;d[p] = x;for (int i = 1; i <= log; i++) update(p >> i);}
        S get(int p) {assert(0 <= p && p < _n);return d[p + size];}
        S add(int p, S x){assert(0 <= p && p < _n);p += size;d[p] += x;for (int i = 1; i <= log; i++) update(p >> i);}
        S prod(int l, int r) {assert(0 <= l && l <= r && r <= _n);S sml = e(), smr = e();l += size;r += size;
            while (l < r) {if (l & 1) sml = op(sml, d[l++]);if (r & 1) smr = op(d[--r], smr);l >>= 1;r >>= 1;}return op(sml, smr);}
        S all_prod() { return d[1]; }
        template <bool (*f)(S)> int max_right(int l) {return max_right(l, [](S x) { return f(x); });}
        template <class F> int max_right(int l, F f) {assert(0 <= l && l <= _n);if (l == _n) return _n;l += size;S sm = e();
            do {while (l % 2 == 0) l >>= 1;if (!f(op(sm, d[l]))) {while (l < size) {l = (2 * l);if (f(op(sm, d[l]))) {sm = op(sm, d[l]);l++;}}return l - size;}sm = op(sm, d[l]);l++;} while ((l & -l) != l);return _n;}
        template <bool (*f)(S)> int min_left(int r) {return min_left(r, [](S x) { return f(x); });}
        template <class F> int min_left(int r, F f) {assert(0 <= r && r <= _n);if (r == 0) return 0;r += size;S sm = e();
            do {r--;while (r > 1 && (r % 2)) r >>= 1;if (!f(op(d[r], sm))) {while (r < size) {r = (2 * r + 1);if (f(op(d[r], sm))) {sm = op(d[r], sm);r--;}}return r + 1 - size;}sm = op(d[r], sm);} while ((r & -r) != r);return 0;}
    private:
        int _n, size, log;std::vector<S> d;void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
        int _ceil_pow2(int n) {int x = 0;while ((1U << x) < (unsigned int)(n)) x++;return x;}
};

ll max_op(ll a,ll b){
    return max(a,b);
}

ll max_e(){
    return -inf;
}

vector<int> find_left(vector<ll> & array){
    int n = array.size();

    vector<Pll> array_idx(n);
    vector<int> ret_array(n);

    rep(i,0,n){
        array_idx[i] = Pll{array[i],i};
    }

    sort(array_idx.begin(),array_idx.end(),[](const Pll & lh,const Pll & rh){
        return lh.first > rh.first;
    });

    set<int> S;

    for (auto [val,idx] : array_idx){
        S.insert(idx);
        auto itr = S.lower_bound(idx);
        if (itr == S.begin()){
            ret_array[idx] = -1;
        }else{
            itr--;
            ret_array[idx] = *itr;
        }
    }

    return ret_array;
}

vector<int> find_right(vector<ll> & array){
    int n = array.size();
    vector<ll> rev_array(n);
    rep(i,0,n){
        rev_array[i] = array[n - 1 - i];
    }
    vector<int> rev_left = find_left(rev_array);
    vector<int> ret_array(n);
    rep(i,0,n){
        ret_array[n - 1 - i] = n - 1 - rev_left[i];
    }
    return ret_array;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;cin >> T;

    while(T--){
        int N;ll C;
        cin >> N >> C;

        vector<ll> A(N),B(N);
        rep(i,0,N){
            cin >> A[i];
        }
        rep(i,0,N){
            cin >> B[i];
        }

        vector<int> Left = find_left(A);
        vector<int> Right = find_right(A);

        segtree<ll, max_op, max_e> dp(vector<ll>(N + 1,-inf));
        dp.set(0,0);

        multiset<ll> max_S{};
        multiset<Pll> max_T{};

        rep(i,0,N){
            
            while(!max_T.empty()){
                auto itr = max_T.begin();
                ll r = itr->first,val = itr->second;
                if (r <= i + 1){
                    max_S.erase(max_S.find(val));
                    max_T.erase(itr);
                }else{
                    break;
                }
            }

            ll tmp = dp.prod(Left[i] + 1,i + 1) + B[i] - C;
            if (!max_S.empty()){
                chmax(tmp,*max_S.rbegin());
            }

            dp.set(i + 1,tmp);
            max_T.insert(Pll{Right[i] + 1,tmp});
            max_S.insert(tmp);
        }

        ll ans = dp.get(N);

        printf("%lld\n",ans);
    }
    return 0;
}