## Project Team

This project has been designed as a part of the GMRT upgrade activities
by Kaushal D. Buch, Mekhala V. Muley, Ajithkumar B., Shreya Shetty
(Short Term Intern) and Pranjali Chumbhale (Short Term Intern) of the
Digital Backend Group, GMRT, NCRA-TIFR, Pune, India.

Post processing and technical support: Sanjay Kudale and the Digital
Backend Group, GMRT, NCRA-TIFR, Pune, India.

Contact details: kdbuch@gmrt.ncra.tifr.res.in,
mekhala@gmrt.ncra.tifr.res.in

## Introduction

The goal of the project is to design packetized incoherent beamformer
for 4-antenna dual polarization input as an add-on to the existing 400
MHz packetized FX correlator using multiple ROACH-1 boards. This
includes designing and implementing beamforming logic and adding 10GbE
packetization logic to the X-engine of the packetized correlator. Also,
the corresponding de-packetization and interleaving scripts were
developed to be record and process the beam data at microsecond time
resolution.

Note: The wide-band packetized FX correlator design was obtained from
the CASPER collaboration and was evolved as per GMRT's upgrade
requirements with help provided by the SKA-SA group.

## Design Specifications

 Number of antennas: 4

 Polarization: Dual

 Number of spectral channels: 512

 Number of F engines: 4

 Number of X-engines: 8 (2 per ROACH-1 board)

 Number of spectral channels per X-engine:64

 Networks used: 1Gbps, XAUI link and 10 Gb Ethernet.

 Clock Frequency: 800 MHz

 Bandwidth : 400 MHz

 Base integration time: 0.163 milliseconds

## Design Details

Four Antenna Incoherent Packetized Beamformer Design File:
![Four\_ant\_incoh\_bf.zip](Four_ant_incoh_bf.zip
"Four_ant_incoh_bf.zip")

The design uses four F-engines and eight X-engines to achieve the above
mentioned specifications.

![Block Diagram](ia_bf1.JPG "Block Diagram")

The design flow of the beamformer block is shown in the figure below.
The design input is the spectral channel data received from the F-engine
through the XAUI link. The beamformer processes the data and send the
integrated beam data over the 10GbE link. Each ROACH-1 board has two
X-engines with 64 channels per X-engine. Hence a total of 8 X-engines (4
ROACH-1 boards) are required to process a 512 spectral channels.

![Block Diagram](ia_bf2.JPG "Block Diagram")

The integration time for the accumulation of beam data is derived from
the sync input to the block. A data valid signal to the design ensures
that the packet drop from the F-engine to X-engine over the XAUI link is
taken into account during Beamforming and integration process.

The inputs to the beamformer subsystem are the following three signals:

1\. Data\_valid signal: Boolean signal; when high the incoming data at
the input data port is valid. 2. Sync signal: For synchronization
between different X-engines. 3. Input data: 16 bit data.

The input data has the following format:

![X-engine Incoming Data Format](ia_bf3.JPG
"X-engine Incoming Data Format")

Within the 16-bit data input, following is the format in which the data
is packed:

![16-bit Input Data Format](ia_bf4.JPG "16-bit Input Data Format")

The input data flow in the X-engine beamformer block is shown in the
figure below

![Working of X-engine](ia_bf5.JPG "Working of X-engine")

### 10 GbE packetization

Figure below shows the signals that are provided to the 10 GbE design
block and their timing relationships.

![Signals to 10GbE block](ia_bf6.JPG "Signals to 10GbE block")

The 10GbE block sends out a UDP Packet. The data format in the UDP
packet is as shown in figure below

![UDP Format](ia_bf7.JPG "UDP Format")

On a ROACH-1 board, there are two X-engines; therefore there are two
Incoherent Beamformer subsystems.

## Post – Processing

There are two options for capturing the data packets via Gulp. One
option is to capture with the header and another without header.

### Without header

Every 163 microsecond, 1 packet of 512 bytes is sent out of an X-engine.
Therefore in 1 second, 3.14 Mbytes are transferred.

Data Rate = 3.14 Mbytes \* 8 =25.13 Mbps.

### With Header

Every 163 microsecond, 1 packet of 554 bytes is sent out of an X-engine.
Therefore in 1 second 3.398 Mbytes are transferred. Data Rate = 3.398
Mbytes \* 8 =27.19 Mbps.

Once the data is acquired using Gulp, the de-packetization stage
consists of two parts. This has been carried out using ‘C’ code which
runs on the acquisition P.C. in off-line mode.

Converting to ASCII: The data packets captured by gulp are in binary
format. These are converted into ASCII format. Further Polarization 1
and Polarisation 0 data is separated.

Separating into 8 files: Gulp captures packets that are sent over 10Gb
Ethernet. 8 X-engines from 4 different ROACH-1 boards are transmitting
packets on to a single 10Gb Ethernet interface of the acquisition P.C.
Hence, these received packets have to be separated depending on the
X-engine and finally has to be interleaved in a particular order so as
to get the entire spectrum of 512 channels.

It may be required to convert this interleaved beam data in to a format
compatible with the pulsar processing software. In the case of GMRT a
locally developed software ‘pmon’ (Pulsar Monitor) was used for
processing of beam data to get pulsar profile.

## Design Testing

### Test Setup

1)CONNECTIONS TO THE F-ENGINE:

F-engine is given four inputs: 1) Sync 2) I (Polarisation 0 input) 3)
Clock 4) Q (Polarisation 1 input)

![Connections to F-engine](ia_bf8.JPG "Connections to F-engine")

2)10 GbE PORT CONNECTIONS OF X-ENGINE: Every ROACH board has four 10 GbE
ports. In this test setup, the 10 GbE ports are configured as shown in
the figure below:

![10GbE ports - Connections to F-engine](ia_bf9.JPG
"10GbE ports - Connections to F-engine")

3)CONNECTIONS BETWEEN F-ENGINE AND X-ENGINE: The connections between
F-engine and X-engine are as shown in the following diagram:

![Connections between F-engine and X-engine](ia_bf10.JPG
"Connections between F-engine and X-engine")

4)CONNECTIONS FROM X-ENGINE TO CONTROL PC: The connection from the
X-engines to control PC is via a 10GbE switch.

![Connections between X-engine and control PC](ia_bf11.JPG
"Connections between X-engine and control PC")

## Data Acquisition

Following is the procedure to capture data from the packetized
beamformer and de-packetize it for further analyses. Data acquisition on
control PC was carried out using GULP utility.

### Capturing Data

'C' code and corresponding executable files:
![Depack\_scripts.zip](Depack_scripts.zip "Depack_scripts.zip")

To make changes to gulp code (i.e. to change number of packets) vim
gulp.c On line 295: num\_packets=<enter the number of packets desired>
(-1 if infinite number of packets to be captured)

Save and run ‘make’ command Enter the following commands to capture
packets: ./gulp/gulp -i eth0 \> \<name of dump file.dat\> (In case of
infinite packet capture, it will capture until ctrl+C command)

### Breaking the captured data into chunks

(The data captured by pulsar is usually greater than 2 GB. For
depacketization codes break the captured data into chunks of 2GB files.

1\) dd if=\<name of dumped file.dat\>.dat of= \<name of dumped
file.dat1\>.dat bs=1999999832 count=1 skip=0. (The above command will
cut first 2GB of the dumped file)

2\) dd if=\<name of dumped file.dat\>.dat of= \<name of dumped
file.dat2\>.dat bs=1999999832 count=1 skip=1.

(The above command will cut next 2GB of the dumped file) For each of the
above 2 GB files, the Depacketization codes have to be run separately.
Give different names to the binary files created in the end.

### Depacketization

1\. From binary to ASCII ./gulp\_ascii\_8.o \<name of dumpedfile1.dat\>
<packet_size> <scaling factor>

(packet size=554) (scaling: 4 taken as standard for our analysis)

The above command will also separate the packets into 8 different files.
Now to convert them to single interleaved file with all 512 channels
enter the following command.

2\. ./intleave\_signed.o \> \<name of ascii interleaved file1.txt\>
Interleaving is carried out at this stage.

3\. The \<name of ascii interleaved file.txt\> can be viewed on gnuplot.

4\. To convert to binary format compatible with most of pulsar analysis
software ./pmon\_bin.o \<name of ascii interleaved file .txt\> \<name of
binary interleaved file.txt\>

(Note: When the depacketization of all the 2GB files (that were created
using ‘dd’ command) is complete, proceed to the next step).

### Concatenating files

Each of the above binary files will be of 441 MB. Concatenation of these
files is required to get back the actual sequence of data. The command
used is: cat \<name of binary interleaved file1.raw\> \<name of binary
interleaved file2.raw\> \<name of binary interleaved file3.raw\>
\<.....\> \> \<name of final concatenated file.raw\> This final .raw
file contains data from all the binary files created earlier. This final
.raw file can be then be provided to Pulsar analysis software.

### Noise test results

Connections: All 8 X-engines connected to control PC via 10GbE switch
Input: Signal from noise generator passed through a low pass filter of
200 Mhz. Output: GNU plot of the interleaved data from all X-engines

![Noise Test Results](ia_bf12.JPG "Noise Test Results")

### Pulsar test – First Light Results

32 MHz bandwidth @ 610 MHz RF – 400 MHz IA Beamformer • Date of
observation: 30th October 2013. • Pulsar: B0329+54 (Period: 714.578196
msec) • Antennas used: 4 central square antennas used. • Sampling clock:
800MHz. • Data acquisition: 5 mins • Integration time: 0.164 millisecond
• Beamformer Bandwidth: 400 MHz • RF Bandwidth: 32 MHz • Number of
channels:512

![PSR B0329+54 First Light Results - 32 MHz BW](ia_bf13.JPG
"PSR B0329+54 First Light Results - 32 MHz BW")

400 MHz bandwidth @ L-Band – 400 MHz IA Beamformer • Date of
observation: 27th November 2013. • Pulsar: B0329+54 • Antennas used: 4
central square antennas used. • Sampling clock:800MHz. • Integration
time: 0.164 millisecond • Beamformer Bandwidth: 400 MHz • RF Bandwidth:
400 MHz • Number of channels:512

![PSR B0329+54 First Light Results - 400 MHz BW](ia_bf14.JPG
"PSR B0329+54 First Light Results - 400 MHz BW")

## Work in progress

1.Development of post processing scripts for longer integration of beam
data and addition of two polarizations.

2.Data quality checks by comparing the beam output with theoretical
improvement in signal to noise ratio as a function of number of
antennas.
