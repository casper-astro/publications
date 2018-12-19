# Parspec

The “Parkes Spectrometer”, v1.0, was built by Peter McMahon for the Parkes Radio Telescope as an evaluation design for a new multi-beam system. It is a dual polarization, power spectrometer with a 1024 channel Polyphase Filter Bank, using the CASPER IBOB hardware platform. A 30kHz readout rate (i.e. 30,000 spectra per second) was targeted, and this necessitated the use of 10Gbit/s Ethernet.

### Specifications ###

Each spectrometer:

| Frequency channels: | 1024 (2048 real samples per spectrum) |
|---------------------|------------------------------------------------------------------------------------------------------------------|
| Signal input: | 5MHz - 400MHz or 400MHz - 800MHz or 800MHz - 1.2GHz -20dBm to -10dBm (-15dBm nominal) 50Ohm SMA |
| Integration time: | Minimum: 5.12us (195kHz spectral dump rate) Maximum: 655us (1.5kHz spectral dump rate) |
| Polyphase filter: | 2 taps, Hamming window |
| Output: | Test mode: 100Mbit Ethernet. 32-bits per spectral bin. Observing mode: 10Gbit Ethernet. 8-bits per spectral bin. |


Both spectrometers:

| Clock input: | 800MHz, 0dBm to +4dBm, 50Ohm SMA |
|----------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| 1PPS input: | 0 to 3V pulse nominal (into 50Ohms) 2V minimum, 5V maximum. Optional. |
| Power input: | 5V, 7A |
| Mechanical: | 1x IBOB and 1x iADC board on a 6U, 8HP plate |
| Control and monitor: | Set up accumulation and corresponding sync period. Set up IP addresses, ports, MAC addresses, and ARP table. Set scaling: 18-bits, binary point at 12. Set output bit selection. Set ARM (optional). |

### User Guide ###

The August 2008 version of the User Guide is available for [download](parspec_files/ParkesUserGuide.pdf).

[Sample Processing Code for Gulp Dumps](parspec_files/parkes_proc_full.c)

### Download ###

The latest build of the Parkes spectrometer is available for [download](parspec_files/Parkes_redist_ug.zip).

This download contains the Simulink models, the compiled bitstream (for the LWIP-enabled version), the User Guide, and the sample C code for processing gulp dumps from the Parspec.
