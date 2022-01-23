# boot-wrapper-aarch64
This repo contains source cloned from https://kernel.googlesource.com/pub/scm/linux/kernel/git/maz/boot-wrapper-aarch64/


$ autoreconf -i  
$ ./configure --host=aarch64-linux-gnu --with-kernel-dir=/home/pre-built-images/ --with-dtb=</boot-wrapper-aarch64/linux-dtb.dtb --disable-psci --with-cmdline="root=/dev/mmcblk0p2 rootwait console=tty1 console=ttyS0,115200 earlycon=uart8250,mmio32,0xfe215040 elevator=deadline"  

$ make CNTFRQ=54000000  
$ aarch64-linux-gnu-objcopy -O binary linux-system.axf armstub8.bin  


U-boot prompt:
TODO
