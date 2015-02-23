#!/bin/sh

echo "Only run if the device is fully booted"
# Meant to be run from hmw6-prog root directory

# Note this will fail if you run it as second time since
# the links have already been created.
adb shell ln -s /dev/block/loop0 /dev/loop0
adb shell ln -s /dev/block/loop1 /dev/loop1
adb shell ln -s /dev/block/loop2 /dev/loop2
adb shell ln -s /dev/block/loop3 /dev/loop3
adb shell ln -s /dev/block/loop4 /dev/loop4
adb shell ln -s /dev/block/loop5 /dev/loop5
adb shell ln -s /dev/block/loop6 /dev/loop6
adb shell ln -s /dev/block/loop7 /dev/loop7

adb push hmwk6.fs /data/misc
adb shell "mkdir -p /data/misc/hmwk6"
adb shell "mount -o loop -t ext3 /data/misc/hmwk6.fs /data/misc/hmwk6"
