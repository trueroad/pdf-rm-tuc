<!-- -*- coding: utf-8 -*- -->
# Remove ToUnicode CMap from PDF

[ [Japanese (日本語)](./README.ja.md) / English ]

[
https://github.com/trueroad/pdf-rm-tuc
](https://github.com/trueroad/pdf-rm-tuc)

This tool removes specified font's ToUnicode CMap from PDF.
Also it changes the font's ROS.

If you use LuaTeX with an Adobe-Japan1 font like
[
HaranoAji Fonts
](https://github.com/trueroad/HaranoAjiFonts),
it embeds the font as Adobe-Identity-0 and generates ToUnicode CMap
for the output PDF.
ToUnicode CMap is a CID-to-Unicode mapping table,
used to extract Unicode text from PDF.
In the case of Adobe-Identity-0 font,
ToUnicode CMap embedding is necessary to extract text from PDF.
However, in the case of Adobe-Japan1 font, embedding is not necessary.

By the default, this tool removes HaranoAji font's ToUnicode CMap
and changes the font's ROS from Adobe-Identity-0 to original Adobe-Japan1-7.

## Usage

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

## Build & install

* Required
    + C++11 compiler (g++ 4.9+ etc.)
    + [libqpdf](http://qpdf.sourceforge.net/)
    + Autotools, pkg-config etc.

```
$ ./autogen.sh
$ mkdir build
$ cd build
$ ../configure
$ make
$ make install
```

## License

Copyright (C) 2019 Masamichi Hosoda. All rights reserved.

License: BSD-2-Clause

See [LICENSE](./LICENSE).
