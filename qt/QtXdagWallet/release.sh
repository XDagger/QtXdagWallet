#!/bin/sh
cp release/xdagwallet .
rm release/* -rf
mv xdagwallet release/
cp xdaglogo.png xdag.desktop release/
linuxdeployqt release/xdagwallet -appimage -qmake=/opt/Qt5.9.1/5.9.1/gcc_64/bin/qmake 
