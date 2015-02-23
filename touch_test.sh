#!/bin/sh

echo '*** modify file'
adb shell 'sleep 20'
adb shell 'echo "foom" >>/data/misc/hmwk6/test_file'
adb shell '/data/misc/file_loc /data/misc/hmwk6/test_file'
echo
echo '*** chmod on file'
adb shell 'sleep 20'
adb shell 'chmod 700 /data/misc/hmwk6/test_file'
adb shell '/data/misc/file_loc /data/misc/hmwk6/test_file'
echo
echo '*** chmod on directory'
adb shell 'sleep 20'
adb shell 'chmod 777 /data/misc/hmwk6/test_dir'
adb shell '/data/misc/file_loc /data/misc/hmwk6/test_dir'
echo
echo '*** file in directory'
adb shell 'sleep 20'
adb shell 'touch /data/misc/hmwk6/test_dir/inner_file'
adb shell '/data/misc/file_loc /data/misc/hmwk6/test_dir'
echo
echo '*** mv on file'
adb shell 'sleep 20'
adb shell 'mv /data/misc/hmwk6/test_file /data/misc/hmwk6/test_file.1'
adb shell '/data/misc/file_loc /data/misc/hmwk6/test_file.1'
echo
echo '*** mv on directory'
adb shell 'sleep 20'
adb shell 'mv /data/misc/hmwk6/test_dir /data/misc/hmwk6/test_dir.1'
adb shell '/data/misc/file_loc /data/misc/hmwk6/test_dir.1'
