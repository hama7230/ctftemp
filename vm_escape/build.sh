#!/bin/sh
gcc -o exp -static -nostdlib -masm=intel exploit.c && gzip -kf exp &&  base64 exp.gz
# cat e | base64 -d | gunzip > exp && chmod +x exp && ./exp
