# FPGA device driver (Memory Mapped Kernel)

## Description

A simple linux device driver for FPGA access. This driver provides memory mapped support and can communicate with FPGA designs. The advantage that memory mapping provides is that the system call overhead is completely reduced. However network overhead and the EPB bus bandwidth limitation exists. PowerPC in ROACH is mainly intended for control and monitoring. For larger transactions and performance numbers, the recommendation is to read the data directly from the FPGA through the 10Ge interface.

## Need for an alternate device driver

BORPH software approach incurs system call latencies, which can degrade performance in applications that make frequent short or random accesses to FPGA resources. System calls are function invocations made from user-space in order to request some service from the operating system. Instead of making a series of system calls that involve file I/O, we memory map the FPGA to
the user process address space in the PowerPC. Memory mapping forms an association between the FPGA and the user process memory. In doing so, the abstraction is being moved from the kernel to the user application. The performance of a memory mapped FPGA device is measurably better than the current approach of BORPH which presents a file system of hardware mapped registers. The contribution of a memory-mapped approach is two-fold: Firstly, the overhead of a system call performing I/O operations is eliminated. Secondly, unnecessary memory copies are not kept in the kernel. While the approach gives a performance benefit, it comes with the limitation that user applications are required to track and provide FPGA symbolic register name to memory to offset mapping. This limitation can be overcome by automating the mapping at FPGA design compile time in the same way as is currently done for BORPH, thereby abstracting this limitation away from ordinary users

## Advantages
* Latest kernel support(Linux 3.10)
* mmap method support
* Improved performance
* support for both ROACH and ROACH2 platforms

## Implications
* Experimental
(Let me know feedback at shanly@ska.ac.za to iron out bugs)

## Usage

The linux kernel communicates with the FPGA through special files called "device nodes". There are two device nodes to be created. 
* /dev/roach/config (FPGA configuration)
* /dev/roach/mem (FPGA read write)

tcpborphserver3 communicates with FPGA through these device specific nodes.

* telnet ip-address portno 
You will see the katcp commands by issuing ?help

## Kernel Source

* https://github.com/ska-sa/roach2_linux
There is a working config file incase you struggle to build the kernel image from the source on your own.
NOTE: Depending on platform use roach or roach2.
** make 44x/roach_defconfig (for roach2, make 44x/roach2_defconfig)
** make cuImage.roach (for roach2, make cuImage.roach2)
(The kernel binary built can be located in arch/powerpc/boot/cuImage.roach)
The driver can be found in drivers/char/roach directory.

##Steps to follow##
1. Build the kernel binary from source as indicated above OR use the provided kernel precompiled binary(uImage-roach-mmap) available after checking out the git repository below
    1. git clone https://github.com/shanlyrajan/roach2_linux
    2. Note the two files uImage-roach-mmap and test_mmap_RW after checking out.
2. Run the below macro in uboot assuming you are nfs booting and you have placed the uImage-roach-mmap file in location from where tftp can fetch it.
    1. setenv roachboot "dhcp;tftpboot 0x2000000 uImage-roach-mmap; setenv bootargs console=ttyS0,115200 root=/dev/nfs ip=dhcp;bootm 0x2000000"
    2. saveenv to save the created macro to flash
    3. run roachboot
3.  Ignore the fatal module dep warning that you see after booting the kernel. After kernel boots in init prompt type the following. Once netbooted, mount the nfs filesystem rw. Create device files if not created, /dev/roach/config that is the programming bitstream interface and /dev/roach/mem that is the memory mapped read/write interface using mknod.
    1. cat /proc/devices (To see whether driver is loaded and check the major number associated with it. I would expect you to see 252 major number)
    2. mount -o rw,remount /
    3. mkdir /dev/roach
    4. mknod /dev/roach/config c 252 0
    5. mknod /dev/roach/mem c 252 1
    6. mount -o ro,remount /
4. Use tcpborphserver3 available along with KATCP which has registername to offset support logic.
    1. Issue katcp commands like ?progdev x.bof, ?listdev, ?wordread and ?wordwrite for communicating with designs.

##Reference userspace code##
The test_mmap_RW.c available in the checked out source code, performs reading, writing and verifying the scratchpad register half a million times. 
The code can be used as a reference and adapted to read data out of BRAMs and send as UDP packets.
Note: The c file has to be cross-compiled to run on powerpc platform and then the executable can run on the PowerPC itself.
Core_info.tab is the authoritative source for checking the register name and memory offset into FPGA.
