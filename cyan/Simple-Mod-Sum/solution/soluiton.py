X, Y = map(int, input().split())
MOD = 998244353
MAX = int(1e12)


assert 1 <= X <= MAX
assert 1 <= Y <= MAX

ans = X * Y

for i in range(X//Y, X + 1):
    if i * i > X:
        for j in range(1, Y + 1):
            if X//j >= i:
                ans -= (X//j) * j
            else:
                break
        break
    if i == 0:
        continue

    M,m = min(X//i, Y),X//(i + 1)
    ans -= (M * (M + 1) //2 - m * (m + 1) // 2 ) * i

ans %= MOD 
print(ans)