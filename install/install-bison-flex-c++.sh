#!/bin/sh
git clone https://github.com/fbb-git/icmake icmake/
git clone https://github.com/fbb-git/bobcat bobcat/
git clone https://github.com/fbb-git/flexcpp flexcpp/
git clone https://github.com/fbb-git/bisoncpp bisoncpp/

cd flexcpp
git apply ../patches/flexcpp.patch
cd ..


cd icmake/icmake
./icm_bootstrap /
./icm_install strip all
cd ../..

cp -f CLASSES.bobcat bobcat/bobcat/CLASSES
cd bobcat/bobcat
echo "\n\n\n\n" | ./build libraries strip
./build install LOG:~/.bobcat
cat ~/.bobcat
cd ../..

cd flexcpp/flexc++
./build program strip
./build install LOG:~/.flexcpp bs
cat ~/.flexcpp
cd ../..

cd bisoncpp/bisonc++
./build program strip
./build install LOG:~/.bisoncpp bs
cat ~/.bisoncpp
cd ../..

rm -Rf icmake bobcat flexcpp bisoncpp
