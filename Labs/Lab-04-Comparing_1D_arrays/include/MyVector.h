#ifndef __MyVector_h
#define __MyVector_h


/**
********************************************************************************
*
*	@file		MyVector.h
*
*	@brief		Class used to manage a 1D vector of single-precision 
*               floating point numbers. The class is used to illustrate 
*               how to compare two vectors with each other. Care is given 
*               to handle numerical inaccuracy.
*
*	@version	1.0
*
*	@date		22/10/2018
*
*	@author		Your name
*
*
********************************************************************************
*/


//******************************************************************************
//	Include
//******************************************************************************
#include <vector>
#include <string>
#include <iostream>


//============================================================================
/**
*	@class	MyVector
*	@brief	MyVector is a class to manage a 1D vector of single-precision 
*           floating point numbers. The class is used to illustrate 
*           how to compare two vectors with each other. Care is given 
*           to handle numerical inaccuracy.
*/
//============================================================================
class MyVector
//----------------------------------------------------------------------------
{
//****************************************************************************
public:
    //------------------------------------------------------------------------
    /// Default constructor.
    //------------------------------------------------------------------------
    MyVector();
    

    //------------------------------------------------------------------------
    /// Copy constructor.
    /**
    * @param aVector: the vector to copy
    */
    //------------------------------------------------------------------------
    MyVector(const MyVector& aVector);


    //------------------------------------------------------------------------
    /// Constructor from a STL vector.
    /**
    * @param aVector: the vector to copy
    */
    //------------------------------------------------------------------------
    MyVector(const std::vector<float>& aVector);


    //------------------------------------------------------------------------
    /// Constructor from a file name.
    /**
    * @param aFileName: the name of the file to load
    */
    //------------------------------------------------------------------------
    MyVector(const char* aFileName);


    //------------------------------------------------------------------------
    /// Constructor from a file name.
    /**
    * @param aFileName: the name of the file to load
    */
    //------------------------------------------------------------------------
    MyVector(const std::string& aFileName);


    //------------------------------------------------------------------------
    /// Load the data from a file name.
    /**
    * @param aFileName: the name of the file to load
    */
    //------------------------------------------------------------------------
    void loadASCII(const char* aFileName);
    

    //------------------------------------------------------------------------
    /// Load the data from a file name.
    /**
    * @param aFileName: the name of the file to load
    */
    //------------------------------------------------------------------------
    void loadASCII(const std::string& aFileName);
    

    //------------------------------------------------------------------------
    /// Display the statistical data in an output stream.
    /**
    * @param anOutputStream: the stream where the data will be displayed
    */
    //------------------------------------------------------------------------
    void printStatistics(std::ostream& anOutputStream) const;
   
    
    //------------------------------------------------------------------------
    /// Accessor on the number of elements in the vector.
    /**
    * @return the number of elements in the vector
    */
    //------------------------------------------------------------------------
    unsigned int getSize() const;
    

    //------------------------------------------------------------------------
    /// Copy operator.
    /**
    * @param aVector: the vector to copy
    */
    //------------------------------------------------------------------------
    MyVector& operator=(const MyVector& aVector);


    //------------------------------------------------------------------------
    /// Accessor on a given element.
    /**
    * @param i: the index of the element to access
    * @return the corresponding element
    */
    //------------------------------------------------------------------------
    float operator[](unsigned int i) const;
    

    //------------------------------------------------------------------------
    /// Accessor on a given element.
    /**
    * @param i: the index of the element to access
    * @return the corresponding element
    */
    //------------------------------------------------------------------------
    float operator()(unsigned int i) const;


    //------------------------------------------------------------------------
    /// Accessor on the smallest element.
    /**
    * @return the smallest element
    */
    //------------------------------------------------------------------------
    float getMinValue() const;
    

    //------------------------------------------------------------------------
    /// Accessor on the largest element.
    /**
    * @return the largest element
    */
    //------------------------------------------------------------------------
    float getMaxValue() const;
    

    //------------------------------------------------------------------------
    /// Compute the sum of all the elements.
    /**
    * @return the sum of all the elements
    */
    //------------------------------------------------------------------------
    float getSum() const;
    

    //------------------------------------------------------------------------
    /// Compute the average.
    /**
    * @return the average
    */
    //------------------------------------------------------------------------
    float getAverage() const;
    

    //------------------------------------------------------------------------
    /// Compute the variance.
    /**
    * @return the variance
    */
    //------------------------------------------------------------------------
    float getVariance() const;


    //------------------------------------------------------------------------
    /// Compute the standard deviation.
    /**
    * @return the standard deviation
    */
    //------------------------------------------------------------------------
    float getStandardDeviation() const;


    //------------------------------------------------------------------------
    /// Operator equal to. Care is given to handle numerical inaccuray.
    /**
    * @param aVector: the vector used for the comparison
    * @return   true if the two vectors are the same,
    *           false if they are different
    */
    //------------------------------------------------------------------------
    bool operator==(const MyVector& aVector) const;
    

    //------------------------------------------------------------------------
    /// Operator not equal to. Care is given to handle numerical inaccuray.
    /**
    * @param aVector: the vector used for the comparison
    * @return   true if the two vectors are different, 
    *           false if they are the same
    */
    //------------------------------------------------------------------------
    bool operator!=(const MyVector& aVector) const;

    
    //------------------------------------------------------------------------
    /// Operator addition.
    /**
    * @param aValue: the value to add to every elements of the vector
    * @return the new vector
    */
    //------------------------------------------------------------------------
    MyVector operator+(float aValue) const;


    //------------------------------------------------------------------------
    /// Operator addition assignment.
    /**
    * @param aValue: the value to add to every elements of the vector
    * @return the current vector after the addition
    */
    //------------------------------------------------------------------------
    MyVector& operator+=(float aValue);


    //------------------------------------------------------------------------
    /// Operator addition. Element-wise addition of elements of two vectors.
    /**
    * @param aVector: the vector to add
    * @return the new vector
    */
    //------------------------------------------------------------------------
    MyVector operator+(const MyVector& aVector) const;


    //------------------------------------------------------------------------
    /// Operator addition assignment. 
    /// Element-wise addition of elements of two vectors.
    /**
    * @param aVector: the vector to add
    * @return the current vector after the addition
    */
    //------------------------------------------------------------------------
    MyVector& operator+=(const MyVector& aVector);


    //------------------------------------------------------------------------
    /// Compute the sum of absolute errors (SAE) between two vectors.
    /**
     * @param aVector: the vector to use in the comparison
     * @return the SAE
     */
    //------------------------------------------------------------------------
    float SAE(const MyVector& aVector) const;
    
    
    //------------------------------------------------------------------------
    /// Compute the mean absolute errors (MAE) between two vectors.
    /**
     * @param aVector: the vector to use in the comparison
     * @return the MAE
     */
    //------------------------------------------------------------------------
    float MAE(const MyVector& aVector) const;
    
    
    //------------------------------------------------------------------------
    /// Compute the sum of squared errors (SSE) between two vectors.
    /**
     * @param aVector: the vector to use in the comparison
     * @return the SSE
     */
    //------------------------------------------------------------------------
    float SSE(const MyVector& aVector) const;
    
    
    //------------------------------------------------------------------------
    /// Compute the mean squared errors (MSE) between two vectors.
    /**
     * @param aVector: the vector to use in the comparison
     * @return the MSE
     */
    //------------------------------------------------------------------------
    float MSE(const MyVector& aVector) const;
    
    
    //------------------------------------------------------------------------
    /// Compute the root mean squared errors (RMSE) between two vectors.
    /**
     * @param aVector: the vector to use in the comparison
     * @return the RMSE
     */
    //------------------------------------------------------------------------
    float RMSE(const MyVector& aVector) const;
    
    
    //------------------------------------------------------------------------
    /// Compute the normalised-cross correlation (NCC) between two vectors.
    /**
    * @param aVector: the vector to use in the comparison
    * @return the NCC
    */
    //------------------------------------------------------------------------
    float NCC(const MyVector& aVector) const;
    

//****************************************************************************
private:
    /// STL vector to store the data
    std::vector<float> m_data;
};

#endif

