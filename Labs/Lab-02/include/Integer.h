#ifndef INTEGER_H
#define INTEGER_H


/**
******************************************************************************
*
*	@file		Integer.h
*
*	@brief		Class used to manage an Integer number.
*
*	@version	1.0
*
*	@date		13/10/2015
*
*	@author		Your name
*
*
******************************************************************************
*/


//******************************************************************************
//	Include
//******************************************************************************
#include <iostream>


//============================================================================
/**
*	@class	Integer
*	@brief	Integer is a class to manage an Integer number.
*/
//============================================================================
class Integer
//----------------------------------------------------------------------------
{
//****************************************************************************
public:
    //------------------------------------------------------------------------
    /// Default constructor.
    //------------------------------------------------------------------------
    Integer();


    //------------------------------------------------------------------------
    /// Copy constructor.
    /**
    * @param anInteger: the integer to copy
    */
    //------------------------------------------------------------------------
    Integer(const Integer& anInteger);


    //------------------------------------------------------------------------
    /// Constructor.
    /**
    * @param anInteger: the integer to copy
    */
    //------------------------------------------------------------------------
    Integer(int anInteger);


	//-------------------------------------------------------------------------
	///	Destructor
	//-------------------------------------------------------------------------
	~Integer();


	//-------------------------------------------------------------------------
	///	Copy operator.
    /**
    * @param anInteger: the integer to copy
    */
	//-------------------------------------------------------------------------
    Integer& operator=(const Integer& anInteger);
    
    
	//-------------------------------------------------------------------------
	///	Copy operator.
    /**
    * @param anInteger: the integer to copy
    */
	//-------------------------------------------------------------------------
    Integer& operator=(int anInteger);
    
    
    friend std::ostream& operator<<(std::ostream& aStream, const Integer& anInteger);
    friend std::istream& operator>>(std::istream& aStream, Integer& anInteger);
    
    
//****************************************************************************
protected:
    /// The data
    int m_data;
};


#endif
