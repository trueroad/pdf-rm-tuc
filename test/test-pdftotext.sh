#!/bin/sh

TESTFILE="$1"
BASENAME=`basename ${TESTFILE} | sed -e "s/-testtext\.pdftotext$//"`
EXPECTED=${BASENAME}-expected.pdftotext

if [ ! -e "${EXPECTED}" ]; then
    EXPECTED=${srcdir}/${BASENAME}-expected.pdftotext
fi   

${DIFF} -ubwBE ${EXPECTED} ${TESTFILE}
