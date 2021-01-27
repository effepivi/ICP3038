set terminal png
set output "log.png"
#set size 1,2
set key top left
#set grid
set xrange[-50:50]
#set title "The log function"
set xlabel "$x$ axis"
set ylabel "$y = \\log{x}$"
plot log(x) with lines lw 3 notitle


