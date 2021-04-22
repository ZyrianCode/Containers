#include "Includes/Src/Zyrian/CustomContainers/Definition/Array.h"

namespace ccl {
    template<class T>
    Array<T>::Array() : _arr(new T[0]), _size(0){}

    template<class T>
    Array<T>::Array(const size_t size) : _arr(new T[size]), _size(size)
    {
        // вызываем конструкторы для каждого элемента
        std::fill(_arr, _arr + _size, T());
    }

    template<class T>
    Array<T>::Array(const Array& arr)
    {
        _size = arr.size();
        _arr = new T[_size];
        // копируем элементы в новый контейнер
        std::copy(arr._arr, arr._arr + _size, _arr);
    }

    template<class T>
    Array<T>::~Array()
    {
        delete[] _arr;
    }

    template<class T>
    Array<T>& Array<T>::operator=(const Array& arr)
    {
        // исключаем работу при присваивании самому себе
        if (this != &arr)
        {
            Array tmp(arr);
            swap(tmp);
        }
        return *this;
    }

    template<class T>
    ForwardIterator<T> Array<T>::begin() const
    {
        return Iterator(_arr);
    }

    template<class T>
    ForwardIterator<T> Array<T>::end() const
    {
        return Iterator(_arr + _size);
    }

    template<class T>
    T& Array<T>::operator[](SizeType index)
    {
        if (index >= _size){ throw std::out_of_range("Array subscript out of range"); }
        return _arr[index];
    }

    template<class T>
    const T& Array<T>::operator[](SizeType index) const
    {
        if (index >= _size) { throw std::out_of_range("Array subscript out of range"); }
        return _arr[index];
    }

    template<class T>
    rsize_t Array<T>::size() const
    { return _size; }

    template<class T>
    bool Array<T>::IsEmpty() const
    { return (_size == 0); }

    template<class T>
    void Array<T>::swap(Array& first, Array& second)
    {
        std::swap(first._arr, second._arr);
        std::swap(first._size, second._size);
    }
}
