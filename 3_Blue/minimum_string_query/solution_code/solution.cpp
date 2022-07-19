#include <bits/stdc++.h>

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

using Pii  = pair<int,int>;
using Pll = pair<ll,ll>;

const vector<Pii> dxy = {{0,1},{1,0}};
const vector<Pii> dxy1 = {{0,-1},{-1,0}};
const int inf = 1e9 + 10;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;cin >> n;
    vector<string> a(n);
    rep(i,0,n){cin >> a[i];}

    auto valid = [&](int x,int y){
        return 0 <= x && x < n && 0 <= y && y < n;
    };

    vector<vector<Pii>> dist(2 * n);
    rep(i,0,n)rep(j,0,n){dist[i + j].emplace_back(Pii{i,j});}

    vector<vector<bool>> direction(n,vector<bool>(n,false));
    vector<vector<int>> priority(n,vector<int>(n));


    rep1(d,0,2 * n - 1){
        if (d == 2 * n - 2){
            priority[n - 1][n - 1] = 0;
            continue;
        }
        vector<tuple<char,int,int,int>> data;
        for (auto [px,py] : dist[d]){
            char best_char = 'z' + 1;
            int best_pri = inf;
            int which = 0;
            rep(itr,0,2){
                auto [dx,dy] = dxy[itr];
                int nx = px + dx,ny = py + dy;
                if (!valid(nx,ny)){
                    continue;
                }
                if (best_char > a[nx][ny]){
                    which = itr;
                    best_char = a[nx][ny];
                    best_pri = priority[nx][ny];
                }else if (best_char == a[nx][ny] && best_pri > priority[nx][ny]){
                    which  = itr;
                    best_pri = priority[nx][ny];
                }
            }
            direction[px][py] = which;
            data.emplace_back(tuple<char,int,int,int>{best_char,best_pri,px,py});
        }

        sort(data.begin(),data.end());
        int rank = 0;
        for (int i = 0; i < data.size();i++){
            auto [c,pr,px,py] = data[i];
            priority[px][py] = rank;
            if (i == data.size() - 1){
                break;
            }
            if (get<0>(data[i]) != get<0>(data[i + 1]) || get<1>(data[i]) != get<1>(data[i + 1])){
                rank++;
            }
        }
    }

    vector<vector<bool>> direction1(n,vector<bool>(n,false));
    vector<vector<int>> priority1(n,vector<int>(n));
    rep(d,0,2 * n - 1){
        if (d == 0){
            priority1[0][0] = 0;
            continue;
        }
        vector<tuple<int,char,int,int>> data;
        for (auto [px,py] : dist[d]){
            int best_pri = inf;
            int which = 0;
            rep(itr,0,2){
                auto [dx,dy] = dxy1[itr];
                int nx = px + dx,ny = py + dy;
                if (!valid(nx,ny)){
                    continue;
                }
                if (best_pri > priority1[nx][ny]){
                    which = itr;
                    best_pri = priority1[nx][ny];
                }
            }
            direction1[px][py] = which;
            data.emplace_back(tuple<int,char,int,int>{best_pri,a[px][py],px,py});
        }

        sort(data.begin(),data.end());
        int rank = 0;
        for (int i = 0; i < data.size();i++){
            auto [pr,c,px,py] = data[i];
            priority1[px][py] = rank;
            if (i == data.size() - 1){
                break;
            }
            if (get<0>(data[i]) != get<0>(data[i + 1]) || get<1>(data[i]) != get<1>(data[i + 1])){
                rank++;
            }
        }
    }


    auto restore_head_string = [&](int i,int j){
        string res;
        for (int x = i,y = j;;){
            if (x < 0 || y < 0){break;}
            res.push_back(a[x][y]);
            if (direction1[x][y] == 1){x--;}
            else{y--;}
        }
        reverse(res.begin(),res.end());
        return res;
    };

    auto restore_tail_string = [&](int i,int j){
        string res;
        for (int x = i,y = j;;){
            if (x >= n || y >= n){break;}
            res.push_back(a[x][y]);
            if (direction[x][y] == 1){x++;}
            else{y++;}
        }
        return res;
    };

    //test
    assert(restore_head_string(n - 1,n - 1) == restore_tail_string(0,0));

    int q;cin >> q;
    rep(i,0,q){
        int X,Y;cin >> X >> Y;
        X--;Y--;
        string query_ans = restore_head_string(X,Y);
        query_ans.pop_back();
        query_ans.append(restore_tail_string(X,Y));
        assert(query_ans.size() == 2 * n - 1);
        cout << query_ans << endl;
    }

    return 0;
}