TESTS = $(TESTPDFFONTS) $(TESTPDFTOTEXT)

TEST_EXTENSIONS = .pdffonts .pdftotext

PDFFONTS_LOG_COMPILER = $(srcdir)/test-pdffonts.sh
PDFTOTEXT_LOG_COMPILER = $(srcdir)/test-pdftotext.sh

TESTS_ENVIRONMENT = top_builddir=$(top_builddir) \
	srcdir=$(srcdir) \
	GREP=$(GREP) \
	DIFF=$(DIFF) \
	PDFFONTS=$(PDFFONTS) \
	PDFTOTEXT=$(PDFTOTEXT)

# Source files for test PDFs
TESTTEXS = ascii.tex ascii-mix.tex kanji.tex kanji-mix.tex
# Test PDFs
TESTPDFS = $(TESTTEXS:.tex=.pdf)

# Tests by pdffonts
TESTPDFFONTS = $(TESTPDFS:.pdf=-testfont.pdffonts)
# Tests by pdftotext
TESTPDFTOTEXT = $(TESTPDFS:.pdf=-testtext.pdftotext)

# Test scripts and test PDFs
EXTRA_DIST = test-pdffonts.sh test-pdftotext.sh check-testpdf.sh \
	$(TESTTEXS) $(TESTPDFS) \
	$(TESTPDFS:.pdf=-expected.pdftotext)

# For `make clean'
CLEANFILES = $(TESTTEXS:.tex=.log) \
	$(TESTPDFFONTS) $(TESTPDFTOTEXT) \
	$(TESTPDFS:.pdf=-test.pdf) \
	$(TESTPDFFONTS:=.grep1.txt) $(TESTPDFFONTS:=.grep2.txt)

# Generate test PDFs
# Tarball contains them for convenience.
%.pdf: %.tex
	$(LUATEX) -halt-on-error -interaction=nonstopmode -file-line-error $<

# Expected pdftotext
# Tarball contains them for convenience.
%-expected.pdftotext: %.pdf
	GREP=$(GREP) DIFF=$(DIFF) PDFFONTS=$(PDFFONTS) \
		$(srcdir)/check-testpdf.sh $<
	$(PDFTOTEXT) $< $@

# Test PDFs
%-test.pdf: %.pdf
	${top_builddir}/src/pdf-rm-tuc $< $@

# Test pdffonts
%-testfont.pdffonts: %-test.pdf
	$(PDFFONTS) $< > $@

# Test pdftotext
%-testtext.pdftotext: %-test.pdf %-expected.pdftotext
	$(PDFTOTEXT) $< $@

.PRECIOUS: %-test.pdf %-testfont.pdffonts %-testtext.pdftotext
