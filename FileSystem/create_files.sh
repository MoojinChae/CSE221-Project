dd if=/dev/urandom of=./random4K bs=4096 count=1
dd if=/dev/urandom of=./random8K bs=4096 count=2
dd if=/dev/urandom of=./random16K bs=4096 count=4
dd if=/dev/urandom of=./random32K bs=4096 count=8
dd if=/dev/urandom of=./random64K bs=4096 count=16
dd if=/dev/urandom of=./random128K bs=4096 count=32
dd if=/dev/urandom of=./random256K bs=4096 count=64
dd if=/dev/urandom of=./random512K bs=4096 count=128
dd if=/dev/urandom of=./random1M bs=4096 count=256
dd if=/dev/urandom of=./random2M bs=4096 count=512
dd if=/dev/urandom of=./random4M bs=4096 count=1024
dd if=/dev/urandom of=./random8M bs=4096 count=2048
dd if=/dev/urandom of=./random16M bs=4096 count=4096
dd if=/dev/urandom of=./random32M bs=4096 count=8192
dd if=/dev/urandom of=./random64M bs=4096 count=16384
dd if=/dev/urandom of=./random128M bs=4096 count=32768
dd if=/dev/urandom of=./random256M bs=4096 count=65536

