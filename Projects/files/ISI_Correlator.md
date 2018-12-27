The [Infrared Spatial
Interferometer](http://en.wikipedia.org/wiki/Infrared_Spatial_Interferometer)
is a three-telescope array located at the [Mount Wilson
Observatory](http://www.mtwilson.edu) outside of Pasadena, California.
The **ISI Correlator** is a wideband FX correlator designed for high
resolution infrared interferometry on the existing ISI array. It is
currently under development at UC Berkeley.

## System Overview

The target spec is a three-telescope correlator with 4 bit resolution
covering 3GHz of bandwidth. We are building this out of three
[ROACH](ROACH "wikilink") boards and six [ 3GSps
ADCs](ADC1x3000-8 "wikilink").

Each telescope has one ROACH. Each ROACH has two ADCs, an F-Engine, some
network interconnect logic, an X-Engine, and some network readout logic.
The gateware running on each ROACH is identical. Each ROACH is connected
to both of the other ROACHes by a single 10Gbps network link, and to a
server (via a switch) by a 1Gbps network link. All ROACHes run
synchronously with one another.

## Data Acquisition

Each ROACH has two ADCs that we clock at 1.5GHz. Each ADC double-samples
(180° out of phase), and we clock both ADCs with the same clock source
using a quadrature splitter (90° out of phase). This gives us four
samples per clock, for a total of 6GSps.

The ADCs also downsample their clocks by 4 and use that signal to clock
the ROACHes, so the ROACHes run at 375MHz. This means that there is a
8:1 demux from each ADC, for a total of a 16:1 demux into each ROACH. At
8 bits per sample, this comes out to 48Gbps coming into each ROACH.

**Status:** Complete.
[Simulink](http://casper.berkeley.edu/svn/trunk/projects/isi_correlator/tests/test_adc083000x2.mdl).
[Python](http://casper.berkeley.edu/svn/trunk/projects/isi_correlator/isipy/test_adc083000x2.py).

## F Engine

The F-Engine splits the 3GHz of bandwidth into 64 frequency bins.

We window the ADC data with a [ polyphase filter
bank](pfb_fir_real "wikilink") FIR filter, and then we send it through a
[ wideband FFT](fft_wideband_real "wikilink") for channelization. Since
there is a 16:1 demux, we use a streaming parallel FFT architecture with
16 streams of real input. This gives 8 streams of complex output, and
there are 64 channels, so we get a full window of channelized data every
8 clock cycles.

**Status:** Complete, but only runs at 1.6GHz.
[Simulink](http://casper.berkeley.edu/svn/trunk/projects/isi_correlator/tests/demo_fengine.mdl).
[Python](http://casper.berkeley.edu/svn/trunk/projects/isi_correlator/isipy/demo_fengine.py).

## Board Interconnect

The board interconnect distributes F-Engine data to the appropriate
X-Engines.

Each F-Engine generates 64 channels of data per telescope. Each X-Engine
processes roughly 1/3 of that. So the interconnect divides the data into
three groups and packs the data for transmission. It sends one group
into a local buffer and two groups to the other two boards, and it
simultaneously receives two data groups from the other two boards. It
re-aligns them with the locally buffered data group, unpacks the data,
and sends them on to the X-Engine.

**Status:** Complete. Only tested at 1.6GHz.
[Simulink](http://casper.berkeley.edu/svn/trunk/projects/isi_correlator/tests/demo_interconnect.mdl).
[Python](http://casper.berkeley.edu/svn/trunk/projects/isi_correlator/isipy/demo_interconnect.py).

## X Engine

The X-Engine computes cross-multiplications for \~1/3 of the frequency
bins.

Each X-Engine receives three channels worth of data from all three
F-Engines on every clock cycle. Each channel of data is 8 bits of
complex data (4 real / 4 imaginary). For each channel, they compute all
autocorrelation and cross-correlation products, and then take the powers
of each of these, giving a total of nine correlation terms.

There are 64 channels, and each X-Engine processes 3 channels per clock.
As described earlier, the F-Engine produces one full data window every
eight clock cycles, so each X-Engine must process 24 channels worth of
data. This means we are actually processing 72 channels worth of data,
even though we're only using 64 of them. This is wasteful, but it
simplifies our design by allowing us to run identical gateware on all
three boards. So, one board receives only 2 channels of actual data per
clock cycle (with the third channel as just zeros).

**Status:** In progress. Working on fast data readout.
[Simulink](http://casper.berkeley.edu/svn/trunk/projects/isi_correlator/tests/demo_xengine.mdl).
[Python](http://casper.berkeley.edu/svn/trunk/projects/isi_correlator/isipy/demo_xengine.py).

## Software

The correlator consists of three main software components:

1.  a [Simulink
    model](http://casper.berkeley.edu/svn/trunk/projects/isi_correlator/models/isi_correlator.mdl),
    which runs on the ROACH FPGA,
2.  some C code, which runs on the ROACH PowerPC, and
3.  a [Python
    script](http://casper.berkeley.edu/svn/trunk/projects/isi_correlator/isipy/isi_correlator.py),
    which runs on a control computer.

The Python control script uses several libraries, which are built upon
the [Corr](Corr "wikilink") library, [NumPy](http://www.numpy.org),
[PyGTK](http://www.pygtk.org), and
[matplotlib](http://matplotlib.sourceforge.net).

## References

  - [Infrared Spatial Interferometer Array](http://isi.ssl.berkeley.edu)
    at SSL. (official site)
  - [Infrared Spatial
    Interferometer](http://en.wikipedia.org/wiki/Infrared_Spatial_Interferometer)
    on Wikipedia.
