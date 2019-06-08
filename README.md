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
Remove ToUnicode CMap from PDF 1.0.0
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

## Install from [source tarball](https://github.com/trueroad/pdf-rm-tuc/releases/download/v1.0.0/pdf-rm-tuc-1.0.0.tar.gz)

### Required

* C++11 compiler (g++ 4.9+ etc.)
* [libqpdf](http://qpdf.sourceforge.net/)
* pkg-config etc.

When you would like to use packages for preparing the required library,
the following might be convenient.

* Debian / Ubuntu
    + libqpdf-dev
* Fedora
    + qpdf-devel
* Cygwin
    + libqpdf-devel

### Build & install

```
$ ./configure
$ make
$ make install
```

If you have `pdffonts`, `pdftotext`, and `diff` etc.,
you can run tests before installation as follows.
(`pdffonts` and `pdftotext` are contained in
[Poppler](https://poppler.freedesktop.org/).)

```
$ ./configure
$ make
$ make check
$ make install
```

## Install from [Git repository](https://github.com/trueroad/pdf-rm-tuc)

Source tarball build requirements and additional requirements are necessary.

### Additional required

* Autoconf 2.69+
* Automake

### Additional recommended

* LuaTeX (for generating test PDFs)
* [
HaranoAji Fonts
](https://github.com/trueroad/HaranoAjiFonts)
(for generating test PDFs)

### Build & install

```
$ git clone https://github.com/trueroad/pdf-rm-tuc.git
$ cd pdf-rm-tuc
$ ./autogen.sh
$ mkdir build
$ cd build
$ ../configure
$ make
$ make check
$ make install
```

## License

Copyright (C) 2019 Masamichi Hosoda. All rights reserved.

License: BSD-2-Clause

See [LICENSE](./LICENSE).
