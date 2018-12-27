The Spectral Kurtosis (SK) Spectrometer was built by [Zhiwei
Liu](User:Zhiwei "wikilink") for Korean Solar Radio Burst Locator
(KSRBL). This instrument utilizes four of these 500 MHz bandwidth SK
spectrometers in parallel, to achieve a 2 GHz instantaneous bandwidth
that is time multiplexed over the entire DC-18 GHz radio frequency
range.

The unique aspect of the spectrometer is that it accumulates both power
and power-squared statistics which are then used to develop a "spectral
kurtosis"(SK) estimator as described by Nita et al. (2007, PASP 119,
805). The SK estimator is used offline for real-time detection and
excision of RFI embedded in the received signal. The required power and
power-squared data are broadcast by the FPGA via fast ethernet and
converted to the SK estimator using software implemented in LabVIEW.

## Specifications

|                     |                                            |
| ------------------- | ------------------------------------------ |
| Frequency channels: | 2048 (4096 real samples per spectrum)      |
| Clock input:        | 1000 MHz                                   |
| Signal input:       | 500 - 1000 MHz                             |
| Integration time:   | 25 ms                                      |
| Polyphase filter:   | 4taps, Hamming window                      |
| Output:             | 100 Mbit Ethernet, 32-bit per spectrum bin |
| Libraries used:     | mlib\_devel 7.1                            |
| hardware:           | iBOB, iADC                                 |

## Source Files

## Documentation

<b>Initialization Commands:</b>

``` text
regwrite reg_shift -1
```

This sets the shifting schedule through the FFT. -1 means every sample
is divided by 2 at every stage.

``` text
regwrite reg_coeff 4096
```

There is a scaling factor at the output of wide\_band\_FFT block. The
fix point position is 12, so 4096=2^13 actually is 1.

``` text
regwrite reg_acclen 6249
```

This sets the integration time to 6250 spectra (around 25.6 ms at 1000
MHz ADC clock)

``` text
regwrite reg_sync_period 25600000
```

This sets the sync period to 25600000 FPGA clocks

``` text
regwrite reg_arm 0
regwrite reg_arm 1
```

The rising edge of reg\_arm starts the operation and reset the
accumulated spectra counter to 0. You can also use external signal to
trigger the arm (connect the external signal to SMA1 of iBOB).

``` text
startudp 169 254 128 5 6969
```

This sends the udp packets to 169.254.128.5 with destination port 6969.

<b>Packets Format:</b>

Each UDP packet is 1045 bytes (21 bytes of header, 1024 bytes of raw
data).

Header Format:

``` text
Byte    Type    Descr., Example
0-3     uint32  spectrum number
4       uint8   register value of reg_power_bitselect
5       uint8   register value of reg_power2_bitselect
6       uint8   register value of reg_power_bfacc_bitselect
7       uint8   Reserved
8-11    uint32  Number of Accumulation -1, eg.3999->4000 accumulation
12      uint8   number of packets per spectrum(power and power^2)
13-20   ------  Reserved
```

## Results

[Watch video of Spectral Kurtosis elimination of Radio Frequency
Interference (RFI)](http://web.njit.edu/~gary/assets/Phone_RFI.htm)

## Resource Utilization

``` text
Logic Utilization:
  Number of Slice Flip Flops:      32,313 out of  47,232   68%
  Number of 4 input LUTs:          15,378 out of  47,232   32%
Logic Distribution:
  Number of occupied Slices:       19,761 out of  23,616   83%
Total Number 4 input LUTs:         23,450 out of  47,232   49%
  Number used as logic:            15,378
  Number used as a route-thru:        562
  Number used for Dual Port RAMs:     556
    (Two LUTs used per Dual Port RAM)
  Number used as 16x1 RAMs:             4
  Number used as Shift registers:   6,950

  Number of bonded IOBs:              152 out of     692   21%
    IOB Flip Flops:                   175
    IOB Master Pads:                   19
    IOB Slave Pads:                    19
    IOB Dual-Data Rate Flops:           1
  Number of PPC405s:                   2 out of       2  100%
  Number of JTAGPPCs:                  1 out of       1  100%
  Number of Block RAMs:               146 out of     232   62%
  Number of MULT18X18s:                64 out of     232   27%
  Number of GCLKs:                      3 out of      16   18%
  Number of DCMs:                       3 out of       8   37%
  Number of GTs:                        0 out of      16    0%
  Number of GT10s:                      0 out of       0    0%
```
