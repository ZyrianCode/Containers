#pragma once
#include <cstddef>
#include <algorithm>
#include <stdexcept>
#include "Includes/Src/Zyrian/CustomContainers/Implementation/ForwardIterator.hpp"

namespace ccl {
    template<class T>
    class Array
    {
    public:
        typedef ForwardIterator<T> Iterator; 
        typedef const ForwardIterator<T> Const_Iterator;
        typedef size_t SizeType;
        using ConstSizeType = const size_t;
        typedef T* Ptr;
        typedef const T* ConstPtr;
        typedef T& Ref;
        typedef const T& ConstRef;

        //Конструкторы
        Array();
        Array(const size_t size);
        Array(const Array& arr);
        ~Array();

        Array& operator =(const Array& arr);

        Iterator begin() const;
        Iterator end() const;

        Ref operator [](SizeType index);
        ConstRef operator [](SizeType index) const;

        SizeType size() const;
        bool IsEmpty() const;

    private:
        void swap(Array& first, Array& second);
        Ptr _arr;
        SizeType _size;
    };
}

