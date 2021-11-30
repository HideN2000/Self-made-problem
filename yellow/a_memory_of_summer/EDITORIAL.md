

数列$A = [{A_1,A_2 ... A_n}]$と、総試合回数$K$が与えられた時に得られる期待値を$f([{A_1,A_2 ... A_n}],K)$と定義します。

この時、関数$f$は線型性を持ちます。すなわち以下が成り立ちます。

◉$f([{A_1 + B_1,A_2 + B_2 ... A_n + B_n}],K) = f([{A_1,A_2 ... A_n}],K) + f([{B_1,B_2 ... B_n}],K)$

◉$f([{A_1 * x,A_2 * x ... A_n * x}],K) = x * f([{A_1,A_2 ... A_n}],K)$

したがって、期待値の線形性を利用すれば

$g(k,i) := f([0,0 ... 1(i項目) ... 0],k)$とした時、全ての$1 \le i \le n$に対して$g(k,i)$の値がわかれば十分です。

では、$g(k,i)$はそれぞれどのように遷移してゆくのか調べてみます。

題意より、

○確率$\frac{p}{100}$で$[0,0 ... 1(i項目) ... 0]$に対して左から右向きに累積和がとられ

$[0,0 ... 1(i項目) ... 0] -> [0,0 ... 1(i項目) ... 1 ... 1]$ となるので

再び線形性を用いることで

$g(k,i) = g(k - 1,i) + g(k - 1,i + 1) + .... g(k - 1,n)$です。

　
 

○確率$\frac{q}{100}$で$[0,0 ... 1(i項目) ... 0]$に対して右から左向きに累積和がとられ

$[0,0 ... 1(i項目) ... 0] -> [1,...1 ... 1(i項目)... 0]$ となるので

再び線形性を用いることで

$g(k,i) = g(k - 1,1) + g(k - 1,2) + .... g(k - 1,i)$です。

　
 

○確率$\frac{r}{100}$で$[0,0 ... 1(i項目) ... 0]$に対して何も行われず

$g(k,i) = g(k - 1,i)$です。


以上より、任意の$g(k,i)$を$g(k - 1,j) (for 1 \le j \le n)$の線形和として表現することができたので

行列累乗を用いることで$g(k,i)$を$O(N^3 logK)$で求めることができ、$E$についてはこの値を利用して$O(N)$で求めることができます。

時間計算量は$O(N^3 logK)$です。


以下、$C$++と$Go$言語による解答例です。
```C++での解答例(283ms)
#include<bits/stdc++.h>

using namespace std;

#pragma GCC optimize("Ofast")

#define ll long long
#define ld long double
#define rep(i, a, b) for (int i = a; i < b; i++)
#define rep1(i, a, b) for (int i = (b) - 1; i >= a; i--)
#define endl '\n'
#define vvii vector<vector<int>>
#define vi vector<int>
#define vvll vector<vector<ll>>
#define vl vector<ll>

template<class T> ostream& operator << (ostream &s, vector<T> &P)
{ for (int i = 0; i < P.size(); ++i) { if (i > 0) { s << " "; } s << P[i]; } return s; }

template <class T>bool chmax(T &a, T b){if (a < b){a = b;return true;}return false;}
template <class T>bool chmin(T &a, T b){if (a > b){a = b;return true;}return false;}

template <class T = int>T gcd(T a, T b){return (b == 0) ? a : gcd(b, a % b);}
template <class T = int>T lcm(T a, T b){return a / gcd(a, b) * b;}
template<class T = int>T powMod(T x, T k, T m) {if (k == 0){return (T)1;}if (k % 2 == 0) {return powMod(x*x % m, k/2, m);}else{return x*powMod(x, k-1, m) % m;}}
template <class T = int>T extgcd(T a,T b,T &x,T &y){T g = a;x = 1;y = 0;if (b != 0) {g = extgcd(b, a % b, y, x), y -= (a / b) * x;}return g;}
template<class T = int> T invMod(T a,T m){T x,y;if (extgcd(a, m, x, y) == 1) {return (x + m) % m;}else{return -1;}}

using Pii  = pair<int,int>;
using Pll = pair<ll,ll>;

const ll mod = 998244353;

template< class T >
struct Matrix {
  vector< vector< T > > A;

  Matrix() {}

  Matrix(size_t n, size_t m) : A(n, vector< T >(m, 0)) {}

  Matrix(size_t n) : A(n, vector< T >(n, 0)) {};

  size_t height() const {
    return (A.size());
  }

  size_t width() const {
    return (A[0].size());
  }

  inline const vector< T > &operator[](int k) const {
    return (A.at(k));
  }

  inline vector< T > &operator[](int k) {
    return (A.at(k));
  }

  static Matrix I(size_t n) {
    Matrix mat(n);
    for(int i = 0; i < n; i++) mat[i][i] = 1;
    return (mat);
  }

  Matrix &operator+=(const Matrix &B) {
    size_t n = height(), m = width();
    assert(n == B.height() && m == B.width());
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        (*this)[i][j] += B[i][j];
    return (*this);
  }

  Matrix &operator-=(const Matrix &B) {
    size_t n = height(), m = width();
    assert(n == B.height() && m == B.width());
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        (*this)[i][j] -= B[i][j];
    return (*this);
  }

  Matrix &operator*=(const Matrix &B) {
    size_t n = height(), m = B.width(), p = width();
    assert(p == B.height());
    vector< vector< T > > C(n, vector< T >(m, 0));
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
        for(int k = 0; k < p; k++)
          C[i][j] = (C[i][j] + (*this)[i][k] * B[k][j]) % mod;
    A.swap(C);
    return (*this);
  }

  Matrix &operator^=(long long k) {
    Matrix B = Matrix::I(height());
    while(k > 0) {
      if(k & 1) B *= *this;
      *this *= *this;
      k >>= 1LL;
    }
    A.swap(B.A);
    return (*this);
  }

  Matrix operator+(const Matrix &B) const {
    return (Matrix(*this) += B);
  }

  Matrix operator-(const Matrix &B) const {
    return (Matrix(*this) -= B);
  }

  Matrix operator*(const Matrix &B) const {
    return (Matrix(*this) *= B);
  }

  Matrix operator^(const long long k) const {
    return (Matrix(*this) ^= k);
  }

  friend ostream &operator<<(ostream &os, Matrix &p) {
    size_t n = p.height(), m = p.width();
    for(int i = 0; i < n; i++) {
      os << "[";
      for(int j = 0; j < m; j++) {
        os << p[i][j] << (j + 1 == m ? "]\n" : ",");
      }
    }
    return (os);
  }


  T determinant() {
    Matrix B(*this);
    assert(width() == height());
    T ret = 1;
    for(int i = 0; i < width(); i++) {
      int idx = -1;
      for(int j = i; j < width(); j++) {
        if(B[j][i] != 0) idx = j;
      }
      if(idx == -1) return (0);
      if(i != idx) {
        ret *= -1;
        swap(B[i], B[idx]);
      }
      ret *= B[i][i];
      T vv = B[i][i];
      for(int j = 0; j < width(); j++) {
        B[i][j] /= vv;
      }
      for(int j = i + 1; j < width(); j++) {
        T a = B[j][i];
        for(int k = 0; k < width(); k++) {
          B[j][k] -= B[i][k] * a;
        }
      }
    }
    return (ret);
  }
};


signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll n,k;
    cin >> n >> k;
    vl a(n);
    rep(i,0,n){cin >> a[i];}
    ll p,q,r;
    cin >> p >> q >> r;
    Matrix<ll> M = Matrix<ll>(n);
    Matrix<ll> X = Matrix<ll>(n,1);
    rep(i,0,n){
        X.A[i][0] = 1;
    }
    ll num = 0,den = powMod(100ll,k,mod);

    rep(i,0,n){
        rep(j,i,n){
            M.A[i][j] += p;
            M.A[i][j] %= mod;
        }
        rep(j,0,i + 1){
            M.A[i][j] += q;
            M.A[i][j] %= mod;
        }
        M.A[i][i] += r;
        M.A[i][i] %= mod;
    }

    Matrix<ll> B = (M^(k)) * X;
    rep(i,0,n){
        num = (num + B.A[i][0]*a[i]) % mod;
    }
    ll ans = num * invMod(den,mod) % mod;
    if (ans < 0){
        ans += mod;
    }
    printf("%d\n",ans);
    return 0;
}


  
  
```

``` GO言語での解答例(318ms)
package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

var wg = bufio.NewScanner(os.Stdin)

const (
	inf            = int(1e18)
	initialBufSize = int(1e6)
	maxBufSize     = int(1e6)
	mod            = 998244353
)

var buf []byte = make([]byte, initialBufSize)

type Matrix struct {
	row, col int
	elem     [][]int
}

func GenMat(row, col int) (*Matrix, bool) {
	retval := new(Matrix)
	if row <= 0 || col <= 0 {
		return retval, false
	}
	retval.row = row
	retval.col = col
	retval.elem = make([][]int, retval.row)
	for i := 0; i < retval.row; i++ {
		retval.elem[i] = make([]int, retval.col)
		for j := 0; j < retval.col; j++ {
			retval.elem[i][j] = 0
		}
	}
	return retval, true
}

func MatMul(lmat, rmat *Matrix) (*Matrix, bool) {
	retval := new(Matrix)
	if lmat.col != rmat.row {
		return retval, false
	}
	retval, _ = GenMat(lmat.row, rmat.col)
	for i := 0; i < lmat.row; i++ {
		for j := 0; j < rmat.col; j++ {
			for k := 0; k < lmat.col; k++ {
				retval.elem[i][j] = (retval.elem[i][j] + lmat.elem[i][k]*rmat.elem[k][j]) % mod
			}
		}
	}
	return retval, true
}

func (mat *Matrix) Get(i, j int) (int, bool) {
	if 0 <= i && i < mat.row && 0 <= j && j < mat.col {
		return mat.elem[i][j], true
	} else {
		return -1, false
	}
}

func (mat *Matrix) Set(i, j, val int) bool {
	if 0 <= i && i < mat.row && 0 <= j && j < mat.col {
		mat.elem[i][j] = val
		mat.elem[i][j] %= mod
		return true
	} else {
		return false
	}
}

func (mat *Matrix) Add(i, j, val int) bool {
	if 0 <= i && i < mat.row && 0 <= j && j < mat.col {
		mat.elem[i][j] += val
		mat.elem[i][j] %= mod
		return true
	} else {
		return false
	}
}

func (mat *Matrix) PowMod(k int) (*Matrix, bool) {
	retval := new(Matrix)
	if k < 0 || mat.row != mat.col {
		return retval, false
	} else if k == 0 {
		retval, _ = GenMat(mat.row, mat.col)
		for i := 0; i < mat.row; i++ {
			retval.elem[i][i] = 1
		}
		return retval, true
	}

	switch k % 2 {
	case 0:
		med, _ := mat.PowMod(k / 2)
		retval, _ = MatMul(med, med)
		return retval, true
	case 1:
		med, _ := mat.PowMod(k / 2)
		retval, _ = MatMul(med, med)
		retval2, _ := MatMul(retval, mat)
		return retval2, true
	}
	return retval, true
}

func main() {
	n, k := nextInt(), nextInt()
	a := make([]int, n)
	for i := 0; i < n; i++ {
		a[i] = nextInt()
	}
	p, q, r := nextInt(), nextInt(), nextInt()
	mat, _ := GenMat(n, n)
	X, _ := GenMat(n, 1)
	for i := 0; i < n; i++ {
		X.Set(i, 0, 1)
	}
	for i := 0; i < n; i++ {
		for j := i; j < n; j++ {
			mat.Add(i, j, p*ModInv(100, mod)%mod)
		}
		for j := 0; j <= i; j++ {
			mat.Add(i, j, q*ModInv(100, mod)%mod)
		}
		mat.Add(i, i, r*ModInv(100, mod)%mod)
	}

	powmat, _ := mat.PowMod(k)
	res, _ := MatMul(powmat, X)
	ans := 0

	for i, v := range a {
		val, _ := res.Get(i, 0)
		ans = (ans + val*v) % mod
	}
	if ans < 0 {
		ans += mod
	}
	fmt.Printf("%d\n", ans)
}

func ModInv(a, modulo int) int {
	b := modulo
	u, v := 1, 0
	for b > 0 {
		t := a / b
		a, b = b, a-t*b
		u, v = v, u-t*v
	}
	u %= modulo
	if u < 0 {
		u += modulo
	}
	return u
}

func init() {
	wg.Split(bufio.ScanWords)
	wg.Buffer(buf, maxBufSize)
}

func nextInt() int {
	wg.Scan()
	i, e := strconv.Atoi(wg.Text())
	if e != nil {
		panic(e)
	}
	return i
}
```