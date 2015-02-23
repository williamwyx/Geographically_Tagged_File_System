#!/bin/sh

# Meant to be run from the hwmk6 root directory
MYMK="./userspace/e2fsprogs/misc/mke2fs"

dd if=/dev/zero of=hmwk6.fs bs=1M count=2

sudo losetup /dev/loop0 hmwk6.fs
sudo ${MYMK} -I 256 -t ext3 -L w4118.hmwk6 /dev/loop0
sudo losetup -d /dev/loop0
