## Overview

3 GHz spectrometers developed here use the National ADC083000 part for
digitization. This page describes the hardware, gateware, and software
for two such spectrometers

  - 3 GHz baseband spectral line analysis, where a 6 Gigasamples/second
    rate is accomplished by time-interleaving 2 ADC083000 boards.
    Precise discussion of how the two ADC boards are interleaved can be
    found
    [here](http://casper.ssl.berkeley.edu/~sgowda/efficient_adc_time_interleaving.pdf).
  - Dual-pol 1.5 GHz spectrometer (calcuating [Stokes parameters](http://en.wikipedia.org/wiki/Stokes_parameters)), for
    multi-pol antennae
      - Project home: <http://www.gb.nrao.edu/gbsapp/>

This work is still ongoing, so please check back for updates\! Gateware
and DSP libraries for these high-rate applications was upgraded from the
CASPER "green" blocks by Suraj Gowda (surajgowda \<<at>\> berkeley.edu.

## Hardware

FPGA Platform: [ROACH](ROACH "wikilink")

Analog-to-Digital Conversion: [ADC1x3000-8](ADC1x3000-8 "wikilink")

## Gateware

Gateware at the moment is somewhat fragmented. Building the design
yourself is recommended only for those who feel they have a grasp of the
Simulink design environment at the level of tutorial 3
([Tutorials](Tutorials "wikilink")).

\[In order to attain the targeted bandwidth, a high FPGA clock speed
(375 MHz) is required. To operate the system at this speed, several
significant resource optimizations to the DSP blockset are required.

\(\beta\) gateware: (Recommended for intermediate users) [\[BWRC fork of
mlib\_devel](http://casper.berkeley.edu/git/?p=mlib_devel/bwrc.git;a=summary)\].
This does not contain the required modifications to the Polyphase Filter
Bank FIR filter.

\(\alpha\) gateware: (Intended for advanced users) Versions of the PFB
FIR and FFT implementing using the [XBlock
Scripting](XBlock_Scripting "wikilink") functions. Contains the latest
tips and tricks, including a 5 DSP slice butterfly and shiny new PFB FIR
block. All existing unit tests pass, but those tests are not yet
comprehensive. (last updated: 4/1/2011)

## Auto-placing the FFT

Structured resource layout for the FFT is required so that route delay
is minimized between components. This is the only way to achieve the
targeted clock rate

Code to automatically do this layout for the FFT (there is a maximum
transform size of 16 simultaneous inputs) can be found at
<http://casper.berkeley.edu/~sgowda/fft_placement/>

This code implements an analytical solution to a more general placement
problem discussed in

`@inproceedings{ gowda_2011,`  
`author = "Suraj Gowda and Aaron Parsons and Robert Jarnot and Dan
Werthimer",`  
`title = "{Automated Placement for FPGA-based FFTs}",`  
`booktitle = "Field-Programmable Custom Computing Machines, Annual IEEE
Symposium on",`  
`month = "May",`  
`year = 2011` `}`

If you utilize the attached autoplacement routine, please cite the above
reference. Thanks\!

## Acknowledgements

The work here was/is supported in part by NASA Space Grant, generous
chip donations from Xilinx, Inc., and grants associated with the UC
Berkeley CASPER group.
