#ifndef ARRAY1D_H
#define ARRAY1D_H

#define USE_STD_VECTOR
#ifdef USE_STD_VECTOR
#include <vector>

template<typename T>
using array1D = std::vector<T>;
#else
// Template class array1D
template<class X>
class array1D {
public:
    array1D();
    ~array1D();
    void resize(int n); //Old name: SetSize
    int size();
    X& operator[](int index);
private:
    int entries; // stores the number of entries
    X* data; // stores the entries themselves
};

// Template class array1D
template<class X>
array1D<X>::array1D():data(0)
{
    resize(0);
}
// destructor
template<class X>
array1D<X>::~array1D()
{delete[] data;
}
// setter for size
template<class X>
void array1D<X>::resize(int n)
{
    if(data)
    {
        delete[] data;
    }
    if (n>0)
    {
        data=new X[n];
    }
    else
    {
        data=0;
    }
    entries=n;
}
// getter for size
template<class X>
int array1D<X>::size()
{
    return entries;
}
// [] operator
template<class X>
X& array1D<X>::operator[](int index)
{
    if (index < 0)
    {
        index = -1 * index;
        index = index % entries;index = entries - index;
    }
    index = index % entries;
    return data[index];
}
#endif


#endif // ARRAY1D_H
