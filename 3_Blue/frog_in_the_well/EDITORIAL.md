ナイーブな方法を考えます。

$dp[i][j] := i番目の生徒までみて、ちょうどi番目の生徒まででj個のクラスに分けられている時の学校の最大の幸福値$とすると

$rangeQ[l][r] := [l,r]における最も能力値の高い生徒の幸福値$と定義した時
       
$dp[i][j] = max(dp[pre_i][j - 1] + rangeQ[pre_i + 1][i] - C)  (0 \le pre_i \le i - 1)$

によって答えは$max(dp[N][k]) (0 \le k \le N)$で与えられることは明らかです。

しかしこのままだと計算量が$O(N ^ 3)$であり、$2sec$内に収めることは難しいです。

新しい$dp$を考えます。$segmentTree上で$、

$dp[i] := [1,i]まででいくつかのクラスに分けている時の学校としての最大の幸福値$と定義します。

さらに、

$Left[i] := i番目の生徒よりも左にいて、能力値の高い生徒のうちi番目の生徒に最も近い生徒の番号(存在しない場合-1)$

とします。（これは$segment Tree/set$などを用いれば$O(NlogN)$で構成できます)

すると

$dp[i] = max(dp[Left[i]..i]) + B[i] - C$です。

加えて、この後

$Right[i] := i番目の生徒よりも右にいて、能力値の高い生徒のうちi番目の生徒に最も近い生徒の番号(存在しない場合N)$

と定義すると、（これは$segment Tree/set$などを用いれば$O(NlogN)$で構成できます)

$dp[j] = max(dp[j],dp[i]) (i \le j < Right[i])$

が適用されます。これは$multiset$などを用いて$dp$全体の更新を通して$O(NlogN)$で更新可能です。

答えは明らかに$dp[N]$であり、全体の時間計算量は$O(NlogN)$です。

