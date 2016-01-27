# CSE221-Project
=================

**Compile Kernel Module**

In home directory(/home/pi),

1. sudo rpi-update && sudo reboot
2. sudo wget https://raw.githubusercontent.com/notro/rpi-source/master/rpi-source -O /usr/bin/rpi-source && sudo chmod +x /usr/bin/rpi-source
3. rpi-source --skip-gcc
4. copying kernel directory(with files) into home directory(/home/pi/kernel)
5. make
6. sudo make install
7. sudo depmod
8. sudo insmod kernel_module.ko

**How to Execute**

1. make
2. ./run