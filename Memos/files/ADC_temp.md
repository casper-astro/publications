ADC temperature vs. sample time characteristics
===============================================

Aaron Parsons, David MacMahon, and Dan Werthimer
------------------------------------------------

April 2006
----------

Test setup:
2 ADC cards in 1 IBOB, data collected post DDC. 4 bits for real & imag,
for ADC cards A and B. For each sample, the relative phase between A and
B was computed via: phase = angle(AB\*)

The 16384 consecutive phase samples were partitioned into 16 sets of
1024 samples, and averaged over each set to mitigate quantization error
while demonstrating the stability of the measurement.

To heat an ADC, we used a heat gun applied to the top, and to cool, we
blew air over the ADC. We measured temperature with an infrared
thermometer aimed at the top of the packaging. This heating/measurement
system was crude because it we had to estimate the die temperature, and
for bursty heating and cooling, it was hard to estimate how much of the
heat penetrated the casing to affect the die.

Sample rate = 600 MHz\
Test tone = 193 MHz\
DDC LO = 150 MHz\
Ambient Temp of casing = 58 C

|dT (K) | rel Phase (deg) |
|-------|-----------------|
| +0 |-3.1 |
| -10 | -1.2 |
| +0 | -3.1 |
| +30 | -14.3 |
| +0 | -3.1 |
| -20 | +1.5|

Estimated dt/dT: (Delta(deg)/360) / (193 MHz \* Delta(dT)) = 5 ps/K

I've attached 2 text files with our data. "delaytemp.txt" contains the
measurements we used to estimate the delay/temperature dependence.

The second is a measurement of the 2 ADCs operating at Ambient
Temperature and observing the scaling of the standard deviation of the
average phase over bins with the number of bins that 16384 samples were
divided into. In our original measurement, we divided 16384 samples into
16 bins and measured the average value over these bins. In this
follow-up measurement, I divided samples into 4, 8, 16, 32, 64, and 128
bins and measured the standard deviation of the average phase across
bins. If the data represents normally distributed noise around a central
value, then the standard deviation should scale as the sqrt of the
number of samples in each bin. Otherwise, if the central value moves
around with time (if it has jitter), then this scaling should not hold.

The final column in the second data file represents the stddev \*
sqrt(samples per bin). If we have normally distributed noise (low
jitter) this should be relatively constant, and I beleive that is what
we observe. Occasionally the 4 bin measurement deviates by being extra
small, but I think this is small-number statistics at work.

So the short answer is that temperature jitter is not a problem on
time-scales of thousands of samples.

A=58 C\
B=55 C

-3.15322680005 -3.18335181476 -3.35976162471 -3.31595207192
-3.1145355192 -3.25755937111 -3.28030150617 -3.0138031465 -3.2978614961
-3.14248831931 -3.34470295547 -3.27486365122 -3.23188883516
-3.02460881675 -3.10050384109 -3.19166346309

A=56 C\
B=47 C

-1.3708478453 -1.17085348732 -1.16411154087 -1.07367451078
-1.22855597932 -1.13587694337 -1.10302417296 -1.18526048825
-1.13856431169 -1.21627090506 -1.30500469789 -0.999883756635
-1.22705929628 -1.16917222611 -1.20305421198 -1.19126156053

A=58 C\
B=57 C

-3.01707252094 -3.16051690914 -3.11750246058 -3.07668555929
-2.99656534133 -2.97219336529 -3.17591973919 -2.99834457663
-3.01581649302 -3.00056409994 -2.94112683123 -3.0777823417
-2.95323428896 -2.99902157763 -2.89381014837 -2.96885395122

A= 58 C\
B= 90 C

-14.5782099666 -14.3137653409 -14.4073532647 -14.2150034546
-14.3840178029 -14.4415900668 -14.4051315171 -14.3636952015
-14.3702305937 -14.3789047345 -14.3962537216 -14.3823193424
-14.4392472367 -14.5628493708 -14.5054609302 -14.4194376141

A=57 C\
B=58 C

-3.07917882633 -3.08086231187 -3.18680388018 -3.18179125854
-3.3116817939 -3.11434984901 -3.17323199343 -2.99414471569
-3.06860219285 -3.31698426658 -3.12920703848 -3.22432943099
-3.1894636915 -3.23763419762 -3.20080800128 -3.29776574634

A=57 C\
B=37 C

1.42983454801 1.53688795344 1.36894090395 1.37285859006 1.30820029861
1.34437184743 1.31560926582 1.35426938466 1.43177449826 1.24541401302
1.41332105256 1.40321809343 1.28758231454 1.37311543221 1.3415487194
1.34686884855

| N bins | stddev | sqrt(16384/bins) \* stddev |
|--------|--------|----------------------------|
| 4 | 3.1981815775 | 0.0229134368952 | 1.46645996129 |
| 8 | 3.19820338993 | 0.0257787959287 | 1.16661513037 |
| 16 | 3.19851303392 | 0.0514320043573 | 1.64582413943 |
| 32 | 3.1993814479 | 0.0905608751967 | 2.04915868678 |
| 64 | 3.20260689425 | 0.169854473079 | 2.71767156927 |
| 128 | 3.21069441931 | 0.284109621643 | 3.21433344103 |
| 4 | 3.17625690738 | 0.0418539779609 | 2.6786545895 |
| 8 | 3.1763039568 | 0.0452839902147 | 2.04931945984 |
| 16 | 3.17738878296 | 0.0945689793665 | 3.02620733973 |
| 32 | 3.17806831046 | 0.115160755999 | 2.60579044779 |
| 64 | 3.17964793258 | 0.152659061169 | 2.44254497871 |
| 128 | 3.18404110494 | 0.226410184745 | 2.56153883141 |
| 4 | 3.19603241967 | 0.0268288037061 | 1.71704343719 |
| 8 | 3.19635584811 | 0.0527945534398 | 2.38920875181 |
| 16 | 3.19752948398 | 0.101446330866 | 3.24628258771 |
| 32 | 3.19853082534 | 0.129212993798 | 2.92375629223 |
| 64 | 3.20065970208 | 0.17412376532 | 2.78598024512 |
| 128 | 3.20674349485 | 0.263249689177 | 2.9783302458 |
| 4 | 3.18348343593 | 0.0233991511728 | 1.49754567506 |
| 8 | 3.18373329125 | 0.0462428723082 | 2.0927135098 |
| 16 | 3.18412566256 | 0.0680952891244 | 2.17904925198 |
| 32 | 3.18568058145 | 0.120588143852 | 2.72859821596 |
| 64 | 3.18834541608 | 0.177559076523 | 2.84094522436 |
| 128 | 3.19744735211 | 0.299416604315 | 3.38751218098 |
| 4 | 3.1458844814 | 0.0379722130126 | 2.43022163281 |
| 8 | 3.14598518293 | 0.0455575445987 | 2.06169911808 |
| 16 | 3.14648981978 | 0.0724631261765 | 2.31882003765 |
| 32 | 3.14836938498 | 0.130700049443 | 2.95740452041 |
| 64 | 3.15105971465 | 0.184472339308 | 2.95155742893 |
| 128 | 3.15628843041 | 0.258861690054 | 2.92868570282 |
| 4 | 3.15800824861 | 0.0454627311364 | 2.90961479273 |
| 8 | 3.15880979006 | 0.0844396316104 | 3.82130151121 |
| 16 | 3.15965663242 | 0.111717484745 | 3.57495951184 |
| 32 | 3.16135753692 | 0.152421251391 | 3.44889921457 |
| 64 | 3.16318753438 | 0.186564035381 | 2.9850245661 |
| 128 | 3.1703314174 | 0.28293472352 | 3.20104098614 |