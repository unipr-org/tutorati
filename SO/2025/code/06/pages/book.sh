#!/bin/sh

if [ ! -d bin ]; then
    mkdir bin
else
    rm -rf bin/*
fi


for a in opt dummy fifo lru lfu mfu
do
    gcc -g -std=c18 -W -Wall -DVERBOSE=1 -DNUM_FRAMES=3 -DNUM_PAGES=8 bookmain.c util.c pra_${a}.c -o bin/bookpra_${a}
done
