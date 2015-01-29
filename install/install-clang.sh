#!/bin/sh
add-apt-repository -y ppa:ubuntu-toolchain-r/test
apt-add-repository 'deb http://llvm.org/apt/precise/ llvm-toolchain-precise main'
wget -O - http://llvm.org/apt/llvm-snapshot.gpg.key | apt-key add -
apt-get update -qq
update-alternatives --install /usr/bin/clang clang /usr/bin/clang-3.5 90
update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-3.5 90

