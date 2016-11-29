set terminal postscript eps enhanced color font 'Helvetica,10'
set output 'gauss1D.eps'

set grid

s1=0.1
s2=0.5  
s3=1.0                
set xrange[-4:4]      
set yrange[-0.1:1.1]      
f2(x)=exp(-(x*x)/(2*s2))    
f3(x)=exp(-(x*x)/(2*s3))    
f1(x)=exp(-(x*x)/(2*s1))    
set samples 1500                                                                                                  
plot f1(x) w l title "{/Symbol s}^2=0.1",f2(x) w l title "{/Symbol s}^2 = 0.5",f3(x) w l title "{/Symbol s}^2 = 1"

reset


set output 'gauss2D.eps'


s1=0.2
set iso 50, 50
set samples 5000, 5000
unset key
set xrange [-2:2]
set yrange [-2:2]
f(x,y) = s1 * 1/(2*pi*s1*s1) * exp(-(x*x+y*y)/(2*s1*s1))
set hidden front
splot f(x,y)









set dummy u, v
set parametric
set view 68, 28, 1, 1
set samples 500, 500
set isosamples 30, 30
set contour base
set cntrlabel onecolor format '%8.3g' font '' start 5 interval 20
set hidden3d back offset 1 trianglepattern 3 undefined 1 altdiagonal bentover
set cntrparam levels discrete 0.1
set style data lines
set style function dots
set xyplane relative 0
set ztics  norangelimit 0.00000,0.05

set urange [ -2.50000 : 2.50000 ] noreverse nowriteback
set vrange [ -2.50000 : 2.50000 ] noreverse nowriteback
set xrange [ -2.50000 : 2.50000 ] noreverse nowriteback
set yrange [ -2.50000 : 2.50000 ] noreverse nowriteback
set zrange [ -0.10000 : 5.100000 ] noreverse nowriteback

s1=0.04

splot u,v,( 1/(2*pi*s1*s1) * exp(-(u*u + v*u) / (2*s1*s1)) ) with line lc rgb "black"

reset
clear

