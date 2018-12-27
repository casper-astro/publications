This 1 GHz Wide-band Spectrometer, designed by Glenn Jones as part of
the GAVRT effort, utilizes a single iBOB and iADC to sample a single
input at 2048 Msamples/sec and perform a 1024 channel 2-tap PFFT.

## Source Files

## Specifications

|                     |                                       |
| ------------------- | ------------------------------------- |
| Frequency channels: | 1024 (2048 real samples per spectrum) |
| Clock input:        | 512 to 1024 MHz                       |
| Signal input:       | DC - 1024 MHz                         |
| Integration time:   | variable (min \~ 50 mS)               |
| Polyphase filter:   | 2taps, Hamming window                 |
| Output:             | 100 Mbit Ethernet                     |
| Libraries used:     | mlib\_devel 7.1 05/01/09              |

## Documentation

<b>Initialization Commands:</b>

``` text
regwrite cfgspec/vacc/acc_len 39999
```

This sets the integration time to 40000 spectra (each spectrum takes 256
FPGA clocks and the FPGA clock rate is 1/4 of whatever you drive the ADC
with)

``` text
regwrite period 10239998
```

This must be set to exactly acc\_len \* 256 - 2

``` text
startudp 192 168 0 10 59000 24
```

This sends to 192.168.0.10 with destination port 59000. The 24 enables
both dumping spectra and raw ADC values.

<b>Packet Format:</b>

UDP Packets with data payload length of 1048 24 bytes of header 1024
bytes raw data

Packets represent a collection of BRAMs associated with a Spectrometer
function.

A BRAM is always 4 bytes (32 bits wide).

Header Format:

``` text
Byte    Type    Descr., Example
0       uint8   BRAM Label, eg. "S" or "A"
1       uint8   Reserved
2       uint8   This BRAM number
3       uint8   Total number of BRAMS of this Label
4-5     uint16  Offset into this BRAM in 4 byte words. Should be a
multiple of 1024/4 = 256 usually
6-7     uint16  Depth of BRAMS in 4 byte words
8-11    uint32  Accumulation number / Measurement ID
12-15   uint32  Master Counter
16-17   uint16  Load Indicator
18-23   ------  Reserved
```

For this spectrometer, there are 2 BRAMs for the spectral data. One BRAM
(BRAM 1) holds the most significant 32 bits and the other (BRAM 0) holds
the least significant 32 bits. There are 1024 locations in each BRAM
which correspond to the 1024 channels. Thus the depth field is set to
1024/4 = 256. So these eight packets make up one spectrum (1K channels
\* 64 bits per channel = 8K)

``` text
53 00 00 02 00 00 04 00 00 00 4C FE A1 73 C2 16 04 4C 00 00 00 00 00 00
53 00 01 02 00 00 04 00 00 00 4C FE A1 73 C2 16 04 4C 00 00 00 00 00 00
53 00 00 02 01 00 04 00 00 00 4C FE A1 73 C2 16 04 4C 00 00 00 00 00 00
53 00 01 02 01 00 04 00 00 00 4C FE A1 73 C2 16 04 4C 00 00 00 00 00 00
53 00 00 02 02 00 04 00 00 00 4C FE A1 73 C2 16 04 4C 00 00 00 00 00 00
53 00 01 02 02 00 04 00 00 00 4C FE A1 73 C2 16 04 4C 00 00 00 00 00 00
53 00 00 02 03 00 04 00 00 00 4C FE A1 73 C2 16 04 4C 00 00 00 00 00 00
53 00 01 02 03 00 04 00 00 00 4C FE A1 73 C2 16 04 4C 00 00 00 00 00 00
```

Notice how the total BRAMs is fixed at 2. The total depth is 04 00
representing 0x0400 = 1024 = 4096/4. The offset counts from 0x0000 to
0x0300 for each BRAM. 0x00004CFE is the accumulation number, which you
notice increments each set of 8 packets. 0xA173C216 is the master
counter which eventually can be used to time tag each spectrum to the
nearest few nanoseconds. 0x044C is the load indicator, which indicates
how much free time the embedded processor that is sending out the data
has. If it gets down to 0x0001 you will start losing spectra because the
integration time is too short.

## Backend Software

## Users

## Resource Utilization

``` text
Logic Utilization:
  Number of Slice Flip Flops:      37,122 out of  47,232   78%
  Number of 4 input LUTs:          19,532 out of  47,232   41%
Logic Distribution:
  Number of occupied Slices:       21,665 out of  23,616   91%
Total Number 4 input LUTs:         27,919 out of  47,232   59%
  Number used as logic:            19,532
  Number used as a route-thru:        495
  Number used for Dual Port RAMs:     716
    (Two LUTs used per Dual Port RAM)
  Number used as 16x1 RAMs:             4
  Number used as Shift registers:   7,172

  Number of Block RAMs:               189 out of     232   81%
  Number of MULT18X18s:               112 out of     232   48%
```
