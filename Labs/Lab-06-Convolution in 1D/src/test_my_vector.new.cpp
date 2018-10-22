
        // Test filtering
        MyVector mean_filter        = y_noise.meanFilter();
        MyVector gaussian_filter    = y_noise.gaussianFilter();
        MyVector median_filter      = y_noise.medianFilter();
        MyVector derivative_filter  = y.derivativeFilter();
        MyVector gradient_magnitude = y.gradientMagnitude();

        mean_filter.saveASCII("mean_filter.mat");
        gaussian_filter.saveASCII("gaussian_filter.mat");
        median_filter.saveASCII("median_filter.mat");
        derivative_filter.saveASCII("derivative_filter.mat");
        gradient_magnitude.saveASCII("gradient_magnitude.mat");


