#!/bin/sh

process=$($(adb shell "ps | grep gpsd") | cut -d' ' -f2 -)
kill $process

adb shell "umount /data/misc/hmwk6"
