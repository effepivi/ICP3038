close all
clear

pkg load image

function f=gaussian2d(N,sigma)
  % N is grid size, sigma speaks for itself
 [x y]=meshgrid(round(-N/2):round(N/2), round(-N/2):round(N/2));
 f=exp(-x.^2/(2*sigma^2)-y.^2/(2*sigma^2));
 f=f./sum(f(:));
endfunction


% First create some data. Consider data sampled at 1000 Hz. Start by forming a time axis for our data, running from t=0 until t=.25 in steps of 1 millisecond. Then form a signal, x, containing sine waves at 50 Hz and 120 Hz.
image=imread('12fig20.jpg');
%image = rgb2gray(image);
figure;imshow(image,[0 255])
title('Clean spatial domain image')
print -deps -F:16 clean_signal_5.eps
y=image;

spacial_filter = (gaussian2d(7,2.5));
figure;imshow(spacial_filter,[])
title('Filter in the spatial domain')
print -deps -F:16 filter1_5.eps

filtered_image1=conv2(y, spacial_filter, 'same');
figure;imshow(filtered_image1,[])
title('Image filtered in the spatial domain')
print -deps -F:16 filtered1_5.eps


Y = fftshift(fft2(y));
Pyy = Y.*conj(Y)/(size(Y,1)*size(Y,2));
figure;imshow(log(Pyy+1),[])
title('Power spectral density')
print -deps -F:16 power_spectral_density_of_noisy_signal_5.eps

frequency_filter = fftshift(fft2(spacial_filter,size(Y,1), size(Y,2)));
figure;imshow(frequency_filter,[])
title('Filter in the frequency domain')
print -deps -F:16 filter2_5.eps

%Pfrequency_filter = frequency_filter.*conj(frequency_filter)/(size(frequency_filter,1)*size(frequency_filter,2));
%figure;imshow(log(Pfrequency_filter+1),[])
%title('Power spectral density')
%print -deps -F:16 power_spectral_density_of_noisy_signal_5.eps

% Filter
frequency_filtered=Y.*frequency_filter;
Pyy_filtered = frequency_filtered.*conj(frequency_filtered)/(size(Y,1)*size(Y,2));
figure;imshow(log(Pyy_filtered+1),[])
title('Power spectral density')
print -deps -F:16 power_spectral_density_of_filtered_signal_5.eps

% IFFT
filtered=real(ifft2(fftshift(frequency_filtered)));
figure;imshow(filtered,[5 max(filtered(:))])
title('Image filtered in the frequency domain')
print -deps -F:16 filtered_signal_5.eps

