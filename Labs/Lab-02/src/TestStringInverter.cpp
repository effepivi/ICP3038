/**
********************************************************************************
*
*	@file		testStringInverter.cpp
*
*	@brief		Here explain here what is the file about.
*
*	@version	1.1
*
*	@date		07/10/2018
*
*	@author		Your name
*
*
********************************************************************************
*/


//******************************************************************************
//	Include
//******************************************************************************
#include<iostream>

#include "StringInverter.h"


//******************************************************************************
//	namespace
//******************************************************************************
using namespace std;


//******************************************************************************
//	Implementation
//******************************************************************************
int main()
{
    StringInverter string1("abc");
    cout << string1 << endl;
    cout << string1.getString() << endl << endl;
    cout << string1.getInvertedString() << endl << endl;
    
    StringInverter string2 = string1;
    cout << string2 << endl;
    cout << string2.getString() << endl << endl;
    cout << string2.getInvertedString() << endl << endl;

    StringInverter string3 = string1.getInvertedString();
    cout << string3 << endl;
    cout << string3.getString() << endl << endl;
    cout << string3.getInvertedString() << endl << endl;

    cout << (string1 == string2 ? "string1 and 2 are the same" : "string1 and 2 are different") << endl;
    cout << (string1 != string2 ? "string1 and 2 are different" : "string1 and 2 are the same") << endl << endl;

    cout << (string1 == string3 ? "string1 and 3 are the same" : "string1 and 3 are different") << endl;
    cout << (string1 != string3 ? "string1 and 3 are different" : "string1 and 3 are the same") << endl << endl;

#ifdef WIN32
#ifdef _DEBUG
    system("pause");
#endif
#endif

    // Exit code
    return (0);
}
