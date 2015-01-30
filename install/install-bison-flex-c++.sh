#!/bin/sh
git clone http://git.code.sf.net/p/icmake/code icmake/
git clone http://git.code.sf.net/p/bobcat/code bobcat/
git clone http://git.code.sf.net/p/flexcpp/code flexcpp/
git clone http://git.code.sf.net/p/bisoncpp/code bisoncpp/

cd bobcat
git apply ../patches/bobcat.patch
cd ..

cd flexcpp
git apply ../patches/flexcpp.patch
cd ..

cd bisoncpp
git apply ../patches/bisoncpp.patch
cd ..


cd icmake/icmake
./icm_bootstrap /
./icm_install strip all
cd ../..

cp -f CLASSES.bobcat bobcat/bobcat/CLASSES
cd bobcat/bobcat
echo "\n\n\n\n" | ./build libraries strip
./build install
cd ../..

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
