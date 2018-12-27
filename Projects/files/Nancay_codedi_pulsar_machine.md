# Nancay CoDeDi Pulsar Machine

The Nancay CoDeDi Pulsar Machine is a high-speed spectrometer intended
for coherent dedispersion applications.

## People

Berkeley: Don Backer

KAT: Peter McMahon

ASTRON/Amsterdam: Joeri van Leeuwen

Nancay: Ismael Cognard, Gilles Theureau

NRAO CV: Paul Demorest

## Instrument Overview

This instrument is in the prototype stage. A first version was deployed
in August 2008. It incorporates the IBOB spectrometer to a single CPU
single GPU computer server, and has observed its first pulsar.

The overall architecture of this class of instrument is as follows:

![NancayCoDeDiSpecArchitecture.png](NancayCoDeDiSpecArchitecture.png
"NancayCoDeDiSpecArchitecture.png")

A spectrometer (IBOB-based) channelizes a 400MHz (perhaps wider)
bandwidth and distributes the resulting complex voltages from each band
to different compute servers, which perform coherent dedispersion in
real-time.

At a high level the IBOB design will look like this:

![NancayCoDeDiSpecIBOB.png](NancayCoDeDiSpecIBOB.png
"NancayCoDeDiSpecIBOB.png")
