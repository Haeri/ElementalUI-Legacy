#!/usr/bin/env bash

old_path=$(pwd)
cd $(dirname "$0")

cd ..
if [ "$1" = "-static" ]; then
	mkdir lib
	cp ./build/libelem.a* ./lib/

	# ------ Package Examples ------

	# Hello World
	mkdir -p samples/calculator
	cp -R ./build/examples/calculator/res ./samples/calculator
	cp ./build/examples/calculator/calculator ./samples/calculator

	# Overview
	mkdir -p samples/slack
	cp -R ./build/examples/slack/res ./samples/slack
	cp ./build/examples/slack/slack ./samples/slack

else
	mkdir bin
	cp ./build/libelem.so* ./bin/
fi
err=$?


if [ $err -ne 0 ]; then
	exit $err
fi

cd $old_path