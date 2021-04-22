#!/bin/zsh

cmake -E rm -rf Bin		#delete directory Bin
cmake -E rm -rf build		#delete directory build
cmake -E make_directory build   #create directory build
cmake . -B build
cmake -E time cmake --build build
