The CASPER correlator is a packetized, highly scalable design currently
using iBOB hardware for the "F engine" and BEE2 hardware for the "X
engine". See also [Correlator users
guide](Correlator_users_guide "wikilink") and [International Correlator
Collaboration](International_Correlator_Collaboration "wikilink"). For
information about correlator scaling, see [Dan's Quotes on
Scaling](Dan's_Quotes_on_Scaling "wikilink").

## History

The CASPER correlator started as a non-packetized 8 antenna design based
around 4 iBOBs and 1 BEE, built by Aaron Parsons. Dan Werthimer
envisaged a packetized design which Aaron Parsons began implementing
until his departure for Arecibo in July 2007 at which time development
was continued by Jason Manley.

## Team

### Current

  - Jason Manley (MeerKAT) (co-ordinator, hardware, software
    development) - jason underscore manley at hotmail dot com
  - Dan Werthimer (CASPER) (architecture consultant)
  - Henry Chen (CASPER) (Simulink and hardware consultant)
  - Billy Mallard (CASPER) (firmware/software)
  - Griffin Foster (CASPER) (software development)
  - Luca Zoni (INAF Italy Medicina) (firmware development)
  - Marco Bartolini (INAF Italy Medicina) (software development)
  - Richard Armstrong (Oxford) (Beamformer)
  - Sandeep Chaudhari (GMRT India) (firmware)
  - Mekhala Muley (GMRT India) (firmware)
  - Shelton Gnanaraj (GMRT India) (firmware/10GbE)
  - Andrew Martens (MeerKAT) (firmware/library maintenance)

### Previous team members

  - Aaron Parsons (CASPER and UC Berkeley Astronomy; currently a postdoc
    in astronomy at UC Berkeley working on
    [PAPER\_Correlator](PAPER_Correlator "wikilink"))
  - Terry Filiba (CASPER) (EECS graduate student UC Berkeley; currently
    working on spectrometers)
  - Arash Parsa (ex-CASPERite; currently graduate EECS student at UC
    Berkeley)
  - Mathias Humbert (EPFL, visiting Berkeley EECS)

## Explanation of Operation

This section will be populated in time... until then, here is a
presentation outlining
operation:[Media:packetized\_correlator\_signal\_flow.pdf](Media:packetized_correlator_signal_flow.pdf "wikilink")

The following diagram illustrates the system interconnect and outlines
the basic operations of each engine:

![Correlator\_block\_diagram.png](Correlator_block_diagram.png
"Correlator_block_diagram.png")

## Software and Firmware

### Software

Control & monitoring scripts are written in Python. They wrap a lite
version of the KatCP control framework client (native to ROACH,
retro-ported to BEE2). Check out the latest version from SVN (see
details below).

Development on 10GbE-output began with software package corr-0.3.0. It
was based on the lightweight UDP framework and has been deprecated by
the corr-0.4.0 version. Versions prior to 0.3.0 used the natively python
borphserver developed by Aaron Parsons.

### Firmware

Note that the F engine currently uses the deprecated ASTRO library, but
the X engine uses the CASPER library.  
X engine revision 310 will include 10gbe output. No change to F engine
required. 10GbE subsystem overhauled to prevent lockups.  
X engine revision 309c adds support for mis-matched numbers of F and X
engines, running at different speeds.  
X engine revision 309 and F engine revision 303 implements generic ibob
communication protocol and per-antenna EQ.  
X engine revision 308 and F engine revision 302 packetizes the F engine
output locally and adds support for transmitting ADC RMS levels in-band
across the XAUI cable.  
X eng rev 307 and F engine 301: First fully-functional release based on
"Pocket Correlator".

### SVN repository

To checkout the current development version of all correlator-related
code:

`svn checkout `<http://casper.berkeley.edu/svn/trunk/projects/packetized_correlator>

Checkouts can be done anonymously.  
Commits require a username and password.

F-engine model files are in the ibob subdirectory.  
X-engine model files are in the bee2 subdirectory.

## Deployments

### PAPER GB

Deployment at Green Bank, WV was completed in January 2008. This is
initially an 8 antenna system using X engine design revision 307d and F
engine revision 301. The intention is to grow the array (and the
correlator) in time, ending with 128 dual-pol antennas and 100MHz
bandwidth.

This deployment has proven successful. Firmware has since been upgraded
to F\_rev302 and X\_rev308d.

The system will be updated to a 16 antenna dual-pol design in Nov 2008
using F\_rev303 and X\_rev310 by adding one BEE2 and another four IBOBs.

### Medicina Italy

Deployment of a 32 single-pol input system based on one BEE2 and 8
IBOBs, processing 40MHz bandwidth in 2048 frequency bins. It is using
F\_rev303 and X\_rev309c. Further details here :
[Medicina\_Correlator](Medicina_Correlator "wikilink").

## Deployment requirements

Many telescope installations have expressed interest in the design. The
following table summarises the different requirements. For further
details, see the wiki page
[International\_Correlator\_Collaboration](International_Correlator_Collaboration "wikilink").

|           |                 |          |                     |        |        |           |                |                                                                                                                               |
| --------- | --------------- | -------- | ------------------- | ------ | ------ | --------- | -------------- | ----------------------------------------------------------------------------------------------------------------------------- |
| Name      | Deployment date | n\_ant   | BW (MHz) x IF Freqs | n\_pol | stokes | n\_chan   | dump times (s) | other                                                                                                                         |
| CARMA     | 2010            | 15 + 8   | 500 x 16            | 2      | full   | 1k        | 0.5            | spectrum zoom; 90d/180d Walsh cycles; 15 CARMA + 8 SZA ant                                                                    |
| meerKAT   | 2012            | 80       | 512                 | 2      | full   | 16k (64K) | 0.1-10         | phase switching, fringe stopping, delay tracking                                                                              |
| PAPER     | 2009            | 128      | 100 x 1             | 2      | full   | 2-4k      | 1-10           | QADC; coarse delay; no delay/f.rate tracking; narrow band subsystem for ORBCOM sat?                                           |
| GMRT      | 2009/2010       | 32       | 400-500 x 1         | 2      | full   | 4-8k      | 1              | incoherent & phased array beams (at microsec dump rates), delay tracking, fringe rotation, phase switching, sub-array support |
| SKA Italy | 2008            | 32       | 32 x 1              | 2      | full   | 2k        |                |                                                                                                                               |
| ATA       | 2009            | 42-\~100 | 500-600 x 4         | 2      | full   | 4k        | 0.001          | zoom, subarrays                                                                                                               |
| FASR      | 2011            | 64       | 500 x 1             | 2      | full   | 4k        | 0.02           | phase switching, fringe rotation, delay tracking, coarse delay                                                                |
|           |                 |          |                     |        |        |           |                |                                                                                                                               |

## Development plans for 2008

In order of priority:

### 10 Gbe output & High speed readout

  - Assigned to: Jason
  - Expected completion: March '09
  - Status: under development

12 Feb '09: New packet format has delayed 10GbE output integration: KAT
have requested a change in format to match their internal packet
formats. The proposed format is much more flexible than the original
one. Before having even finished testing the previous arrangement, I am
switching to this new packet format.

19 Dec: Ready to test new firmware. Awaiting high-speed capture code.

10 Oct: Entire 10GbE subsystem overhaul. Blocks now provide backpressure
by default, after discovering strange 10GbE block behaviour. Obscure bug
in descramble block is preventing system from sync'ing.

06 May: Ready to test new firmware blocks. Awaiting correlator hardware
in South Africa. Expect completion in June. Python code modified to cope
with new packet format (corr-0.2.1 package). Testing found current
hardware and Python code to be too slow (1.7GHz single core 100Mbps
laptop). In process of switching to 10GbE and C code on new hardware
platform.

### Data acquisition in C

  - Assigned to: Billy & Griffin
  - Status: In progress
  - Expected completion: Nov '08
  - To date: High-speed capture code written and waiting to be tested.
    Currently working on formatting data for UV file output.

### Port to ROACH

  - Assigned to: Jason Manley & Andrew Martens
  - Expected completion: Mar '09
  - Status:

12 Feb '09: QDR vector accumulator has been created and tested with a
single roach board. Requires modifications to X engine block to only
output 32-bit data. Awaiting sufficient hardware to test
fully-integrated correlator system.

19 Dec 2008: Initial core X engine ported to 10.1 and bitstream
successfully compiled for ROACH. Still requires new vector accumulator
targetting ROACH QDR memory. Awaiting additional ROACH hardware in Feb
2009 for testing. F engine port not yet started. Awaiting simulation
verification of new PFB and FFT blocks. Will also need new corner-turn
block utilising ROACH QDR memory

### X engine Conjugation mod

  - Assigned to: Hardware: Jason ; Software: Billy, Griffin
  - Status: Currently fixed in PP, awaiting C receive code. Jason busy
    with hardware fix.

Last triangle of X engine is conjugated (see correlator operation
presentation for output order details). Proposal to correct this in
software receive code at the same time as arbitrary antenna input
reordering. To be implemented in C receive code. Hardware fix required
for KAT.

### Fine delay and fringe rotation

  - Assigned to: Mekhala
  - Expected completion: Feb 2009
  - Requires: Modified sin/cos generator to allow multi-output phased
    offsets in order to process wideband signals. Operates on full
    bitwidth post-FFT signal.
  - Status: 01 Dec 2008: Initial work begun

### Monitoring & Control

  - Assignend to: Jason
  - Status: continuous development

Dec 2008: Porting to katCP control framework. Created KatCP\_lite python
client. Busy debugging.

### Quad ADC and low bandwidth version

  - Assigned to: Jason, Billy, Henry
  - Status: QADC hardware tested.
  - Required work: low-bandwidth FFT mod (switch to real FFT) in F
    engine.

### ADC histogram/snap block

  - Assigned to: Luca Zoni
  - Status: Test in progress

### Test bigger switches

  - Assigned to:

### 90/270deg phase switching

  - Assigned to: Billy
  - Status: Preliminary investigation.

### non-2^n antennas

  - Assigned to: Terry
  - Required work: Initially, changing addressing target X engines

### Phase/Walsh switch

  - Assigned to:
  - Work required: add block to F engine
  - Estimated completion: scheduled to start development in 2010

### Add Beamformer functionality to X engine

  - Assigned to: Richard
  - Work required: Add "B engine" to X engine
  - Comments: Originally the beamformer was to be constructed on a
    separate set of hardware. However, it is now believed that it would
    be simpler and make more efficient use of hardware resources to add
    the ability to form a single beam in the existing correlator's X
    engine. For additional beams, additional hardware can be
added.

![correlator\_beamformer\_block\_diagram.png](correlator_beamformer_block_diagram.png
"correlator_beamformer_block_diagram.png")

### High bandwidth design

  - Assigned to: Jason and Andrew
  - Work required: replacing complex FFT\&PFB with wideband FFT
  - Expected completion: Scheduled to start in Feb 2009

First instrument will be ROACH-based pocket correlator.

### Output frequency subset

  - Assigned to: Jason and Andrew
  - Work required: modifications to F engine
  - Expected completion: Scheduled to start in Feb 2009

First instrument will be ROACH-based pocket correlator.

### Zoom

Allows system to "zoom in" on a frequency band. Can be implemented in
one of three ways:

  - Fixed N chan, decrease bandwidth. Easy (reduce F engine clock rate)
  - multiple sub-bands (likely implementation, can piggy-back off
    existing blocks)
  - N\>\>, B\<\< (Difficult, requires significant mods to existing
    blocks)

## Completed Mods

### Coarse delay

  - Assigned to: Mekhala
  - Status: Complete and tested, added to mlib\_devel\_7.1 library in
    Dec 2008.

Fully parameterised and able to process wideband signals. Allows runtime
configurable delay to within one sample clock.

### X engine loopback lockup fix

  - Assigned to: Jason
  - Status: Bug found 2008/10/10 and corrected in X engine rev310.

The problem was a symptom of another issue: The 10GbE receive fifo would
stop providing a valid signal if it overflows (even though there is
still valid data in the buffer) and would not provide another valid line
until the ACK signal was preemptively pulsed.

### Benchmark 10Gbe Acquisition

  - Assigned to: Jason & Terry
  - Status: Completed 2008/03/20. See CASPER memo \#21 for updates.

Constructed test-suite for benchmarking 10GbE network cards/switches.
Bitstream compiled for BEEs which allows control of datarate and packet
sizes. C capture/analysis code. Python control code needs to be ported
to UDP framework.

### Monitoring & Control Software

  - Assigned to: Jason
  - Status: Completed 2008-03-18. Corr-0.3.0

Some scripts show speedup of more than 10x. Speeds are now fast enough
for control of larger systems.

### Generalise iBOB register read/write over XAUI

  - Assigned to: Jason
  - Status: 2008-02-22. Partially completed.
  - Details: Done to cope with EQ per antenna. BEE -\> iBOB
    communication now generalised. Generalised iBOB-\>BEE not done.
    Further development halted as ROACH makes this redundant.
  - Goal: Will allow registers to be read from/written to on the iBOB by
    the BEE over free bandwidth on existing XAUI cables. Requires
    generalisation of "read ADC levels" block and reallocation of
    register assignment. To be completed in conjunction with
    "Equalisation per antenna"

### Equalization per antenna/pol

  - Assigned to: Jason
  - Status: Completed, 2008-02-22, F.rev303 and X.rev309
  - Implementation: Two EQ blocks, separately programmable over XAUI
    ports. Possible further improvement: allow scaling of EQ for
    separate polarisations.

### iBOB Packetization

  - Assigned to: Jason
  - Status: Completed 2008-01-30, rev308d
  - Benefits: Improved system reliability. Access to registers
    indicating XAUI failure rates.
  - Implementation: Basic header added to packet stream by iBOB (MCNT
    and antenna number). IP address and antenna number offsets added by
    BEE based on software register setting (as in Rev 307 firmware).

### Read ADC RMS levels

  - Assigned to: Jason
  - Status: Completed Wed, 09 Jan 2008. F\_rev302, X\_rev308.

Implementation: ADC levels are squared and accumulated on the F engine
before being quantised to 16 bits and transmitted in-band across the
XAUI as a single 64 bit word between ordinary data-valids. OOB
signalling is used to distinguish ADC level data from ordinary data.

### 32-ant design

  - Assigned to: Jason
  - Status: Awaiting C acquisition code to test.
  - Required work: Overhaul receive software.
  - To date: Firmware rev 309a compiled with two X engines per FPGA.
    This required sacrificing debug tools to make it fit. Design syncs
    properly.

## Diagrams

OmniGraffle source for many of the diagrams featured in CASPER memos,
posters and presentations by CASPER collaborators is available
[here](Media:Correlator_omnigraffle.tar.gz‎ "wikilink").
