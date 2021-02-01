
    //------------------------------------------------------------------------
    /// Save the data into file.
    /**
     * @param aFileName: the name of the file to write
     */
    //------------------------------------------------------------------------
    void saveASCII(const char* aFileName);
    
    
    //------------------------------------------------------------------------
    /// Save the data into file.
    /**
     * @param aFileName: the name of the file to write
     */
    //------------------------------------------------------------------------
    void saveASCII(const std::string& aFileName);


    //------------------------------------------------------------------------
    /// Apply a spatial convolution filter on the data.
    /**
     * @param apKernel: the filter kernal
     * @return the data after filtering
     */
    //------------------------------------------------------------------------
    MyVector convolve(const float* apKernel) const;
    
    
    //------------------------------------------------------------------------
    /// Apply a mean filter on the data.
    /**
     * @return the data after filtering
     */
    //------------------------------------------------------------------------
    MyVector meanFilter() const;
    
    
    //------------------------------------------------------------------------
    /// Apply a Gaussian filter on the data.
    /**
     * @return the data after filtering
     */
    //------------------------------------------------------------------------
    MyVector gaussianFilter() const;
    
    
    //------------------------------------------------------------------------
    /// Apply a derivative filter on the data.
    /**
     * @return the data after filtering
     */
    //------------------------------------------------------------------------
    MyVector derivativeFilter() const;
    
    
    //------------------------------------------------------------------------
    /// Apply a median filter on the data.
    /**
     * @return the data after filtering
     */
    //------------------------------------------------------------------------
    MyVector medianFilter() const;
    
    
    //------------------------------------------------------------------------
    /// Apply a filter that apply the absolute value on the data.
    /**
     * @return the data after filtering
     */
    //------------------------------------------------------------------------
    MyVector abs() const;
    
    
    //------------------------------------------------------------------------
    /// Get the gradient magnitude.
    /**
     * @return the data after filtering
     */
    //------------------------------------------------------------------------
    MyVector gradientMagnitude() const;
   