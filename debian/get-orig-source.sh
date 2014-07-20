#!/bin/sh

# run this script in the root of the PEBL source tree to build an orig source
# tarball for the current version

# This strips the original PEBL sources of everything that has no value in the
# context of the Debian package. In particular: windows/mac binaries, duplicate
# fonts, compiled documentation, ...

set -e
set -u

uversion=$(grep '^PEBL_VERSION' Makefile | cut -d '=' -f 2,2)

tar --transform "s/^./pebl-language-${uversion}~dfsg.1/" \
    --exclude '*~' \
    --exclude '*.exe' \
    --exclude 'codeblocks' \
    --exclude 'devcpp' \
    --exclude '/pebl/*' \
    --exclude '*.pdf' \
    --exclude 'vc' \
    --exclude 'w32-launcher' \
    --exclude 'xcode' \
    --exclude .svn \
    --exclude .git \
    --exclude 'media/fonts/Caliban*' \
    --exclude 'media/fonts/CaslonBold*' \
    --exclude 'media/fonts/CaslonItalic*' \
    --exclude 'media/fonts/CaslonRoman*' \
    --exclude 'media/fonts/CharisSIL*' \
    --exclude 'media/fonts/DejaVu*' \
    --exclude 'media/fonts/DoulosSILR.ttf' \
    --exclude 'media/fonts/Free*' \
    --exclude 'media/fonts/freefont-COPYING.txt' \
    --exclude 'media/fonts/Gen*' \
    --exclude 'media/fonts/UnBatang*' \
    --exclude 'media/fonts/vera*' \
    --exclude 'media/fonts/Vera*' \
    --exclude 'media/fonts/RELEASENOTES.TXT' \
    --exclude 'media/fonts/wqy-zenhei*' \
    --xz \
    -cvf ../pebl-language_${uversion}~dfsg.1.orig.tar.xz .
