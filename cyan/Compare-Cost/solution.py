'''
    Python3(PyPy3) Template for Programming-Contest.
'''

from math import gcd
import sys


def input():
    return sys.stdin.readline().rstrip()


mod = int(1e9 + 7)


def main():
    n, K = map(int, input().split())
    Num = n * (n - 1) // 2 * \
        (K * K * (K + 1) - (K * (K + 1) * (4 * K - 1)) // 6)
    Den = pow(K, 2)
    print(Num,Den)
    g = gcd(Num, Den)
    print(Num // g, Den // g)
    ans = Num * pow(Den, mod - 2, mod) % mod
    print(ans)

    return 0


if __name__ == "__main__":
    main()
