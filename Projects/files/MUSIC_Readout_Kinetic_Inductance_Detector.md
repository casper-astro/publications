## Latest Development

Latest Development, Detailed Documentation and Files on KIDs Readout Can
be found at:

''''' <http://www.its.caltech.edu/~rduan/Readout.html> '''''

## MUSIC Overview

### Team

Contact about this page:

**Ran Duan**: ***rduan@caltech.edu***
<http://www.its.caltech.edu/~rduan/Readout.html>

**Sunil Golwala**: ***golwala@caltech.edu***

**Jonas Zmuidzinas**: ***jonas@caltech.edu***

**Caltech**: Ran Duan, Nicole Czakon, David Moore, Omid Noroozian, Tasos
Vayonakis, Tom Downes, Matt Hollister, Loren Swenson, Chris McKinney,
Larry Beirich, Sunil Golwala, Jonas Zmuidzinas

**JPL**: Jack Sayers, Bruce Bumble, Peter Day, Rick Leduc, Hien Nguyen,
Phil Wilson

**University of Colorado**: James Schlaerth, Amandeep K Gill, Clint
Bockstiegel, Spencer Christian Brugger, Phil Maloney, Jason Glenn

**UCSB**: Sean McHugh, Ben Mazin's MKID group

**UCBerkeley**: Bruno Serfass

### Overview

The MUlticolor Submillimeter Inductance Camera (MUSIC) is a new camera
for the Caltech Submillimeter Observatory (CSO), built by a
collaboration of Caltech, JPL, the University of Colorado (CU), and the
University of California at Santa Barbara. It uses novel technologies to
provide 576 spatial pixels across a 14' field-of-view (FoV), each pixel
having sensitivity simultaneously in spectral bands at 0.87, 1.04, 1.33,
and 1.98 mm, with angular resolutions of 22*, 25*, 31*, and 45*, and
performance approaching the limits from background photon noise and
unremovable atmospheric noise on Mauna Kea.

## Readout Overview

Microwave Kinetic Inductance Detectors(MKID) technology was first
introduced in Caltech/ JPL, it has been fast developing due to its
numerous advantages and potential applications. One of the most
important advantage of MKID is that it allow superconducting
microresonators (which serve as detectors) to be multiplexed in
frequency domain at microwave frequency band. Since the transmission far
away from the resonance frequency will not be affected by resonators, we
can multiplex many MKID off a single transmission line by setting each
MKID resonant frequencies to be slightly different with lithography.

The proposed MKID readout system was successfully tested with MKID
camera at CSO in June 2010. The readout electronics have the general
task of performing multiple realtime complex microwave transmission
measurements, in order to monitor the instantaneous resonance frequency
and dissipation of the superconducting microresonators that serve as
mm/submm photon detectors. The full camera array will have total 576
spatial pixels, and each pixel will simultaneously cover 4 different
frequency bands. And the total 2304 detectors will be divided into 16
tiles, each MKID readout unit will be used to readout 1 tiles which is
144 frequency multiplexed resonators. After perform data channelizing,
MKID readout system will output the complex S21 measurement result at
100Hz. The readout electronics are designed so that it will not add any
additional noise to the system. Noise will be dominated by cryogenic
HEMT amplifier, which has noise temperature around 2 to 5 K. Besides the
HEMT, ADC chip will be the next limiting factor for the noise
performance of the readout. Based on the physical frequency spacing of
all the resonators, the sampling rate are chosen to match the resonator
bandwidth. Sampling rate of proposed readout system can be flexible.
Right now it is up to 550 MHz which is the limit of ADC chip. We have
been developing new ADC board using lasted high SNR(12-16 bits), high
sampling rate (gsps) ADCs.

### How to Readout MKIDs

One of the most important advantage of MKIDs: Resonators can be
frequency domain multiplexed (FDMUX).

  - 1\. Lithographically tune each detector to a slightly different
    frequency
  - 2\. Use a single HEMT amplifier to simultaneously read out many
    detectors
  - 3\. Move the complexity and challenge of readout to room temperature
    electronics

![howtoreadout.jpg](howtoreadout.jpg "howtoreadout.jpg")

The idea to readout all the MKID resonators is using IQ homodyne mixing,
which is essentially a dual-phase lockin detection technique: One
generated a comb of probe frequencies for each resonator, this comb is
then sent through the MKID array, where probe signal is modified in both
amplitude and phase direction based on the change of surface impedance
of superconductor which is caused by the incident photons. After
amplified by the cryostat high electron mobility transistor(HEMT)
amplifier, the comb is sent through room temperature electronics to
digitize and analyze. Aside the HEMT and MKID itself, there is no other
cryogenic components, which bring the complexity and challenge of
readout to room temperature electronics system.

![Overview\_full\_system.jpg](Overview_full_system.jpg
"Overview_full_system.jpg")

### summary of the Readout electronics performance

![Resultall.jpg](Resultall.jpg "Resultall.jpg")

## Hardware Availability

![roach\_adcdac\_if.jpg](roach_adcdac_if.jpg "roach_adcdac_if.jpg")

We use the open source reconfigurable open architecture computing
hardware (ROACH) as a FPGA process board and developed our own DAC and
ADC board, IF board and software. In order to synchronize the system, we
add a synchronization port on ADC board to lock the FPGA with GPS. Both
the 16 bit DAC and 12 bit ADC have been proved to meet specification on
datasheet e.g. SNR, SFDR, IMD etc.. DAC is able to work up to 1Gsps with
SNR 75dBFS; ADC is able to work up to 550Msps with SNR 60 dBFS.

Commercial IQ mixers are used to convert the baseband signal into
resonator frequency. And frequency comb are carefully designed to avoid
the inter-modulation caused by the mixers.

### IF board

The IF board configuration is shown in figure below and each component
in the IF board are selected and configured carefully so that:

  - 1\. all the amplifier and mixer are working in the optimal range;

<!-- end list -->

  - 2\. noise level reach ADC will dominate by the HEMT noise( other
    component in system, e.g. amplifiers, ADC etc will not add any
    noise);

<!-- end list -->

  - 3\. two VCOs, FPGA and DAC/ADC are all locked with same frequency
    standard to avoid frequency drift;

<!-- end list -->

  - 4\. DAC and ADC dynamic range are fully used;

<!-- end list -->

  - 5\. the probe signal power level and frequency reaching MKID device
    are optimized for each individual resonator across the whole readout
    bandwidth.

After DAC board, there is LPF, IQ up converter, digital attenuator and
then goes into the dewar. DAC full range will give output 2 dBm power.
In general, if there is 192 carriers, each carrier will have average
power -19dBm. To be more accurate, we use FPGA network analyzer mode
(another firmware we developed) to record roll off pattern of the each
frequency bins for all FFT bins. By adjusting the DAC LUT and digital
attenuator, we can make sure the resonator power level and frequency are
what we expected. We can generally consider HEMT and LNA have gain 34-
35 dB; baseband amplifier has gain 20 dB. And taking into account all
the attenuation, IQ conversion lass, LPF loss etc through the readout,
we can calculate the signal and noise level through the system. To be
more accurate on signal level reach ADC, we look at digitized ADC time
stream data to make sure first we do not overflow ADC, and then try to
use as much ADC dynamic range as possible.

Based on noise temperature of 2 -5 K, there is total 61 dB gain from
HEMT to ADC input. HEMT noise temperature at ADC input is around 2.5e6 K
where ADC full scale is 4.1 mw. So the HEMT noise at the ADC results in
SNR around 55-59 dB where the ADC has SNR 64. The whole readout system
will dominate by the HEMT noise and still has 5-9 dB margin. And this is
also confirmed by measured results.

Function of IF boards:

  - 1\. Control the VCO for LO from 2.2 to 4.4 GHz and from 4.4 to 5GHz
    or higher with doubler.

<!-- end list -->

  - 2\. Control the VCO for Clock from 137.5 MHz to 4400MHz.

<!-- end list -->

  - 3\. Control Baseband switch to do BB loop back test

<!-- end list -->

  - 4\. Control RF switch to do RF loop back test.

<!-- end list -->

  - 5\. Control 3 variable attenuator, each with attenuation from 0‐31.5
    dB.

<!-- end list -->

  - 6\. Control to use External LO or External Clock.

![IF\_part1.jpg](IF_part1.jpg "IF_part1.jpg")

![IF\_part2.jpg](IF_part2.jpg "IF_part2.jpg")

### ADC DAC Board

Feature of ADCDAC board:

  - Two ADC: 550 msps, 12 bits SNR: 64 dB

<!-- end list -->

  - Two DAC: 1000 msps,16 bit NSD: 75 dBc

<!-- end list -->

  - Common Voltage Reference

<!-- end list -->

  - Great Thermal Performance

<!-- end list -->

  - External/OnBoard Power option

![adcdac.jpg](adcdac.jpg "adcdac.jpg")

![power.jpg](power.jpg "power.jpg")

## Software Availability

### FPGA Design

We have successfully design and implement a FPGA firmware with 65536K
point channelizer, 7500 Hz resolution and corresponding FIR filter, band
selection, timestamp function etc on FPGA. The firmware running on FPGA
can be divided into following parts:

![firmware.jpg](firmware.jpg "firmware.jpg")

1\) Comb Lookup Table Generation: The look up table for DAC are directly
stored on ROACH's DRAM. And LUT is designed to have the same length or
integer multiple of channelizer size to get consistent phase for each
bin. All the resonator tones will sum up together to play back in the
LUT buffer. An avoid-clipping program is designed and used to maximize
each resonator power by transfer the clipping (due to summing) into the
off resonator bins(power are sent out in both on and off carrier bins).
In order to get optimal power level for each resonator frequency, effect
of LPF at DAC output, IQ mixer, DAC output transformer, impedance
mismatch and the DAC intrinsic SINC function roll off are all taken into
account and compromised when the buffer is generated to make sure both
power and frequency is optimized across the whole readout bandwidth when
reaching MKID device.

In the current implement, we use DAC frequency step size of 7.5 KHz
(there is still plenty extra memory on FPGA, which allow the readout to
have DAC step size even below 50 Hz), same as the FPGA channelizer bin
width. And the buffer size, frequency resolution, sampling rate of the
ADC and DAC chip, and how many tones we want to play back in the buffer
are all programmable from the firmware and can be easily modified based
on different requirement.

2\) ADC digitization: Above 500 MHz clock rate for FPGA is too fast even
for state-of-art FGPA with large design on it. In order to process the
data from ADC and DAC in real time, we will first deserialize data on
FPGA, which reduce the FPGA clock rate by 2 in current design, at the
cost of twice the amount of logic cells.

As requirement of bandwidth and ADC sampling rate increase, we will be
able to control serializer / deserializer level to match high rate.

3\) Channelizing design: Different channelizing implementation in FPGA,
e.g. digital down converter (DDC), directly 65K FFT; FFT zoom, polyphase
filter bank and co-addition mode etc are considered and compared, we
eventually implement an Direct 65K FFT. (lot of optimization was done
within the single complex FFT block in order to fit on the FPGA). After
channelizing, only the 192 bins that carry resonator information are
selected out of 131072 bins based on another LUT we implement on FPGA.
This LUT which contain the position information of the resonator bins
are generated together when the LUT for DAC are generated and will be
able to update automatically once the LUT for DAC are changed. The
ability to reprogram LUT buffer on FPGA when channlizing is running is
important for real observation: MKID probe frequency and power need to
be optimized based on different sky loading, LUT will need to be changed
all the time when point to different part of the sky. After resonator
bins selection, only 192 bins that carry the resonator information are
further processed and stored: instead of simple co-addition or
averaging, each selected resonator bins data stream will go through a
192 channels 150 tap hamming window FIR filter and then decimate the
data rate into 100Hz to give better noise performance.

4\) Synchronization: 1pps signal are imported to FGPA from GPS locked
frequency standard to provide TTL signal with raising edge on the second
boundary. Both DAC and channelizer will start at exactly same edge of a
second to make sure we get consistent phase for all the carrier bins. In
order to synchronize with the absolute time of the day, a c program
running on power PC is written to transfer the current unix time on PPC
(which is locked to network time protocol server) to the FPGA, and the
1pps locked counter will start counting the integer seconds from that
time in FPGA. Another counter that running at FPGA clock rate will be
reset by the 1pps signal continuously, this counter will provide the
fractional part of the seconds for the data package which is accurate up
to 1/FPGA clock rate second( in the level of 1e-8 second). Internal
delay inside the FPGA between the signal received at ADC and the 100Hz
final output are also taken into account. Delay in the IF system are
measured with FPGA network analyzer mode we designed and also taken into
account in calculation.

So each data package will contain a timestamp (both seconds and
fractional seconds), a header and 126 complex resonator data. And the
data packages are send out through 10Gbit Ethernet at 100Hz to DAQ
computer. As shown in figure 1, the FPGA clock is imported from ADC
board and shared with ADC and DAC, this can make sure all the
synthesizer, ADC, DAC, FPGA are synchronized together.

5\) network analyzer mode of FPGA: Besides the normal channelizing mode
for observation, we also designed a FPGA firmware to make the whole
readout system works as a network analyzer: send out chirp signal or
white noise, then co-add the ADC digitized time domain data and store to
computer. Network analyzer mode allow us to quickly make resonator
sweep; by comparing the phase of each frequency bin, we can calculate
the cable delay of the readout setup; we could also use it to check the
current ADC dynamic range and do system check. More importantly, all
different designs can be implemented by simply reprogram the FPGA
firmware without any hardware change.

### DAQ Process

![daq.jpg](daq.jpg "daq.jpg")

## MUSIC Instrument DAQ and Bof source code

MUSIC DAQ code: [link MUSIC DAQ
Files](https://www.dropbox.com/s/slpouopnfmje3i5/music_daq.tar.gz?dl=0)

MUSIC Bof files: [link MUSIC Bof
Files](https://www.dropbox.com/s/g14y8hn8ekar09u/music_bof.tar.gz?dl=0)
