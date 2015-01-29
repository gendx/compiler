#!/bin/sh
add-apt-repository -y ppa:ubuntu-toolchain-r/test
apt-get update -qq
apt-get install -qq g++-4.9
update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.9 90

