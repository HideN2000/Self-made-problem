#include<bits/stdc++.h>
#include<atcoder/segtree>

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

        atcoder::segtree<ll,max_op,max_e> dp(vector<ll>(N + 1,-inf));//dp[i] := [0,i]まで処理した時の最大値
        dp.set(0,0);//dp[0] = 0

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
