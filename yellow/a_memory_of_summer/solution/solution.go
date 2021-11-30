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
