/**
********************************************************************************
*
*	@file		TestStringInverter.cxx
*
*	@brief		Here explain here what is the file about.
*
*	@version	1.1
*
*	@date		20/10/2020
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
#include<string>

#include "StringInverter.h"


//******************************************************************************
//	namespace
//******************************************************************************
using namespace std;


//******************************************************************************
//	Implementation
//******************************************************************************
int main(int argc, char** argv)
{
  if (argc != 2)
  {
      cerr << "Wrong number of command line arguments." << endl;
      cerr << "Usage:\t" << argv[0] << "  string_to_invert" << endl;
      return 1;
  }

  StringInverter my_string = argv[1];

  cout << my_string << ", once inverted, becomes " << my_string.getInvertedString() << "." << endl;

  return 0;
}
