#!/bin/sh
git clone http://git.code.sf.net/p/icmake/code icmake/
git clone http://git.code.sf.net/p/bobcat/code bobcat/
git clone http://git.code.sf.net/p/flexcpp/code flexcpp/
git clone http://git.code.sf.net/p/bisoncpp/code bisoncpp/

#apt-get install libbobcat-dev

cd icmake/icmake
./icm_bootstrap /
echo "\n***** icmake bootstrap done *****\n"
./icm_install strip all
echo "\n***** icmake install done *****\n"
cd ../..

#cp -f bisoncpp/bisonc++/CLASSES.bobcat bobcat/bobcat/CLASSES
cd bobcat/bobcat
echo "\nbigint" >> CLASSES
echo "\n\n\n\n" | ./build libraries strip
echo "\n***** bobcat build done *****\n"
./build install
echo "\n***** bobcat install done *****\n"
cd ../..

cd flexcpp/flexc++
./build program strip
echo "\n***** flexcpp build done *****\n"
./build install program
echo "\n***** flexcpp install done *****\n"
./build install skel
echo "\n***** flexcpp skel done *****\n"
cd ../..

cd bisoncpp/bisonc++
./build program strip
echo "\n***** bisoncpp build done *****\n"
./build install
echo "\n***** bisoncpp install done *****\n"
cd ../..

rm -Rf icmake bobcat flexcpp bisoncpp

