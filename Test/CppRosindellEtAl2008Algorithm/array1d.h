#ifndef ARRAY1D_H
#define ARRAY1D_H

#include <vector>

template<class T>
class array1D_Bilderbeek
{
public:
  array1D_Bilderbeek() {}
  array1D_Bilderbeek(const int size, const T& initial_value)
    : m_data(size,initial_value)
  {
  }
  ~array1D_Bilderbeek() {}
  void SetSize(int n) { m_data.resize(n); }
  int size() { return m_data.size(); }
  T& operator[](int index) { return m_data[index]; }
private:
  std::vector<T> m_data; // stores the entries themselves
};

#ifdef DEFINE_ARRAY1D_ROSINDELL
// Template class array1D
template<class X>
class array1D_Rosindell {
public:
    array1D_Rosindell();
    ~array1D_Rosindell();
    void SetSize(int n); //Old name: SetSize
    int size();
    X& operator[](int index);
private:
    int entries; // stores the number of entries
    X* data; // stores the entries themselves
};

// Template class array1D
template<class X>
array1D_Rosindell<X>::array1D_Rosindell():data(0)
{
    SetSize(0);
}
// destructor
template<class X>
array1D_Rosindell<X>::~array1D_Rosindell()
{delete[] data;
}
// setter for size
template<class X>
void array1D_Rosindell<X>::SetSize(int n)
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
int array1D_Rosindell<X>::size()
{
    return entries;
}
// [] operator
template<class X>
X& array1D_Rosindell<X>::operator[](int index)
{
    if (index < 0)
    {
        index = -1 * index;
        index = index % entries;index = entries - index;
    }
    index = index % entries;
    return data[index];
}
#endif // DEFINE_ARRAY1D_ROSINDELL

template<typename T> using array1D = array1D_Bilderbeek<T>;

#endif // ARRAY1D_H
