#!/usr/bin/env bash

old_path=$(pwd)
cd $(dirname "$0")

cd ..
rm -rf build
mkdir build
cd build

cmake .. -DVCPKG_TARGET_TRIPLET=x64-linux -DOVERLAY_PORTS="../extern/custom-ports"

err=$?

if [ $err -ne 0 ] ; then
	exit $err
fi

cd $old_path