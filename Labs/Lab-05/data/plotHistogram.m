% Import the data from the file
histogram=importdata('histogram_y_noise_16bins.txt', ' ', 1);

% Plot the data using a bar chart
bar(histogram.data(:, 1), histogram.data(:, 2));

% Set the title of the graph
title('Histogram with 16 bins')

% Set the axis labels
xlabel('Intensity')
ylabel('Count')

% Store the graph in an EPS file (vector graphics)
print -deps -color -FHelvetica:16 "histogram_matlab.eps"

% Store the graph in a PNG file (bitmap)
print -dpng -color -FHelvetica:16 "histogram_matlab.png"
