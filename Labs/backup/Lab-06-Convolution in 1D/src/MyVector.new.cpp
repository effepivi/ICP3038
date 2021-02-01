


//---------------------------------------------
void MyVector::saveASCII(const char* aFileName)
//---------------------------------------------
{
    // Open the file
    std::ofstream file_data(aFileName);
    
    // The file is not open
    if (!file_data.is_open())
    {
        // Generate an error message
        std::stringstream error_message;
        error_message << "Cannot open the file \"" << aFileName << "\". ";
        error_message << "See: " << std::endl;
        error_message << "\t" << __FILE__ << std::endl;
        error_message << "\t" << __FUNCTION__ << std::endl;
        error_message << "\t" << __LINE__ << std::endl;
        
        // Throw an error
        throw error_message.str();
    }
    
    // Write the file
    for (std::vector<float>::const_iterator ite(m_data.begin());
         ite != m_data.end();
         ++ite)
     {
         file_data << *ite << "\t";
     }
}


//----------------------------------------------------
void MyVector::saveASCII(const std::string& aFileName)
//----------------------------------------------------
{
    // Save the file
    saveASCII(aFileName.data());
}




//------------------------------------------------------
MyVector MyVector::convolve(const float* apKernel) const
//------------------------------------------------------
{
    // Replace with your own code
    return MyVector();
}


//-----------------------------------
MyVector MyVector::meanFilter() const
//-----------------------------------
{
    // Replace with your own code
    return MyVector();
}


//---------------------------------------
MyVector MyVector::gaussianFilter() const
//---------------------------------------
{
    // Replace with your own code
    return MyVector();
}


//-----------------------------------------
MyVector MyVector::derivativeFilter() const
//-----------------------------------------
{
    // Replace with your own code
    return MyVector();
}


//-------------------------------------
MyVector MyVector::medianFilter() const
//-------------------------------------
{
    // Replace with your own code
    return MyVector();
}


//----------------------------
MyVector MyVector::abs() const
//----------------------------
{
    // Replace with your own code
    return MyVector();
}


//------------------------------------------
MyVector MyVector::gradientMagnitude() const
//------------------------------------------
{
    // Replace with your own code
    return MyVector();
}

