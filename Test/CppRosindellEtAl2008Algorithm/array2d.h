#ifndef ARRAY2D_H
#define ARRAY2D_H

#include "array1d.h"
#include <cassert>
#include <vector>

template<class T>
struct array2D_Bilderbeek {
  void SetSize(int Yin, int Xin)
  {
    data.resize(Yin,array1D<T>(Xin,0));
  }

  array1D<T>& operator[](const int index)
  {
    const int size = static_cast<int>(data.size());
    const int valid_index = (index + size) % size;
    assert(valid_index >= 0);
    assert(valid_index < static_cast<int>(data.size()));
    return data[valid_index];
  }

  private:
  std::vector<array1D<T>> data;

};

#ifdef DEFINE_ARRAY2D_ROSINDELL
// Template class array2D as an array of rows
template<class X>
class array2D_Rosindell {
private:
    // number of entries in the two dimensions
    int entriesX, entriesY;
    // a an array of arrays to store the data
    array1D<X>* data;
public:
    // constructor
    array2D_Rosindell(): data(0)
    {
        SetSize(0,0);
    }
    // destructor
    ~array2D_Rosindell()
    {
        delete[] data;
    }
    // setter for size
    void SetSize(int Yin, int Xin)
    {
        if (data)
        {delete[]data;
        }
        if (Xin > 0 && Yin >0)
        {
            data=new array1D<X>[Yin];
            for (int i=0;i<Yin;i++)
            {
                data[i].SetSize(Xin);
            }
        }
        else
        {
            Yin=0;
        }
        entriesX=Xin;
        entriesY=Yin;
    }
    // [] operator
    array1D<X>& operator[](int index)
    {
        if (index < 0)
        {
            index = -1 * index;
            index = index % entriesY;
            index = entriesY - index;
        }
        index = index % entriesY;
        return data[index];
    }
};
#endif // DEFINE_ARRAY2D_ROSINDELL

template<typename T> using array2D = array2D_Bilderbeek<T>;

#endif // ARRAY2D_H
