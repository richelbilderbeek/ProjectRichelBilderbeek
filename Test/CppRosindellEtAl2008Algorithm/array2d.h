#ifndef ARRAY2D_H
#define ARRAY2D_H

#include "array1d.h"

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


template<typename T> using array2D = array2D_Rosindell<T>;

#endif // ARRAY2D_H
