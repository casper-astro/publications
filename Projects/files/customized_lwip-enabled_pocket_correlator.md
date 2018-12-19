# Customized LWIP-enabled Pocket Correlator

## News and Updates
Nov 26, 2007: Uncovered a small bug in the sync_gen block that caused delayed application of updated sync_period.  Fix currently compiling.<br/>
Nov 25, 2007: Compiled design at 205MHz, working great at 200MHz.<br/>
June, 2008: 13.5 MHz band, 1024 channels design deployed at Green Bank on PAPER array to track satellites.

## Diagrams and Images
* View [top level block diagram](customized_lwip_pocket_correlator_files/pocoforwiki.pdf) 

## Pocket Correlator Software

Most recent software development for PoCo is in the CASPER SVN repository at http://casper.ssl.berkeley.edu/svn/trunk/projects/pocketcorrelator/poco-0.1.0/

* [udprec.c: Raw UDP Packet Recorder](customized_lwip_pocket_correlator_files/udprec.c)
* [corrplot.c: Real-Time Plotting Correlator Data w/ GRACE](customized_lwip_pocket_correlator_files/corrplot.c)
* [configure.c: Generate Configuration Scripts](customized_lwip_pocket_correlator_files/configure.c)
* `poco_conf.py`: Configure an IBOB over Ethernet w/ Python
    ```python
    import telnetlib
    import time

    t = telnetlib.Telnet('169.254.128.5') #ibob address fd = open('parspecTofu.txt') #file with configuration commands

    for line in fd.readlines():

    if not line.startswith('#'): # don't process lines that start with a pound sign
        t.write(line)
        print "Writing:", line
        time.sleep(1)
    t.close() fd.close()
    # Save this, and run it (replacing filename.py for the real filename):
    python filename.py
    ```

## Useful Software Tools
A great tool for real time plotting and visualization is [GRACE](http://plasma-gate.weizmann.ac.il/Grace/). <br/>
[Netcat](http://netcat.sourceforge.net/download.php) is very useful for writing/sending configuration scripts.<br/>  

Note on editing Netcat source for microsecond delay intervals:
Netcat only supports delay intervals in seconds (via the -i option) by default. An absurdly ugly hack to enable microsecond delays can be accomplished by changing line 729 in core.c (Netcat version 0.7.1):

`delayer.tv_sec = opt_interval;`

to:

`delayer.tv_usec = opt_interval;`

and recompiling. After making this change, the argument to the -i option will be interpreted in microseconds.

[Ethereal/Wireshark](http://www.wireshark.org/)

## Deployments
* [UNC PARI Pocket Correlator](UNC_pari_pocket_correlator.md)
* SatCorr