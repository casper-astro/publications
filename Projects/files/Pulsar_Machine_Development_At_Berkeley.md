Up: [Pulsar Machines](Pulsar_Machines "wikilink")

## ATA Pulsar Processing

There are two forms of signal processing that are used in pulsarometry:
incoherent wherein the volt- age signal is detected and then averaged
and analyzed; and coherent wherein the dispersion from propagation
through interstellar thermal plasma is removed in voltage domain,
typically via Fourier transform–multiply by inverse dispersion
filter–inverse transform. Current coherent dedispersion pro- cessors
at the Green Bank, Arecibo and Nan¸cay telescopes feed 32 4-MHz signals
to a cluster of 20-60 linux boxes. This is a modest cluster. A modern
cluster of similar size (approximately $75k) can probably handle 200-MHz
bandwidth. The scientific application of coherent dedispersion,
particularly at decimeter wavelengths, is mainly focused on the faint
millisecond pulsars. While some of these can be detected with the modest
sensitivity ATA-42, and even ATA-84, it is not clear about the urgent
science that can be done. If one gives up on millisecond pulsars and
focuses instead on the science with slow pulsars, then a lower demand on
cpu resources follows. A simple plan might be that shown in Figure 4: a
CASPER beamformer feeds an IBOB that performs a fairly high resolution
PFB, 2k or 4k, or more? The result is detected including polarization
cross terms and that power vector is averaged down to 0.1-1.0
millisecond. The resulting modest data rate signal is then sent to a
small linux cluster for subsequent analysis: single pulses, average
pulses, dynamic spectra etc.

The [Berkeley ATA Pulsar Processor](BAPP "wikilink") was deployed to the
ATA in March 2008, and the first detection of PSRB0329+54 took place in
April 2008.

## Midend DSP at Arecibo/Green Bank/Nancay

[Nancay CoDeDi Pulsar Machine](Nancay_CoDeDi_Pulsar_Machine "wikilink")

If the IBOB delivered raw complex voltage data from a coarse PFB with
4-10 MHz channel bandwidths to linux cluster nodes, then such a board,
with ADCs would be ideal for a major upgrade of the G/ASP systems at
Green Bank, Arecibo and Nancay telescopes. There it could replace the
current downconvertors-samplers-PFB-dataservers hardware. The new system
would

  - Potentially allow more flexibility in the PFB parameters (smaller
    channels at lower frequencies)
  - Remove any remaining systematic issues due to analog downconversion
    / complex sampling.
  - Give \~25% more BW by freeing up data servers for computation.
  - Reduce data server maintenance

The main advantage of such an upgrade would be the increase of available
bandwidth. To exploit that advantage the upgrade should preferably be
combined with an upgrade of the currently limiting cluster CPU power.

Our primary program there is detection of stochastic background of
gravitational radiation by precision timing an array of millisecond
pulsars. As the ATA Gain/Tsys improves, this experiment can move to the
ATA whose frequency agility and available beam time are very attractive.
The implementation on these national facilities will serve the broader
community as well, particularly those involved with the Arecibo PALFA
program.

## Standalone Spectrometers for Parkes/HartRAO

We have developed a 400MHz, 1024-ch power spectrometer, named
[Parspec](Parspec "wikilink"), for Parkes (see [Swinburne
Instrumentation Projects](Swinburne_Instrumentation_Projects "wikilink")
and [Parkes HTRL
Survey](http://astronomy.swin.edu.au/pulsar/?topic=hlsurvey)). This has
been modified to a 400MHz, 512-ch "Full Stokes" spectrometer for
[HartRAO](http://www.hartrao.ac.za).

## Roadmap

    Digitizer to nodes:
    -------------------
    Here an iBOB splits the receiver bandwidth into sub-bands. These sub-bands are sent to a PC cluster 
      for further reduction ('coherent dedispersion')
    This is a setup that could replace (G)ASP
    
    1) two pols -> iADC -> PFBFFT -> Detect (incl. cross terms) -> Integrate -> Send to PC
       * on an iBOB
       * Proof of concept 
       * Parameter ranges: 
            BW ~10/100MHz, iADC 8 bits, PFB+FFT >=32 channels, Integrate ~1ms, bandwith to PC low (iBOB = ~50Mbps ethernet)
       * Power detection cross terms: l*conj(l), r*conj(r), real(r*conj(l)), imag(r*conj(l))
       ? Check with Dave M. on 100Mbit iBOB
    
    2) As 1, but output to 10Gbps ethernet packets, that a 10Gb->1Gb switch distributes over a cluster
       ? finally on an iBOB, possibly develop on a BEE2 (?)
       ? change from sending detected signal to sending raw complex voltage data
       ? first to single PC, then add routing scheme to send packets to nodes
       ? 10Gbps output once there's firm ware
    
    3) Increase capabilities: 
         BW 128-512MHz over 32(?) 4-16MHz channels at baseband sampling (no integration/accumulation)
         Output over 2 x 10GE if needed
    
    4) Add digital downconverter
         
    Filterbank:
    -----------
    Here an iBOB or BEE2 splits up the bandwidth in many channels. These are sent out to a data PC for
    reduction later ('incoherent dedispersion').
    
    5) As 3) but with tunable number of channels in 200MHz BW: 
       * up to 4096 channels 0.5MHz channels, integrate to keep data rate < 50MB/s
       ? on a BEE2 in/after the ATA beamformer
    
    6) Delay each channel appropriately, then add all to one output stream: on board
         incoherent dedispersion
       ? on a BEE2/ATA
    
    Coherent dedisperser:
    ---------------------
    Here a BEE2 splits up the bandwidth with a PFB into ~10MHz sub-bands. Each band is coherently 
    dedispersed.
    
    7) 200-800 MHz -> PFB FFT into Nx10MHz -> Each 10MHz: [Forward FFT -> 'chirp' -> Reverse FFT -> Send to PC]
       * Set up chirp function depending on DM
       ? fold, upload a polyco

## People

The four people involved are Don Backer, [Peter
McMahon](User:Pmcmahon "wikilink"), [Joeri van
Leeuwen](User:Joeri "wikilink") and Dan Werthimer.

We collaborate on the projects descibed here with Matthew Bailes
(Swinburne), Ismael Cognard (Nancay) and Paul Demorest (NRAO CV).

## ATA Pulsar Nodes

Two dual quad-core Xeon nodes were acquired in January 2008. [
Installation log](ATA_PuMa_NodeInstLog "wikilink"). [ Node
log](ATA_PuMa_FlyEye "wikilink").

## Status Updates

(By Peter. Contact peter \[at\] dotnet \[dot\] za \[dot\] net for more
information.)

**1 July 2007**: Project started.

**6 August 2007**: Development of Milestone \#1 nearing completion in
simulation. Detector and 16-vector accumulator (integrator for 4
parameters for each of 4 simultaneous frequency channels) built. Design
from ADCs to accumulator compiled for IBOB successfully, with \~80%
resource utilization.

**30 August 2007**: Milestone \#1 is complete in simulation. Issues with
new CASPER libraries have been resolved/mitigated. The design has been
built for hardware, and its correctness has been verified with a limited
set of tests. Output has been tested with RS232 serial and Lightweight
IP 100Mbit Ethernet. Work is in progress to visualize output on a PC,
after which a more rigous array of tests will be conducted.

**18 September 2007**: Visualization software for Milestone \#1 has been
completed. More tests have been done to check correctness of the output.
Input from signal and noise generators appears to yield the correct
results, but more thorough testing will be done when Joeri returns near
the end of the month. All issues that have arisen thus far have been
resolved.

**1 October 2007**: Further testing revealed a problem in hardware that
manifested itself as an asymmetry in the FFT output when a real signal
was inputted. This has now been debugged, and the cause was determined
to be "by design": the FFT block output is only accurate to a certain
number of decimal places. Further testing is underway. The backend
software is being rewritten in C, and will use Grace as its plotting
engine. This should enable easier testing.

**5 October 2007**: HP ProCurve 10GbE/1GbE hybrid switch successfully
tested with iBOB and 10GbE core, sending data from the iBOB to a single
computer on 1GbE.

**10 October 2007**: 10GbE/1GbE switch tested with two 1GbE nodes being
fed by one 10GbE node (an iBOB). Performance numbers obtained for one
and two 1GbE nodes showed the expected throughput, but with unacceptably
high packet loss (\~0.15%).

**19 October 2007**: Simulations done to better understand behavior of
Stokes calculations with noise inputs. Hardware results appear to be
consistent (correct order of magnitude).

**2 November 2007**: The design path fork has now happened - we are
currently working on an ATA filterbank design using biplex FFTs at low
bandwidth (200MHz), and the GASP-replacement coherent dedispersion
machine design, which has no accumulator. Tests were conducted that
confirmed that a high-bandwidth filterbank does not fit on the iBOB FPGA
when more than 32 channels are used, hence the switch to a low-bandwidth
design using biplex FFTs. This filterbank design will have a single
10GbE output to a single node. The GASP replacement design, however,
will use the space freed up by the absence of the vector accumulator to
include a "load balancing" mechanism to allow packets to be sent to
multiple 1GbE nodes at an aggregate bandwidth of \>14Gbps using two
10GbE connections (via the HP switch).

Issues with the new biplex PFB block have hampered efforts on the
filterbank - debugging is underway. Development of the "load balancing"
mechanism for the coherent dedispersion machine has started.

**11 December 2007**: Development has halted pending the release up
fixed PFB/FFT libraries, and the completion of the [ATA "Fly's Eye"
Pulse Finder](ATA_"Fly's_Eye"_Pulse_Finder "wikilink") instrument. Data
recording software for the Fly's Eye will be reusable by the pulsar
machine.

Discussions were held with Glenn Jones during his visit in late November
on synchronization issues. In addition, Joeri, Glenn and Peter did some
preliminary work on architecting a coherent dedispersion machine using
IBOB/BEE2 or ROACH boards.

**10 January 2008**: Following the successful deployment of the Fly's
Eye instrument, development on the pulsar machine has resumed. The
compute nodes, which were expected to arrive in mid-December, were
delayed by Dell, so new nodes have now been ordered. These should arrive
before the end of January.

Glenn's latest revision of the vector accumulator has been integrated
into a design that does 400MHz dual polarization with 10GbE readout.
This appears to be working in simulation. Hardware tests will commence
shortly.

**30 January 2008**: Pulsar nodes have arrived and been set up. The
400MHz dual polarization design was compiled, and 10GbE output has been
verified in hardware, to a single node with a 10GbE NIC. Further tests
of correctness are underway. When this instrument is complete, work will
resume on the design to use the ATA beamformer as input over XAUI.

**27 February 2008**: The 400MHz design for Parkes has now been tested
with both a direct 10GbE to server with NIC, and with 10GbE to an HP
10GbE/1GbE switch, and 1GbE to a server. The output appears to be
correct, so this design should be shipped in March. The ATA 108MHz
complex sampling design has been completed with an analogue (ADC)
interface. Oren at RAL has completed work on providing an interface from
the Beamformer to our IBOB pulsar spectrometer over XAUI. The XAUI-input
IBOB design has been built, and integration testing will be conducted
over the next two weeks. This will hopefully by followed by a deployment
to the ATA.

**17 March 2008**: We have now tested the ATA pulsar spectrometer with a
beamformer emulator and, last week, Oren's actual beamformer "dual
beamformer combiner" design. The tests have been largely successful. We
will test the instrument at the ATA on 19, 20 and 21 March. We have also
christened the instrument "BAPP": the "Berkeley ATA Pulsar Processor".

**23 March 2008**: Tests of BAPP at ATA were moderately successful; we
were able to get the spectrometer to communicate with the beamformer,
and saw a nice narrow H1 line in Cas A. However, attempts to find
PSRB0329+54 were unsuccessful. We suspect that selection of antennas
with poor signal quality is to blame, rather than the DSP systems.
Further tests will be conducted in the coming week.

**15 April 2008**: Joeri gets first good data out of BAPP. First light
with PSRB0329+54. Individual pulses can now be detected (which was not
possible without the beamformer).

**1 May 2008**: Peter is back in South Africa. Joeri is back in the
Netherlands. Development work on the coherent machine is halted pending
resolution of tools licencing issues.

**12 May 2008**: Glen Langston at NRAO has conducted the first test of
the [Parspec](Parspec "wikilink") design with telescope data. He, Scott
Ransom and Paul Demorest were able to detect PSRB0950+08 using the 140ft
telescope at Green Bank.

**27 July 2008**: We have been making progress on several fronts. We now
have a version of [Parspec](Parspec "wikilink") that produces
cross-terms (i.e. a "Full Stokes" spectrometer) that has been tested at
HartRAO. We've also been working on a spectrometer for a coherent
dedispersion application at [
Nancay](Nancay_CoDeDi_Pulsar_Machine "wikilink"). This instrument will
be discussed at the forthcoming CASPER workshop.

**23 August 2008**: The specs for our prototype instrument for [
Nancay](Nancay_CoDeDi_Pulsar_Machine "wikilink") were decided on during
the CASPER workshop. A 400MHz bandwidth, 256 channel, non-load-balancing
design has now been built and tested in the lab. The prototype
deployment will take place from 2 - 5 September.

## Links

  - [Peter McMahon's M.Sc.
    Thesis](http://casper.berkeley.edu/papers/McMahon-Thesis.pdf)
    (covering the development of the [ATA "Fly's Eye" Pulse
    Finder](ATA_"Fly's_Eye"_Pulse_Finder "wikilink"),
    [BAPP](BAPP "wikilink"), [Parspec](Parspec "wikilink"), the [Nancay
    CoDeDi Pulsar Machine](Nancay_CoDeDi_Pulsar_Machine "wikilink"), and
    related spinoffs of these projects)

Deprecated material on the (G)ASP SERENDIP5-based pulsar machine:

  - [Paul Demorest's Ph.D.
    Thesis](http://astro.berkeley.edu/~demorest/thesis.pdf), mainly
    [chapter 3](http://astro.berkeley.edu/~joeri/pulsarmachine/PaulDemorest-Thesis-Chapter3.pdf)
  - <http://astro.berkeley.edu/~demorest/aas_2005_poster.ps>
  - <http://astro.berkeley.edu/~demorest/psu_2005_poster.ps>
  - <http://astro.berkeley.edu/~demorest/gasp_pres.pdf>
