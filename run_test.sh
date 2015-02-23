#!/bin/sh

echo "Making file system"
./make_fs.sh

echo "Doing the sym links"
./ln_loop.sh

# Doesn't seem to work, do daemon work by hand.
echo "Building the daemon"
make -C ./userspace/gpsd/
adb push ./userspace/gpsd/gpsd /data/misc/

echo "Starting up daemon"
adb shell "
sleep 5
/data/misc/gpsd
sleep 5
"

echo "Creating test_file and test_dir on new file system"
adb shell "touch /data/misc/hmwk6/test_file"
adb shell "mkdir /data/misc/hmwk6/test_dir"

echo "Building file_loc"
make -C ./userspace/file_loc/
adb push ./userspace/file_loc/file_loc /data/misc/

echo "file_loc for file"
adb shell "/data/misc/file_loc /data/misc/hmwk6/test_file"
echo "file_loc for dir"
adb shell "/data/misc/file_loc /data/misc/hmwk6/test_dir"
