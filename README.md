# boot-wrapper-aarch64
This repo contains source cloned from https://kernel.googlesource.com/pub/scm/linux/kernel/git/maz/boot-wrapper-aarch64/

# How to compile for rpi4

$ autoreconf -i  
$ ./configure --host=aarch64-linux-gnu --with-kernel-dir=/home/pre-built-images/ --with-dtb=</boot-wrapper-aarch64/linux-dtb.dtb --disable-psci --with-cmdline="root=/dev/mmcblk0p2 rootwait console=tty1 console=ttyS0,115200 earlycon=uart8250,mmio32,0xfe215040 elevator=deadline"  

$ make CNTFRQ=54000000  
$ aarch64-linux-gnu-objcopy -O binary linux-system.axf armstub8.bin  

# Execution with u-boot support  

$ ext2load mmc 0:2 $address armstub8.bin  
$ go $address

Note that $address must be the base address used in the device-tree, as shown in the memory node of the dts.  
  
memory@0 {  
		device_type = "memory";  
		reg = <0x00 $address 0x1000000>;  
};  
