DC Offset in FFT Butterflies
============================

Aaron Parsons (aparsons@ssl)
----------------------------

In an effort bless the 3 MULT complex multiply, I characterized the DC
offset introduced in the butterflies in the FFT. I found initially that
it was larger than I thought reasonable (of order the LSB per multiply,
I seem to remember). The culprit was that the twiddle factors were all
being truncated (instead of rounded) as simulink converted the floating
point coefficients into fixed-point numbers. I solved this by rounding
manually. This bug is hard to detect in practice because it does not
apply to the first 2 stages of an FFT (so you would see it in the DC bin
at a maximum of 1 LSB \* 1/4 FFT window), and generally by making the
FFT slightly noisier between bins because of imperfect signal
cancellation. I doubt this bug has affected anyone's data in a
perceptible way so far, but with correlators on the way, we'd have
noticed at some point.

After the fix, I ran a random amplitude \* e\^iwt quantized at 18 bits
through the cmult \* twiddle\_factor and calculated the integrated
change in complex amplitude over 10,000 clocks:\
\
Type of multiplier, behavior between mults & adds\
\
3 MULT complex multiply, truncating: -7e-3 offset over 1e5 clocks =
-7e-8\
\
3 MULT complex multiply, round even: -5e-3 offset over 1e5 clocks =
-5e-8\
\
4 MULT complex multiply, truncating: -5e-3 offset over 1e5 clocks =
-5e-8\
\
4 MULT complex multiply, round even: -5e-3 offset over 1e5 clocks =
-5e-8

Do not confuse the rounding behavior internal to the multiplier with
rounding behavior on the final result: truncating the final result will
introduce a DC bias of order the LSB. What these results show is that
internal to the cmult, truncating vs. rounding before adding doesn't
affect the final 18 bits out for a 4 MULT, and it does slightly for the
3 MULT. For 18 bits out, this DC bias is of order the 23/24th bit.

Anyway, just an FYI.

Aaron Parsons\
aparsons@astron.berkeley.edu\
(work) 510-642-5189
