#!/bin/sh

gcc -o exp exp.c -lpthread
gcc -fno-builtin -static -nostdlib -masm=intel exp.c -o exp
chown 1000:1000 ./exp
mv ./exp fs/exp

cd fs
find ./ | cpio -o > ../rootfs.cpio
