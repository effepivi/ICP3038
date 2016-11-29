close all
clear

pkg load image

% First create some data. Consider data sampled at 1000 Hz. Start by forming a time axis for our data, running from t=0 until t=.25 in steps of 1 millisecond. Then form a signal, x, containing sine waves at 50 Hz and 120 Hz.
image=imread('12fig20.jpg');
%image = rgb2gray(image);
figure;imshow(image,[0 255])
title('Clean spatial domain image')
print -deps -F:16 clean_signal_3.eps


% Add some random noise with a standard deviation of 2 to produce a noisy signal y. Take a look at this noisy signal y by plotting it.
y = image + 20*randn(size(image));
figure;imshow(y,[0 255] )
title('Noisy spatial domain image')
print -deps -F:16 noisy_signal_3.eps

% Clearly, it is difficult to identify the frequency components from looking at this signal; that's why spectral analysis is so popular.
y_padding=zeros(max(size(image)));
y_padding(1:size(image,1),1:size(image,2))=y;

% Finding the discrete Fourier transform of the noisy signal y is easy; just take the fast-Fourier transform (FFT).
%Y = fftshift(fft2(y_padding,size(y_padding,1)*2+1,size(y_padding,2)*2+1));
Y = fftshift(fft2(y));

% Compute the power spectral density, a measurement of the energy at various frequencies, using the complex conjugate (CONJ). Form a frequency axis for the first 127 points and use it to plot the result. (The remainder of the points are symmetric.)
Pyy = Y.*conj(Y)/(size(Y,1)*size(Y,2));
figure;imshow(log(Pyy+1),[])
title('Power spectral density')
print -deps -F:16 power_spectral_density_of_noisy_signal_3.eps

% Create a filter
[columnsInImage rowsInImage] = meshgrid(1:size(Y,1), 1:size(Y,2));
centerX = int32(size(Y,1)/2);
centerY = int32(size(Y,2)/2);
radius = int32(size(Y,1)/3);
circlePixels = (rowsInImage - centerY).^2 + (columnsInImage - centerX).^2 <= radius.^2;
circlePixels = circlePixels';
figure;imshow(circlePixels)
title('Filter')
print -deps -F:16 filter1_3.eps
%circlePixels = ones(size(circlePixels));

% Filter
frequency_filtered=Y.*circlePixels;
Pyy_filtered = frequency_filtered.*conj(frequency_filtered)/(size(Y,1)*size(Y,2));
figure;imshow(log(Pyy_filtered+1),[])
title('Power spectral density')
print -deps -F:16 power_spectral_density_of_filtered_signal1_3.eps

% IFFT
filtered=real(ifft2(fftshift(frequency_filtered)));
figure;imshow(filtered,[0 255])
title('Filtered image')
print -deps -F:16 filtered_signal1_3.eps


% Create a filter
[columnsInImage rowsInImage] = meshgrid(1:size(Y,1), 1:size(Y,2));
centerX = int32(size(Y,1)/2);
centerY = int32(size(Y,2)/2);
radius = int32(size(Y,1)/10);
circlePixels = (rowsInImage - centerY).^2 + (columnsInImage - centerX).^2 <= radius.^2;
circlePixels = circlePixels';
figure;imshow(circlePixels)
title('Filter')
print -deps -F:16 filter1_2.eps
%circlePixels = ones(size(circlePixels));

% Filter
frequency_filtered=Y.*circlePixels;
Pyy_filtered = frequency_filtered.*conj(frequency_filtered)/(size(Y,1)*size(Y,2));
figure;imshow(log(Pyy_filtered+1),[])
title('Power spectral density')
print -deps -F:16 power_spectral_density_of_filtered_signal2_3.eps

% IFFT
filtered=real(ifft2(fftshift(frequency_filtered)));
figure;imshow(filtered,[0 255])
title('Filtered image')
print -deps -F:16 filtered_signal2_3.eps



