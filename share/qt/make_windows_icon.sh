#!/bin/bash
# create multiresolution windows icon
ICON_DST=../../src/qt/res/icons/macpuffins.ico

convert ../../src/qt/res/icons/macpuffins-16.png ../../src/qt/res/icons/macpuffins-32.png ../../src/qt/res/icons/macpuffins-48.png ${ICON_DST}
