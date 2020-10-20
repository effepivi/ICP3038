CMAKE_MINIMUM_REQUIRED (VERSION 3.10)

# set the project name
PROJECT (ICP3038-lab4 VERSION 1.0)

# Lab 2 ########################################################################
# add the executable
ADD_EXECUTABLE (lab2-1-C lab2-1.c)
ADD_EXECUTABLE (lab2-1-CXX lab2-1.cxx)
ADD_EXECUTABLE (lab2-2-C lab2-2.c)
ADD_EXECUTABLE (lab2-2-CXX lab2-2.cxx)
ADD_EXECUTABLE (lab2-3 lab2-3.cxx)

ADD_EXECUTABLE (lab3-1 lab3-1.cxx)
ADD_EXECUTABLE (lab3-2 lab3-2.cxx)
ADD_EXECUTABLE (lab3-3 lab3-3.cxx)
ADD_EXECUTABLE (lab3-4 lab3-4.cxx)
ADD_EXECUTABLE (lab3-5 lab3-5.cxx)
ADD_EXECUTABLE (celsius2fahrenheit celsius2fahrenheit.cxx)

# Lab 3 ########################################################################

# Enable unit testing
enable_testing()

add_test(NAME Runs COMMAND celsius2fahrenheit 25.0)

add_test(NAME Usage COMMAND celsius2fahrenheit)
set_tests_properties(Usage
  PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*temp_in_celcius"
)

function(do_test target arg result)
    add_test(NAME Comp${arg} COMMAND ${target} ${arg})
    set_tests_properties(Comp${arg}
        PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endfunction(do_test)

do_test(celsius2fahrenheit   20   "20 degrees Celsius is the same as 68 degrees Fahrenheit.")
do_test(celsius2fahrenheit   20.5   "20.5 degrees Celsius is the same as 68.9 degrees Fahrenheit.")
do_test(celsius2fahrenheit   50.5   "50.5 degrees Celsius is the same as 122.9 degrees Fahrenheit.")

# Lab 4 ########################################################################
