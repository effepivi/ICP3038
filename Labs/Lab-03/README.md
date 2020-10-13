---
title: Lab 3 -- Unit tests, and arrays
author: Dr Franck P. Vidal
subtitle: ICE-3038-0 Computer Vision 202021
date: Week 3
keywords: ICP3038, Computer Vision, C/C++, image processing, OpenCV, Bangor University, School of Computer Science and Electronic Engineering
institute: School of Computer Science and Electronic Engineering, Bangor University
---

# Introduction

Last week, you wrote a program to convert temperatures from degrees Celsius to Fahrenheit.
But does it work? Have you tested it. In this lab we will see how we can use CMake to perform some unit testing.
We will also process the command line arguments. However, you will need to learn about C arrays first.

# Prerequisite

Make sure you completed the lab from last week as we are going to reuse the code.
We are going to extend it.


# Integer division

As everybody knows, 1 divided by 2 is equal to 0.
Or 0.5, well it depends.

## Task 1: Careful when you divide

Create a new program, e.g. `lab3-1.cxx`. You must add it to `CMakeLists.txt`.
In this program, enter:

```cpp
#include <iostream>

using namespace std;

int main()
{
    cout << "1 / 2 = " << 1 / 2 << endl;
    cout << "1.0 / 2 = " << 1.0 / 2 << endl;
    cout << "1 / 2.0 = " << 1 / 2.0 << endl;
    cout << "1.0 / 2.0 = " << 1 / 2.0 << endl;
    return 0;
}
```

What is the output of each line?
Can you identify what is going on?
1/2 corresponds to an integer division (fast).
The other three lines make use of a floating-point division (slow).

## Task 2: Remainder

Create a new program, e.g. `lab3-2.cxx`. You must add it to `CMakeLists.txt`.

```cpp
#include <iostream>

using namespace std;

int main()
{
    [...]

    cout << a << " / " << divisor << " = " << division << endl;
    cout << a << " % " << divisor << " = " << remainder << endl;

    cout << division << " * " << divisor << " + " << remainder<< " = " << b << endl;

    return 0;
}
```

Replace `[...]` above with your own code so that

- a number `a` is equal to 5.
- The divisor is equal to 3.
- The division is equal to `a / divisor`.

The remainder can be obtained using the operator `%` with two integer numbers as operands:
```cpp
float remainder = a % divisor;
```

In this case, a is equal to `b` where
```cpp
b = division * divisor + remainder;
```




# C arrays


# argc/argv

[How to parse command line parameters.](http://www.cplusplus.com/articles/DEN36Up4/)

You can easily parse the command-line arguments in a C or C++ program.
Every C and C++ program has a `main` function.
The simplest `main` function is defined as follows:

```cpp
int main()
```

To enable the command line, change this line into:
```cpp
int main(int argc, char* argv[])
```
or
```cpp
int main(int argc, char* argv[])
```
Both lines are equivalent.
`argc` (also known as *argument count*) is the number of command-line arguments. It is equal to or greater than 1.
`argv` (also known as *argument vector*) is an array of C strings that contains the actual command-line arguments.
The first argument, `argv[0]`, is ALWAYS the command used to invoke the program.

## Task 1

Create a new program, e.g. `lab3-3.cxx`. You must add it to `CMakeLists.txt`.
In this program, enter:

```cpp
#include <iostream>
int main(int argc, char** argv)
{
    cout << "The program is: " << argv[0] << endl;
    return 0;
}
```

Compile and test that your code works.

## Task 2

Create a new program, e.g. `lab3-4.cxx`. You must add it to `CMakeLists.txt`.
I want you to write a program that will output:
```bash
The program is: lab3-4
argument 1 is: hello
argument 2 is: world
```
when the command line is `lab3-4 hello world`.

I should output:
```bash
The program is: lab3-4
argument 1 is: I
argument 2 is: am
argument 3 is: studying
argument 4 is: ICP3038
```
when the command line is `lab3-4 I am studying ICP3038`.




int main(int argc, char* argv[]) // or char** argv


Edit & Run


argc tells you how many command-line arguments there were. It is always at least 1, because the first string in argv (argv[0]) is the command used to invoke the program. argv contains the actual command-line arguments as an array of strings, the first of which (as we have already discovered) is the program's name. Try this example:

1
2
3
4
5
6
7



#include <iostream>

int main(int argc, char* argv[])
{
   cout << argv[0] << endl;
   return 0;
}



# stof/stoi


# Unit testing support in CMake
