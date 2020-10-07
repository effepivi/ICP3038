---
title: Lab 2 -- Introduction to C++ programming
author: Dr Franck P. Vidal
subtitle: ICE-3038-0 Computer Vision 202021
date: Oct 7th, 2020
keywords: ICP3038, Computer Vision, C/C++, image processing, OpenCV, Bangor University, School of Computer Science and Electronic Engineering
institute: School of Computer Science and Electronic Engineering, Bangor University
---

# Introduction

It can be extremely complicated to use an Integrated Development
Environment (IDE) to maintain the project files, etc. particularly if
most students use MS Windows, some use Mac, and others use GNU/Linux.
I personally use the three operating systems (OS), but I have also my personal preferences, which may differ from yours.
In this matter, I will respect your choice.
I also developed a large open source library.
There are:

- 71 .h files,
- 39 .inl files,
- 74 .cxx files, and
- 27 .py files.

I need to make sure people can compile it 1) regardless of their choice of OS, 2) regardless of their choice of compiler, and 3) regardless of the age of the compiler.
In other words, my code and how I package it have to be portable and cross-platform.
This is good practice too.

In this lab, you start coding in C++ using CMake as a toolchain.
The C++ objects and methods that you need to use are:

- `ostream& operator<< (val)`
- `istream operator>> (&val)`
- `std::cin`
- `std::cout`
- `std::string`

`cout`, `cin`, `<<`, `>>`, are defined in the `<iostream>` header
file. The 'c' in `cout` refers to "character" and 'out' means "output":
`cout` means "character output". It is used along with the insertion
operator (`cout <<`) to display a stream of characters. The general
syntax is:

## cout <<
```cpp
cout << varName;
```

Or

```cpp
cout << "Some String";
```

The extraction operator can be used more than once with a combination of
variables, strings and manipulators (like endl):

```cpp
cout << var1 << "Some String" << var2 << endl;
```

Note that `endl` means "end of line". It replaces `\n` in the `printf`
function of C.

## cin >>

`cin` means "character input". It is used along with the extraction
operator (`cout`>>+) to receive a stream of characters. The general
syntax is:

```cpp
cin >> varName;
```

The extraction operator can be used more than once to accept multiple
inputs as:

```cpp
cin >> var1 >> var2 >> ... >> varN;
```

## C++ strings

 `string` is defined in the `<string>` header file. It is a class that handles strings of characters.



# C++ resources

There are plenty of tutorials and resources for Java programmers who wish
to learn C and C++. You are strongly recommended to research this
topic on your own to gain better understanding of the differences
between C++ and Java. This module is not meant to teach C++ but
expects that you gain basic C++ skills as you solve the tasks at the
laboratory classes.


Some on-line resources for Java programmers moving to C++:

- Moving from Java to C++ -- [http://www.horstmann.com/ccj2/ccjapp3.html](http://www.horstmann.com/ccj2/ccjapp3.html)
- C and C++ for Java programmers -- [http://goo.gl/SxHYS](http://goo.gl/SxHYS)
- C++ tutorials and documentation -- [http://www.cplusplus.com/](http://www.cplusplus.com/):
    - [C: `printf`](http://www.cplusplus.com/reference/cstdio/printf/)
    - [C++: `cout <<`](http://www.cplusplus.com/reference/iostream/cout/)
    - [C: `scanf`](http://www.cplusplus.com/reference/cstdio/scanf/)
    - [C++: `cin >>`](http://www.cplusplus.com/reference/iostream/cin/)
    - [C++: `string`](http://www.cplusplus.com/reference/string/)

# A bit about CMake

CMake is a cross-platform free and open-source software tool for managing the build process of software using a compiler-independent method. It supports directory hierarchies and applications that depend on multiple libraries. It is used in conjunction with native build environments such as Make, Qt Creator, Ninja, Apple's Xcode, and Microsoft Visual Studio.

Source: [Wikipedia](https://en.wikipedia.org/wiki/CMake)

# Brief history of CMake

CMake development began in 1999 in response to the need for a cross-platform build environment for the Insight Segmentation and Registration Toolkit. The project is funded by the United States National Library of Medicine as part of the Visible Human Project. It was partially inspired by pcmaker, which was made by Ken Martin and other developers to support the Visualization Toolkit (VTK). At Kitware, Bill Hoffman blended components of pcmaker with his own ideas, striving to mimic the functionality of Unix configure scripts. CMake was first implemented in 2000 and further developed in 2001.

Version 3.0 was released in June 2014. It has been described as the beginning of "Modern CMake". Experts now advise to avoid variables in favor of targets and properties. The commands `add_compile_options`, `include_directories`, `link_directories`, `link_libraries` that were at the core of CMake 2 should now be replaced by target-specific commands.

[Adapted from Wikipedia](https://en.wikipedia.org/wiki/CMake)

As you can imagine from the above, CMake did not exist when I was a student. I had to learn on my own. Continuous learning is one of the thing computer scientists need to do to keep up-to-date.




<!--


This is a typical script that you will be working with at each
laboratory session. To work with such a script efficiently, follow the
guidelines below:

1.  The script is not a step-by-step tutorial. It introduces the problem
    but it is your task to solve it.

2.  If you get stuck, make sure that you read the *Help* section at the
    end of the document.

3.  If you still have problems, ask the lecturer, demonstrator or fellow
    students for help.

4.  Try to do as much work as possible in the class, where it is easier
    to get help.

5.  If you need help when working at home, use the Blackboard discussion
    board. I tend to reply to my emails, but sometimes they get buried,
    so don't worry if I don't reply to your email and send it again. My
    office is Room 324, and Shatah's is 320.

6.  Finish all assignments at least a week before the deadline. If you
    get stuck, you will still have one week to ask for help.

Task 1: Using CMake {#task-1-using-cmake .unnumbered}
------------------- -->

# Content of the ZIP file

```
    ICP3038
        \-Lab-02
            |-README.md
            |-bin (where you compile the code)
            |-lab2-1.c: experiment with printf
            |-lab2-1.cxx: experiment with cout <<
            |-lab2-2.c: experiment with scanf
            |-lab2-2.cxx: experiment with cin >>
            |-lab2-3.cxx: write a program that converts temperatures in Celsius |             into Fahrenheit
            \-CMakeLists.txt
```

# Task 1: Edit CMakeLists.txt

The most basic project is an executable built from source code files.
This is what we are going to do during the first few weeks.
In today's lab, a three line `CMakeLists.txt` file is all that you need to start with.  
This will be the starting point for our lab.
Using your favourite text editor, open the CMakeLists.txt file that is provided in the ZIP file so that it becomes:

```cmake
CMAKE_MINIMUM_REQUIRED (VERSION 3.10)

# set the project name
PROJECT (ICP3038-lab2)

# add the executable
ADD_EXECUTABLE (lab2-1-C lab2-1.c)
```

Note that this example uses lower case commands in the CMakeLists.txt file. Upper, lower, and mixed case commands are supported by CMake. The source code for tutorial.cxx is provided in the Step1 directory and can be used to compute the square root of a number.

# Task 2: Run CMake once

DO NOT COMPILE YOUR CODE DIRECTLY IN THE `src` DIRECTORY. Extract the ZIP
file, and set up the compilation environment using `cmake`. In the GUI,
the source directory corresponds to the direction in which
`CMakeLists.txt` is. The binary directory is where the code will be
compiled. Often, we call this directory `bin`. Once the paths are set,
press `Configure`. The first time you run the configuration tool, you
have to select a generator. If you want to use MSVC++ in the lab, make
sure to use *Visual Studio 16 2019 Win64*. For Mac OS X, you may want to
use the Xcode generator. For Linux, you may choose Makefile. Once the
configuration step is over, press `Generate`. The project files are now
ready in the `bin` directory. You can compile the code using your
preferred IDE.

# Task 3: experiment with printf

1. Consider the program below:

```c
#include <stdio.h>

int main(void)
{
    // Start the block with the declaration and initialisation of the local variables
    int i = -1;
    unsigned int ui = -1;

    short s = -2;
    unsigned short us = -2;

    char c = 255;
    unsigned char uc = 255;

    float f = -1.2;
    double d = -1.4;

    char* string = "Hey you!";

    printf("To print an int in C, I need: %i\n", i);
    printf("To print an unsigned int in C, I need: %u\n", ui);

    printf("To print a short in C, I need: %i\n", s);
    printf("To print an unsigned short in C, I need: %u\n", us);

    printf("To print a char in C, I need: %i\n", c);
    printf("To print an unsigned char in C, I need: %u\n", uc);

    printf("To print a float in C, I need: %f\n", f);
    printf("To print a double in C, I need: %f\n", d);

    printf("To print a string in C, I need: %s\n", string);

    return 0;
}
```

2. Type this code in `lab2-1.c`.
3. Once done, compile it and
4. run it.


The output I get on my GNU/Linux computer is as follows:

```
To print an int in C, I need: -1
To print an unsigned int in C, I need: 4294967295
To print a short in C, I need: -2
To print an unsigned short in C, I need: 65534
To print a char in C, I need: -1
To print an unsigned char in C, I need: 255
To print a float in C, I need: -1.200000
To print a double in C, I need: -1.400000
To print a string in C, I need: Hey you!
```

## Riddle 1 about data types and their limitations

Can you explain what is going on?

## Riddle 2 about data types and their limitations

Yesterday I read this article: [https://www.theguardian.com/politics/2020/oct/05/how-excel-may-have-caused-loss-of-16000-covid-tests-in-england](https://www.theguardian.com/politics/2020/oct/05/how-excel-may-have-caused-loss-of-16000-covid-tests-in-england).
Can you explain what went wrong from a computer science point of view?
From this article, I guessed how a row ID is encoded in Excel.
Can you guess? ;-)
As a developer, it is important to understand the data types and  their limitations.


# Task 4: Convert this code into C++

1. Add a new line in the CMakeLists.txt file:

```cmake
ADD_EXECUTABLE (lab2-1-CXX lab2-1.cxx)
```

2. Copy paste from `lab2-1.c` into `lab2-1.cxx`.
3. Change the header file from `stdio.h` to `iostream` (yes, omit `.h`).
4. `printf` is replaced with `std::cout <<` as follows:

    ```c
    printf("To print an int in C, I need: %i\n", i);
    printf("To print an unsigned int in C, I need: %u\n", ui);
    ```

    to

    ```cpp
    std::cout << "To print an int in C, I need: " << i << std::endl;
    std::cout << "To print an unsigned int in C, I need: " << ui << std::endl;
    ```

    - `%i` is replaced with the name of the variable;
    - `%u` is replaced with the name of the variable.
    - There is no need to care about the data type. The C++ compiler will guess.
    - `\n` is replaced with `std::endl` (END of Line)
    - Replace all the C calls (`printf`) with C++ code `std::cout << ... << std::endl`.
5. Compile and run your code. If there is a compilation error, DON'T CARRY ON UNTIL YOU FIX IT.
6. before the `main` function, add a new line that contains:

```cpp
using namespace std;
```

- Using namespace `std` means we use the namespace named `std`. "std" is an abbreviation for "standard".
- Replace `std::cout` with `cout`, and
- `std::endl` with `endl`.
- It simplifies the code.

7. In C, the local variables must be declared at the start of each block, i.e. after `{`.

    ```c
    int i = -1;
    printf("To print an int in C, I need: %i\n", i);

    unsigned int ui = -1;
    printf("To print an unsigned int in C, I need: %u\n", ui);
    ```

    The code above will generate an error when compiled with a C compiler whereas a C++ compiler will not raise an eyebrow. In C++, declaration of variables can be anywhere.


# Task 5: experiment with scanf

1. Add a new line in the CMakeLists.txt file:

```cmake
ADD_EXECUTABLE (lab2-2-C lab2-2.c)
```

2. Consider the program below:

```c
#include <stdio.h>

int main(void)
{
    // Start the block with the declaration and initialisation of the local variables
    int i = -1;
    char my_string[16];

    printf("Please enter an integer\n");
    scanf("%i", &i);
    printf("You typed \"%i\"\n", i);

    printf("Please enter a string (in other words anything)\n");
    scanf("%15s", &my_string);
    printf("You typed \"%s\"\n", my_string);

    return 0;
}
```

3. Type this code in `lab2-2.c`.
4. Once done, compile it and run it.

In C, `scanf`, just like `printf` needs to know the data type of the variables it is using. There is no polymorphism in C, the compiler can't guess.


# Task 6: Convert this code into C++

In C++, this is another story.

1. Add a new line in the CMakeLists.txt file:

```cmake
ADD_EXECUTABLE (lab2-2-CXX lab2-2.cxx)
```

2. Copy paste from `lab2-2.c` into `lab2-2.cxx`.
3. Change the header file from `stdio.h` to `iostream` (yes, omit `.h`).
4. `printf` is replaced with `std::cout <<`.
5. To input a value in a variable from the prompt, replace `scanf("%i", i);` with `std::cin >> i;` (you may omit `std::` if you added `using namespace std;`).
6. Compile and run your code. If there is a compilation error, DON'T CARRY ON UNTIL YOU FIX IT.



# Task 7: Improve this program further

1. Did you notice the two numbers, 16 and 15 (i.e. $15=16-1$)?
    - 16 in `char my_string[16];` means that `my_string` is an array of 16 signed integer numbers stored using 8 bits.
    - 15 in `scanf("%15s", &my_string);` means that the longest string it can store is $16 -1$ as the array must contain the end of string character `\0`.
What if there are more than 15 characters? You must edit the program and manually change the values, and recompile the code. Not ideal to say the least, source of bugs and crashes. Ideally we should avoid hard coding such limits ([see Riddle 2 above](#riddle-2 about-data-types-and-their-limitations)).
2. Add a new header file, `<string>`. This is where the C++ string class is declared.
3. Change the C string (`char my_string[16];`) into a C++ string (`std::string my_string;`). You may omit `std::` if you used `using namespace std`.
4. Compile and run your code. If there is a compilation error, DON'T CARRY ON UNTIL YOU FIX IT.
5. Now, you don't need to worry about the size of the string, the code is more robust.


# Task 8: Write a program that convert a temperature in Celsius into Fahrenheit

1. Add a new line in the CMakeLists.txt file:

```cmake
ADD_EXECUTABLE (lab2-3 lab2-3.cxx)
```
2. Edit `lab2-3.cxx` so that it:
    - It prompts the user to input a temperature in Celsius. (use `cout`).
    - Retrieve the temperature in Celsius into a floating point number (use `cin`).
    - To convert temperatures in degrees Celsius to Fahrenheit, multiply by 1.8 (or 9.0/5.0) and add 32. Store the resulting value into another floating point number.    
    - Print the result in the prompt using the format as follows (use `cout`):

    "XXX degrees Celsius is the same as YYY degrees Fahrenheit.", replacing XXX and YYY with the corresponding variables.
3. Test your code to make sure it provides the right output. Next week will use CMake to do the testing for us.


<!--

Task 2: Size of basic types {#task-2-size-of-basic-types .unnumbered}
---------------------------

Your task is to program a command-line application that produces the
output as follows:

    The size of char is:        1  bytes
    The size of short is:       2  bytes
    The size of int is:         4  bytes
    The size of long is:        8  bytes
    The size of long long is:   8  bytes
    The size of float is:       4  bytes
    The size of double is:      8  bytes
    The size of long double is: 16 bytes
    The size of bool is:        1  bytes  

To get the size of a `char`, just use `sizeof(char)`.

Task 3: Command line arguments {#task-3-command-line-arguments .unnumbered}
------------------------------

Your task is to program a command-line application that gets two
integers from the command line arguments and swap their order to produce
the output below:

    Input 1st number: 25
    Input 2nd number: 39
    After swapping the 1st number is: 39
    After swapping the 2nd number is: 25

You need first to read the two integers, display the first two lines,
swap the integers using the function provided, and display the last two
lines.
Note that in `int main(int argc, char** argv)`, `argc` is the total
number of command line arguments passed to your program, `argv` is an
array of C strings containing the arguments. `argv[0]` corresponds to
the executable file, `argv[1]` is its first argument, `argv[argc-1]`
is the last one.
To convert a C string into an integer, you need the
`int atoi (const char * str)` function. It is located in `<cstdlib>`
header file.

The C++ objects and methods that you need to use are:

-   `cerr` for the standard output of errors (that's where error
    messages should be printed); and

-   `double strtod (const char* str, char** endptr)` to convert a
    C-string into float. To learn about a standard function, it is
    always useful to go on <http://www.cpluplus.com/>. In the menu on
    the left-hand side, there is *Reference*. That's where you have to
    go. Hint, `strtod` is defined in the `<cstdlib>` header file. As an
    alternative, you could use the search button to directly go to the
    page about `strtod`. The advantage of the search method is that you
    don't need to know in which header the function is.

Task 4: Bubble sort {#task-4-bubble-sort .unnumbered}
-------------------

Your task is to program a command-line application that:

1.  Reads a single integer $N$ from the standard input, where $N$ is the
    number of floating point values to be sorted.

2.  Reads exactly $N$ floating point values from the standard input. The
    numbers are separated by a new-line character.

3.  Store the $N$ floating point values into an array/

4.  Sorts those values in increasing order using your own implementation
    of the bubble sort algorithm, swapping the values using the function
    *swap* written by you.

5.  Prints out to the standard output the number of elements and then,
    in separate lines, all the numbers in the sorted order.

Example: Given the input file:

    3
    1.5
    -2
    0

your program should generate:

    3
    -2
    0
    1.5

Help {#help .unnumbered}
====

C++ resources {#c-resources .unnumbered}
-------------

There are plenty of tutorials and resources for Java programmers who
wish to learn C and C++. You are strongly recommended to research this
topic on your own to gain better understanding of the differences
between C++ and Java. This module is not meant to teach C++ but expects
that you gain basic C++ skills as you solve the tasks at the laboratory
classes.

Some on-line resources for Java programmers moving to C++:

1.  Moving from Java to C++ ---
    <http://www.horstmann.com/ccj2/ccjapp3.html>

2.  C and C++ for Java programmers --- <http://goo.gl/SxHYS>

3.  C++ tutorials and documentation --- <http://www.cplusplus.com/>

Installing CMake on your computer {#installing-cmake-on-your-computer .unnumbered}
---------------------------------

It is strongly recommended that you install CMake on your PC so that you
can complete your labs and assignments at home. You can find it at
<https://cmake.org/download/>. Go to *Binary distributions* and choose
your platform.

Installing an IDE on your computer {#installing-an-ide-on-your-computer .unnumbered}
----------------------------------

For the same reasons, it is strongly recommended that you install Visual
Studio on your PC, Xcode on Mac, or Eclipse CDT on linux. Note that the
installation of the development tools is often a difficult and
time-consuming process. Do not assume that you can install the software
a few days before deadlines. Install the software as soon as possible
and let us know if there are any problems.

### Windows: Installing Visual Studio Community {#windows-installing-visual-studio-community .unnumbered}

Download and install *MS Visual Studio Community* from

<https://visualstudio.microsoft.com/vs/community/>

### Mac OS X: Installing Xcode {#sec:install-from-package .unnumbered}

This setup will require installing Xcode, which can take up to 2-3GB of
your hard drive. Make sure that you have sufficient hard drive space
before your proceed.

Install *Xcode* from App Store. *Xcode* is a free application for
Mountain Lion and later versions of OSX.

### Linux: Eclipse CDT {#linux-eclipse-cdt .unnumbered}

Download and Install *Eclipse CDT* from
<https://eclipse.org/cdt/downloads.php>. You will need a Java virtual
machine as it uses Java in the background. -->
