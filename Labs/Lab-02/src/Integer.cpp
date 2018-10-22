/**
******************************************************************************
*
*	@file		Integer.cpp
*
*	@brief		Class used to manage an Integer number.
*
*	@version	1.1
*
*	@date		07/10/2018
*
*	@author		Your name
*
*
******************************************************************************
*/


//******************************************************************************
//	Include
//******************************************************************************
#include "Integer.h"


//-----------------
Integer::Integer()
//-----------------
    // Uncomment the lines below to add an initialisation list
    /*
     :
        m_data(0)
     */
//-----------------
{
    std::cout << "IN: Integer::Integer()" << std::endl;
    
    std::cout << "\t" << m_data << std::endl;
    
    m_data = 0;
    
    std::cout << "\t" << m_data << std::endl;
    
    std::cout << "OUT: Integer::Integer()" << std::endl;
}


//-----------------------------------------
Integer::Integer(const Integer& anInteger):
//-----------------------------------------
        m_data(anInteger.m_data)
//-----------------------------------------
{
    std::cout << "IN: Integer::Integer(const Integer& anInteger)" << std::endl;

    std::cout << "\t" << m_data << std::endl;

    std::cout << "OUT: Integer::Integer(const Integer& anInteger)" << std::endl;
}


//------------------------------
Integer::Integer(int anInteger)
//------------------------------
    // Uncomment the lines below to add an initialisation list
    /*
     :
        m_data(anInteger)
     */
//------------------------------
{
    std::cout << "IN: Integer::Integer(int anInteger)" << std::endl;

    std::cout << "\t" << m_data << std::endl;

    m_data = anInteger;

    std::cout << "\t" << m_data << std::endl;

    std::cout << "OUT: Integer::Integer(int anInteger)" << std::endl;
}


//-----------------
Integer::~Integer()
//-----------------
{
    std::cout << "IN: Integer::~Integer()" << std::endl;
    std::cout << "OUT: Integer::~Integer()" << std::endl;
}


//---------------------------------------------------
Integer& Integer::operator=(const Integer& anInteger)
//---------------------------------------------------
{
    std::cout << "IN: Integer::operator=(const Integer& anInteger)" << std::endl;

    std::cout << "\t" << m_data << std::endl;

    m_data = anInteger.m_data;

    std::cout << "OUT: Integer::operator=(const Integer& anInteger)" << std::endl;

    return (*this);
}


//----------------------------------------
Integer& Integer::operator=(int anInteger)
//----------------------------------------
{
    std::cout << "IN: Integer::operator=(const Integer& anInteger)" << std::endl;

    std::cout << "\t" << m_data << std::endl;

    m_data = anInteger;

    std::cout << "OUT: Integer::operator=(const Integer& anInteger)" << std::endl;

    return (*this);
}


//-----------------------------------------------------------------------
std::ostream& operator<<(std::ostream& aStream, const Integer& anInteger)
//-----------------------------------------------------------------------
{
    aStream << anInteger.m_data;
    return (aStream);
}


//-----------------------------------------------------------------
std::istream& operator>>(std::istream& aStream, Integer& anInteger)
//-----------------------------------------------------------------
{
    aStream >> anInteger.m_data;
    return (aStream);
}
