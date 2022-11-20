#!/bin/bash
./dlc bits.c
make clean
make btest
if [ $? -ne 0 ]; then
    echo "make failed!"
    exit 1
fi

if [ $# -gt 0 ]; then
    ./btest -f $1
else
    ./btest
fi