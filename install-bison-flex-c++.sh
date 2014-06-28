#!/bin/sh
git clone http://git.code.sf.net/p/icmake/code icmake/
git clone http://git.code.sf.net/p/bobcat/code bobcat/
git clone http://git.code.sf.net/p/flexcpp/code flexcpp/
git clone http://git.code.sf.net/p/bisoncpp/code bisoncpp/

cd icmake/icmake
./icm_bootstrap /
echo "\n***** icmake bootstrap ok *****\n"
./icm_install strip progs
echo "\n***** icmake install ok *****\n"
cd ../..

cp -f flexcpp/flexc++/CLASSES.bobcat bobcat/bobcat/CLASSES

cd bobcat/bobcat
echo "\n\n\n\n" | ./build libraries strip
echo "\n***** bobcat build ok *****\n"
./build install
echo "\n***** bobcat install ok *****\n"
cd ../..

cd flexcpp/flexc++
./build program strip
echo "\n***** flexcpp build ok *****\n"
./build install program
echo "\n***** flexcpp install ok *****\n"
./build install skel
echo "\n***** flexcpp skel ok *****\n"
cd ../..

cd bisoncpp/bisonc++
./build program strip
echo "\n***** bisoncpp build ok *****\n"
./build install
echo "\n***** bisoncpp install ok *****\n"
cd ../..

rm -Rf icmake bobcat flexcpp bisoncpp

