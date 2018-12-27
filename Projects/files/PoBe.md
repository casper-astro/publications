## Development Team

This project was carried out as a part of the summer project by Cambodge
Bist, under the guidance of Kaushal Buch, Ajithkumar B. and Yashwant
Gupta at the Giant Metrewave Radio Telescope, National Centre for Radio
Astrophysics, TIFR, India.

Technical discussions and offline post-processing support: Sanjay Kudale

Testing support: Irappa Halagali

For further details or clarifications regarding this project please
contact Kaushal Buch, Digital Backend Group, GMRT, NCRA-TIFR, India
(kdbuch@gmrt.ncra.tifr.res.in, kaushal.buch@gmail.com)

## Pocket Beamformer

The Pocket Beamformer (PoBe) is FPGA (ROACH-1) based digital design that
implements incoherent beamforming algorithm for 2 antennas required for
pulsar studies at the Giant Metrewave Radio Telescope (GMRT).

The PoBe is an add-on to the Pocket Correlator (PoCo) which is a
2-antenna design that is used for correlation and has been developed a
part of the GMRT upgrade activities. This project mentions the PoBe
digital design in terms of modification on PoCo, incoherent beamforming
algorithm and packetised design.

It uses 10Gbps network link for transporting data from the ROACH-1 board
to the P.C. This is necessary for beamformer's short-time integration
requirements. The project includes de-packetisation and offline data
processing.

A detailed design is available as a CASPER memo:
<https://casper.berkeley.edu/wiki/Pocket_Beamformer%28PoBe%29_on_FPGA>

The design has been tested for 600 MHz ADC clock (i.e. 300 MHz
beamformer).

## Compiling the design

The design of two element incoherent beamformer was carried out on
Xilinx System Generator 10.1 and Matlab R2008a on Windows platform for
ROACH-1 board using the standard CASPER tool-flow. The design file, bof
file, scripts for configuring and acquiring data from the correlator and
beamformer and depacketization scripts are provided for the user. The
following software are required for compilation and testing of this
design

Matlab R2008a  
Xilinx ISE 10.1 (with System Generator)  
Python 2.6  
Wireshark  
Gulp  

### Project Files

Design file: Contains .mdl and .bof files

Python file: Contains python scripts for Pocket Correlator and Pocket
Beamformer

Depacketization: Contains 'C' file and executable file for
de-packetization of beam data

![Beamformer.tar.gz](Beamformer.tar.gz "Beamformer.tar.gz")

## Testing the design

### Step 1: Power ON and instrument settings

(i) Signal generator settings as CLOCK to iADC's clock input: Freq =
600MHz , Power = 0dbm (Note: Current version of design works for a
maximum clock frequency of 600 MHz i.e. 300 MHz beamformer)

(ii) Connect broadband analog or noise source signals to iADC's inputs
with a total channel power between -14dbm to -17dbm.

(iii) Power “ON” the ROACH board.

(iv) Configure ROACH board through control P.C.

### Step 2: Initialization and configuration the design on ROACH-1 board

Following changes may be required in the script
according to your requirements   
vim pobe\_incoh\_2k.py \<br \\\>

my\_corr.write\_int("acc\_cntrl\_int\_time",1024)   
Note: This is the integration time for beamformer
(1024 for 600MHz clock & 512 for 400MHz clock) \<br \\\>
Theoretically, the data rate can go much beyond this; however we found
for our system, we could a get minimum integration time of 1.3 ms with
this test setup and integration time settings as mentioned above. \<br
\\\>

my\_corr.write\_int("Input\_mux",0)   
Use '1' for digital noise and '0' for ADC input \<br \\\>

Run the script to configure the design  
python\_scripts$ ./pobe\_incoh\_2k.py \<br \\\>

### Step 3: Check packets on 10GbE port of the control P.C.

To ensure packets being received by the PC from ROACH-1 board \<br \\\>

python\_scripts$ sudo wireshark \<br \\\>

"The Wireshark Network Analyzer" window opens  \<br
\\\>

Select Capture/Interfaces in the Menu. Another window "Wireshark: Capture 
Interfaces" opens \<br \\\>

Observe at Packets and Packets/sec. Counts here show that the
packets are being  received (0 for no packets received) \<br \\\>

Select File/Quit to exit  \<br \\\>

### Step 4: Capture beam data on 10GbE port using Gulp

For setting the number of packets to be captured, go to the directory
where Gulp has been installed.  python\_scripts$ cd /data/Gulp/ \<br
\\\>

gmrt@ctrlpoco:/data/Gulp$ vim gulp.c \<br \\\>

int num\_packets = ­-1;    
  Note: Change the value of num\_packets
to ­-1 to capture till ctrl+c or any number to capture 
those many packets \<br \\\>

gmrt@ctrlpoco:/data/Gulp$ sudo make \<br \\\>

Capture packets using Gulp using the following command. Check the port
on which 10GbE NIC is connected. In this case, it is 'eth2'. '\>'
operates dumps into the required destination
(file).

python\_scripts$ sudo /data/Gulp/gulp ­i eth2 \> 150mhz\_14122012.dat \<br
\\\>

The packet would consist of 512 channel of beam data with each channel
having 32-bit precision. Gulp captures the data in 32-bit binary format.
To plot it or convert it to 16-bit binary format, a de-packetization
routine has been written (Refer next section). \<br \\\>     

### Step 5: Depacketization and plotting the beam data

gmrt@ctrlpoco$ vim file\_fast.c \<br \\\>

Edit this 'C' file as per requirement. A brief explanation is given
below. \<br \\\>

fprintf(ha,"%u\\n",v); \<br \\\> Keep the above statement
to make the output ASCII file plot able by  GNUPLOT. \<br \\\>

fwrite(\&v,sizeof(v),1,ha); \<br \\\> This statement is
required to make the output BINARY file compatible with Pulsar
Monitor (PMON). PMON is a software developed at the GMRT for
de-dispersion and folding of beam data to get pulsar profile. \<br \\\>

After making these changes follow the steps below to create .exe file
\<br \\\> 

2antenna$ gcc ­-o file\_fast.o file\_fast.c \<br \\\>

Usage : ./file\_fast.o <Dump_filename> <OUTPUT_filename> <Packet_size> 
<Scaling_factor> \<br
\\\>

This De-packetizes the \*.data file in to \*.out file with packet\_size of 2K
bytes and a desired scaling factor \<br
\\\>

2antenna$ ./file\_fast.o 150mhz\_14122012.dat1 150mhz\_14122012.out 2048 1024 \<br
\\\>

2antenna$ ./file\_fast.o
150mhz\_14122012.dat1 150mhz\_14122012.out 2048 1024 \<br \\\>

Plot the De-packetized OUTPUT\_file using GNUPLOT. \<br \\\>

## Documentation

A detailed design document is available as a CASPER memo:
<https://casper.berkeley.edu/wiki/Pocket_Beamformer%28PoBe%29_on_FPGA>
