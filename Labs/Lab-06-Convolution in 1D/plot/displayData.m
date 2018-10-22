clear
close all

y = load("../data/y.mat");
y_noise = load("../data/y_noise.mat");

mean_filter = load("mean_filter.mat");
gaussian_filter = load("gaussian_filter.mat");
derivative_filter = load("derivative_filter.mat");
gradient_magnitude = load("gradient_magnitude.mat");
median_filter = load("median_filter.mat");


x=[1:size(y,2)]

figure;plot(x,y_noise,x,mean_filter,x,gaussian_filter,x,median_filter)
legend('$Y_{noise}$','$Y_{mean}$', '$Y_{gaussian}$', '$Y_{median}$')
title('Low-pass filters')
%print -dpdflatex -F:12 -color low_pass_filters.tex

figure;plot(x,y,x,derivative_filter,x,gradient_magnitude)
legend('$Y$','$Y_derivative$', '$Y_{gradient magnitude}$')
title('High-pass filters')
%print -dpdflatex -F:12 -color high_pass_filters.tex
