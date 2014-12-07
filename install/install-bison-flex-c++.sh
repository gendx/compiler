#!/bin/sh
git clone http://git.code.sf.net/p/icmake/code icmake/
git clone http://git.code.sf.net/p/bobcat/code bobcat/
git clone http://git.code.sf.net/p/flexcpp/code flexcpp/
git clone http://git.code.sf.net/p/bisoncpp/code bisoncpp/

cd icmake/icmake
./icm_bootstrap /
./icm_install strip all
cd ../..

cp -f CLASSES.bobcat bobcat/bobcat/CLASSES
cp -f patches/fswap bobcat/bobcat/fswap/fswap
cd bobcat/bobcat
echo "\n\n\n\n" | ./build libraries strip
./build install
cd ../..

cp -f patches/startconditions.h flexcpp/flexc++/startconditions/startconditions.h
cp -f patches/scanner.h flexcpp/flexc++/scanner/scanner.h
cd flexcpp/flexc++
./build program strip
./build install program
./build install skel
cd ../..

cd bisoncpp/bisonc++
./build program strip
./build install program
./build install skel
cd ../..

rm -Rf icmake bobcat flexcpp bisoncpp

