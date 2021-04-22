#pragma once
#include <iterator>

namespace ccl {
    template <typename T>
    class ForwardIterator
    {
    public:
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef std::forward_iterator_tag iterator_category;
        typedef ptrdiff_t difference_type;

        // конструкторы
        ForwardIterator();
        ForwardIterator(T* Current);
        ForwardIterator(const ForwardIterator& Iterator);
        // оператор присваиваний
        ForwardIterator& operator =(const ForwardIterator& Iterator);

        // сдвиги операторов
        ForwardIterator& operator ++();    // префиксный инкремент
        ForwardIterator  operator ++(int Elem); // постфиксная инкремент

        // операторы обращения
        T& operator *();
        T* operator ->();

        // операторы сравнения
        bool operator ==(const ForwardIterator& Iterator);
        bool operator !=(const ForwardIterator& Iterator);

    private:
        T* current;
    };
}
