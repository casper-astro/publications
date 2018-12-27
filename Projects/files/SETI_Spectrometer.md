The SERENDIP V SETI Spectrometer is a 128M channel, 200MHz, 1 pol
spectrometer on the [iBOB](iBOB "wikilink")/[BEE2](BEE2 "wikilink") and
was designed for applications in SETI, FX correlators, pulsar, and
general radio astronomy.

The signal processing is implemented in a Xilinx Virtex-II Field
Programmable Gate Array (FPGA) chip, which can be dynamically programmed
for various applications.

The spectrometer uses a polyphase filter bank (PFB) to implement a bank
of steep cut-off bandpass filters, providing a significant improvement
in signal-to-noise and out-of-band-rejection over the common FFT
algorithm. The PFB uses a biplex pipelined architecture which allows
data to be input and output at the full sample rate, and can do two
polarizations simultaneously with no extra cost in hardware or data flow
rate.

For information on SERENDIP science, visit [UC Berkeley
SETI](http://seti.berkeley.edu)

## People

[Terry Filiba](User:Terry "wikilink")

[Mark Wagner](User:Mwagner "wikilink")

[Andrew Siemion](User:siemion "wikilink")

[Laura Spitler](User:Laura "wikilink")

Dan Werthimer

Jim Cordes

## SERENDIP Mailing List

[Search the SERENDIP Mailing
List](http://www.mail-archive.com/serendip@lists.berkeley.edu/)

## SERENDIP Block Diagram

[ Block Diagram ](Image:Setiblock.png "wikilink")

## Simulink Model files

#### IBOB

[DDC Model
File](http://casper.berkeley.edu/svn/trunk/projects/seti_spec/model_files/DDC/adcddcxaui.mdl)

#### BEE2

[PFB (4k) Model File -
FPGA 2](http://casper.berkeley.edu/svn/trunk/projects/seti_spec/model_files/PFB/seti_pfb_test.mdl)

[Corner Turner Model File -
FPGA 3](http://casper.berkeley.edu/svn/trunk/projects/seti_spec/model_files/CT/seti_ct.mdl)

[FFT (32k) Model File -
FPGA 4](http://casper.berkeley.edu/svn/trunk/projects/seti_spec/model_files/FFT/casper_fft_stripped_legacy.mdl)

[Thresholder Model File -
FPGA 1](http://casper.berkeley.edu/svn/trunk/projects/seti_spec/model_files/Thresholder/t_t_200_tge5.mdl)

## Assembly

Connect power to IBOB, BEE2, and BEE2 fans

Connect ethernet to IBOB (IBOB has IP address 192.168.2.6 where the last
two octets are set on the headers) for more info on communication with
IBOB, see: [IBOB UDP server
documentation](http://casper.berkeley.edu/memos/udp_packetization.pdf)

Connect ethernet to BEE2 (Check board for IP address)

Connect XAUI1 to F2-0 on BEE2

Connect Passive LVPECL termination to J117 on BEE2

Connect LVCMOS to LVPECL converter to SMA1 (converter should be
connected to 5V)

Connect SMA to one of outputs of LVPECL converter to 3db attenuator to
LVPECL termination

Connect F1-3 to 10GbE NIC on your computer

Clock ADC at 800MHz 0dBm

## SETI Spectrometer Software

### Initialization Scripts

All of the bee2 bof files and initialization scripts are available in
svn
<http://casper.berkeley.edu/svn/trunk/projects/seti_spec/bee2_software/>.
After copying these files to the bee2, either add the checked out bin
directory to the path or move the read\_reg and write\_reg binaries into
a directory already in the path.

The top level script start\_seti.sh will kill any previous setispec run,
reload all the bof files, and configure the chips. The bofs/ directory
contains the current versions of the bof files and the bin/ directory
contains all the subscripts for initializing and restarting the bee2.

The [10GbE](10GbE "wikilink") block is configured by the 10gbe.conf
file. There is documentation on editing this file here: [10GbE
configuration](10GbE#Configuration "wikilink").

Most initialization values are hard coded into the scripts but a few
parameters can be modified via a configuration file in the bin/
directory named bee2.config. The file in svn is currently empty so the
scripts will use default values. If a line in the config file is found
with a parameter name followed by the value then the script will use
that value instead of the defaults.

Here is an example of a config file that sets max\_hits\_per\_bin to 25
and scale\_threshold to 96:

    max_hits_per_bin 25
    scale_threshold 96

Currently the scripts will only look for max\_hits\_per\_bin and
scale\_threshold. Additional parameters can be added to the script by
defining a variable using the following code and replacing
max\_hits\_per\_bin with an appropriate variable name.

    config_file="bee2.config"
    
    #read in parameters from config file
    max_hits_per_bin=$(awk '/max_hits_per_bin/ {print $2}' $config_file)
    
    #set default values if parameters are not defined in the config file
    max_hits_per_bin=${max_hits_per_bin:-25}
    
    #write max_hits_per_bin into the register
    write_reg $thrproc thr_comp1_thr_lim $max_hits_per_bin

### Data Recorder

To run the test software and the data recorder the following packages
are required: g++, tk, tk-dev, and grace

To set up the data recorder svn checkout the
<http://casper.berkeley.edu/svn/trunk/projects/seti_spec/server_software/datarecorder2/>
directory from the casper svn and go through the following steps. (Note
all paths are relative to this datarecorder2 directory).

  - Verify that the top level Makefile has the correct include path for
    tk. This is set in the third line of the makefile and is set by
    default to /usr/include/tk.
  - Next, you need to rebuild some of the include libraries. This only
    needs to be compiled once.
      - Run make in AO/\_home\_cima\_Wapp\_Bin\_Sources\_Lib\_linux and
        copy all the object files (\*.o) to
        AO/\_home\_cima\_Wapp\_Bin\_Sources\_Lib\_linux to AO/lib
      - Run make in AO/\_home\_phil\_vw\_pnt\_exportCode and copy
        libazzatoradec.a in AO/\_home\_phil\_vw\_pnt\_exportCode to
        AO/lib

Then the datarecorder is compiled by running make in the datarecorder2
directory and should produce the setispec\_dr executable.

## DDC

The DDC is a decimating quadrature downconverter. It receives samples of
the IF from the ADC at a rate of 4 8-bit real samples per cycle at
200MHz, and outputs 1 16-bit complex (8-bit real, 8-bit imaginary)
sample of the baseband signal per cycle. The incoming IF is mixed down
with 200MHz, put through a decimating symmetric low-pass filter. The
filter downsamples by 4 and has a -6dB cutoff frequency of 80MHz. Filter
specs:

  - Filter type: Windowed FIR
  - Filter order: 63
  - Cutoff frequency: 80MHz; -6dB
  - Windowing: Tukey, alpha=0.5

**Input:** ADC block, 4 parallel data streams

**Output:** XAUI

**General description:**

For normal operation, the register "ddc\_en" must be set HI,
"beam\_switcher/switchyard\_BRAM" must be filled, and
"beam\_switcher/max\_addr" set.

It may be that for the XAUI link to be set up properly, the "tx\_nvalid"
pin needs to be toggled. See point 3 below.

1\) Snap blocks

2\) Functionality of we pins

3\) "tx\_nvalid" (Transmission NOT valid pin) Sometimes when
establishing a link, the RX XAUI block reports "rx\_valid" = 0. This can
be fixed by toggling the "tx\_valid" port on the TX XAUI block. The
"tx\_nvalid" provides a manual NOT enable register which when toggled
HI, toggles "tx\_valid" LO in line with the sync pulse.

[TVG's, Software Registers, and
Snapshots\#DDC](TVG's,_Software_Registers,_and_Snapshots#DDC "wikilink")

## PFB

The first stage of data processing is a coarse channelization handled by
a 4096-channel polyphase filter bank (PFB). A general description of the
PFB algorithm and architecture can be found
[here](http://seti.ssl.berkeley.edu/~aparsons/papers/2003-06_pfb_32.html).
The PFB takes a 16-bit (8 bits real, 8 bits imaginary) input from the
DDC per cycle which is passed through a 4K-channel, 8-tap FIR filter
that allows bit growth from 8 to 18 bits (18.17 signed). The post-FIR
data is then fed into a 4096-point biplex pipelined complex FFT with
programmable downshifts, which maintains 18.17 signed data at the
output.

**Input:** XAUI

**Output:** gpio (data \[0:35\], sync \[36\] leftlink)

**General description:**

"fft\_shift" must be set for all operation modes.

For simulation mode, MUX select sync\_period registers must be set.

Default output method is gpio links.

[Interchip Links](Interchip_Links "wikilink")

[TVG's, Software Registers, and
Snapshots\#PFB](TVG's,_Software_Registers,_and_Snapshots#PFB "wikilink")

## Corner Turner

The corner turner is a 4Kx32K matrix transpose that bridges the PFB and
the FFT. By buffering each PFB frequency slice in DRAM, the transpose
converts frequency-domain data back into time-domain data for use in the
FFT. No data processing is done except for reordering, so it takes
36-bit data from the PFB, and feeds 36-bit data to the FFT. 32K samples
of each of the PFB's 4K channels is buffered for use in the 32K FFT.

**Input:** gpio (data \[0:35\], sync \[36\] rightlink) or XAUI (port 0)

**Output:** gpio (data\[0:35\], sync \[36\] leftlink) or XAUI (port 1 &
2)

**General Description:**

For normal operation no registers need set. For test operations, the
appropriate MUX selector pins, data, and sync\_periods need set. The
default is for data to be sent and received over gpio links.

## FFT

The FFT block implements a 32768-point FFT with programmable downshifts.
It takes 36-bit data from the corner turner and outputs 36-bit data to
the thresholder.

**Input:** gpio (data\[0:35\], sync \[36\] rightlink) or XAUI (port 0)

**Output:**

`        FFT: gpio (data[37:72], sync [73] leftlink) or XAUI (port 1)`  
`        CT: gpio (data[0:35], sync[36])`

**General Description:** In order to feed the thresholder with the
output of the CT, the data input to FFT block (from CT) is passed
through block.

## Thresholder

The spectrometer's thresholder module compares the power of each
frequency bin with a scaled local average and reports those bins that
are over the noise floor. It is comprised of three subcomponents: a
threshold computation (averaging plus scaling), the actual thresholder,
and a reporting interface to the postprocessing software backend. It
takes 36-bit data as complex samples from the PFB and FFT, and reports
32-bit data out as power squared (r^2 + i^2; from here on "power" refers
to power squared).

#### Threshold computation

Local averages are calculated per PFB channel by taking the same data
being fed to the the FFT directly from the corner turner. This way, the
total power in each PFB bin can be accumulated while the FFT is being
computed (via Parseval's theorem). A 36-bit power is calculated from
each 36-bit complex sample received from the corner turner. The 32K
(2^15) powers corresponding to a PFB bin are accumulated and divided by
32K to get the local average, then scaled according to the scalar set by
the user via software. The scalar is input as a 32-bit integer, of which
only the bottom 18 bits are used as an 18.9 unsigned number. The integer
scalar setting is divided by 2^9, giving it an interpreted range of
\[0.001953125, 511.998046875\]. The spectrometer boots to a default
scalar of 48 (0.09375).

The small interpreted value of the scalar is misleading, due to the
interaction of downshifts in the FFT. The spectral power doubles for
every stage in the FFT that does not downshift, and halves for every
stage that does. Thus, the power gets scaled by a factor of (2^N/2^n ; N
= number of stages without downshift, n = number of stages with
downshift) through the transform. A similar scaling happens in the FFT
of the PFB module, but since the bin powers and local average powers are
calculated from the same post-PFB data, that scale factor cancels out
with regards to thresholding. Taking all of these factors into account,
the threshold is set at integer\_scalar/\[(2^9\*2^(N-n)\] times the
average power.

\(N = \frac{N_{hw}}{2^9 \; 2^{(N_{ns}-N_{ws})}}\)

where

\(P_{event} \ge N<P>\)

\(N_{hw}\) is integer to write to software register

\(N_{ns}\) is number of FFT stages without a downshift

\(N_{ws}\) is number of FFT stages with a downshift

The spectrometer boots up with default settings at 11 of 15 stages
downshifting in the FFT and an integer scalar of 48. Following the above
the relation, this sets the threshold at 12 times the average power.

#### Thresholding and reporting

fft\_bin - 15 bits - number between 0 and 32k pfb\_bin - 12 bits -
number between 0 and 4096k over\_thresh - 1 bit - high when there are
more hits than 'max\_num\_hits' blank - 3 bits - no data, should e
zero's event = 1 bit - will be 1 if fft\_power is over threshold
fft\_pfb\_power - 32 bits - if fft\_bin is 0, then the average power is
reported, if fft\_bin is not 0 then the fft fine bin is reported. Note
that we will lose the first fft fine bin, although we will see if there
was an event.

The number of records per spectra depends on the threshold and the max
number of hits (max\_num\_hits) we're going to allow for each pfb bin,
so we won't know how many records there are going to be for a spectra.
The 4096 byte packet size is somewhat arbitrary and we will need more
than one packet to construct a spectra.

Note that the pfb and fft bins are flipped, so they should be
interpreted as fft bins coming out as 0 to 16383 then -16384 to -1 and
the pfb coming out 0 to 2047 then -2048 to -1.

The thresholding triggers "hits" for FFT bins that are greater than or
equal to the threshold power. Due to bandwidth limitations in the link
between the BEE2 and post-processing PC, the number of hits reported per
PFB bin is capped via a software-adjustable setting. To aid the software
in determining the PFB baseline, the first sample of each PFB bin is
always reported, though it may not be flagged as a "hit". Data is always
reported a group of 5 32-bit numbers, which include the PFB bin number,
the FFT bin number, the threshold power, the FFT bin power, and
flags/error codes. Reported data is buffered in FIFOs that are self-
regulating; when almost full writes are halted to avoid overflows that
could cause data to become misaligned. The FIFOs are emptied by the on-
chip PowerPC core to be assembled into UDP packets for transmission to
the backend software.

**Input:**:

` FFT: gpio (data[37:72], sync [73] leftlink) or XAUI (port 1)`  
` CT: gpio (data[0:35], sync[36] leftlink) or XAUI (port 0)`

**Output:** 10 GbE

For normal operation, "thr/comp1/thr\_lim" and "thr/scale/p1\_scale"
must be set. For simulation mode, Input MUX registers must also be set.

## ADC level testing

ADC level tests were done with ALFA set to a center frequency of 1375
MHz with the wideband filter on the afternoon of 7 June 2009.

Plot: <http://casper.berkeley.edu/wiki/Image:Adcwidehist.pdf>

RMS: 27.6

A 3dB attenuator was added later in the day. The new RMS should now be
19.4, but no data has currently been taken.

## 09 July 2009 Testing

Data from three snap blocks on the BEE2 and one snap block on the iBOB
were captured manually during an observing session from 22:00 to 23:00
AST on 09 July 2009. The iBOB snap block grabbed 8-bit values from the
ADC. The three SNAP blocks on the BEE immediately followed the DDC
(mixer+dec\_fir), PFB (pfb\_fir+fft) and FFT (fft) blocks. These tests
were taken without the datarecorder code capturing packets. In the last
few minutes of the observing session, the recorder was restarted and a
small amount of data was taken from which the "ALFA setup" below is
derived.

ALFA setup:

`  Wideband filter`  
`  Center frequency = 1374940266 Hz`

iBOB setup:

`  "ddc_en" 0x01`  
`  "blank_radar" 0x00`

BEE setup:

`  PFB "fft_shift" 0x0FFF`  
`  FFT "fft_shift" 0x6EEE`  
`  THR "thr_scale_p1_scale" 0x60 (96)`  
`  THR "thr_comp1_p1_lim" 0x19 (25)`

![hist\_adc\_Jul09.pdf](hist_adc_Jul09.pdf "hist_adc_Jul09.pdf")

![hist\_ddc\_Jul09.pdf](hist_ddc_Jul09.pdf "hist_ddc_Jul09.pdf")

![hist\_pfb\_Jul09.pdf](hist_pfb_Jul09.pdf "hist_pfb_Jul09.pdf")

![hist\_fft\_Jul09.pdf](hist_fft_Jul09.pdf "hist_fft_Jul09.pdf")

## JPL Deployment

[JPL\_setispec](JPL_setispec "wikilink")

## Internal Configuration Pages

[Seti Spec Restricted](Seti_Spec_Restricted "wikilink")

## Analysis

[Serendip Analysis](Serendip_Analysis "wikilink")
