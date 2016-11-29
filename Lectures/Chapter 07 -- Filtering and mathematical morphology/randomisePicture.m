close all;
clear;

lena=load("lena-std.mat");
lena=(lena.-min(lena(:))) ./ (max(lena(:))-min(lena(:)));
figure;imshow(lena);
title('Lena');
print -dpdf -mono -F:16 lena.pdf


histogram=imhist(lena,256);
figure;bar(histogram)
title("Lena's histogram")
xlabel('Intensity')
ylabel('Count')
axis([0,255,0,max(histogram(:))+0.01*max(histogram(:))])
print -dpdf -mono -solid -F:16 lena-histogram.pdf

index=randperm(numel(lena));
new_image=lena;
new_image(index)=lena;
figure;imshow(new_image);
title('Shuffled Lena');
print -dpdf -mono -F:16 shuffled_lena.pdf

histogram=imhist(new_image,256);
figure;bar(histogram)
title("Shuffled Lena's histogram")
xlabel('Intensity')
ylabel('Count')
axis([0,255,0,max(histogram(:))+0.01*max(histogram(:))])
print -dpdf -mono -solid -F:16 shuffled_lena-histogram.pdf
