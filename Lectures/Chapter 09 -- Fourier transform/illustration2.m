close all
clear

X=[0:1:255];
L=size(X,2);

Y1=zeros(1,L);
Y1([1:L*0.2])=1;

FFT_Y = fft(Y1);

figure;plot (X,Y1)
title('Signal')
xlabel('x')
ylabel('f(x)')
axis([min(X),max(X),0,1.2])
print -deps -F:16 signal1-1D.eps

NFFT=size(FFT_Y, 2);
nVals=(0:NFFT-1)/NFFT; %Normalized DFT Sample points
figure;plot (nVals,FFT_Y)
title('FFT')
xlabel('Normalised frequency')
ylabel('F(u)')
print -deps -F:16 FFT1-1D.eps

fVals=(-NFFT/2:NFFT/2-1)/NFFT; %DFT Sample points	 	 
figure;plot(fVals,fftshift(abs(FFT_Y)));
title('Fourier Spectrum');	 	 
xlabel('Normalized Frequency')	 	 
ylabel('|F(u)|');
axis([min(fVals),max(fVals),min(abs(FFT_Y))-0.05,max(abs(FFT_Y))+0.05])
print -deps -F:16 Fourier_spectrum-1D.eps

figure;plot(fVals,fftshift(abs(FFT_Y).^2));
title('Power Spectrum (P(u))');	 	 
xlabel('Normalized Frequency')	 	 
ylabel('|F(u)|^2');
axis([min(fVals),max(fVals),min(abs(FFT_Y))^2-0.05,max(abs(FFT_Y))^2+0.05])
print -deps -F:16 Power_spectrum-1D.eps



