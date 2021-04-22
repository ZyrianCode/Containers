#include "Includes/Src/Zyrian/CustomContainers/Definition/ForwardIterator.h"

namespace ccl {
    template<typename T>
    ForwardIterator<T>::ForwardIterator() : current(0)
    {}

    template<typename T>
    ForwardIterator<T>::ForwardIterator(T* Current) : current(Current)
    {}

    template<typename T>
    ForwardIterator<T>::ForwardIterator(const ForwardIterator& Iterator) : current(Iterator.current)
    {}

    template<typename T>
    ForwardIterator<T>& ForwardIterator<T>::operator=(const ForwardIterator& Iterator)
    {
        // исключаем присваивание самому себе
        if (this != &Iterator) { current = Iterator.current; }

        return *this;
    }

    template<typename T>
    ForwardIterator<T>& ForwardIterator<T>::operator++()
    {
        ++current;
        return *this;
    }

    template<typename T>
    ForwardIterator<T> ForwardIterator<T>::operator++(int Elem)
    {
        ForwardIterator iterator(*this);
        operator++();
        return iterator;
    }

    template<typename T>
    T& ForwardIterator<T>::operator*()
    {  return *current; }

    template<typename T>
    T* ForwardIterator<T>::operator->()
    {  return current; }

    template<typename T>
    bool ForwardIterator<T>::operator==(const ForwardIterator& Iterator)
    {  return current == Iterator.current; }

    template<typename T>
    bool ForwardIterator<T>::operator!=(const ForwardIterator& Iterator)
    {  return !(*this == Iterator); }
}
