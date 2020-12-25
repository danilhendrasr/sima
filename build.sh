#! /usr/bin/bash

[[ ! -d ./dist/ ]] && mkdir dist
g++ -o dist/sima main.cpp
dist/./sima
