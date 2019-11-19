clear
close all

pkg load communications

function value = gauss(A, B, C, x)
    value = A * exp(-((x - B)^2)/(2*(C^2)));
end

function NCC = computeNCC(y1, y2)
    NCC=100*sum(((y1 .- mean(y1)).*(y2 .- mean(y2))) ./ (std(y1, 1)*std(y2, 1))) / (size(y1, 1) * size(y1, 2));
end

function SAE = computeSAE(y1, y2)
SAE = sum(abs(y1 - y2));
end

function MAE = computeMAE(y1, y2)
MAE = computeSAE(y1, y2) / (size(y1, 1) * size(y1, 2));
end


function SSE = computeSSE(y1, y2)
SSE = sum((y1 - y2).^2);
end

function MSE = computeMSE(y1, y2)
MSE = computeSSE(y1, y2) / (size(y1, 1) * size(y1, 2));
end


function RMSE = computeRMSE(y1, y2)
RMSE = sqrt(computeMSE(y1, y2));
end


a1=2;
b1=-2.0;
c1=0.5;
a2=5;
b2=1.5;
c2=1.0;

x=[-10:0.05:10];
y=zeros(size(x));

for idx = 1:numel(y)
    y(idx) = gauss(a1,b1,c1,x(idx)) + gauss(a2,b2,c2,x(idx));
end


y_quadriple = y .* 4;
%y_noise = awgn(y,10);
y_noise = load("../data/y_noise.mat");
y_negative = -y;

y_min = min(y)
y_max = max(y)
y_sum = sum(y)
y_average = mean(y)
y_variance = var(y, 1)
y_std_dev = std(y, 1)

y_quadriple_min = min(y_quadriple)
y_quadriple_max = max(y_quadriple)
y_quadriple_sum = sum(y_quadriple)
y_quadriple_average = mean(y_quadriple)
y_quadriple_variance = var(y_quadriple, 1)
y_quadriple_std_dev = std(y_quadriple, 1)

y_noise_min = min(y_noise)
y_noise_max = max(y_noise)
y_noise_sum = sum(y_noise)
y_noise_average = mean(y_noise)
y_noise_variance = var(y_noise, 1)
y_noise_std_dev = std(y_noise, 1)

y_negative_min = min(y_negative)
y_negative_max = max(y_negative)
y_negative_sum = sum(y_negative)
y_negative_average = mean(y_negative)
y_negative_variance = var(y_negative, 1)
y_negative_std_dev = std(y_negative, 1)


save -ascii "../datay.mat" y
save -ascii "../datay_noise.mat" y_noise
save -ascii "../datay_negative.mat" y_negative
save -ascii "../datay_quadriple.mat" y_quadriple

SAE_y_y_quadriple=computeSAE(y,y_quadriple)
SAE_y_y_negative=computeSAE(y,y_negative)
SAE_y_y_noise=computeSAE(y,y_noise)

MAE_y_y_quadriple=computeMAE(y,y_quadriple)
MAE_y_y_negative=computeMAE(y,y_negative)
MAE_y_y_noise=computeMAE(y,y_noise)

SSE_y_y_quadriple=computeSSE(y,y_quadriple)
SSE_y_y_negative=computeSSE(y,y_negative)
SSE_y_y_noise=computeSSE(y,y_noise)

MSE_y_y_quadriple=computeMSE(y,y_quadriple)
MSE_y_y_negative=computeMSE(y,y_negative)
MSE_y_y_noise=computeMSE(y,y_noise)

RMSE_y_y_quadriple=computeRMSE(y,y_quadriple)
RMSE_y_y_negative=computeRMSE(y,y_negative)
RMSE_y_y_noise=computeRMSE(y,y_noise)

NCC_y_y_quadriple=computeNCC(y,y_quadriple)
NCC_y_y_negative=computeNCC(y,y_negative)
NCC_y_y_noise=computeNCC(y,y_noise)

bins = 64;
y_hist=hist(y,bins);
y_quadriple_hist=hist(y_quadriple,bins);
y_noise_hist=hist(y_noise,bins);
y_negative_hist=hist(y_negative,bins);

figure;plot(x,y)
figure;plot(x,y_quadriple)
figure;plot(x,y_noise)
figure;plot(x,y_negative)
figure;plot(x,y,x,y_quadriple,x,y_noise,x,y_negative)
legend('$Y$','$Y_{quadriple}$', '$Y_{noise}$', '$Y_{negative}$')
title('Test data')
print -dpdflatex -F:12 -color curves.tex

figure;plot([y_min:(y_max-y_min)/(bins-1):y_max], y_hist)
title('Histogram of Y')
xlabel('Intensity')
ylabel('Count')
print -dpdflatex -F:12 -color y_hist.tex


figure;plot([y_quadriple_min:(y_quadriple_max-y_quadriple_min)/(bins-1):y_quadriple_max],y_quadriple_hist)
title('Histogram of $Y_{quadriple}$')
xlabel('Intensity')
ylabel('Count')
print -dpdflatex -F:12 -color y_quadriple_hist.tex


figure;plot([y_noise_min:(y_noise_max-y_noise_min)/(bins-1):y_noise_max],y_noise_hist)
title('Histogram of $Y_{noise}$')
xlabel('Intensity')
ylabel('Count')
print -dpdflatex -F:12 -color y_noise_hist.tex


figure;plot([y_negative_min:(y_negative_max-y_negative_min)/(bins-1):y_negative_max],y_negative_hist)
title('Histogram of $Y_{negative}$')
xlabel('Intensity')
ylabel('Count')
print -dpdflatex -F:12 -color y_negative_hist.tex




