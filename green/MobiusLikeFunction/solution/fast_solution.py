mod = 998244353
n = int(input())
P = list(map(int,input().split()))
one = [-1]*(1 << n)
for bit in range(n):
    one[1<<bit] = bit
dp = [0]*(1 << n)
for i in range(1 << n):
    if one[i] >= 0:
        dp[i] = P[one[i]]
        continue
    val = 1
    T = i
    while True:
        if T != i:
            val = dp[T] * val % mod
        if T == 0:
            break
        T = (T - 1) & i
    dp[i] = val 
print(dp[(1 << n) - 1] % mod)