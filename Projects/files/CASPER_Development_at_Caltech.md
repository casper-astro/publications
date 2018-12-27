## Introduction

We are implementing a digital back end for a novel wide band radio
astronomy receiver with an instantaneous sky frequency coverage of
either \~0.5-4 GHz or \~2-14 GHz. This reconfigurable back end will be
able to perform spectroscopy, polarimetry, and pulsar observations. The
radio telescope is the 34m DSS-28 dish at Goldstone and will be operated
by the Lewis Center for Educational Research
([www.lcer.org](http://www.lcer.org)) as part of the GAVRT science
curriculum for K-12 students.

**New\!**: [Picture of the receiver](#Status "wikilink")

## Contributions

### BEE2 Interchip Interconnects

  - Notes on using the BEE2 [Interchip
    Interconnects](Interchip_Interconnects "wikilink")

### DRAM Notes

  - Hints for interfacing with the BEE2 DRAM: [DRAM
    Notes](DRAM_Notes "wikilink").

### gtkWaveCapture

  - Tool to replace Simulink scope:
    [gtkWaveCapture](gtkWaveCapture "wikilink")

### GAVRT/Caltech Blockset

I have developed a number of useful blocks, some of which will
eventually end up in the CASPER library. The blocks are available in the
CASPER SVN: [1](http://casper.berkeley.edu/svn/trunk/caltech/lib/).
Note: these blocks are mostly tested, but certainly not guaranteed.
Please email jjoonneess\_\_ggll@@ccaalltteecchh..eedduu if you find any
issues.

(Right-click and save to disk and rename to .zip. Wiki will not allow
most file types)
[Media:Gavrtlib\_Dec\_19\_2007.pdf](Media:Gavrtlib_Dec_19_2007.pdf "wikilink")

### Notable blocks

**Vector Accumulator**: The vacc, Serialize, and Vacc Readout Control
blocks together make a very clean and functioning vector accumulator.
They are reasonably well documented except for Serialize. (Note: the
Readout Control does not work as well as hoped in hardware because the
PPC misses the BRAM\_WE signal that signifies a valid spectrum has been
recorded. A latch is needed; this will be updated soon.)

**cram and uncram**: These blocks make passing several parallel values
around much easier.

**nCasts**: Just what it sounds like. Saves a lot of time. Trick: if you
cascade a nCasts with a cram and connect the output to a gpio configured
for Unsigned data, you can quickly wire a number of boolean or other
signals to LEDs or general gpio without having to create a separate gpio
for each signal.

**SuperSlice**: Simple but invaluable. I find it much more useful than
the normal slice block. Great for breaking a software register out into
control bits.

## Status

*' April 14, 2009*': Deep capture buffer is working well on BEE2. This
design buffers a run-time configurable number of samples (from 2^22 to
2^30) streaming in from a set of iBOBs over XAUI. The ADCs can be
clocked at 1 GHz (2Gsps). In the interim implementation, two iBOBs can
be connected to each of FPGAs 2 and 4, and the data will be passed to
FPGA 3 via interchip links to be transmitted over a 10 GbE port on FPGA
3. In the final implementation, each user FPGA will connect to a pair of
iBOBs for a total of eight 1 GHz bands. The data will then stream into
the Control FPGA to be sent out via it's two 10 GbE ports. The next step
is to run the incoherent trigger system on the iBOBs simultaneously and
then pass the trigger over XAUI to the BEE2 logic. This is well
underway.

*' February 24, 2009*': First giant pulses detected from the Crab Pulsar
with DSS-28\!
[Media:2009.02.23\_-\_First\_Giant\_Pulses\_with\_DSS-28.pdf](Media:2009.02.23_-_First_Giant_Pulses_with_DSS-28.pdf "wikilink")
This incoherent dedispersion trigger will be used at Arecibo in March to
capture giant pulses from the Crab and B1937+21.

*' September 02, 2008*': Feeds and receiver has been installed on
DSS-28. Both feeds have been successfully cooled and tested on the dish.
The LFF is currently running and feeding an iBOB spectrometer under
remote control. The HFF will be running this week pending an additional
cable installation. The tertiary mirror is currently fixed in place, but
should be under computer control this week. ![Equipment at the DSS-28
vertex](dss28vertex.jpg "Equipment at the DSS-28 vertex") *' July 22,
2008*': Working on capturing and decoding packets from BEE2 capture
buffer. Started [Gigabit\_NIC\_Notes](Gigabit_NIC_Notes "wikilink") to
document notes on what works well for getting data from BEE2 to PC.
![DSS-27, which is identical to the 34-m DSS-28 on which the GAVRT
equipment will be mounted](DSS27.JPG
"DSS-27, which is identical to the 34-m DSS-28 on which the GAVRT equipment will be mounted")
**July 18, 2008**: Successfully tested receiver box and feeds at
Goldstone. Initial iBOB is set up, ready to take spectra. ![GAVRT
Receiver Box](GAVRT_RSS1.JPG "GAVRT Receiver Box") **July 15, 2008**:
The Phase I GAVRT Receiver will be going to Goldstone tomorrow for
initial testing. In addition to getting ready for the trip, I have
gotten a basic BEE2 DRAM transient buffer working. In doing so, I
started to document how to interface with the DRAM: [DRAM
Notes](DRAM_Notes "wikilink").

**June 30, 2008**: The GAVRT Receiver Box is now on the roof at Caltech
for final testing before installation on the telescope. In the past few
months I have been working on incoherent dedispersion on the iBOB to
allow for more sensitive giant pulse triggering. This seems to be
working well. Now I am focusing on the BEE2 DRAM buffer to store the
time domain data and transfer it to a cluster of PCs for processing.
While investigating the effectiveness of my I/Q imbalance compensating
spectrometer, I came across a problem of excess leakage from a CW tone.
I am still working to understand and if possible, mitigate this problem.
So far, I have fully tested these spectrometer designs, each fitting on
an iBOB:

  - 4096 channel, 2 tap, single input, up to 128 MHz BW "Hi-Res" mode
  - 1024 channel, 2 tap, single input, up to 1024 MHz BW "Wide-Band"
    mode
  - 512x2 channel, 2 tap, dual input, up to 2x512 MHz BW "Dual-Pol" mode
  - 512x2 channel, 2 tap, I/Q input, up to 2x512 MHz BW "I/Q correcting"
    mode
  - 256 channel, 2 tap, single input, up to 1024 MHz BW on-chip
    dedispersion "Trigger" mode

**May 16, 2008**: Continuing receiver tests. I added a test vector
generator to my spectrometer designs and then spent about a week
understanding the deviations from ideal behavior. Conclusions: the
CASPER DSP and GAVRT block sets are robust. Keep in mind that while the
power spectrum of a signal with a period that divides the FFT length
should not depend on time shifts of the signal, rounding errors can make
the spectrum fluctuate in the LSBs depending on the time shift.

**Apr. 30, 2008**: We have been testing the initial receiver hardware in
the lab for the past two weeks. The initial hardware consists of a
dual-polarization receiver tunable from 0.5 to 18 GHz with up to 2 GHz
IF bandwidth, along with noise calibration and fiber optic transmission.
Eventually there will be four such receivers in the box. I have begun
end-to-end tests from the input of the receiver, through the fiber optic
outputs into some basic iBOB based spectrometer designs. Most CASPER
work has been on backend software to support the tests.

**Apr. 05, 2008**: Receiver hardware should be arriving this week. Thus
I will be focusing on refining the fast dump spectrometers to use a
common back end infrastructure for readout and data capture on the PC.
Have been working on a DRAM capture buffer, to allow capturing large
amounts of baseband voltage data. Eventually this buffer will be
triggered by an incoherent dedispersion system for transient capture.
For now it will be manually triggered. I have learned a lot about the
DRAM block, and will write a supplementary document to clarify the
existing documentation.

**Mar. 29, 2008**: Made new versions of PFB\_FIR and PFB\_FIR\_REAL
blocks that allow runtime configuration of the FIR coefficients. Thus
various windows can be tested without having to compile many seperate
designs. Email me if you want a copy. Working on fast dump spectrometer
to do stability testing when the GAVRT receiver arrives. Hardware IQ
correction seems to be working well.

**Mar. 19, 2008**: Took a short diversion to write a tool,
[gtkWaveCapture](gtkWaveCapture "wikilink") that captures data from the
Simulink environment to allow viewing in the
[gtkWave](http://home.nc.rr.com/gtkwave/) waveform viewer.

**Mar. 15, 2008**: Have been busy preparing for candidacy exam. Now that
the exam is successfully out of the way, back to work on IQ correction,
which seems to be working in hardware. Updated vacc block to allow
setting MUX latency to improve timing.

**Feb. 20, 2008**: Initial documentation of iBOB to BEE2 link completed:
[Media:IBOB-BEE2 XAUI
Overview.pdf](Media:IBOB-BEE2_XAUI_Overview.pdf "wikilink") (actual PDF,
do not rename). Updated Model files: [Media:Xaui align Release Feb20
2008.pdf](Media:Xaui_align_Release_Feb20_2008.pdf "wikilink") (rename
.zip)

**Feb. 19, 2008**: Beginning to document iBOB to BEE2 connection. Have
spent the past couple of weeks working on an IQ imbalance correction
scheme which seems to be working well. Report to come soon. Spent a
while trying to figure out why designs with DRAM were failing to meet
timing with strange errors. Turned out that I had not applied the 7.0.4
patch to ISE on the build machine. Preview of iBOB-BEE2 XAUI link:
[Media:xaui\_align\_PreRelease\_Feb19\_2008.pdf](Media:xaui_align_PreRelease_Feb19_2008.pdf "wikilink")
(rename .zip)

**Jan. 24, 2008**: Alignment between iBOB and BEE2 seems to be working
well at 250 MHz (actually managed to overclock to 300+ MHz, so it seems
stable). Saw no glitches in 13 hours of continuous operation. The
'traditional' approach of generating clk/2 on an iBOB SMA output and
connecting this to the usr\_clk input SMA on the BEE2 and running the
BEE2 design off of usr\_clk2x did not work at 250 MHz. Instead, I had to
generate clk/4 and hack the XPS base system to lock the BEE2 DCM to
usr\_clk \* 4. This seems to work well. All of my CASPER designs will
soon be available by anonymous FTP.

**Jan. 15, 2008**: Continuing work on aligning data from iBOB to BEE2.
Original design worked OK but fails to compile at 250 MHz. After
analyzing timing reports and trying various pipelining locations, it
appears there will need to be a latency of at least 3 cycles between an
rx\_get being issued to the XAUI block and receiving OOB data, as this
feedback is a critical path. Currently figuring out how to get the
design to work with this much latency.

**Dec. 23, 2007**: Traced down trouble with iBOB lwIP refusing
connections after a reset connection. Modified version of
*/drivers/xps\_lwip/lwiputil.c*:[Mod\_lwiputil.c](Mod_lwiputil.c "wikilink")

**Dec. 19, 2007**: Wiki page created. Updated FAQ with information about
using the DCMs. Currently working on streaming data from iBOBs to the
BEE2 over XAUI in synchrony. This seems to be working well. Current
design:
[Media:Xaui\_align\_Dec\_19\_2007.pdf](Media:Xaui_align_Dec_19_2007.pdf "wikilink")
(rename .zip)

## People Involved

The overall GAVRT DSS-28 project involves many people, however the
people most involved with the back-end development are:

**Glenn Jones**: CASPER hardware development

**Robert Karl**: Software development

**Tom Kuiper**: Science requirements

**Sandy Weinreb**: Overall system design

## Acknowledgments

We are very grateful of Xilinx's generous donations enabling development
of this project.
