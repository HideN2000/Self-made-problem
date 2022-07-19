大きく分けて$2$通りの回答があると思います.

$(1) 桁に関するDP.$ 前計算$O(N)$のもとで,クエリあたり$O(K)$.

$(2)XOR$に関する性質を用いた数式計算.クエリあたり$O(1)$.

いずれでも実行時間には余裕があると思います.以下それぞれに関する簡単な説明を記します.

---

▷$(1) 桁に関するDP.$ 

・$L \le A_1 \oplus A_2 \oplus ... ... \oplus A_N \le R$の代わりに

・$ A_1 \oplus A_2 \oplus ... ... \oplus A_N \le R$の個数　$・・・（#)$

を数えることを考えます.これが解決できれば元の問題も

同様に解決できることは明らかです.

以下,$（#)$を解決することを考えます.

さて,$R$以下の数は,「$R$と比較した時,初めて$bit$が優位に小さくなる最上位桁」でグループ分けできます。

例を挙げると$R = 11010(2)$の時$(0????),(10???),(1100?),(11010)$のようなグループに分けることができます.

この時,$?$は${0,1}$どちらでもよいです.

さて,$i(bit)$目が${0,1}$であるかどうかは,$i$に非依存であり,それぞれが

$\sum_{i\ is\ even}^{} comb(N,i),\sum_{i\ is\ odd}^{} comb(N,i)$

であることは$XOR$の定義から明らかです.

従って,最上位$bit$からグループを走査してゆくことで,動的計画法の要領で$（#)$は$O(K)$で求めることができます.

以上のことから,二項係数テーブルを$O(N)$で構築のもと,各クエリには$O(K)$で回答することができます.

---

$(2)XOR$に関する性質を用いた数式計算.クエリあたり$O(1)$.

実は,$A_1 \oplus A_2 \oplus ... ... \oplus A_N  = i$を満たす数列の個数は$i$によらず$2 ^ {K(N - 1)}$です.

なぜなら,これは前半$N - 1$項を適当に決めることに相当し,そのいずれにおいても残る$1$項は一意に定まるからです.

以上より求める個数は $(R - L + 1) 2 ^ {K(N - 1)}$です.

$2^{K(N - 1)}$はクエリ全体を通して固定ですのでこれを前計算しておけばクエリごと$O(1)$です.
