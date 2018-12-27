## Development Team

This project has been designed as a part of the GMRT upgrade activities
by Kaushal D. Buch of the Digital Backend group, Giant Metrewave Radio
Telescope, NCRA-TIFR, India.

Testing Support: Shruti Bhatporia, Short Term Engineering Intern,
Digital Backend Group, GMRT.

For further details or clarifications regarding this project email on :
kdbuch@gmrt.ncra.tifr.res.in, kaushal.buch@gmail.com

## Project Introduction

This RFI mitigation block uses the excision technique for removal of
impulsive RFI. Primarily, the block has been designed to mitigate
impulsive time domain (broadband) RFI. This type of RFI is
pre-dominantly observed due to high voltage power-line and automobile
sparking, corona discharges and switching of inductive load. The block
operates on Nyquist sampled digital time-series and can be integrated
with the CASPER tool-flow along with the other signal processing blocks
on the FPGA. The design contains two distinct blocks, one for RFI
detection and the other for RFI filtering.

## Computing Robust Standard Deviation

RFI manifest as outliers in the statistical distribution of astronomical
signal. A conventional estimator of statistical dispersion (standard
deviation) gets biased in the presence of outliers and provides an
inaccurate estimate in the presence of RFI. Here, Median Absolute
Deviation (MAD) has been used for computing standard deviation of the
distribution. This estimator can handle up to 50% outliers
(theoretically) in a given data set.

MAD = median(|x - median(x)|)

For normal distribution, MAD can be scaled to robust standard deviation
using σ = 1.4826 \* MAD

RFI detection and filtering threshold can be calculated from robust
standard deviation : Threshold = median ± n\*σ

Here ‘n’ is ‘aggressiveness’ parameter which is user programmable.

Any value occurring outside this threshold would be considered as RFI.

## RFI Detection and Filtering using MAD based Threshold

Once the RFI is detected, the sample can be filtered by replacing it
with either the median or a constant value or a sample drawn from a
Gaussian distribution (noise). Alternatively the samples can simply be
clipped at their detection threshold. The option can be selected by the
user.

In case of replacement with noise, a sample with standard deviation
similar to that of the distribution has to be generated. This is done
with the help of digital noise source developed at the GMRT. More
details of the digital noise source are available on:
<https://casper.berkeley.edu/wiki/Variable_Correlation_Digital_Noise_Source_for_FPGA>

## FPGA Implementation

Since MAD requires recursive median computation, it is difficult to
implement the approach in real-time. It was found that the histogram
based approach for median calculation is best suitable for real-time
FPGA implementation and is used in this block.

Currently, the design has fixed parameters and can work with 8-bit
signed data and a window size of 1024 samples up to a maximum clock of
250 MHz. Sliding window MAD is computed for contiguous 1024 sample
windows. The resource utilization for design in its current form is \~20
% slices and 3% Block RAM.

A separate block computes the threshold and filters the RFI based on the
option selected by the user.

## Project Files

Design file: Version 1: June 2014:
![Rfi\_blk\_v6\_casper.zip](Rfi_blk_v6_casper.zip
"Rfi_blk_v6_casper.zip")

Note: This version is undergoing rigorous testing and
improvements/changes would be reflected in the subsequent versions.

## Test Results

The design was integrated with the GMRT wideband backend (GWB) and was
tested with antenna signals. The results presented here provide a
glimpse of the broadband RFI removal capability of the design.

The tests described here were carried out with the following setup:

RF: 600 MHz  
RF BW: 100 MHz  
Processing BW: 200 MHz  
Antenna: GMRT Central Square Antenna - C04  
No. of Spectral Channels: 2048  
GWB mode: Incoherent Array  
Integration time: 1.3ms  
The plots shown below are Total Intensity over time for one spectral
channel corresponding to RF of \~651 MHz. The first subplot shows the
filtered time series at 3 sigma threshold (filtered values replaced by
zero), the second subplot is the original time series (without
filtering) and the third subplot shows overlap plot of the filtered and
unfiltered time series.  
![Impulsive RFI Mitigation - Results from
GWB](Timeseries_1blk_skytest_3s_rc0.jpg
"Impulsive RFI Mitigation - Results from GWB")  
  
![Impulsive RFI Mitigation - Results from
GWB](Timeseries_skytest_3s_rc0.jpg
"Impulsive RFI Mitigation - Results from GWB")  

## Queries, Suggestions and Feedback

Kaushal Buch, Digital Backend Group, GMRT, NCRA-TIFR, India
(kdbuch@gmrt.ncra.tifr.res.in, kaushal.buch@gmail.com)
