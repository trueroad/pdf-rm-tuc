#!/bin/sh

PDF="$1"
BASENAME=`basename ${PDF} .pdf`

${PDFFONTS} ${PDF} | ${GREP} "HaranoAji" \
    > ${BASENAME}.pdffonts.grep1.txt
${GREP} "yes\s\s*yes\s\s*yes" ${BASENAME}.pdffonts.grep1.txt \
    > ${BASENAME}.pdffonts.grep2.txt

if [ ! -s ${BASENAME}.pdffonts.grep2.txt ]; then
    exit 1
fi

${DIFF} -ubwBE ${BASENAME}.pdffonts.grep1.txt ${BASENAME}.pdffonts.grep2.txt
