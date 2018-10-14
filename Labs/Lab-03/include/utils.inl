// For a template function, write the code in the header file
template <typename T> T getMinValue(T i, T j)
{
    return (i < j? i : j);
    
    // "return (i < j? i : j)" means:
    // if (i < j) is equal to true, then return i, else return j.
}


// Replace the function below by template functions

// 3 steps for each function:
// (i) remove 'inline' (in utils.inl)
//    In C, we have used Macro function an optimized technique used by compiler to reduce the execution time etc.
//    In C++, we use inline functions. (see here for an online article on this topic: http://www.cplusplus.com/articles/2LywvCM9/
//    The keyword inline needs to be remove for template functions.
// (ii) Add 'template <typename T>' at the front of every function declaration.  (in utils.h and in utils.inl)
//    'template <typename T>' means that the corresponding function is template, and that the template type is 'T'
// (iii) replaces occurences of 'int' by T (in utils.inl).
inline int getMaxValue(int i, int j)
{
    return (i < j? j : i);
}


inline void swap(int& i, int& j)
{
    int temp = i;
    i = j;
    j = temp;
}


inline void sort(int& i, int& j)
{
    if (i > j)
    {
        swap(i, j);
    }
}


inline int power(int i, unsigned int j)
{
    int results = 1;

    for (int k = 0; k < j; ++k)
    {
        results *= i;
    }

    return results;
}


inline double getAverage(int i, int j)
{
    return (i + j) / 2.0;
}

