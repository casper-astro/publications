## Overview

The PASP uses an iBOB and an iADC to digitize and channelize two
signals. The design breaks up a 400MHz band into 2^k channels and
outputs the spectrum over two 10GbE links. This design produces about
12Gb/s and distributes the channels to 2^n computers.

## Block Diagram

## Simulink Design

This design can be configured at the top level block by specifying 3
parameters:

Number of IPs: The number of ip addresses. This must be a power of 2 to
ensure it is divisible by the number of channels.

Number of Channels: The number of real channels in the FFT. This must be
\<= number of ips (there is no way to split a single channel between
multiple CPUs).

Samples per Packet: The number of 64 bit data blocks to put into a
packet. Each packet has 128 bit header containing a 64 timestamp and 64
bit packet id so the total packet size (in bits) will be
64\*<samples per packet> + 128

Each IP receives a continuous subset of channels.

## Compilation

This design is compiled with a stripped down version of the CASPER LWIP
UDP server <http://casper.berkeley.edu/memos/udp_packetization>. If the
design errors during software compilation, running out of BRAM space,
make sure MAKESMALL is defined in lwiputil.h. This file is located in
the build directory under XPS\_iBOB\_base/drivers/lwip. Refer to
[FAQ](FAQ "wikilink") for more info on this error.

## Download

This design requires Impact 10.1 for downloading. Refer to [MSSGE
Toolflow](MSSGE_Toolflow "wikilink") for more documentation on the
toolflow.

## Configuration

### IBOB

After programming the board, it can be accessed via ethernet. The top IP
address of the board is 192.168.X.X. The bottom 2 triplets are set by
jumpers on the board. Once you can connect successfully to the board
(try pinging the ip to check if it responds) the board can be configured
using netcat via port 7.

Before taking data, the board must be configured. To view all registers
and brams available type (replace 192.168.0.4 with the appropriate IP
address):

    echo listdev | nc -u -w 1 192.168.0.4 7

To set the register pasp/reg\_sync\_period to 102400
    type:

    echo "regwrite pasp/reg_sync_period 102400" | nc -u -w 1 192.168.0.4 7

Multiple commands can be run together by placing them in a file and
sending the file to the board via cat:

    cat pasp_init.txt | nc -u -w 1 192.168.0.4 7

There is an example configuration file in the CASPER SVN repository
<http://casper.berkeley.edu/svn/trunk/projects/pasp/configure/pasp_init.txt>.

#### Sync, Shift, and Bit Selection

    regwrite pasp/reg_sync_period 102400
    
    regwrite pasp/reg_coeff_pol1 4096
    regwrite pasp/reg_coeff_pol2 4096
    
    regwrite pasp/reg_fft_shift 0xffffffff
    
    regwrite pasp/reg_output_bitselect_pol1 2
    regwrite pasp/reg_output_bitselect_pol2 2

#### 10GbE Blocks

This code sets the ip addresses of the 10GbE ports to 192.168.4.10 and
192.168.4.11

    write l xd0000000 xffffffff
    
    setb x40000000
    writeb l 0  x00000060
    writeb l 4  xdd47e301
    writeb l 8  x00000000
    writeb l 12 xc0a8040a
    writeb b x16 x0f
    writeb b x17 xa0
    writeb l x3130 x00000060
    writeb l x3134 xdd47e34d
    writeb b x15 xff
    write l xd0000000 x0
    
    setb x40004000
    writeb l 0  x00000060
    writeb l 4  xdd47e302
    writeb l 8  x00000000
    writeb l 12 xc0a8040b
    writeb b x16 x0f
    writeb b x17 xa0
    writeb l x3130 x00000060
    writeb l x3134 xdd47e34d
    writeb b x15 xff
    write l xd0000000 x0

#### Output IP Addresses

This code sets reg\_ip1 and reg\_ip2 to 192.168.4.2

    regwrite pasp/dist_gbe/ip_ctr/reg_ip1 0xC0A80402
    regwrite pasp/dist_gbe/ip_ctr/reg_port1 4001
    regwrite pasp/dist_gbe/ip_ctr/reg_ip2 0xC0A80402
    regwrite pasp/dist_gbe/ip_ctr/reg_port2 4002

### ROACH

## Packet Format

The packet format depends on the number of channels and number of
computers selected in the simulink design. Each packet will be tagged
with a 64 bit counter (used as a packet timestamp) and a 64 bit channel
id.

Packet header format:

|         |             |
| ------- | ----------- |
| Name    | Size (bits) |
| Counter | 64          |
| ID tag  | 64          |

\===Number of channels = Number of computers=== Each computer will
receive 1 channel. In this case the channel id is equal to the 1-indexed
channel number. Each 64 bit line of data contains the 8 bit real and
imaginary data from the same spectrum calculate for pol 0 and
pol1.

|                       |                            |                       |                            |
| --------------------- | -------------------------- | --------------------- | -------------------------- |
| Spectrum 0 pol 0 real | Spectrum 0 pol 0 imaginary | Spectrum 0 pol 1 real | Spectrum 0 pol 1 imaginary |
| Spectrum 1 pol 0 real | Spectrum 1 pol 0 imaginary | Spectrum 1 pol 1 real | Spectrum 1 pol 1 imaginary |
| etc...                |                            |                       |                            |

### Number of channels \> Number of computers

This design will interleave the channels as well as the pols. In this
example there are 16 computers and 4 ips. Each computer will receive 4
channels. IP 1 receives channels 1-4, IP 2 receives channels 5-8, IP 3
receives channels 9-12, and IP 4 receives channels 13-16.

### Software

    sysctl -w net.core.wmem_max = 838860800
    sysctl -w net.core.rmem_max = 838860800
    sysctl -w net.core.rmem_default = 819260800
    sysctl -w net.ipv4.udp_rmem_min = 8192000
