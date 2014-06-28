#!/bin/sh
git clone http://git.code.sf.net/p/icmake/code icmake/
git clone http://git.code.sf.net/p/bobcat/code bobcat/
git clone http://git.code.sf.net/p/flexcpp/code flexcpp/
git clone http://git.code.sf.net/p/bisoncpp/code bisoncpp/

icmake/icmake/icm_bootstrap /
icmake/icmake/install strip progs

echo 'n\nn\n' | bobcat/bobcat/build libraries strip
bobcat/bobcat/build install

flexcpp/flexc++/build program strip
flexcpp/flexc++/build install program
flexcpp/flexc++/build install skel

bisoncpp/bisonc++/build program strip
bisoncpp/bisonc++/build install

#rm -Rf icmake bobcat flexcpp bisoncpp

