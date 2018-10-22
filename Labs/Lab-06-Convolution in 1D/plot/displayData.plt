set term png
set output "low_pass_filters.png"
set title "Low-pass filters"
plot "< awk '{for(i=1;i<=NF;i++) print $i}' ../data/y_noise.mat" w l t "Y_{noise}", \
     "< awk '{for(i=1;i<=NF;i++) print $i}'     mean_filter.mat" w l t "Y_{mean}", \
     "< awk '{for(i=1;i<=NF;i++) print $i}' gaussian_filter.mat" w l t "Y_{gaussian}", \
     "< awk '{for(i=1;i<=NF;i++) print $i}'   median_filter.mat" w l t "Y_{median}"

set output "high_pass_filters.png"
set title "High-pass filters"
plot "< awk '{for(i=1;i<=NF;i++) print $i}'          ../data/y.mat" w l t "Y", \
     "< awk '{for(i=1;i<=NF;i++) print $i}'  derivative_filter.mat" w l lw 3 t "Y_{Y_{derivative}", \
     "< awk '{for(i=1;i<=NF;i++) print $i}' gradient_magnitude.mat" w l t "Y_{gradient magnitude}"
