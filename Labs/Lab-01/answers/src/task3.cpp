/**
********************************************************************************
*
*	@file		task3.cpp
*
*	@brief		Add floating point numbers passed as arguments.
*
*	@version	1.0
*
*	@date		06/10/2015
*
*	@author		Franck P. Vidal (f.vidal@bangor.ac.uk)
*
*
********************************************************************************
*/


//******************************************************************************
//	Include
//******************************************************************************
#include<iostream>
#include<string>


//******************************************************************************
//	namespace
//******************************************************************************
using namespace std;


//******************************************************************************
//	Global variables
//******************************************************************************


//******************************************************************************
//	Function declaration
//******************************************************************************
unsigned int getNumberOfVowels(const std::string& aString);
bool isVowel(char aCharacter);


//******************************************************************************
//	Implementation
//******************************************************************************


//-----------------------------
int main(int argc, char** argv)
//-----------------------------
{
    // Error code (0 == no error)
    int return_code(0);
    
    // At least a string has been passed
    if (argc > 1)
    {
        // Process all the strings
        for (unsigned int i(1); i < argc; ++i)
        {
            // Convert from C-string to C++ string
            std::string old_argument(argv[i]);
        
            // Get the number of characters in the string (does not include the end of string character '\0')
            unsigned int number_of_letters(old_argument.size());
        
            // Get the number of vowels
            unsigned int number_of_vowels(getNumberOfVowels(old_argument));
        
            // Compute the number of characters in the new string (including the end of string character '\0')
            unsigned int new_number_of_characters(
                    number_of_letters +     // Keep the number of letters
                    2 * number_of_vowels /*+  // The number of '-'
                    1       */                // The end of string character '\0'
            );
        
            // Create the new string
            char* p_argument(new char[new_number_of_characters]);
        
            // Process every character of the old string
            unsigned int current_character_in_new_string(0);
            for (unsigned int j(0); j < number_of_letters; ++j)
            {
                // Get the current character of the old string
                char current_character(old_argument[j]);
            
                // The current character of the old string is not a vowel
                if (!isVowel(current_character))
                {
                    p_argument[current_character_in_new_string++] = current_character;
                }
                // The current character of the old string is a vowel
                else
                {
                    p_argument[current_character_in_new_string++] = '-';
                    p_argument[current_character_in_new_string++] = current_character;
                    p_argument[current_character_in_new_string++] = '-';
                }
            }
        
            // Add the end of string character '\0'
            p_argument[current_character_in_new_string] = '\0';
        
            // Display the result
            std::cout << old_argument << ":\t" << p_argument << std::endl;
        
            // Release the memory
            delete [] p_argument;
        }
    }
    // No string has been passed
    else
    {
        return_code = 1;
        std::cerr << "No string has been passed as argument" << std::endl;
    }
    
    // Exit code
    return (return_code);
}


//--------------------------------------------------------
unsigned int getNumberOfVowels(const std::string& aString)
//--------------------------------------------------------
{
    // Store the number of vowels
    unsigned int number_of_vowels(0);
    
    // Process every letter of the string
    for (unsigned int i(0); i < aString.size(); ++i)
    {
        // The current character is a vowel
        if (isVowel(aString[i]))
        {
            // Increment the counter
            ++number_of_vowels;
        }
    }
    
    // Return the counter
    return (number_of_vowels);
}

//---------------------------
bool isVowel(char aCharacter)
//---------------------------
{
    bool return_value(false);
    
    if (aCharacter == 'a' || aCharacter == 'e' || aCharacter == 'i' || aCharacter == 'o' || aCharacter == 'u' || aCharacter == 'y' ||
        aCharacter == 'A' || aCharacter == 'E' || aCharacter == 'I' || aCharacter == 'O' || aCharacter == 'U' || aCharacter == 'Y')
    {
        return_value = true;
    }
    
    return (return_value);
}
