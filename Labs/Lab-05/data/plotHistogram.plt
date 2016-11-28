# Set the title of the graph
set title('Histogram with 16 bins')

# Set the axis labels
set xlabel('Intensity')
set ylabel('Count')

# Set the size of a bar in the bar chart
set boxwidth 0.35

# Set the style of a bar (use solid colour)
set style fill solid

# Make sure the output will be an EPS file
set term post enh color eps font 'Helvetica,16'

# Set the range of x values
# (note that it is optional)
set xrange[-1:6]

# Set the name of the EPS file
set output("histogram_gnuplot.eps")

# Plot the bar chart from the file
plot "histogram_y_noise_16bins.txt" using 1:2 with boxes notitle

# Make sure the output will be a PNG file
set term png font 'Helvetica,16'

# Set the name of the PNG file
set output("histogram_gnuplot.png")

# Replot the chart
replot
