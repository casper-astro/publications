## ROACH CORRELATOR COSTS

Werthimer, Wright, Backer, Manley 12may07. Manley update: 12July09

The hardware costs for replication of a ROACH-based correlator are an
issue of consideration in the discussions.

### Comparison to IBOB/BEE2 Processing Abilities

We had hoped that a ROACH would have a comparable processing ability of
a BEE2 because it'd have twice the capacity and run at twice the speed.

The SX240 is not available in the ROACH1's 1136 pin package. ROACH2 will
target the larger 1738-pin package and should become available towards
the end of 2009. It will include an additional two CX connectors and
potentially an extra DRAM DIMM slot.

Capacity-wise, (on paper, at least) a ROACH2 with an SX240 would be
roughly equivalent to 3/4 of a BEE2. The initial ROACH1 with an SX95
doesn't make half a BEE2 as it is BRAM constrained (SX95 is about 3/8 of
a BEE2's BRAM). BRAM is the current limiting-factor for the X engine and
will become the limit for FFTs in the F engine. As an aside, the fact
that the SX95 has more BRAM than the LX110 is what motivates the choice
to select the SX95 FPGA instead of the LX110 part for ROACH1. An SX95
ROACH1 has between 2 and 3 times the processing capacity of an IBOB's
2VP50, depending on your metric.

In terms of operating speed, initial investigations suggest that the
ROACH board will run at typical speeds of 250MHz, the limitation being
the controllers for the peripheral cores used. If no peripherals are
required (10GbE, DRAM, QDR etc), then speeds closer to 350MHz should be
achievable. Work will be ongoing through 2009 to improve the speeds of
the peripheral cores in order to increase typical operation speeds. As
of Dec 2008, ROACH has a processing speed improvement of at least 1.25x
faster than the legacy hardware (250MHz vs IBOB/BEE2s' 200MHz).

Thus, in terms of raw processing power, an SX240-equipped ROACH2 could
replace a BEE2, or 6 IBOBs. An SX95-equipped ROACH1 would be around half
a BEE2 or 3 to 4 IBOBs. It needs to be considered that practically this
additional processing power would not always be easily realisable: The X
engines can reasonably effectively load-share at any incoming F engine
rates; but for F engines, processing a 150MHz band on a board running at
250MHz (for example) would be an inefficient operation - we'd run the
boards at 150MHz anyway, losing the speed advantage that ROACH offers.

We would thus like to caution designers against using raw processing
power as a metric for determining hardware requirements, but to also
consider the mapping of the algorithms into the hardware and the losses
this might incur.

### Hardware Costs

A 2008 costing of the ROACH board is 2500 USD; completing this with
Xilinx Vertex 5 chip, would bring it to 4500 USD; for simplicity and
perhaps providing some overhead for case, power supply and cabling,
let's call this 5000 USD. The 2GSa/s ADC is 1200 USD ea for low
quantities and under 500 USD for larger quantities. One ADC is required
per dual-polarization antenna. Thus, the total cost for a fully
populated ROACH is about 6000 USD.

### Mapping to Correlator Requirements

With current hardware, we can get 2 "F" engines per IBOB with 2048
channels and a top speed of 200MHz. "X" engines: two 32 antenna X
engines per BEE2 user FPGA, again with a top speed of 200MHz. The
current 32 antenna, 200MHz correlator requires 16 IBOBs and four BEE2s
(16 user FPGAs). If the speed of F engines (bandwidth) equals the speed
of X engines (clock rate), the ratio of required F:X engines is 1:1.

#### Ethernet switch requirements

Switch port requirements scales linearly with the number of antennas and
the bandwidth. A single antenna, dual polarization complex data stream
of \~450MHz with 4-bit samples will tie up a full 10Gbe port. Ports on
10GbE switches come in at the 300 to 1000 USD level. For simplicity, we
will assume 500 USD per port.

Cost (switch) = 500 x N x B/450MHz

#### F engine

The "F" operation for 2 antennas and 2 polarization lines from each at
250 MHz with 8k channels can, nominally, be done in a single ROACH
board. Computation requirements scales linearly with the system
bandwidth and logarithmically (barring memory requirements) with the
number of frequency channels. Memory requirements scale linearly with
FFT size. It is not yet known for certain that delay/fringe rate
computation will fit with this F design. However, FFT length can be
traded for these additional features. We will assume 4k channels for
costing

Thus, assuming higher volume ADCs,

Cost (F engine) = 6000 x N x B/500MHz x (1+log(C/4k)) USD

#### X engine

The computation required for the "X" operation depends on the number of
antennas (scales with N^2) and the bandwith to be processed (scales
linearly). Nominally, one X engine of length suitable for 64 antennas
should fit on one ROACH board and each engine will process 250MHz/64
bandwidth. No ADCs are required for these ROACH boards.

A simplified cost estimation equation of the X engine requirements is
then

Cost (X engine) = 5000 x N^2 /64 x B/250MHz USD.

#### Total

More work is needed to assess the cost algorithm and ability of design
to include such items as delay/rate tracking; walsh switch cycles; etc.
Note that non-binary numbers of antennas is currently not an option.

Cost = 12BN x (1.1 + log(c/4096)) + 0.3125BN^2 USD

Where:

  - B is bandwidth in MHz, rounded-up to be one of \[125MHz, 250MHz,
    500MHz, 1GHz, 2GHz\].
  - N is the number of dual polarisation antennas and N=2^?.
  - C is the number of frequency channels and C=2^? and C\>64.

#### Examples of Efficient mapping of ROACH processing ability:

Assuming a board speed of 250MHz:  
  
F engine (one F engine accepts dual-polarised data): Two 250MHz, 8k chan
engines on one ROACH, or, two 500MHz, 4k chan engines, or, one 500MHz,
8k chan engine.  
X engine (assuming SX95): two 32 antenna X engines per ROACH or one 64
antenna engine.  
  
Thus, for 32 antenna, dual polarisation, full stokes, 250MHz, 8k channel
system: 32 ROACH boards. Or, with 500MHz bandwidth, 4k chan, 48 ROACH
boards.  
  
The grand total for 32-antenna, 500-MHz, 4k-channel, full Stokes
correlator is \~275,000 USD without computers and attendant disks, etc.
This is replication cost with little room for system integration.

## CARMA Correlator

Hawkins 08may07

Current systems:

  - Antennas; 15-CARMA antennas (http://www.mmarray.org/), 8-SZA
    antennas (http://astro.uchicago.edu/sza/)
  - Bandwidth; CARMA has 4GHz IF double-sideband. SZA has 8GHz IF
    single-sideband.
  - Polarization; single (currently)
  - Phase-switching; 180-degree phase switching at 1024pps (977us
    period, 950us correlation time), with a Walsh-sequence length of
    16-states (15.625ms completion time). 90-degree phase-switching at
    64Hz (15.625ms period), i.e., every time a 180-degree sequence
    completes.
  - Delay tracking; phase-offset (lobe-rotation) and phase-slope
    correction. Primary lobe-rotation, or phase-offset tracking, of the
    first LO is implemented in the LO analog electronics. Secondary
    lobe-rotation of the bands downconverted within the 1GHz to 9GHz IF
    band, must be tracked in the digitizer board. For example, the phase
    of the numerically controlled oscillators (NCOs) used to mix the
    positive-frequency signal to complex-baseband can be used to
    compensate the phase. Delay-slope correction is implemented at the
    whole-sample scale using FPGA memory resources, and logic element
    multiplexers, while sub-sample delay correction is implemented using
    asymmetric FIR filters with re-loadable taps. Tap updates occur on
    the 90-degree phase-switch timescale.
  - Bands; CARMA has 3 independently tuneable bands, soon will have 8.
    SZA has 16 500MHz bands (covering their 8GHz IF).
  - Bandwidth modes; 500MHz, 250MHz, 125MHz, 62MHz, 31MHz, 8MHz, and
    2MHz.
  - Downconversion; analog downconverters are used to extract either a
    500MHz band, or a 250MHz band from the 1GHz to 9GHz IF. Two analog
    filters are used, as the 250MHz filter has a flatter passband than
    the 500MHz filter. The 250MHz signal is sampled at 1GHz clock rate,
    and then FIR filtered into the 250MHz bands and lower.
  - Readout times; 90-degree Walsh phase-switching completes every
    250ms. Readout times are nominally every 500ms from the hardware to
    the pipeline processing machine (which receives data from all
    baselines in all bands). Data typically arrives at the processing
    machine within about 100ms of a 500ms boundary (relative to a 1pps
    GPS reference).
  - Channel resolutions; 500MHz mode produces about 100-channels, while
    spectral modes produce up to 1k-channels. Both auto-correlation and
    cross-correlation spectra are generated, with identical channel
    resolutions.

Future systems / wish-list:

  - 23-station correlator (CARMA + SZA antennas)
  - 8GHz IF double-sideband
  - Selectable processing of single- or dual-polarization
  - \`Buddy antenna' phase-tracking system. We plan to utilize cheaper
    antennas paired with the CARMA/SZA antennas, to track the phase of a
    calibrator. The phase-estimate from the tracking system would then
    be applied as a phase-correction to the radio-source data received
    on the CARMA/SZA antennas (at 500ms timescales). Requires a
    low-cost, wideband, coarse resolution, correlator.
  - Option; copy MeerKAT 32-antenna bands to create 23-antenna 500MHz or
    1GHz bands.
  - Option; Direct digitization of the full IF using 20GSps digitizer
    (from Agilent via BWRC). Filter the 10GHz sampled band (8GHz
    useable) into multiple (16) 500MHz (or narrower) bands. Send the
    multiple bands into parallel CASPER processing backends.

## PAPER/CASPER Correlator

Backer 08may06; 09nov24 update

PAPER (Precision Array to Probe the Epoch of Reionization) is a 100-200
MHz dipole array being deployed in Green Bank (PGB) and in South Africa
(PSA); <http:astro.berkeley.edu>:\~dbacker/eor. PGB is 16 antennas,
single polarization, and will grow to 32 antennas, dual polarization by
2010 March. This is our testbed array. PSA was deployed in 16-dipole
configuration for a 7-day run in 2009 October, and will be expanded to
32 dipoles, full Stokes in 2010 January. A CASPER FX packetized
correlator for 8 antennas, full Stokes and 150-MHz bandwidth is in use
on PGB; this will be expanded to 32 antennas in early 2010. The
32-antenna correlator architecture is QuADC, IBOB and ROACH hardware
boards.

To Be Done:

  - convert CASPER correlator design to 10 Gbe output
  - develop Monitor, Control, Data Acquisition (MCDA)
  - lab test 32-antenna
  - field test 32-antenna unit
  - add coarse delay to F-engine to allow varying cable lengths
  - add QuADC input statistics monitoring
  - grow antenna inputs to 64 for 2010 campaign; i.e., complete by 2010
    June
  - possibly add phase switch to remove ADC cross-coupling

## ATA Correlator-Beamformer-Imager (CoBI)

Backer 08may07; 09nov24 update

The current ATA correlator is an FX correlator designed by Lynn Urry.
Bandwidth is 100 MHz. Units with 64 IF inputs and integration time down
to 2.5s are available. More complete description can be updated by
Wright or MacMahon. A next generation, 500-MHz bandwidth
correlator-beamformer-imager is being developed in collaboration with
KAT team (see below), ASIAA (Taiwan), Brigham Young University and
Caltech. A first step is being taken with a "pocket" version, PoCoBI. An
NSF ATI proposal was submitted 2009 Nov for 2010-2011 effort.

Features:

  - 500-MHz bandwidth
  - integrate with KAT ADC (see following)
  - minimum 4k channel PFB
  - delay/phase tracking in F engine either pre/post PFB
  - walsh switching drive waveform output and digital inversion on ADC
    input
  - integrated beamformer (one or more pointings; feed pulsarometer,
    setiometer)
  - stream packetized correlations (uv data) to 10 GbE switch for
    cluster cpu/gpu
  - 10-ms integration (goal..1 factor of 10 at a time)
  - realtime imaging (and rfi excision and adaptive calibration)

## Karoo Array Telescope

The Karoo Array Telescope (KAT) is South Africa's SKA pathfinder array.
It will be built in two stages:

1.  KAT-7 demonstrator array with seven antennas, itself in two phases.
2.  MeerKAT, the full 80-dish array.

### KAT-7 precursor

Manley original; Marten update 09nov23; Manley update 2010aug18.

As a precursor to the KAT-7 digital backend (DBE), a pocket-correlator
instrument will be constructed for primarily for debugging dishes,
pointing subsystems, RF feeds and frontends. It is known internally as
the "Fringe-Finder". This device will be co-housed in the antenna
control container and not in the computing container (as such, it needs
to be compact). It will be the first complete product developed in
collaboration with GMRT. Target completion is mid-2009 with deployment
by year-end.

Features:

  - Based on a single, stand-alone ROACH board.
  - Four inputs, usually mapped to two dual-pol antennas in the KAT
    application.
  - Will not require a computer to operate, beyond storing data (option
    to store data directly using external USB harddrive).
  - 500MHz bandwidth (processed using wideband real PFB/FFT blocks).
  - Hardware interpolated fringe rotation.
  - Coarse delay and fine delay (maximum coarse delay length will be
    BRAM limited).
  - Arbitrary per-channel phase and amplitude correction with update
    rates of \<10 seconds.
  - Synchronous control of external noise diodes at antennas.

Current system has following specs:

  - 4 input (2 dual-pol or 4 single)
  - 400MHz
  - 512 channel (4 tap PFB FIR)
  - coarse delay allowing up to 2047 clock sample delays
  - 32-bit DRAM based accumulator
  - current data output is via 1Ge ethernet link
  - \~60% BRAMs, \~90% DSP48Es, \~80% registers, \~70% LUTs, \~90 slices
    used
  - \~100ms dump times supported

Planned future upgrades:

  - add fine and fringe delay block in development in collaboration with
    GMRT

### KAT-7

The KAT-7 correlator will be based on next-generation hardware platform,
ROACH. The firmware will be based on PAPER's 8 antenna design currently
deployed in Green Bank. ROACH's architecture closely resembles that of a
BEE2, which should enable us to port the existing CASPER/PAPER
correlator design to the new platform without too much difficulty.

Basic specifications for first phase (end 2010) are as follows:

  - 8 dual-polarisation inputs (7 antennas + 1 test input).
  - 512MHz instantaneous bandwidth (IF center frequency 256MHz,
    Fsample=1GHz, selectable output frequency channel subset).
  - 1024 frequency channels.
  - Programmable integration periods down to 100ms.
  - Coarse and fine delays.
  - Hardware interpolated fringe rotation.
  - Arbitrary per-channel amplitude and phase correction.
  - Time-syncronisation and up-front packet time-stamping synchronised
    to an external 1PPS input.
  - Synchronous control of external noise diodes at antennas.
  - Continuous raw data capture on all antenna inputs (not simultaneous
    with correlator operation).

KAT-7 will use the KATADC with onboard analogue amplitude control
(-11.5dB to +20dB in 0.5dB steps). It also has the ability to switch out
the analogue input to a 50ohm terminator in case of over-range inputs
that could damage the device.

KAT requires a beamformer mode, which will amount to an addition to the
X engine. This will be completed in 2011.

The following diagram illustrates KAT-7's proposed Digital Backend
architecture:

![KAT-7\_architecture.png](KAT-7_architecture.png
"KAT-7_architecture.png")

### MeerKAT

Targetting 64 antennas (Gregorian offset, 13.5m effective), with 1024MHz
of instantaneous bandwidth (phase 1) and 2048 frequency channels and 8km
baselines (phase 1), MeerKAT will be a significantly more challenging
technically than KAT-7. The datarates from this instrument are
signficantly higher than KAT-7 and at this stage it would seem
unreasonable to expect to be able to capture raw data from each antenna.
It is still unclear if MeerKAT will use ROACH-II hardware, or an
entirely new board. The technical requirements have yet to be finalised.

Phase 2 will add a spur of 60km and increase the bandwidth, including a
new low frequency feed. Phase 3 and 4 are not yet well defined.

MeerKAT will require a new ADC(s).

-----

## GMRT Correlator

Gupta, July 2008

The GMRT consists of 30 antennas, each of 45 meter diameter, operating
in interferometric and array mode. The present configuration processes a
maximum of 32 MHz bandwidth in each of 2 orthogonal polarizations, using
an ASIC based FX correlator that gives 256 channels across the band. An
array processor attached to the output of the F stage of the correlator
produces a single incoherent and coherent beam output for pulsar work.

The GMRT is going for an upgrade where the maximum instantaneous
bandwidth will be 400 MHz. For this, a back-end with the following
specifications is required :

  - Number of stations : 32
  - Max instantaneous BW : 400 MHz
  - Number of spectral channels : 4-8 K
  - Number of input polarizations : 2
  - Full Stokes capability
  - Dump times : 1 sec or better
  - Coarse and fine delay tracking
  - Fringe rotation
  - Walsh switching
  - Subarray support
  - Incoherent and phased array beams (for pulsar work)

Time scale for implementation : late 2009 / early 2010

## FASR Correlator

Hurford/Bastian, July 2008

The Frequency Agile Solar Array is a radioheliograph designed to perform
ultra-broadband imaging spectroscopy, spanning 50 MHz to 21 GHz using
three arrays of antennas (FASR-A, -B, and -C). These will share a common
correlator and data system. FASR is currently in its design and
development phase pending NSF-ATM approval for construction funding.

  - Number correlator inputs: 64
  - Number pol'n channels: 2
  - Bandwidth: 500 MHz
  - Number frequency channels: 4096
  - Stokes: full
  - Dump time: 20 ms
  - Phase switching, coarse/fine delay, fringe rotation
  - Onboard computation of signal moments, each channel after F, before
    X
  - Subarray support

Time scale for implementation: 4 station engineering prototype in
2010-11; full deployment in 2011-12

## Medicina Correlator

Medicina, Italy, October 2008

Deployment and some early results are described at
[Medicina\_Correlator](Medicina_Correlator "wikilink").

*detailed description coming soon*

  - Number correlator inputs: 32
  - Number pol'n channels: 1
  - Bandwidth: 16 MHz
  - Number frequency channels: 2048
  - Stokes: full
  - Dump time: 30s
