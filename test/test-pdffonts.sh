#!/bin/sh

TESTFILE="$1"
BASENAME=`basename ${TESTFILE} | sed -e "s/-testfont\.pdffonts$//"`

${GREP} "HaranoAji" ${TESTFILE} \
    > ${BASENAME}-testfont.pdffonts.grep1.txt
${GREP} "yes\s\s*yes\s\s*no" ${BASENAME}-testfont.pdffonts.grep1.txt \
    > ${BASENAME}-testfont.pdffonts.grep2.txt

if [ ! -s ${BASENAME}-testfont.pdffonts.grep2.txt ]; then
    exit 1
fi

${DIFF} -ubwBE ${BASENAME}-testfont.pdffonts.grep1.txt \
    ${BASENAME}-testfont.pdffonts.grep2.txt
