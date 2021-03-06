問題文
=====
$8$月です。Moja王国にも待望の夏休みが来ました。

夏休みに入ると人の動きが活発になるせいか、それまでと比べて事故の発生件数が多くなりがちです。

そこで、医療センターのモジヤ局長は今後増加が見込まれるかもしれない重大な事故による緊急輸血に備え、今のうちから対策を講じることにしました。

今現在、Moja王国には合計で$T$の病院があります。

それぞれの病院には、($A$型の血液,$B$型の血液,$O$型の血液,$AB$型の血液)が$(A_{in},B_{in},O_{in},{AB}_{in})$ずつ保管されています。

また、王国屈指のスーパーコンピュータにより、それぞれの病院において夏休みの間必要な血液の量が予測され、

それぞれの病院には、($A$型の血液,$B$型の血液,$O$型の血液,$AB$型の血液)が$(A_{out},B_{out},O_{out},{AB}_{out})$だけ必要とされることがわかりました。

あなたは、各病院において、保管されている血液の量がこの要求を満たす上で十分であるかどうか確認し、もし条件を満たせていないなら

今すぐ必要な分を送り届ける必要があります。しかし、当然ながら実際に不足することがわかってから送り届けていては間に合いません。

困っているモジヤ局長の代わりに、各病院において条件が満たされているか判定してください。

**ただし、血液型によっては、他の血液型からも供給を補えうることに注意してください。(例えば、AB型はA型からも輸血可能＆供給できます。)**

制約
-----

・$1 \le T \le 1000$

◉全てのテストケースにおいて以下が成立する。

・手元に保管されている血液の量は$0 \le A_{in},B_{in},O_{in},{AB}_{in} \le 100$

・必要と見込まれる血液の量は$0  \le A_{out},B_{out},O_{out},{AB}_{out} \le 100$

・入力は全て整数値である。

入力
-----
初めに整数$T$ = (テストケースの数)が与えられます。

それから$2T$行にわたって標準入力が与えられます。

$2i - 1,2i$行目では$i(1 \le i \le T)$番目の病院におけるデータを指し、

$2i - 1$行目ではそれぞれ順に現在病院に保管されている($A$型の血液量,$B$型の血液量,$O$型の血液量,$AB$型の血液量)が与えられます。

$2i$行目ではそれぞれ順に夏休み中に必要と思われる($A$型の血液量,$B$型の血液量,$O$型の血液量,$AB$型の血液量)が与えられます。
```
T
a_in b_in o_in ab_in
a_out b_out o_out ab_out
.
.
.
a_in b_in o_in ab_in
a_out b_out o_out ab_out
```

出力
-----
全部で$T$行出力してください。

$i$行目には、$i$番目の病院の病院に関して、

血液の供給が間に合いそうならば"Yes"、供給が間に合わない場合は"No"と出力してください。

最後に改行してください。

サンプル
=====
```入力1
1
1 2 3 4
1 2 3 4
```

```出力1
Yes
```
病院$1$では、

病院に保管されている($A$型の血液量,$B$型の血液量,$O$型の血液量,$AB$型の血液量) = $(1,2,3,4)$

夏休み中に必要と思われる($A$型の血液量,$B$型の血液量,$O$型の血液量,$AB$型の血液量) = $(1,2,3,4)$

という状況ですが、いずれの血液型の血液量も要求を満たすことは明らかです。

```入力2
2
1 2 3 4
1 0 2 7
1 2 3 4
1 0 4 4
```

```出力2
Yes
No
```
病院$1$では、

病院に保管されている($A$型の血液量,$B$型の血液量,$O$型の血液量,$AB$型の血液量) = $(1,2,3,4)$

夏休み中に必要と思われる($A$型の血液量,$B$型の血液量,$O$型の血液量,$AB$型の血液量) = $(1,0,2,7)$

という状況ですが、$AB$型に対しては$A,B,O$いずれからも輸血可能であるため、$A$型から$A$型用に1保管しておき、$O$型から$O$型用に2保管しておき、

残りの血液から$7$取り出し、$AB$型用に備えておけば要求を満たすことができます。

一方病院$2$では、

病院に保管されている($A$型の血液量,$B$型の血液量,$O$型の血液量,$AB$型の血液量) = $(1,2,3,4)$

夏休み中に必要と思われる($A$型の血液量,$B$型の血液量,$O$型の血液量,$AB$型の血液量) = $(1,0,4,4)$

という状況ですが、$O$型への輸血は$O$型からしか輸血できないのに対し、その$O$型の保管量が必要量よりも不足しているため、要求を満たすことは不可能です。