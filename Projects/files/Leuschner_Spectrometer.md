# People

Prof. Geoff Bower

Prof. Carl Heiles

Dan Werthimer

Attila Kabai

James McBride

[Andrew Siemion](User:siemion "wikilink")

## Description

### Version 1

This IBOB-based spectrometer design has been optimized for narrow band,
high resolution spectroscopy. Compiled for a sampling rate of 96
Msamp/sec, three of four parallel times samples are dropped to yield a
12 MHz bandwidth. A 16384 channel PFB is performed, followed by 64
bits/channel vector accumulation of only the 8192 negative frequencies.
A selectable 32 bits/channel of each accumulated spectrum is written to
shared memory for output over 100Mbit ethernet. In the complete system,
the sky frequency is mixed down to a 150MHz IF, passed through a 150/10
bandpass filter and the 12 MHz region 144-156 MHz aliases down to
baseband.

### Version 2

Week 1: Introduction to single-dish radio astronomy, single-dish radio
astronomy instrumentation, ADCs and DSP

Week 1-2: Training using step-by-step CASPER tutorials - blink-a-light,
ADC sampling, channelization.

Week 2-3: Back-end software development - (IDL, Python, Matlab and/or C
- depending on student's experience)

Week 3-4: Spectrometer design, compilation, gateware simulation

Week 4-5: Instrument characterization: Introduction to laboratory
electronics equipment; oscilloscopes, signal generators, spectrum
analyzers

Week 5-6: Instrument characterization: Testing with laboratory noise
sources, plotting results

Week 7-8: Deployment at Leuschner Observatory

Week 8-9: 21 cm observations

Week 9-10: Depending on progress, observations of OH maser emission,
Crab pulsar giant pulses, ??

## Specifications

|                     |                                                |
| ------------------- | ---------------------------------------------- |
| Frequency channels: | 8192 (16384 real samples per spectrum)         |
| Clock input:        | 96 MHz                                         |
| Signal input:       | 144 to 156 MHz (13th Nyquist zone)             |
| Integration time:   | \~ 25 ms                                       |
| Polyphase filter:   | 4taps, Hamming window                          |
| Output:             | 100 Mbit Ethernet, 32-bit per spectral channel |
| Libraries used:     | mlib\_legacy 7.1 (pink blocks)                 |
| hardware:           | iBOB, iADC                                     |

## Leuschner Specific

### Configure iBOB

``` text
siemion$ ssh -XAY -p 3000 root@leuschner.berkeley.edu
Password: 
Warning: No xauth data; using fake authentication data for X11 forwarding.
Last login: Thu Apr  8 12:18:11 2010 from mercury.berkeley.edu
Have a lot of fun...
/usr/bin/xauth:  creating new authority file /root/.Xauthority

heiles:~/radiolab/spec_code/bin # ./poco_conf
Usage: ./poco_conf CONFIG_FILE IBOB_IP_ADDRESS
ibob will send packets to 169.254.128.10

heiles:~/radiolab/spec_code/bin # ./poco_conf ../../config.heiles 169.254.128.1
Trying host: 169.254.128.1
Port open, sending data to iBob
Communication with iBob good... 
Opened configuration file ../../config.heiles
configuring ibob: 169.254.128.1
Sending packets to 169.254.128.10
Done... 
```

### Check if ibob is sending UDP traffic

``` text
heiles:~/radiolab/spec_code/bin # ifconfig eth0 | grep RX
          RX packets:38440685 errors:0 dropped:0 overruns:0 frame:0
          RX bytes:3262325846 (3111.1 Mb)  TX bytes:100336043 (95.6 Mb)

heiles:~/radiolab/spec_code/bin # ifconfig eth0 | grep RX
          RX packets:38440781 errors:0 dropped:0 overruns:0 frame:0
          RX bytes:3262430582 (3111.2 Mb)  TX bytes:100337231 (95.6 Mb)
```

### Collect data and instantiate plotter

``` text
heiles:~/radiolab/spec_code/bin # ./udprec &
[1] 20224
spec_data, 1, 2441
Beginning to write to file spec_data0.log
heiles:~/radiolab/spec_code/bin # ./specplot spec_data0.log 
```

## Models and Software

The Leuschner Spectrometer SVN repository is located at
<http://casper.berkeley.edu/svn/trunk/projects/leuschner_spec>

<b>Note:</b>You will have to hack in the main.c file from the
ppc\_source directory, making appropriate changes to register names in
order to compile this design. If you have any questions about this
procedure, email Andrew Siemion or the CASPER mailing list.

## Configuration

## Packet Format

Note: The text below is from an email description.

In order to fully describe the packet format of the files created by the
udprec program, it is useful to first examine the way in which
packetization takes place on the IBOB itself.

During configuration of the spectrometer, you may recall that one of the
registers we set was ‘sync\_gen/period.’ This register sets the period,
in clock cycles, for a signal, called a sync pulse, that propagates
through the spectrometer defining the start (and end) of an
accumulation. As we discussed, the spectrometer is constantly performing
FFTs over the window size (16k samples), and the sync pulse determines
how many of these FFTs are summed together each time a spectra is
written out to a shared memory region of the FPGA. For example, if the
period is set to 128k clock cycles, 128k/16k == 8 individual spectra are
summed for each accumulation. In addition to triggering a write to
shared memory, the sync pulse increments a software register, called
‘acc\_num,’ which keeps count of how many sync pulses have been
received.

An important point to note is that the above process is happening
CONSTANTLY while the spectrometer is operating, regardless of whether or
not any data is being sent out over the ethernet port.

A side note is that although the sync pulse period can theoretically be
set to arbitrary values that are an appropriate multiple of the fft
window size, we have to make sure that we can actually egress data out
of the instrument fast enough to catch up with the next accumulation.
For example, in the case above, it would not be possible to output an
entire 8k spectra over the 100Mbit ethernet port within 128k clock
cycles. The maximum data rate for the 100Mbit ethernet port is about
7Mbits per second, which requires accumulations be no shorter than about
50msec.

When the ‘startudp’ command is issued to the spectrometer, an onboard
powerpc processor takes note of the current value of the ‘acc\_num’
register and watches for it to increment by one, indicating that a sync
pulse has been received and a new spectra full of data is waiting in the
shared memory region. At this point the processor individually creates
and sends 32 UDP packets, each of which contains 256 of 8192 channels of
the spectrum. As soon as it is done sending those 32 packets, the
processor watches the acc\_num register for a change, and then repeats
the process.

Each payload of the 32 packets sent for each spectra has the following
format:

``` text
Total size: 1045 bytes (21 bytes header + 1024 bytes data) (we will call these bytes 0 through 1044)

Bytes 4, 5, 6, 7 contain a 4 byte unsigned integer equal to the accumulation number for a given spectrum. (accnum)

Bytes 9, 10, 11, 12 contain a 4 byte unsigned integer equal to the packet vector number (0 – 31) which is incremented for each of the 32 packets sent. (vecnum)

Bytes 21 – 1044 contain a series of 256 4 byte unsigned integers representing the 256 spectral channels starting at bin number 256 * vecnum  
```

Although the ACTUAL packets that are sent over the wire contain
additional headers to the 1045 byte payloads, the udprec program strips
all of that data off and only outputs the 1045 byte payloads to its .log
output file.

As you might have guessed, you should expect to receive 32 total packets
for each accnum, and accnum should increment by 1 every 32 packets.
However, because you can never be sure whether or not the udprec program
began recording packets during a 32 packet dump, the first spectra in
each blah.log file might be incomplete. Thus its usually a good idea to
read through the file a few packets until you reach a packet with vecnum
equal to zero (indicating it is the beginning of a new spectrum), and
begin converting data at that point.

Here is the c code I use to convert from the binary payloads to the
values discussed above (payload is a 1045 byte char array containing a
packet payload):

``` c
vector_number = (((unsigned int) payload[12])%256);
vector_number += (((unsigned int) payload[11])%256) * 256;
vector_number += (((unsigned int) payload[10])%256) * 65536;
vector_number += (((unsigned int) payload[9])%256) * 16777216;

accumulation_number = (((unsigned int) payload[4])%256);
accumulation_number += (((unsigned int) payload[5])%256) * 256;
accumulation_number += (((unsigned int) payload[6])%256) * 65536;
accumulation_number += (((unsigned int) payload[7])%256) * 16777216;

for(j=0;j<256;j++){
 placeholder[0] = payload[21 + (j*4)];
 placeholder[1] = payload[21 + (j*4) + 1];
 placeholder[2] = payload[21 + (j*4) + 2];
 placeholder[3] = payload[21 + (j*4) + 3];
 spectral_value = *(long*) placeholder;
}
//(spectral_value is a long int)
```

## Application

The Leuschner Spectrometer is used for [undergraduate student radio
astronomy instruction](http://ugastro.berkeley.edu/radio/index.html) at
UC Berkeley in conjunction with a 4.5m dish at Leuschner Observatory in
Lafayette, California. Primarily this system is used for 21cm work, but
occasionally OH observations are performed as well.

### Leuschner Dish Specifications

Coordinates:

Longitude = -122° 9' 12.31" (East)

Latitude = +37.8732° = +37° 55' 10.07"

Pacific Standard Time = Universal Time + 8 hours

Dish Diameter: 3.6 m

Frequency Range: 1320 - 1740 MHz with a 110 MHz bandwidth

  

Image:FCLnu5rG\_alt\_limit.pdf.png|[Vector version of
alt\_limit.pdf](Media:FCLnu5rG_alt_limit.pdf "wikilink")
Image:Kv8u3r6e\_Leuschner\_circuit.png|Leuschner\_circuit.png
Image:\_23v91rk\_rpa.pdf.png|[Vector version of
rpa.pdf](Media:_23v91rk_rpa.pdf "wikilink")

</gallery>

<b>The Leuschner Radio Dish was originally part of the Rapid Prototype
Array (RPA) - a pathfinder for the Allen Telescope Array. The
documentation below describes technical details of the site, antenna and
receiver.</b>

#### RPA Technical Documentation

[RPA Technical Documentation \#1](Media:RPA1.pdf "wikilink") (from the
Dave DeBoer Library)

[RPA Technical Documentation \#2](Media:RPA2.pdf "wikilink") (from the
Dave DeBoer Library)

[RPA Technical Documentation \#3](Media:RPA3.pdf "wikilink") (from the
Dave DeBoer Library)

[RPA Technical Documentation \#4](Media:RPA4.pdf "wikilink") (from the
Dave DeBoer Library)

[RPA Technical Documentation \#5](Media:RPA5.pdf "wikilink") (from the
Dave DeBoer Library)

[RPA Technical Documentation \#6](Media:RPA6.pdf "wikilink") (from the
Dave DeBoer Library)

[RPA Technical Documentation \#7](Media:RPA7.pdf "wikilink") (from the
Dave DeBoer Library)

[RPA Technical Documentation \#8](Media:RPA8.pdf "wikilink") (from the
Dave DeBoer Library)

[RPA Technical Documentation \#9](Media:RPA9.pdf "wikilink") (from the
Dave DeBoer Library)

[RPA Technical Documentation \#10](Media:RPA10.pdf "wikilink") (from the
Dave DeBoer Library)

[RPA Technical Documentation \#11](Media:RPA11.pdf "wikilink") (from the
Dave DeBoer Library)

[RPA Technical Documentation \#12](Media:RPA12.pdf "wikilink") (from the
Dave DeBoer Library)

### Curriculum

[21cm Lab](http://ugastro.berkeley.edu/docs/radio/HI1.ps)

[Data Collection Procedures (UCB
Specific)](http://ugastro.berkeley.edu/radio/leuschner/spechowto.pdf)

[An exemplary student lab](Media:RW8Qe8h1_astro_121_lab4.pdf "wikilink")
by Adam Fries utilizing the Leuschner Spectrometer (UCB Undergrad 2009)

  

Image:FCLnu5rG\_leus\_spec.pdf.png|[Vector version of
leus\_spec.pdf](Media:FCLnu5rG_leus_spec.pdf "wikilink")
