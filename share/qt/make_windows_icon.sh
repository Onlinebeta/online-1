#!/bin/bash
# create multiresolution windows icon
ICON_SRC=../../src/qt/res/icons/online.png
ICON_DST=../../src/qt/res/icons/online.ico
convert ${ICON_SRC} -resize 16x16 online-16.png
convert ${ICON_SRC} -resize 32x32 online-32.png
convert ${ICON_SRC} -resize 48x48 online-48.png
convert online-16.png online-32.png online-48.png ${ICON_DST}

