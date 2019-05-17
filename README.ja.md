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
Adobe-Japan1 フォントで、かつ ToUnicode CMap が埋め込まれていない場合は、
PDF viewer が自分で持っている ToUnicode CMap を使ってテキスト抽出します。
この際に使われる `Adobe-Japan1-UCS2` という ToUnicode CMap は、
逆変換の問題が発生しないようにあらかじめ調整されたものなので、
意図しない文字化けなどが発生しにくくなっています。

デフォルトでは、このツールは PDF から
原ノ味フォントの ToUnicode CMap を削除し、
原ノ味フォントの ROS を Adobe-Identity-0 から
元の Adobe-Japan1-7 に変更します。

## 注意

XeTeX を使う場合や pTeX や upTeX で dvipdfmx を使う場合
（xdvipdfmx / dvipdfmx を使う場合）は、
Adobe-Japan1 フォントなら ToUnicode CMap が生成されず埋め込まれませんので
本ツールは不要です。

LuaTeX の出力した PDF に対して使う場合、
ToUnicode CMap を削除するフォントは GID ＝ CID の関係である必要があります。
そうでない場合はテキスト抽出すると文字化けを起こしてしまいます。
原ノ味フォントの場合は 20190501 以降であれば問題ありません。

ToUnicode CMap を削除してしまうと、
`Adobe-Japan1-UCS2` などを持っていない
PDF viewer でテキスト抽出できなくなります。

PDF/A-1a, PDF/A-2a, PDF/A-3a, PDF/A-2u, PDF/A-3u といった
レベル A やレベル U の PDF/A 規格では ToUnicode CMap が必要なので、
削除すると対応ではなくなる可能性があります。

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

## ライセンス

Copyright (C) 2019 Masamichi Hosoda. All rights reserved.

License: BSD-2-Clause

[LICENSE](./LICENSE) をご覧ください。
