VEGAS is a next generation instrument that will expand the capabilities
of the current spectrometer at the Green Bank Telescope, to address the
increased bandwidth and spectral resolution needed with the new 7-pixel
Ku-band focal plane array receiver. The [NRAO
website](http://www.gb.nrao.edu/vegas/report/) gives a detailed
description of the instrument and it's scientific objectives.

[VEGAS Testing Notes](VEGAS_Testing_Notes "wikilink")

## Team

Marty Bloss, Patrick Brandt, Hong Chen, Jayanth Chennamangalam, Paul
Demorest, Gregory Desvignes, Terry Filiba, John Ford, David Frayer, Bob
Garwood, Glenn Jones, Joe Masters, Randy McCullough, Guifré Molera,
Karen O'Neil, Aaron Parsons, Jason Ray, Anish Roshi, Simon Scott, Amy
Shelton, Mark Wagner, Galen Watts, Dan Werthimer

## Block Diagram

![Gbtspec-blockdiagram.png](Gbtspec-blockdiagram.png
"Gbtspec-blockdiagram.png")

## Software

### ROACH Firmware

  - [BORPH](BORPH "wikilink") - A modified Linux kernel that runs on the
    PPC, and allows for interaction with shared memory on the FPGA.
  - [KATCP](KATCP "wikilink") - Allows for remote command and control of
    the firmware, over the network.
  - [ Roach Monitor](Roach_monitor_and_management_subsystem "wikilink")
    - Monitors voltages and temperatures of ROACH boards.

### HPC Software

The HPC (which is a cluster of CPUs and GPUs) will be running a modified
version of the backend software for GUPPI (guppi\_daq). There are two
different versions of the HPC software:

  - vegas\_hpc\_hbw : the HPC software for high-bandwidth modes (the CPU
    merely accumulates)
  - vegas\_hpc\_lbw : the HPC software for low-bandwidth modes (the GPU
    implements a PFB)

Depending on the desired mode, one of the two HPC applications must be
run on the HPC. Note that a separate instance of the HPC application
must be started on each CPU/GPU node in the cluster.

#### Starting and Stopping the HPC Software

To start the HPC software, simply run an instance of vegas\_hpc\_\*
application on each CPU. The application does not require any
command-line parameters. The one optional parameter that can be passed
to the process is "--disk", which causes the application to write SDFITS
files for debugging purposes.

To stop the HPC software, simply kill the process on each CPU node.

#### Outputting Data

By default, the HPC software does not write to disk. The HPC software
writes integrated spectra to a shared memory buffer. The M\&C process
(external to the HPC software) then reads the spectra from the shared
memory buffer and writes the spectra to disk.

However, if the "--disk" flag is passed to the HPC software, via the
command line, the HPC software will create a disk thread which writes
the spectra from the output buffer to SDFITS files on disk. This mode is
merely for testing purposes, and will not be used during normal
operation.

#### Shared Memory Buffers

Details on the shared memory buffers can be found in the *Memo on the
Shared Memory Buffers* and *Memo on the Critical Settings for the HPC*,
both of which can be found in the section on [Technical Documentation on
the VEGAS HPC Software
Architecture](VEGAS:_VErsatile_GBT_Astronomical_Spectrometer#Technical_Documentation_on_the_VEGAS_HPC_Software_Architecture "wikilink")
below.

#### Installing the HPC Software

Installation notes for the VEGAS HPC software can be found here
[http://casper.berkeley.edu/wiki/GBT\_guppi\_installattion Installation
notes](http://casper.berkeley.edu/wiki/GBT_guppi_installattion_Installation_notes "wikilink")

#### Technical Documentation on the VEGAS HPC Software Architecture

  - Memo on the Critical Settings for the HPC: [
    vegas\_hpc\_critical\_settings.pdf](Media:vegas_hpc_critical_settings.pdf "wikilink")
  - VEGAS HPC Software Developer Documentation: [
    vegas\_hpc\_dev\_doc.pdf](Media:vegas_hpc_dev_doc.pdf "wikilink")
  - VEGAS HPC GPU thread code-level documentation: [VEGAS GPU Code
    Documentation](VEGAS_GPU_Code_Documentation "wikilink")

Older documents that have been subsumed by the HPC Developer
Documentation:

  - Memo on Control and Timing for the ROACHs and HPC: [
    gbt\_memo\_control\_timing.pdf](Media:gbt_memo_control_timing.pdf "wikilink")
  - Memo on the Shared Memory Buffers [
    vegas\_memo\_shmem.pdf](Media:vegas_memo_shmem.pdf "wikilink")
  - SPEAD Packet Format for High-Bandwidth Modes: [
    spead\_format\_high\_bandwidth.pdf](Media:spead_format_high_bandwidth.pdf "wikilink")
  - SPEAD Packet Format for Low-Bandwidth Modes: [
    spead\_format\_low\_bandwidth.pdf](Media:spead_format_low_bandwidth.pdf "wikilink")

### Network Packets

[http://casper.berkeley.edu/astrobaki/index.php/Spead\_specification
SPEAD](http://casper.berkeley.edu/astrobaki/index.php/Spead_specification_SPEAD "wikilink")
protocol - The SPEAD protocol allows for a very robust and flexible
means for streaming packets. This protocol is used for packets that are
sent from the FPGA to the HPC. Detailed information of the packet format
at [http://casper.berkeley.edu/wiki/VEGAS\_Spead\_Packet VEGAS Packet
Format](http://casper.berkeley.edu/wiki/VEGAS_Spead_Packet_VEGAS_Packet_Format "wikilink")

## Hardware

  - 9x [ROACH](ROACH "wikilink") boards
  - 18x [ADC1x3000-8](ADC1x3000-8 "wikilink") Single-8 bit, 3000Msps
    National ADC083000 ADC
  - 9x CPUs
  - 9x GPUs
  - 9x [http://www.myri.com/Myri-10G/NIC/10G-PCIE-8A-C.html Myricom
    10GbE
    NICs](http://www.myri.com/Myri-10G/NIC/10G-PCIE-8A-C.html_Myricom_10GbE_NICs "wikilink")

## Firmware

The firmware is the code that runs on the FPGA. It is available from the
VEGAS project [https://github.com/casper-astro/vegas\_devel git
repository](https://github.com/casper-astro/vegas_devel_git_repository "wikilink")
(deprecated: [https://casper.berkeley.edu/git/?p=gbt\_devel.git
gbt\_devel git
repository](https://casper.berkeley.edu/git/?p=gbt_devel.git_gbt_devel_git_repository "wikilink")).
We are using the 11.5 [MSSGE](MSSGE "wikilink") toolflow for all modes.

## Monitor and Control of the ROACH Boards

[Vegas FPGA Register
Definitions](Vegas_FPGA_Register_Definitions "wikilink")

[Vegas SSG Modes](Vegas_SSG_Modes "wikilink")

All shared memory on the FPGA will be accessed over the 100Mbit port
using the corr and katcp python packages that communicate with the
tcpborphserver running on the PPC. Monitoring of ROACH voltages and
temperatures will be done by the Actel Fusion and can be accessed via
the Xport (see [ ROACH
Monitor](Roach_monitor_and_management_subsystem "wikilink") for
details).

[| Mark's google doc about VEGAS modes and
configurations](https://docs.google.com/document/d/1C_it02j8yqu_VZcYnN6aVC-jrgP4ClAxbj8KP4cH4EQ/edit?pli=1)

[Anish's SSG
specifications](https://casper.berkeley.edu/wiki/images/1/18/Ssgprogram.pdf)
