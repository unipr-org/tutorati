#!/bin/sh

if [ ! -d bin ]; then
    mkdir bin
else
    rm -rf bin/*
fi

# for a in opt fifo lru clock lfu mfu
# for a in opt fifo lru clock mfu lfu
for a in opt fifo lru clock mfu
do
    gcc -g -std=c18 -W -Wall $@ main.c util.c pra_${a}.c -o bin/pra_${a}
    # gcc -g -std=c18 -W -Wall -DNOISI_PAGE_REFERENCES $@ main.c util.c pra_${a}.c -o bin/pra_${a}
done
