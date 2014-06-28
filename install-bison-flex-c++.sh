#!/bin/sh
git clone http://git.code.sf.net/p/icmake/code icmake/
git clone http://git.code.sf.net/p/bobcat/code bobcat/
git clone http://git.code.sf.net/p/flexcpp/code flexcpp/
git clone http://git.code.sf.net/p/bisoncpp/code bisoncpp/

cd icmake/icmake
./icm_bootstrap /
./install strip progs
cd ../..

cd bobcat/bobcat
echo 'n\nn\n' | ./build libraries strip
./build install
cd ../..

cd flexcpp/flexc++
./build program strip
./build install program
./build install skel
cd ../..

cd bisoncpp/bisonc++
./build program strip
./build install
cd ../..

#rm -Rf icmake bobcat flexcpp bisoncpp

