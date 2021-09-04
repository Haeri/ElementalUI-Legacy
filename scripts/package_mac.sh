#!/usr/bin/env bash

old_path=$(pwd)
cd $(dirname "$0")

cd ..
if [ "$1" = "-static" ]; then
	mkdir lib
	cp ./build/Release/libelem*.a ./lib/

	# ------ Package Examples ------

	# Hello World
	mkdir -p samples/calculator
	cp -R ./build/examples/calculator/res ./samples/calculator
	cp ./build/examples/calculator/Release/calculator ./samples/calculator

	# Overview
	mkdir -p samples/slack
	cp -R ./build/examples/slack/res ./samples/slack
	cp ./build/examples/slack/Release/slack ./samples/slack
else
	mkdir bin
	cp ./build/Release/libelem*.dylib ./bin/
fi
err=$?


if [ $err -ne 0 ]; then
	exit $err
fi

cd $old_path