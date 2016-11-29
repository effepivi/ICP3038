close all
clear

X=[2:0.01:2.5*pi];
Y1=3*sin(X);
Y2=2*sin(X*2);
Y3=1*sin(X*10);
Y4=0.7*sin(X*15);
Y5=0.3*sin(X*500);
figure;plot (X,Y1,X,Y2,X,Y3,X,Y4,X,Y5)

figure;plot (X,Y1)
title('First sine wave')
print -deps -F:16 sine_wave1.eps

figure;plot (X,Y2)
title('Second sine wave')
print -deps -F:16 sine_wave2.eps

figure;plot (X,Y3)
title('Third sine wave')
print -deps -F:16 sine_wave3.eps

figure;plot (X,Y4)
title('Fourth sine wave')
print -deps -F:16 sine_wave4.eps

figure;plot (X,Y5)
title('Fifth sine wave')
print -deps -F:16 sine_wave5.eps

figure;plot (X,Y1 + Y2 + Y3 + Y4 + Y5)
title('signal')
print -deps -F:16 signal.eps

figure;plot (X,Y1 + Y2)
title('signal')
print -deps -F:16 signal12.eps

figure;plot (X,Y1 + Y2 + Y3)
title('signal')
print -deps -F:16 signal123.eps

figure;plot (X,Y1 + Y2 + Y3 + Y4)
title('signal')
print -deps -F:16 signal1234.eps
