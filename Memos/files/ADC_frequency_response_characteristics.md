ADC frequency response characteristics
======================================

Christina de Jesus
------------------

### May 2006

Introduction
------------

The iADC, which can digitize either two streams of data at 1 Gsps or one
stream of data at 2 Gsps, was designed to be the IBOB's input data
source. It has seven SMA input ports: I+, I-, clk\_i, sync, Q+, Q-, and
clk\_q. Each of these input ports was designed for 50-ohm termination.
I- and Q- traces have been cut in all 0.2.x ADCs, and likely will be in
future runs.

Motivation
----------

This characterization was undertaken to quantify the extent of the ADC's
power rolloff and to check for a power dip around 700MHz.

Test equipment
--------------

The 1GHz, 6 April 2006 version of the pocket spectrometer and 16 March
2006 version of pocketplot was used for measurement.\
Clock: 1024MHz @ 0 dBm, HP 8780A rated to 3 Ghz\
Input: 16MHz-1000MHz, 16MHz intervals @ -30dBm, Agilent E4438C rated to
1.0GHz

Results
-------

ADC datasheet characteristics (from page 23 of the ADC datasheet, found
at <http://www.atmel.com/dyn/resources/prod_documents/doc2153E.pdf>)

![Atmel ADC power response](ADC_frequency_response_characteristics_files/datasheetresp.png)

Measurements show that the ADC levels are consistent with those
specified in the datasheet. No significant dip in power was observed at
700MHz; however, power levels reduce significantly after 1GHz. All data
taken can be found below.

Further measurements should be taken at input frequencies beyond 1GHz to
verify ADC behavior. It will also be convenient to characterize each ADC
board's frequency response for testing purposes.

Data
-----

![](ADC_frequency_response_characteristics_files/0.2.1.png)

**ADC serial: 0.2.1**

| Frequency (Mhz) | Power level (?) |
|-----------------|-----------------|
| 16 | 2.42E+013 |
| 32 | 2.28E+013 |
| 48 | 2.22E+013 |
| 64 | 2.22E+013 |
| 80 | 2.20E+013 |  
| 96 | 2.19E+013 |  
| 112 | 2.19E+013 |
| 128 | 2.11E+013 |
| 144 | 2.43E+013 |
| 160 | 2.30E+013 |
| 176 | 2.07E+013 |
| 192 | 2.06E+013 |
| 208 | 2.06E+013 |
| 224 | 2.00E+013 |
| 240 | 1.97E+013 |
| 256 | 1.96E+013 |
| 272 | 1.95E+013 |
| 288 | 1.93E+013 |
| 304 | 1.87E+013 |
| 320 | 1.88E+013 |
| 336 | 1.85E+013 |
| 352 | 1.82E+013 |
| 368 | 1.79E+013 |
| 384 | 1.75E+013 |
| 400 | 1.70E+013 |
| 416 | 1.68E+013 |
| 432 | 1.67E+013 |
| 448 | 1.63E+013 |
| 464 | 1.57E+013 |
| 480 | 1.52E+013 |
| 496 | 1.49E+013 |
| 512 | 1.61E+013 |
| 528 | 1.46E+013 |
| 544 | 1.44E+013 |
| 560 | 1.39E+013 |
| 576 | 1.32E+013 |
| 592 | 1.33E+013 |
| 608 | 1.34E+013 |
| 624 | 1.30E+013 |
| 640 | 1.26E+013 |
| 656 | 1.24E+013 |
| 672 | 1.24E+013 |
| 688 | 1.18E+013 |
| 704 | 1.11E+013 |
| 720 | 1.12E+013 |
| 736 | 1.14E+013 |
| 752 | 1.14E+013 |
| 768 | 1.08E+013 |
| 784 | 1.01E+013 |
| 800 | 9.89E+012 |
| 816 | 9.51E+012 |
| 832 | 8.52E+012 |
| 848 | 8.19E+012 |
| 864 | 7.57E+012 |
| 880 | 7.05E+012 |
| 896 | 4.68E+012 |
| 912 | 4.68E+012 |
| 928 | 3.38E+012 |
| 944 | 2.94E+012 |
| 960 | 2.86E+012 |
| 976 | 3.36E+012 |
| 992 | 4.15E+012 |


![](ADC_frequency_response_characteristics_files/0.2.3.png)

**ADC serial: 0.2.3**

| Frequency (Mhz) | Power level (?) |
|-----------------|-----------------|
| 16 |  2.47E+013 |
| 32 |  2.32E+013 |
| 48 | 2.27E+013 |
| 64 | 2.28E+013 |
| 80 | 2.26E+013 |
| 96 | 2.19E+013 |
| 112 | 2.23E+013 |
| 128 | 2.20E+013 |
| 144 | 2.23E+013 |
| 160 | 2.17E+013 |
| 176 | 2.07E+013 |
| 192 | 2.04E+013 |
| 208 | 2.09E+013 |
| 224 | 2.06E+013 |
| 240 | 2.01E+013 |
| 256 | 1.98E+013 |
| 272 | 1.98E+013 |
| 288 | 1.97E+013 |
| 304 | 1.93E+013 |
| 320 | 1.92E+013 |
| 336 | 1.92E+013 |
| 352 | 1.88E+013 |
| 368 | 1.82E+013 |
| 384 | 1.78E+013 |
| 400 | 1.75E+013 |
| 416 | 1.72E+013 |
| 432 | 1.70E+013 |
| 448 | 1.66E+013 |
| 464 | 1.61E+013 |
| 480 | 1.56E+013 |
| 496 | 1.52E+013 |
| 512 | 1.44E+013 |
| 528 | 1.49E+013 |
| 544 | 1.48E+013 |
| 560 | 1.43E+013 |
| 576 | 1.39E+013 |
| 592 | 1.37E+013 |
| 608 | 1.38E+013 |
| 624 | 1.35E+013 |
| 640 | 1.30E+013 |
| 656 | 1.29E+013 |
| 672 | 1.29E+013 |
| 688 | 1.27E+013 |
| 704 | 1.23E+013 |
| 720 | 1.20E+013 |
| 736 | 1.22E+013 |
| 752 | 1.21E+013 |
| 768 | 1.19E+013 |
| 784 | 1.11E+013 |
| 800 | 1.07E+013 |
| 816 | 1.02E+013 |
| 832 | 9.39E+012 |
| 848 | 9.00E+012 |
| 864 | 9.00E+012 |
| 880 | 7.34E+012 |
| 896 | 5.10E+012 |
| 912 | 5.49E+012 |
| 928 | 4.53E+012 |
| 944 | 4.79E+012 |
| 960 | 5.45E+012 |
| 976 | 6.52E+012 |
| 992 | 7.51E+012 |


![](ADC_frequency_response_characteristics_files/0.2.4.png)

**ADC serial: 0.2.4**

| Frequency (Mhz) | Power level (?) |
|-----------------|-----------------|
| 16 | 2.41E+013 |
| 32 | 2.25E+013 |
| 48 | 2.20E+013 |
| 64 | 2.21E+013 |
| 80 | 2.18E+013 |
| 96 | 2.14E+013 |
| 112 | 2.16E+013 |
| 128 | 2.31E+013 |
| 144 | 2.20E+013 |
| 160 | 2.08E+013 |
| 176 | 2.02E+013 |
| 192 | 1.96E+013 |
| 208 | 2.02E+013 |
| 224 | 1.97E+013 |
| 240 | 1.90E+013 |
| 256 | 1.89E+013 |
| 272 | 1.88E+013 |
| 288 | 1.89E+013 |
| 304 | 1.86E+013 |
| 320 | 1.82E+013 |
| 336 | 1.77E+013 |
| 352 | 1.72E+013 |
| 368 | 1.68E+013 |
| 384 | 1.67E+013 |
| 400 | 1.61E+013 |
| 416 | 1.60E+013 |
| 432 | 1.58E+013 |
| 448 | 1.58E+013 |
| 464 | 1.53E+013 |
| 480 | 1.46E+013 |
| 496 | 1.41E+013 |
| 512 | 1.37E+013 |
| 528 | 1.38E+013 |
| 544 | 1.36E+013 |
| 560 | 1.32E+013 |
| 576 | 1.26E+013 |
| 592 | 1.25E+013 |
| 608 | 1.23E+013 |
| 624 | 1.18E+013 |
| 640 | 9.10E+012 |
| 656 | 1.09E+013 |
| 672 | 1.14E+013 |
| 688 | 1.13E+013 |
| 704 | 1.08E+013 |
| 720 | 1.04E+013 |
| 736 | 1.06E+013 |
| 752 | 1.08E+013 |
| 768 | 1.08E+013 |
| 784 | 9.85E+012 |
| 800 | 9.70E+012 |
| 816 | 9.85E+012 |
| 832 | 9.82E+012 |
| 848 | 8.67E+012 |
| 864 | 8.52E+012 |
| 880 | 7.84E+012 |
| 896 | 6.25E+012 |
| 912 | 5.62E+012 |
| 928 | 4.35E+012 |
| 944 | 3.51E+012 |
| 960 | 2.77E+012 |
| 976 | 2.46E+012 |
| 992 | 2.75E+012 |