# ATA "Fly's Eye" Operation Instructions

There are two primary parts to controlling the Fly's Eye experiment at ATA. The first is to control the pointings of the antennas, and this is done using the standard ATA system on the "user1" machine. The second is to configure the Fly's Eye spectrometers and dump data from them to the data recorder machine "flytrap". Typically you will control the antennas, and then control the instrument.

These instructions provide a rough guide, and many more advanced options have not been explained. [[User:Pmcmahon|Peter McMahon]] and [[User:Siemion|Andrew Siemion]] are the principle developers of the system, so any questions you have can be addressed to them. Dan Werthimer is the developer team lead, so he is also an excellent contact, and will be available in the long term.

## ATA Antenna Control ##

You need a login to the machine user1. If you do not have an appropriate login, contact Prof. Geoffrey Bower (UC Berkeley). All ATA control commands are issued via an SSH session to user1.

There are two main modes of operation: either you will want to point the antennas connected to the Fly's Eye spectrometers at specific points in the sky and track those points (e.g. at a known pulsar), or you will want to specify a fixed azimuth and elevation for each antenna and let the sky rotate through the beams. Typically you will use the former mode to verify that the system is working, and the latter mode when you want to run the Fly's Eye experiment for its intended purpose - to search the sky for strong single pulses. In both modes, you need to set the  "sky frequency", which is the frequency of the mixer that controls where the centre of the 200MHz band that you are observing is.

### Mode 1: Tracking a single source with all antennas ###

* Set sky frequency in MHz. This is typically 1430MHz. Use the command:

  > atasetskyfreq a 1430.0

* The ATA has a catalogue of ephemeris data for a number of sources. To generate an emphemeris for a source in the catalogue, use:

  > ataephem crab

This will generate a file crab.ephem. It is also possible to generate ephemeris for source not in the catalog. See ataephem help for options on using ra and dec.

  > atadescribeephem crab.ephem

This will tell you over what range the ephemeris is valid for.  By default ataephem generates an ephemeris that can be used until the source sets.

* If the source you wish to track is not in the ATA catalogue, then you need to generate an ephemeris manually by specifying RA an DEC.

  > ataradecephem 03:32:59.3758 54-34-43.518 now +1hours > B0329+54.ephem

This creates an ephemeris for PSR0329+54, which is stored in the file B0329+54.ephem.

* Once you have generated an ephemeris file, you can set the antennas to track the source.

  > atatrackephem {antenna list} crab.ephem

This tracks the source described in crab.ephem. {antenna list} is of the form 1a,1b,2a,2c,.... You need to supply the list of antennas that are connected to the Fly's Eye instrumentation. The Radio Astronomy Lab maintains an up-to-date list of these connections. Prof. Bower should be able to supply you with this list. There is a [[ATA "Fly's Eye" antenna connections|list]] of the connections on this wiki, but it is not guaranteed to be up-to-date, so check with Prof. Bower before using it.

An example of this, using the original antenna list, is:

  > atatrackephem 3l,1j,1h,5c,5g,3g,4l,3d,1k,1d,2j,1c,4j,5e,1a,1e,2b,1f,2c,4k,2f,1g,2h,2l,1b,2a,2g,2k crab.ephem

* Watch antenna status until the antennas have moved the positions you have requested before beginning your observation. You can view antenna status using:

  > ataasciistatus -l

Wait until the "errors" for each antenna are zeros.

### Mode 2: Setting fixed azimuth/elevation configurations for all antennas ###

* Set sky frequency in MHz. This is typically 1430MHz. Use the command:

  > atasetskyfreq a 1430.0

* To generate a set of az,el coordinates for each antenna and use atasetazel to set each antenna. For example:

  > atasetazel 1a 150 30

will move antenna 1a to azimuth 150, elevation 30.

There is script for setting a subset of antennas at:

  /data/tumulus/obs/2007/1219/fly/antennapos.csh

This sends antennas to the south pointing, which includes the Galactic Center.

  /data/tumulus/obs/2007/1219/fly/flyseye/flyseyenorth.sh

This sends antennas to the north, az=20, el=40, as center coordinates.

Note that these two files point the antennas that were connected to the instrument on 19 December 2007, and the antenna list may have changed. Check with Prof. Bower before you use them if you're not sure. A copy of the 'flyseyenorth' script is below:
```bash
#!/usr/bin/env bash
atasetazel 3L 10.767984 35.669873
atasetazel 1J 13.845322 35.669873
atasetazel 1H 16.922661 35.669873
atasetazel 5C 20.000000 35.669873
atasetazel 5G 23.077339 35.669873
atasetazel 3G 26.154678 35.669873
atasetazel 4L 12.086415 37.834936
atasetazel 3D 15.251849 37.834936
atasetazel 1K 18.417283 37.834936
atasetazel 1D 21.582717 37.834936
atasetazel 2J 24.748151 37.834936
atasetazel 1C 27.913585 37.834936
atasetazel 4J 10.209445 40.000000
atasetazel 5E 13.472964 40.000000
atasetazel 1A 16.736482 40.000000
atasetazel 1E 20.000000 40.000000
atasetazel 2B 23.263518 40.000000
atasetazel 1F 26.527036 40.000000
atasetazel 2C 11.567888 42.165064
atasetazel 4K 14.940733 42.165064
atasetazel 2F 18.313578 42.165064
atasetazel 1G 21.686422 42.165064
atasetazel 2H 25.059267 42.165064
atasetazel 2L 28.432112 42.165064
atasetazel 1B 9.515261 44.330127
atasetazel 2A 13.010174 44.330127
atasetazel 2G 16.505087 44.330127
atasetazel 2K 20.000000 44.330127
```


## Fly's Eye Instrumentation Control ##

* Turn Walsh Switching off. To do this, use a web browser to access 10.3.33.3 (again, contact Prof. Bower for the login details if you do not have them), and turn off the power point marked "Walsh Switching". You can either use a VNC session to a machine at HCRO with a graphical browser, or you can use the text browser "lynx" in an SSH session.

* Log in to the machine flytrap. This is the data recording and control machine connected to the two racks of Fly's Eye IBOBs.

* There should be two USB-attached 500GB SATA drives connected to flytrap. Use the command df to verify that they are connected and have been mounted. They are typically mounted to /media/disk1 and /media/disk2.

* It is possible to reconfigure the IBOBs using a variety of programs in /home/casper/findpulse_master. Of particular interest is configure which is used to generate configuration files for all the IBOBs (which most importantly contain the sync pulse period that specifies the dump rate (nominally 1600Hz), the equalization coefficients and the selection of which 8 bits out of the 64-bit accumulator are to be outputted. The findpulseconf program configures the IBOBs using the configuration files in the current directory.

* The firewall on flytrap needs to be configured to ensure that ICMP packets are not sent on Ethernet interface eth1 (which is the interface connected to the IBOBs). This is because the IBOB's PowerPC cannot handle processing received ICMP packets and sending out data at 1600Hz simultaneously, so if ICMP packets are received by an IBOB, some data packet loss occurs. The following command sets up the iptables rule to drop (-j DROP) outgoing (-A OUTPUT) ICMP packets (-p icmp) on the outgoing interface eth1 (-o eth1).

 > iptables -A OUTPUT -o eth1 -p icmp -j DROP

* Set the system UDP receive buffers to be large (e.g. 8MB). This appears to help reduce/remove instances of lost packets.

 > sysctl -w net.core.rmem_max=8388608

 > sysctl -w net.core.rmem_default=8388608

* To capture data being sent from the IBOBs to flytrap, we use [gulp](http://staff.washington.edu/corey/gulp/). Only write data dumps to one of the two USB disks. Writing to any other location, including the local disk, will likely result in packet loss. The command to start a gulp capture is:

 > nuhup ~root/fulp/gulp -i eth1 > /media/disk2/data/observation_date/dump.log 2> /media/disk2/data/observation_date/dump.err &

You can stop the capture by using

 > ps -aux | grep -i gulp

to find the process ID of gulp and then issuing a kill command. If ps reported that the process ID was 32562, then you would issue this command to end the dump:

 > kill -2 32562

The reason we use nuhup is to prevent the dump from stopping if your SSH connection dies. The dump will be saved to dump.log and the output from stderr will be saved to dump.err. It is very important to look at the contents of dump.err - it will contain an entry noting how many packets were dropped by the kernel. This should be zero. It will also report the percentage of the ring buffer that gulp used, and this should be less than 100% (typically less than 50% for a run of 20 hours).

* Before you do your actual data run, we highly recommend you do a quick run to check that everything is working. Do a 20 second data dump, and check the stderr output (dump.err, in the case above) to make sure that no packets were lost. Copy the output data file to your data analysis machine and take a look at some of the accumulated spectra. Make sure they look as you expect (the most common problem here is that the set of 8 bits you are extracting from the IBOBs is set too high or too low, so you may see nothing, or noise in all 8 bits). Once you are satisfied that you are receiving data the looks reasonable, and that you aren't losing any packets when dumping data, then you can start your actual, long data dump.

* Once you have killed your data dump, turn Walsh Switching back on.

## Logfile Format ##
```c
/* packet headers */
/* the 21 byte UDP data packets look like this: */
/* 8 bytes (double) time */
/* 1 byte x engine number */
/* 4 bytes (unsigned int) vector number within an integration */
/*   (ie if you want to send 10MB every integration and you break it up into 1MB packets, this */
/*    number will range from 0 to 9) */
/* 4 bytes (unsigned int) flags (not used atm - foresee use to flag bad data) */
/* 4 bytes (unsigned int) data length (in bytes) (payload length) */


 // PCAP global header -- SEE: http://wiki.wireshark.org/Development/LibpcapFileFormat
 //typedef struct pcap_hdr_s {
 //     4  guint32 magic_number;   /* magic number */
 //     2  guint16 version_major;  /* major version number */
 //     2  guint16 version_minor;  /* minor version number */
 //     4  gint32  thiszone;       /* GMT to local correction */
 //     4  guint32 sigfigs;        /* accuracy of timestamps */
 //     4  guint32 snaplen;        /* max length of captured packets, in octets */
 //     4  guint32 network;        /* data link type */
 //} pcap_hdr_t;  //24 bytes total

//PCAP per packet header
//typedef struct pcaprec_hdr_s {
//        guint32 ts_sec;         /* timestamp seconds */
//        guint32 ts_usec;        /* timestamp microseconds */
//        guint32 incl_len;       /* number of octets of packet saved in file */
//        guint32 orig_len;       /* actual length of packet */
//} pcaprec_hdr_t;
```