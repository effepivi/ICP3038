close all
clear

% First create some data. Consider data sampled at 1000 Hz. Start by forming a time axis for our data, running from t=0 until t=.25 in steps of 1 millisecond. Then form a signal, x, containing sine waves at 50 Hz and 120 Hz.
t = 0:.001:.25;
x = sin(2*pi*50*t) + sin(2*pi*120*t);
plot(x(1:50))
title('Clean time domain signal')
print -deps -F:16 clean_signal.eps

% Add some random noise with a standard deviation of 2 to produce a noisy signal y. Take a look at this noisy signal y by plotting it.
y = x + 2*randn(size(t));
plot(y(1:50))
title('Noisy time domain signal')
print -deps -F:16 noisy_signal.eps

% Clearly, it is difficult to identify the frequency components from looking at this signal; that's why spectral analysis is so popular.

% Finding the discrete Fourier transform of the noisy signal y is easy; just take the fast-Fourier transform (FFT).
Y = fft(y,251);

% Compute the power spectral density, a measurement of the energy at various frequencies, using the complex conjugate (CONJ). Form a frequency axis for the first 127 points and use it to plot the result. (The remainder of the points are symmetric.)
Pyy = Y.*conj(Y)/251;
f = 1000/251*(0:127);
plot(f,Pyy(1:128))
title('Power spectral density')
xlabel('Frequency (Hz)')
print -deps -F:16 power_spectral_density_of_noisy_signal.eps

% Zoom in and plot only up to 200 Hz. Notice the peaks at 50 Hz and 120 Hz. These are the frequencies of the original signal.
plot(f(1:50),Pyy(1:50))
title('Power spectral density')
xlabel('Frequency (Hz)')
print -deps -F:16 zoom_power_spectral_density_of_noisy_signal.eps



