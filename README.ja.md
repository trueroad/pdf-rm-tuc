<!-- -*- coding: utf-8 -*- -->
# PDF から ToUnicode CMap を削除するツール

[ Japanese (日本語) / [English](./README.md) ]

[
https://github.com/trueroad/pdf-rm-tuc
](https://github.com/trueroad/pdf-rm-tuc)

このツールは、指定したフォントの ToUnicode CMap を PDF から削除します。
フォントの ROS も変更できます。

LuaTeX で
[
原ノ味フォント
](https://github.com/trueroad/HaranoAjiFonts)
のような Adobe-Japan1 フォントを使うと、出力される PDF には
Adobe-Identity-0 フォントとして埋め込まれ、
ToUnicode CMap が生成されます。
ToUnicode CMap は、 PDF から Unicode テキストを抽出
（PDF viewer でテキストをコピーするなど）するときに使用される
CID から Unicode へのマッピングテーブルです。
Adobe-Identity-0 フォントの場合、
PDF からテキストを抽出するには ToUnicode CMap 埋め込みが必要です。
ただし、 Adobe-Japan1 フォントの場合は埋め込みは必ずしも必要ではありません。

また、LuaTeX はフォントの cmap テーブルから逆変換で
ToUnicode CMap を生成しているようで、
縦書き用グリフを使った場合や異字体を使った場合など、
テキスト抽出すると意図しない結果になることがあります。
一方 PDF viewer は ToUnicode CMap が埋め込まれていなくても、
Adobe-Japan1 フォントならば自分で持っている ToUnicode CMap を使って
テキスト抽出することができます。
この際に使われる `Adobe-Japan1-UCS2` という ToUnicode CMap は、
逆変換の問題が発生しないようにあらかじめ調整されたものなので、
意図しない文字化けなどが発生しにくくなっています。
しかし LuaTeX が出力した PDF のように ToUnicode CMap が埋め込まれている場合は
それを優先して使用するため、
一部のグリフでテキスト抽出に問題が発生してしまいます。

本ツールはデフォルトでは PDF から
原ノ味フォントの ToUnicode CMap を削除し、
原ノ味フォントの ROS を Adobe-Identity-0 から
元の Adobe-Japan1-7 に変更します。
これによってテキスト抽出で意図しない結果になることを防げる
と考えています。

## 注意

XeTeX を使う場合や pTeX や upTeX で dvipdfmx を使う場合
（xdvipdfmx / dvipdfmx で PDF を生成する場合）、
Adobe-Japan1 フォントなら ToUnicode CMap が生成されず埋め込まれませんので
本ツールは不要です。

LuaTeX の出力した PDF に対して使う場合、
ToUnicode CMap を削除するフォントは GID ＝ CID の関係である必要があります。
そうでない場合はテキスト抽出すると文字化けを起こしてしまいます。
原ノ味フォントの場合は 20190501 以降であれば問題ありません。

ToUnicode CMap を削除してしまうと、
`Adobe-Japan1-UCS2` などを持っていない
PDF viewer などでテキスト抽出できなくなります。
Adobe Acrobat Reader は持っていますし、
まともに日本語対応しているものであれば持っていると思われますので
問題ありません。

PDF/A-1a, PDF/A-2a, PDF/A-3a, PDF/A-2u, PDF/A-3u といった
レベル A やレベル U の PDF/A 規格では ToUnicode CMap が必要なので、
削除すると非準拠になる可能性があります。（ただし、PDF/A 検証ツール[
veraPDF
](https://verapdf.org/)
のドキュメントに、 Adobe-Japan1 ならば ToUnicode CMap が無くてもよい、
と解釈できそうなところ
([
Rule 6.3.8-1, PDF/A-1 validation rules
](http://docs.verapdf.org/validation/pdfa-part1/#6.3.8-1),
[
Rule 6.2.11.7-1, PDF/A-2 and PDF/A-3 validation rules
](http://docs.verapdf.org/validation/pdfa-parts-2-and-3/#6.2.11.7-1))
があります。
実際、下記の使用例の通り試してみた限りでは合格になりました。）
PDF/A-1b, PDF/A-2b, PDF/A-3b のような
レベル B の PDF/A 規格なら ToUnicode CMap が無くても問題ありません。

## 使い方

```
$ pdf-rm-tuc
Remove ToUnicode CMap from PDF 0.0.1
Copyright (C) 2019 Masamichi Hosoda. All rights reserved.
License: BSD-2-Clause

https://github.com/trueroad/pdf-rm-tuc

Usage: pdf-rm-tuc [options] [INPUT.pdf OUTPUT.pdf] ...

  -h, --help
    Print help and exit
  -V, --version
    Print version and exit
  --verbose
    Verbose

Font settings:
  --pattern=PATTERN   (default is HaranoAji fonts pattern)
    Font name regex pattern for removing ToUnicode CMap
  --registry=STRING   (default=Adobe)
    Registry for changing ROS
  --ordering=STRING   (default=Japan1)
    Ordering for changing ROS
  --supplement=INTEGER   (default=7)
    Supplement for changing ROS

Output PDF settings (QPDF):
  --linearize
    Output linearized (web-optimized) PDF
  --object-streams=[preserve|disable|generate]   (default=preserve)
    Settings for object streams
  --newline-before-endstream
    Output newline before endstream
  --qdf
    Output QDF

$
```

## ビルドとインストール

* 必要なもの
    + C++11 対応コンパイラ（g++ 4.9 以降など）
    + [libqpdf](http://qpdf.sourceforge.net/)
    + Autotools, pkg-config など

```
$ ./autogen.sh
$ mkdir build
$ cd build
$ ../configure
$ make
$ make install
```

## 使用例

試しに Adobe-Japan1 である
[
原ノ味フォント 20190501 版
](https://github.com/trueroad/HaranoAjiFonts)
を使い LuaLaTeX で PDF/A-2u 規格に準拠した PDF を作成し、
本ツールを通して原ノ味フォントの ToUnicode CMap を削除した
PDF を作ってみます。
（諸々の設定や pdfx.sty で PDF/A に準拠する方法などは
各種のマニュアルなどを参考にしてください。）

ソース `test-pdfa2u.tex` は以下の通りです。

```test-pdfa2u.tex
% -*- coding: utf-8 mode:latex -*-

% PDF/A のメタデータ
\begin{filecontents*}{\jobname.xmpdata}
  \Title{タイトル}
  \Author{著者1\sep 著者2\sep 著者3}
  \Language{ja-JP}
  \Keywords{キーワード\sep きーわーど\sep key words}
  \Publisher{出版者}
\end{filecontents*}

\documentclass{ltjsarticle}

% 原ノ味フォントを使う
\usepackage[deluxe,match,nfssonly]{luatexja-preset}
\ltjnewpreset{HaranoAji}{%
  mc-l = HaranoAjiMincho-Light.otf,
  mc-m = HaranoAjiMincho-Regular.otf,
  mc-bx = HaranoAjiMincho-Bold.otf,
  gt-m = HaranoAjiGothic-Regular.otf,
  gt-bx = HaranoAjiGothic-Bold.otf,
  gt-eb = HaranoAjiGothic-Heavy.otf,
  mg-m = HaranoAjiGothic-Heavy.otf}
\ltjapplypreset{HaranoAji}

% pdfx.sty で PDF/A-2u の作成を指定
\usepackage[a-2u]{pdfx}

% LuaTeX で PDF/A-2 を作る際に必要
\pdfvariable omitcidset=1

\begin{document}

\section{節}

本文。

\end{document}
```

まずは以下のように LuaLaTeX を使って `test-pdfa2u.pdf` を作ります。

```
$ lualatex test-pdfa2u.tex
$ lualatex test-pdfa2u.tex
```

得られた `test-pdfa2u.pdf` について
Poppler に含まれている `pdffonts` を使ってフォント情報を表示してみます。

```
$ pdffonts test-pdfa2u.pdf
name                                 type              encoding         emb sub uni object ID
------------------------------------ ----------------- ---------------- --- --- --- ---------
AXWKUP+LMSans12-Regular              CID Type 0C       Identity-H       yes yes yes     14  0
RKUEDA+HaranoAjiGothic-Regular       CID Type 0C       Identity-H       yes yes yes     15  0
OMFKQB+HaranoAjiMincho-Regular       CID Type 0C       Identity-H       yes yes yes     16  0
JFRMQG+LMRoman10-Regular             CID Type 0C       Identity-H       yes yes yes     17  0

$
```

原ノ味フォント（`name` 列に `HaranoAji` が含まれる行）は
`uni` 列が `yes` になっているので ToUnicode CMap が含まれている、
ということがわかります。
また、PDF/A 検証ツール[
veraPDF
](https://verapdf.org/)
にかけてみると検証に合格し正しく PDF/A-2u に準拠していることがわかります。
（PDF/A に準拠したいのに、ここで不合格になる場合は何らかの修正が必要です。
本ツールは不合格になる PDF を合格する PDF へ変換することはできません。）

次に、この PDF を本ツールにかけて
ToUnicode CMap を削除してみることにします。
以下のコマンドを実行します。
本ツールで PDF/A を出力するには `--newline-before-endstream` が必要です
（これは必要条件であって
PDF/A 非準拠ファイルを PDF/A 準拠へ変換するような機能はありません）。
さらにリニアライズ `--linearize` と
PDF 1.5 のオブジェクト・ストリーム有効化 `--object-streams=generate`
（PDF/A-1 の場合は PDF 1.4 までの機能しか使えないので、
これを有効化すると非準拠になってしまい検証に不合格となります）
を使ってみました。
（このあたりの出力用オプションは [QPDF](http://qpdf.sourceforge.net/)
のサブセットになっています。
詳細は QPDF のマニュアルをご覧ください。）

```
$ pdf-rm-tuc --newline-before-endstream --linearize --object-streams=generate \
    test-pdfa2u.pdf test-pdfa2u-notuc.pdf
```

得られた `test-pdfa2u-notuc.pdf` について
Poppler に含まれている `pdffonts` を使ってフォント情報を表示してみます。

```
$ pdffonts test-pdfa2u-notuc.pdf
name                                 type              encoding         emb sub uni object ID
------------------------------------ ----------------- ---------------- --- --- --- ---------
JFRMQG+LMRoman10-Regular             CID Type 0C       Identity-H       yes yes yes     29  0
OMFKQB+HaranoAjiMincho-Regular       CID Type 0C       Identity-H       yes yes no      28  0
RKUEDA+HaranoAjiGothic-Regular       CID Type 0C       Identity-H       yes yes no      27  0
AXWKUP+LMSans12-Regular              CID Type 0C       Identity-H       yes yes yes     26  0

$
```

原ノ味フォント（`name` 列に `HaranoAji` が含まれる行）は
`uni` 列が `no` に変わったので ToUnicode CMap が削除されたことがわかります。
また、ToUnicode CMap 削除とオブジェクト・ストリーム有効化に伴い
ファイルサイズが少し小さく（20 KB → 17 KB）なりました。
テキスト抽出を試してみるため、
Adobe Acrobat Reader で開いて全文選択してコピーし、
メモ帳などのテキストエディタへペーストしてみたところ
文字化けや欠けなどの問題なくコピペできました。
また、PDF/A 検証ツール[
veraPDF
](https://verapdf.org/)
にかけてみたところ検証に合格することができました。

## ライセンス

Copyright (C) 2019 Masamichi Hosoda. All rights reserved.

License: BSD-2-Clause

[LICENSE](./LICENSE) をご覧ください。
