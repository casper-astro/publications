# Mars Weather Reports

<http://www.msss.com/msss_images/subject/weather_reports.html>

# People

William Barott (Embry-Riddle)

Geoff Bower (Berkeley)

Tom Kuiper (JPL)

Walid Majid (JPL)

Imke de Pater (Berkeley)

Nilton Renno (U. Michigan)

Chris Ruf (U. Michigan)

Dan Werthimer (Berkeley)

[Marin Anderson](User:manderson "wikilink") (Berkeley)

[Andrew Siemion](User:siemion "wikilink")
(Berkeley)

# Specifications

|                     |                                                                           |
| ------------------- | ------------------------------------------------------------------------- |
| Frequency channels: | 1024                                                                      |
| Clock input:        | usrclk 2x @ 50-75 MHz                                                     |
| Signal input:       | XAUI dual-pol 8 bit r/i                                                   |
| Integration time:   | 10 microsec to 10 ms                                                      |
| Polyphase filter:   | 4taps, Hamming window                                                     |
| Output:             | 10 Gbit Ethernet, 8 bit x/y power, 16 bit x/y power squared, 8 bit xy r/i |
| Libraries used:     | mlib\_devel 7.1                                                           |
| hardware:           | BEE2 or iBOB, iADC (legacy version)                                       |

# Models and Software

[Mars Lightning SVN
Repository](http://casper.berkeley.edu/svn/trunk/projects/dig_int_kurt_spec/)

Description:  
bofs/ - compiled bof files  
init\_scripts/ - initialization scripts  
matlab\_scripts/ - matlab scripts for testing  
mdls/ - model files  
reg\_tools/ - bee2/borph tools  

# [Instrument Options](Mars_Lightning_Machine_Options "wikilink")

# Instrument

## Configuration

### From Processor Software Registers and Recommended Values

<table>
<thead>
<tr class="header">
<th><p>Register</p></th>
<th><p>Data Type</p></th>
<th><p>Description</p></th>
<th><p>Recommended Value</p></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td><p>reg_sync_period</p></td>
<td><p>UFIx 32.0</p></td>
<td><p>Period of fiducial sync pulse / vector warning signal.<br />
Should be equal to (reg_acclen + 1) * 1024</p></td>
<td><p>131072</p></td>
</tr>
<tr class="even">
<td><p>reg_acclen</p></td>
<td><p>UFix 32.0</p></td>
<td><p>Accumulation length - 1, in units of number of frames.<br />
Should be equal to reg_sync_period/1024 - 1</p></td>
<td><p>127</p></td>
</tr>
<tr class="odd">
<td><p>reg_coeff_stokes1</p></td>
<td><p>UFix 18.12</p></td>
<td><p>X-polarization scaling value</p></td>
<td><p>12288<br />
During tests all scaling values have been equal</p></td>
</tr>
<tr class="even">
<td><p>reg_coeff_stokes2</p></td>
<td><p>UFix 18.12</p></td>
<td><p>XY real scaling value</p></td>
<td><p>12288<br />
During tests all scaling values have been equal</p></td>
</tr>
<tr class="odd">
<td><p>reg_coeff_stokes3</p></td>
<td><p>UFix 18.12</p></td>
<td><p>XY imaginary scaling value</p></td>
<td><p>12288<br />
During tests all scaling values have been equal</p></td>
</tr>
<tr class="even">
<td><p>reg_coeff_stokes4</p></td>
<td><p>UFix 18.12</p></td>
<td><p>Y-polarization scaling value</p></td>
<td><p>12288<br />
During tests all scaling values have been equal</p></td>
</tr>
<tr class="odd">
<td><p>kurt_scale_1a</p></td>
<td><p>UFix 18.12</p></td>
<td><p>X-polarization power^2 scaling value</p></td>
<td><p>12288<br />
During tests all scaling values have been equal</p></td>
</tr>
<tr class="even">
<td><p>kurt_scale_1b</p></td>
<td><p>UFix 18.12</p></td>
<td><p>Y-polarization power^2 scaling value</p></td>
<td><p>12288<br />
During tests all scaling values have been equal</p></td>
</tr>
<tr class="odd">
<td><p>kurt_output1a</p></td>
<td><p>UFIx 3.0</p></td>
<td><p>X-pol power^2 short selector</p></td>
<td><p>2</p></td>
</tr>
<tr class="even">
<td><p>kurt_output1b</p></td>
<td><p>UFIx 3.0</p></td>
<td><p>Y-pol power^2 short selector</p></td>
<td><p>2</p></td>
</tr>
<tr class="odd">
<td><p>reg_output_bitselect1</p></td>
<td><p>UFIx 3.0</p></td>
<td><p>X-pol power byte selector</p></td>
<td><p>1</p></td>
</tr>
<tr class="even">
<td><p>reg_output_bitselect2</p></td>
<td><p>UFIx 3.0</p></td>
<td><p>XY real byte selector</p></td>
<td><p>1</p></td>
</tr>
<tr class="odd">
<td><p>reg_output_bitselect3</p></td>
<td><p>UFIx 3.0</p></td>
<td><p>XY imag byte selector</p></td>
<td><p>1</p></td>
</tr>
<tr class="even">
<td><p>reg_output_bitselect4</p></td>
<td><p>UFIx 3.0</p></td>
<td><p>Y-pol power byte selector</p></td>
<td><p>1</p></td>
</tr>
<tr class="odd">
<td><p>Packet_Size</p></td>
<td><p>UFIx 32.0</p></td>
<td><p>Size of packets in 64 bit words</p></td>
<td><p>1025</p></td>
</tr>
<tr class="even">
<td><p>reg_ip</p></td>
<td><p>UFIx 32.0</p></td>
<td><p>destination ip address</p></td>
<td><p>10.0.0.4 == 0167772164</p></td>
</tr>
<tr class="odd">
<td><p>reg_10GbE_destport0</p></td>
<td><p>UFIx 32.0</p></td>
<td><p>Destination port number</p></td>
<td><p>6001</p></td>
</tr>
<tr class="even">
<td><p>xaui_error_reset</p></td>
<td><p>UFIx 32.0</p></td>
<td><p>Used to reset the xaui error counters, drive high then low</p></td>
<td><p>0,1,0</p></td>
</tr>
</tbody>
</table>

### To Processor Software Registers and Recommended Values

| Register     | Data Type | Description                             | Characteristic Value                  |
| ------------ | --------- | --------------------------------------- | ------------------------------------- |
| rx\_valid    |           | indicates reception of valid data       | 1                                     |
| rx\_linkdown |           | counts every clock rx\_linkdown is high | 0, if the link is up                  |
| rx\_empty    |           | counts every clock rx\_empty is high    | 0, if the link is properly configured |

## Design Files

[IBOB Design (not
used)](http://casper.berkeley.edu/svn/trunk/projects/dig_int_kurt_spec/meat_1024pt_lwip.mdl)

[BEE2 Design
(02/05/10)](http://casper.berkeley.edu/svn/trunk/projects/dig_int_kurt_spec/mdls/meat_1024pt_bee2_fpv3.mdl)

[iBOB ADC -\> XAUI Beamformer
Mimicker](http://casper.berkeley.edu/svn/trunk/projects/dig_int_kurt_spec/adc_to_xaui.mdl)

[PDF of Feb 8, 2010
Model](http://casper.berkeley.edu/wiki/images/c/cb/MarsSpec_model_feb8_2010.pdf)

## Description

total spectral output: 1024 channels \* (8 bits X power + 8 bits Y power
+ 8 bits XY real + 8 bits XY imag + 16 bits SK X + 16 bits SK Y) + 8
byte counter = 8200 bytes = 5 x 1640 byte packets

It looks like pulsing the 10GbE end-of-frame several times during 1025
clocks of valid data doesn't work. Probably will just dump the entire
8200 bytes in a single jumbo frame. - never mind, this works fine.

Data rate: 8200 bytes / sampling period

Ex: 1 millisecond period -\> 8 MB/sec

Diagram of original IBOB design:

![Design](kurt_spec.png‎ "Design")

# [ Background](Mars_Lightning_Machine_Background "wikilink")

# Testing

## 18:0:32, Thu Feb 4, 2010

  

Image:qDiSYq2f\_kurt\_spec\_test.png|kurt\_spec\_test.png

# Operation Instructions

## Data Collection

An appropriate 'gulp' command line for capturing all ethernet traffic to
interface eth0:

``` text
sudo gulp -i eth0 > out.pcap
```

Separating a two-beamformer capture into individual
captures:

``` text
/usr/sbin/tcpdump 'src host <beamformer ip address 1>' -r <input file.pcap>  -w <output ip 1.pcap>
/usr/sbin/tcpdump 'src host <beamformer ip address 2>' -r <input file.pcap>  -w <output ip 2.pcap>
```

## Pre-Observing / Testing Procedures

Below are instructions for taking a quick look at a .pcap capture from
the MLM

\- Setup path (tools used are in \~siemion/bin on pulsar-1)

``` text
siemion@pulsar-1:~> export PATH=$PATH:~siemion/bin
siemion@pulsar-1:~> ls -al *.pcap
-rw-r--r-- 1 siemion obs 7507222 2010-02-10 02:12 test.pcap
```

\- Run the MLM pcap processor, meat\_pcap, on the test pcap file.
'prefix' is the file prefix for extracted files

``` text
siemion@pulsar-1:~> meat_pcap32 test.pcap prefix
Completed Successfully
Spectra count: 908
Dropped packet count: 0
```

\- Note that above the dropped packet count is zero, this is calculated
by following the clock cycle counter in each packet. - This will create
a series of binary files containing extracted and reordered spectra for
each polarization and moment:

``` text
siemion@pulsar-1:~> ls -al *.bin
-rw-r--r-- 1 siemion obs  929792 2010-02-10 02:37 prefix_xpower.bin
-rw-r--r-- 1 siemion obs 1859584 2010-02-10 02:37 prefix_xpowersq.bin
-rw-r--r-- 1 siemion obs  929792 2010-02-10 02:37 prefix_ypower.bin
-rw-r--r-- 1 siemion obs 1859584 2010-02-10 02:37 prefix_ypowersq.bin
```

\- Run the 'mkfits.sh' script to create .fits files, syntax is:
mkfits.sh <file_prefix> <spectra>

``` text
siemion@pulsar-1:~> mkfits.sh prefix 908
siemion@pulsar-1:~> ls -al *.fits
-rw-r--r-- 1 siemion obs  933120 2010-02-10 02:37 prefix_xpower.fits
-rw-r--r-- 1 siemion obs 1863360 2010-02-10 02:37 prefix_xpowersq.fits
-rw-r--r-- 1 siemion obs  933120 2010-02-10 02:37 prefix_ypower.fits
-rw-r--r-- 1 siemion obs 1863360 2010-02-10 02:37 prefix_ypowersq.fits
```

\- Launch ds9 to view one of the .fits files

``` text
siemion@pulsar-1:~> ds9 prefix_ypowersq.fits 
```

\- You should see a plot like this (note that I selected the View -\>
Horizontal Graph option to see the slice plot at bottom. I also zoomed
to 1/2):  

Image:xFxNO5yg\_saods9.png|plot of ypol-squared from a test pcap capture

## Data File Format

.pcap captures created on hcro node pulsar-1 should be processed using:

``` text
siemion@pulsar-1:~> meat_pcap32 <input pcap file> <output prefix>
```

The four .bin files output as

``` text
<output prefix>_xpower.bin
<output prefix>_ypower.bin
<output prefix>_xpowersq.bin
<output prefix>_ypowersq.bin
```

are concatenated unsigned binary values with no header information.
...power.bin files are formatted as 8 bit unsigned integers (uint8),
...powersq.bin files are formatted as 16 bit unsigned integers (uint16)

all files contain 1024 point spectra ordered as:

spectra\_1, freq\_1023, spectra\_1, freq\_1022, spectra\_1, freq\_1021
... spectra\_1, freq\_0

spectra\_2, freq\_1023, spectra\_2, freq\_1022, spectra\_2, freq\_1021
... spectra\_2, freq\_0

...

spectra\_N, freq\_1023, spectra\_N, freq\_1022, spectra\_N, freq\_1021
... spectra\_N, freq\_0

Where freq\_1023 is the highest frequency channel (upper side of the
band), freq\_0 is the lowest frequency (lower side of the band)

For example, these files can be read in Matlab using commands like:

``` matlab
power_file = fopen('~/jupiter_on_xpower.bin')
powersq_file = fopen('~/jupiter_on_xpowersq.bin')

power_spectra = fread(power_file, 1024, 'uint8');
powersq_spectra = fread(powersq_file, 1024, 'uint16');
```

### Extracting Small Portions of Captures

Extract 5000 packets from an existing pcap
file:

``` text
-bash-3.00$ /usr/sbin/tcpdump -r jupiter_on.pcap -c 5000 -w jupiter_on_5000.pcap
```

``` text
-bash-3.00$ zip jupiter_on_5000.pcap.zip jupiter_on_5000.pcap 
  adding: jupiter_on_5000.pcap (deflated 18%)
-bash-3.00$ ls -alh *.zip
-rw-r--r--  1 siemion werthimer 25M Mar 26 17:26 jupiter_on_5000.pcap.zip
```

  
  

# Observations

## [MLM Wednesday February 10 2010](MLM_Wednesday_February_10_2010 "wikilink")

## [MLM Monday March 8 2010](MLM_Monday_March_8_2010 "wikilink")

4 pm - 10 pm PST

## [MLM Monday March 22 2010](MLM_Monday_March_22_2010 "wikilink")

5 pm - 11 pm PST

## [MLM Monday March 29 2010](MLM_Monday_March_29_2010 "wikilink")

5 pm - 11 pm PST

## [MLM Monday April 12 2010](MLM_Monday_April_12_2010 "wikilink")

2:45 pm - 10:45 pm PDT

## [MLM Monday April 16 2010](MLM_Monday_April_16_2010 "wikilink")

2:45 pm - 10:45 pm PDT

## [MLM Monday May 8 2010](MLM_Monday_May_8_2010 "wikilink")

<Time>

## [MLM Monday June 1 2010](MLM_Monday_June_1_2010 "wikilink")

<Time>

# Mailing List Archive

[marslightning mailing
list](http://www.mail-archive.com/marslightning@lists.berkeley.edu/)

# References

[Ruf et al
GRL](http://ktb.engin.umich.edu/RSG/pubs_files/GRL-2009-36-13_Ruf_etal_Mars-lightning.pdf)

[Ruf et al
detector](http://ktb.engin.umich.edu/RSG/pubs_files/TGRS-2006-44-3_Ruf-etal_RFI-Detector.pdf)

[Ruf et al Kurtosis as an RFI
Discriminant](http://ktb.engin.umich.edu/RSG/pubs_files/IGARSS-2006_Ruf_etal_ADD_RFI.pdf)
