# Swinburne Instrumentation Projects

This page describes the instrumentation desires for ATNF/Swinburne for the next few years.

## 13 beam digital pulsar survey of the Galaxy/Universe ##
(September 2008)

This will use 13 iBobs, straight to a 10 Gb card, 1024 channels, Nstokes=2, 400 MHz IF, ~300 MHz of which is useable.

## 1 GHz baseband broadband polyphase FB for coherent dedispersion ##
(As soon as possible)

This is to replace CPSR2 = 2x2x64 MHz x 2bits -> DMA -> IP to 28 servers.

Ideally we would want:

256 MHz -> 16 polyphase filterbank channels @ 8 bits -> 16 IP addresses. (8 Gb/s)
512 MHz -> 32 polyphase filterbank channels @ 8 bits -> 32 IP addresses. (16 Gb/s)
1024 MHz -> 32 polyphase filterbank channels @ 4 bits -> 32 IP addresses. (16 Gb/s)

1 ROACH board looks the goods.

We are achieving 64 MHz coherently dedispersed in real time for DM=250 at 3.0 GHz on a single server.

## iBOB firmware upgrade to allow selectable 2/4 bit baseband data over a tunable filter spanning 192 or 128 or 64 MHz out of 400 MHz ##
(March 2009)

Number of bits probably max 4, min 2. This would enable high-res spectroscopy at Parkes.

Preliminary trials achieve up to 400 GB/s into a server (catching
only) ~250 MB/s
(catch and move to larger ring buffer). I think we may be limited to
128 MHz here,
192 MHz is a stretch target. Ideally we would deliver ~16384 channels over the
192 MHz for 2.5 km/s resolution. May have to stoop to 3 bits. 4 bits and 192 MHz looks very tough on existing servers. Newer 1600 MHz FSH units may be better.

## Multiple tied array beams from a large-N small-D telescope ##
(2010+)

The MWA and ASKAP will have large fields of view. Timing multiple pulsars at once is an ideal app. We've looked into this in software and it looks difficult because of memory bandwidth issues. If we could feed ~512 2x32 MHz bands into a ROACH-based correlator and receiver 16-32 tied array beams this would be fantastic for pulsar monitoring applications. For MeerKAT, ~80 x 1024 MHz into a tied array beam would be wonderful.

## GMRT upgrade ##

30 x 400 MHz system.
