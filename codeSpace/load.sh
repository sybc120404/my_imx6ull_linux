#!/bin/bash

echo "start load.sh, load bin to i.mx6ull"
./tools/imxdownload target/target.bin /dev/sdb
echo "done"