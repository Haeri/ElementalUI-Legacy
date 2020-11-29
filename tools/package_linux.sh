#!/usr/bin/env bash

old_path=$(pwd)
cd $(dirname "$0")

cd ..
if [ "$1" = "-static" ]; then
	mkdir lib
	cp ./build/libelem.a* ./lib/ 	
else
	mkdir bin
	cp ./build/libelem.so* ./bin/
fi
err=$?


if [ $err -ne 0 ]; then
	exit $err
fi

cd $old_path