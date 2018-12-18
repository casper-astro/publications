% Gaussian noise (1024 vectors with 1024 samples/per vector)
x=randn(1024);

% Order 100 FIR filter (band-pass from 1/2 to 3/4 band)
b=fir1(100,[0.5 0.75]);

% Band limited Gaussian noise
y=filter(b,1,x);

% Simulate 20% gain mismatch between interleaved ADCs
xgain=x;
xgain(1:2:1023,:)=xgain(1:2:1023,:)*1.2;

ygain=y;
ygain(1:2:1023,:)=ygain(1:2:1023,:)*1.2;

% Simulate 1% of dynamic range DC offset between interleaved ADCs
% (Assume RMS of band limited noise is 20% of total dynamic range)
xoff=x;
xoff(1:2:1023,:)=xoff(1:2:1023,:)+0.01*5*std(reshape(x,1,2^20),1);

yoff=y;
yoff(1:2:1023,:)=yoff(1:2:1023,:)+0.01*5*std(reshape(y,1,2^20),1);

% Simulate both effects
xboth=x;
xboth(1:2:1023,:)=xboth(1:2:1023,:)*1.2+0.01*5*std(reshape(x,1,2^20),1);

yboth=y;
yboth(1:2:1023,:)=yboth(1:2:1023,:)*1.2+0.01*5*std(reshape(y,1,2^20),1);

% Plot integrated spectra of all signals
subplot(4,2,1);
semilogy(sum(abs(fft(x)),2));
legend('Ideal (broadband)');

subplot(4,2,2);
semilogy(sum(abs(fft(y)),2));
legend('Ideal (band limited)');

subplot(4,2,3);
semilogy(sum(abs(fft(xgain)),2));
legend('Gain Mismatch (broadband)');

subplot(4,2,4);
semilogy(sum(abs(fft(ygain)),2));
legend('Gain Mismatch (band limited)');

subplot(4,2,5);
semilogy(sum(abs(fft(xoff)),2));
legend('DC Offset Mismatch (broadband)');

subplot(4,2,6);
semilogy(sum(abs(fft(yoff)),2));
legend('DC Offset Mismatch (band limited)');

subplot(4,2,7);
semilogy(sum(abs(fft(xboth)),2));
legend('Gain and DC Offset Mismatch (broadband)');

subplot(4,2,8);
semilogy(sum(abs(fft(yboth)),2));
legend('Gain and DC Offset Mismatch (band limited)');

% Compute and plot intra-spectrum correlations
figure(2);
fx=fft(x);
fxg=fft(xgain);
fxxf=fx(2:512,:).*fx(512:-1:2,:);
fxggxf=fxg(2:512,:).*fxg(512:-1:2,:);

subplot(2,2,1);
semilogy(abs(sum(fxxf,2)));
legend('Ideal ISC (Mag)');

subplot(2,2,2);
plot(angle(sum(fxxf,2)));
legend('Ideal ISC (Phase)');

subplot(2,2,3);
semilogy(abs(sum(fxggxf,2)));
legend('Mismatched gain ISC (Mag)');

subplot(2,2,4);
plot(angle(sum(fxggxf,2)));
legend('Mismatched gain ISC (Phase)');
