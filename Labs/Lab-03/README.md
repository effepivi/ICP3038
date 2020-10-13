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
Or maybe 0.5, well it depends.

I tried in Python 2
```python
print(1/2)
```
and it outputted `0`.
I tried in Python 3
```python
print(1/2)
```
and it outputted `0.5`.
Same code. Same language-ish. Two different outcomes. Oooops.

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

What is the output of each line of code?
Can you identify what is going on?
1/2 corresponds to an integer division (fast).
The other three lines make use of a floating-point division (slow).

**Don't try to guess what the compiler (or interpreter for Python) might guess or not. Don't trust the compiler. Be in charge, you're the one in control!**

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
- The `divisor` is equal to 3.
- The `division` is a floating-point number equal to `a / divisor`.

The remainder can be obtained using the operator `%` with two integer numbers as operands:
```cpp
float remainder = a % divisor;
```

In this case, `a` is equal to `b` where
```cpp
b = division * divisor + remainder;
```

# C arrays

An array in C is a kind of data structure that can store fixed number of elements of the same type in a contiguous part of the main memory.
An array of ten single-precision floating-point numbers is declared as follows:

```cpp
float my_array[5];
```

`my_array` is actually a pointer that contains the memory location of the 1st element of the array.
To access the first element, use the index `0` such as:

```cpp
my_array[0]
```

and the index of the last element is `total number of elements in the array minus one`, i.e.:

```cpp
my_array[4]
```

**In C or C++, there is no memory bounds checks. It's your job to do it and to be careful!**

There are several ways to initialise an array.

## Task 3: Initialisation of an array

1. Create a new program, e.g. `lab3-3.cxx`. You must add it to `CMakeLists.txt`.
2. In this program, enter:

```cpp
#include <iostream>
#include <string>

using namespace std;

void printArray(const string& aName, float* anArray, unsigned int aNumberOfElements);


int main()
{
    // write your own code here

    return 0;
}


void printArray(const string& aName, float* anArray, unsigned int aNumberOfElements)
{
    // write your own code here
}
```

3. In `printArray`, write a `for` loop that will display every element `i` such as:
```cpp
cout << aName << "[" << i << "]: " << anArray[i] << endl;
```

4. In the `main`, create the arrays as follows:

```cpp
float a[5] = {1.0, 2.0, 4.4, 8.0, 16.0};
```
Note that the number of values between the curly brackets `{` and `}` cannot be larger than the number of elements that we declared between the square brackets `[` and `]`.

**Don't forget, compile often, test often.**

5. The following should generate a compilation error:
```cpp
float b[5] = {1.0, 2.0, 4.4, 8.0, 16.0, 32.0};
```
I get:
```bash
[  6%] Building CXX object CMakeFiles/lab3-3.dir/lab3-3.cxx.o
/home/franck/PROGRAMMING/GitHub/ICP3038/Labs/Lab-03/lab3-3.cxx: In function ‘int main()’:
/home/franck/PROGRAMMING/GitHub/ICP3038/Labs/Lab-03/lab3-3.cxx:12:49: error: too many initializers for ‘float [5]’
     float b[5] = {1.0, 2.0, 4.4, 8.0, 16.0, 32.0};
```
Well as `float b[5] = {1.0, 2.0, 4.4, 8.0, 16.0, 32.0};` does not work, comment this line using `//`.

**Don't forget, compile often, test often.**

6. You can omit the number between the square brackets `[` and `]`. In this case the compiler will determine the right value:
```cpp
float c[] = {1.0, 2.0, 4.4, 8.0, 16.00};
```

**Don't forget, compile often, test often.**

7. You may not initialise the array at all:
```cpp
float d[5];
```

You got the idea, compile often, test often. ;-)

8. or like this:

```cpp
float e[5] = {};
```

9. We are still working in the `main`. You can now print the content of every array with the `printArray` function that you wrote, e.g.

```cpp
printArray("a", a, 5);
cout << endl;
```


# argc/argv

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

## Task 4

Create a new program, e.g. `lab3-4.cxx`. You must add it to `CMakeLists.txt`.
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

## Task 5

Create a new program, e.g. `lab3-5.cxx`. You must add it to `CMakeLists.txt`.
I want you to write a program that will output:
```bash
The program is: lab3-4
argument 1 is: hello
argument 2 is: world
```
when the command line is `lab3-5 hello world`.

I should output:
```bash
The program is: lab3-4
argument 1 is: I
argument 2 is: am
argument 3 is: studying
argument 4 is: ICP3038
```
when the command line is `lab3-5 I am studying ICP3038`.

**NOTE: A common mistake I've seen in the past. Don't add `lab3-5` as an argument of the command line in VisualStudio.** It's not required as it is automatic.

# stof/stoi

1. Create a new program, e.g. `celsius2fahrenheit.cxx`. You must add it to `CMakeLists.txt`.
2. Copy paste the content of `lab2-3.cxx` into `celsius2fahrenheit.cxx`. We are going to make the program more flexible by replacing `cin` with `argc` and `argv`.
3. Get rid of `cout << "Please enter a temperature in Celsius: ";` as we won't need it.
4. Same with `cin >> celsius;`.
5. Add `int argc, char** argv` as the parameters of the `main`.
6. `celsius` should be equal to the 2nd command-line argument, i.e. `argv[1]`.
But `float celsius = argv[1]` does not work :-(
```bash
/home/franck/PROGRAMMING/GitHub/ICP3038/Labs/Lab-03/celsius2fahrenheit.cxx: In function ‘int main(int, char**)’:
/home/franck/PROGRAMMING/GitHub/ICP3038/Labs/Lab-03/celsius2fahrenheit.cxx:7:27: error: cannot convert ‘char*’ to ‘float’ in initialization
     float celsius = argv[1];
                           ^
```
`argv[1]` is a C string whereas celsius is a single-precision floating-point number.
We need to convert it.

7. Include the `<string>` header.
8. Convert the C string into a floating-point number using:
```cpp
float celsius = stof(argv[1]);
```
9. Compile and run your code (fix compilation errors if any).
I got a problem when I run the code. Do you?
Mine is
```bash
terminate called after throwing an instance of 'std::logic_error'
  what():  basic_string::_M_construct null not valid
Aborted (core dumped)
```
It's because `argv[1]` is a random memory location.

10. Display an error message if `argc` is not equal to 2.
```cpp
if (argc != 2)
{
    cerr << "Wrong number of command line arguments." << endl;
    cerr << "Usage: " << argv[0] << " temp_in_celcius" << endl;
    return 1;
}
```
11. If argc is equal to 2, run the code.

# Unit testing support in CMake

1. In `CMakeLists.txt`, add a version number. Replace `project(ICP3038-lab3 VERSION 1.0)` with `project(ICP3038-lab3 VERSION 1.0)`
2. Enable unit testing. In the same file, add `enable_testing()`.
3. To test if the application runs, add `add_test(NAME Runs COMMAND celsius2fahrenheit 25.0)` at the bottom of the file.
4. Check if it all ok (run cmake, reload the project in MSVC++, run the unit tests).
Below is the output I get:
```bash
Running tests...
Test project /home/franck/PROGRAMMING/GitHub/ICP3038/Labs/Lab-03/bin
    Start 1: Runs
1/1 Test #1: Runs .............................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.00 sec
```
5. To test if the usage message works, add at the bottom of the file:
```cmake
add_test(NAME Usage COMMAND celsius2fahrenheit)
set_tests_properties(Usage
  PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*temp_in_celcius"
)
```
6. Check if it all ok (run cmake, reload the project in MSVC++, run the unit tests).
Below is the output I get:
```bash
Running tests...
Test project /home/franck/PROGRAMMING/GitHub/ICP3038/Labs/Lab-03/bin
    Start 1: Runs
1/2 Test #1: Runs .............................   Passed    0.00 sec
    Start 2: Usage
2/2 Test #2: Usage ............................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 2

Total Test time (real) =   0.01 sec
```
7. Define a function to simplify adding tests:
```cmake
function(do_test target arg result)
    add_test(NAME Comp${arg} COMMAND ${target} ${arg})
    set_tests_properties(Comp${arg}
        PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endfunction(do_test)
```
8. Using Google, figure out what 20C, 25C and 30.8C are in Fahrenheit.
9. Add the tests, e.g.
```cmake
do_test(celsius2fahrenheit   20   "20 degrees Celsius is the same as 68 degrees Fahrenheit.")
```
Do the same for 25C  and 30.8C.
10. Check if it all ok (run cmake, reload the project in MSVC++, run the unit tests).
Below is the output I get:
```bash
Running tests...
Test project /home/franck/PROGRAMMING/GitHub/ICP3038/Labs/Lab-03/bin
    Start 1: Runs
1/5 Test #1: Runs .............................   Passed    0.00 sec
    Start 2: Usage
2/5 Test #2: Usage ............................   Passed    0.00 sec
    Start 3: Comp20
3/5 Test #3: Comp20 ...........................   Passed    0.00 sec
    Start 4: Comp25
4/5 Test #4: Comp25 ...........................   Passed    0.00 sec
    Start 5: Comp30.8
5/5 Test #5: Comp30.8 .........................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 5

Total Test time (real) =   0.01 sec
```

    The point is, if you made a mistake in your code and the Fahrenheit value was invalid, the unit tests would fail!
