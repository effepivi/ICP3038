---
title: Lab 3 -- Introduction to Classes in C++
author: Dr Franck P. Vidal
subtitle: ICE-3038-0 Computer Vision 202021
date: Week 4
keywords: ICP3038, Computer Vision, C/C++, image processing, OpenCV, Bangor University, School of Computer Science and Electronic Engineering
institute: School of Computer Science and Electronic Engineering, Bangor University
---


# Introduction

Last week, you wrote a program to convert temperatures from degrees Celsius to Fahrenheit. It made use of the command line to pass data to the program. Unit testing was used to check that

1. the program can run;
2. an error message is displayed when the command line is invalid;
3. the program outputs the right values when the command line is valid.

You also used C arrays. The aims of today's lab are:

1. Understand the constructor in C++ and using initialisation lists;
2. Get familiar with the implementation of (basic) classes;
3. Overwrite some operators (`=`, `<<` and `>>`);
4. Use `std::string` instead of `char*`.

Next week, we will use the STL library and write our own template class.


# Prerequisite

Make sure you completed the lab from last week as we are going to use unit testing to check our code again. It's good practice.


# Task 1: Initialisation lists
===========================================================

For this task, you are given three C++ files:

1.  `include/Integer.h`, the header file defining a class to handle
    integer numbers;

2.  `src/Integer.cpp`, the source file that implements the code;

3.  `src/TestInteger.cpp`, a test program to try the class.

We want to adopt good C++ practice. There are plenty of tutorials,
forums, etc. on the Web that deal with how to write simple C++ classes.
I googled 'How to write a simple class in C++?'. The first item returned
from Google was:
[http://stackoverflow.com/questions/865922/how-to-write-a-simple-class-in-c](http://stackoverflow.com/questions/865922/how-to-write-a-simple-class-in-c)
The answers to the question on StackOverflow are mostly correct, but not
perfect. Most people did not use initialisation lists.

Initialisation lists have been around for a very long time, but many
people still ignore them despite their advantages. Initialisation lists
are used in constructors to set the initial values of class members in
an efficient manner. On the web, we may often see:

    DummyClass my_instance;
    my_instance = 10;

This is not very good. What will happen in practice?

1.  One call of the default constructor (`DummyClass::DummyClass()`);
2.  One call of the copy operator (`DummyClass::operator=(int)`). Note that the copy operator is also called assignment operator.

There are therefore two function calls to perform the declaration and the initialisation the
object instance. It is obviously not very good if we consider how many times we
may have to create objects in a large program. Instead, we should use:

    DummyClass my_instance(10);

or

    DummyClass my_instance = 10;

Both are equivalent and only the constructor
(`DummyClass::DummyClass(int)`) will be called. This is more effective
and it is better OOP practice.

We are going to declare a new class called *Integer* in `include/Integer.h`.

## Use of #include guards

In `include/Integer.h`, add the #include guards:

```cpp
#ifndef __Integer_h
#define __Integer_h

class Integer
{
};

#endif // __Integer_h
```

## Encapsulation: Keep your private parts private

There are three types of encapsulation in C++:

- public: If a class member (attribute or method) is declared as *public*, then it can be accessed from anywhere.
- protected: If it is declared as *protected*, then it can be accessed only within the class itself and by inheriting classes.
- private: If it is declared as *private*, then it can only be accessed by the class that defines that member.

In this class, we only have one attribute called: `m_data` that will be used to store the data.
For safety reason, we make sure it is private. If anyone wants to access it, we'll provide special methods usually called getters and setters.

```cpp
#ifndef __Integer_h
#define __Integer_h

class Integer
{
private:
    m_data
};

#endif // __Integer_h
```

I always start a class with the attributes, then the constructors. There are 3 constructors we could provide:

- a Default constructor that can instantiate a new object without the new of any parameter: `Integer()`;
- a copy constructor that can instantiate a new object from another object of the same type: `Integer(const Integer& aValue)`; and
- a constructor that can instantiate a new object from an `int`: `Integer(int aValue)`

These are public.


```cpp
#ifndef __Integer_h
#define __Integer_h

class Integer
{
public:
    Integer();
    Integer(const Integer& aValue);
    Integer(int aValue);

private:
    m_data
};

#endif // __Integer_h
```

## Initialisation lists

We will now modify `src/Integer.cxx` to implement the constructors.

### Add the header inclusion.

```cpp
#include "Integer.h"
```

By convention, use `"` when including your own headers.

### Add the skeleton



```cpp
#include "Integer.h"

Integer::Integer()
{}


Integer::Integer(const Integer& aValue)
{}


Integer::Integer(int aValue)
{}
```

### Create the test program

In `TestInteger.cxx`, type:

```cpp
#include "Integer.h"

int main()
{
    int i = 10;

    Integer j;      // Default constructor
    Integer k = 20; // Initialise from an int
    Integer l = i;  // Initialise from an int
    Integer m = k;  // Initialise from another object Integer
}
```


Have a look at the code I and execute it. 3 instances of Integer have been
created and data has been printed in the standard output. Look at the
different values of `m_data` that have been printed and try to
understand what happened.

For Task 1, you only have to modify `Integer.cpp`. The methods that you
need to modify are:

    Integer::Integer()
    Integer::Integer(int anInteger)

But first, look below at the code of the copy constructor. It has an
initialisation list. See the '`:`' character at the end of Line 2 and
look at Line 4 to see how to set the initial value of `m_data`.

``` {.numberLines numbers="left"}
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
```

**Add an initialisation list to the other constructors** (see
`src/Integer.cpp` for further instructions).

The code of the initialisation list is execute first, at the
instanciation of the objet. Then the body of the constructor is
executed. It is not unusual for C++ constructors to have an empty body.
Using the list is faster than using the copy `operator=` in the body of
the constructor.

Task 3: Create your own class {#task-3-create-your-own-class .unnumbered}
=============================

You are going to write a new class called "StringInverter". You need 3
extra files:

1.  `include/StringInverter.h`, the header file defining a class to
    handle integer numbers;

2.  `src/StringInverter.cpp`, the source file that implements the code;

3.  `src/TestStringInverter.cpp`, a test program to try the class.

First, modify CMakeLists.txt to add a new project. Just add:

    add_executable(Task2
        include/StringInverter.h
        src/TestStringInverter.cpp
        src/StringInverter.cpp)

Now you can start implementing the class. It should include the public
methods as follows:

        StringInverter();
        StringInverter(const StringInverter& aString);
        StringInverter(const char* aString);
        StringInverter(const std::string& aString);
        ~StringInverter();
        void setString(const char* aString);
        void setString(const std::string& aString);
        const std::string& getString() const;
        const std::string& getInvertedString() const;
        StringInverter& operator=(const StringInverter& aString);
        StringInverter& operator=(const char* aString);
        StringInverter& operator=(const std::string& aString);
        bool operator==(const StringInverter& aString) const;
        bool operator==(const char* aString) const;
        bool operator==(const std::string& aString) const;
        bool operator!=(const StringInverter& aString) const;
        bool operator!=(const char* aString) const;
        bool operator!=(const std::string& aString) const;

It should also include the following private method:

    void invertString();

Also add friend functions `operator<<` and `operator>>`:

    std::ostream& operator<<(std::ostream& aStream, const StringInverter& aString);
    std::istream& operator>>(std::istream& aStream, StringInverter& aString);

In `TestStringInverter.cpp`, you have to test each method and each
function.
