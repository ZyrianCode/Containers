//#include "Src/Zyrian/Additional/pch.h"
#include "Includes/Src/Zyrian/CustomContainers/Definition/ForwardList.h"

namespace ccl {
    template<class T>
    ForwardList<T>::ForwardList()
    {
        _head = nullptr;
        _size = 0;
    }

    template<class T>
    ForwardList<T>::~ForwardList()
    {
        clear();
    }

    template<class T>
    int ForwardList<T>::size()
    {
        return _size;
    }

    template<class T>
    bool ForwardList<T>::is_empty()
    {
        return _size == 0;
    }

    template<class T>
    void ForwardList<T>::clear()
    {
        while (_size)
        {
            pop_front();
        }
    }

    template<class T>
    void ForwardList<T>::pop_front()
    {
        if (_size <= 0) return;
        SingleDirectionalNode<T>* current = _head;
        _head = _head->PNext;
        delete current;
        _size--;
    }

    template<class T>
    void ForwardList<T>::pop_back()
    {
        remove_at(_size - 1);
    }

    template<class T>
    void ForwardList<T>::push_front(T value)
    {
        _head = new SingleDirectionalNode<T>(value, _head);
        _size++;
    }

    template<class T>
    void ForwardList<T>::push_back(T value)
    {
        if (_head == nullptr) {
            _head = _end = new SingleDirectionalNode<T>(value, nullptr);
        }
        else {
            SingleDirectionalNode<T>* current = this->_head;
            while (current->PNext != nullptr)
            {
                current = current->PNext;
            }
            current->PNext = new SingleDirectionalNode<T>(value);
        }
        _size++;
    }

    template<class T>
    void ForwardList<T>::place_after(SingleDirectionalNode<T>* index, T value)
    {
        SingleDirectionalNode<T>* current = index;
        SingleDirectionalNode<T>* newNode = new SingleDirectionalNode<T>(value, current->PNext);
        current->PNext = newNode;
        _size++;
    }

    template<class T>
    void ForwardList<T>::place_after(T index, T value)
    {
        if (_index < 0) { invalid_index(); }
        else if (_index > _size) {
            _index = _size + 1;
            push_back(value);
        }
        else {
            if (_index == _size - 1) { push_back(value); }
            else {
                SingleDirectionalNode<T>* current = this->_head;
                auto prevIndex = _index - 1;
                for (auto i = 0; i <= prevIndex; i++)
                {
                    current = current->PNext;
                }
                SingleDirectionalNode<T>* newNode = new SingleDirectionalNode<T>(value, current->PNext);
                current->PNext = newNode;
                _size++;
            }
        }
    }

    template<class T>
    void ForwardList<T>::remove_after(SingleDirectionalNode<T>* index)
    {
        SingleDirectionalNode<T>* removableNode = index->PNext;
        index->PNext = removableNode->PNext;
        removableNode->PNext = nullptr;
        if (removableNode == _end) {
            _end = index;
        }
        else if (removableNode == _head) { _head = index; }
        else if (index == _head) { invalid_index(); }
        _size--;
    }

    template<class T>
    void ForwardList<T>::remove_after(T index)
    {
        auto current_pos = _index + 1;
        auto list_size = size();
        if (_index > _size || _index < 0) { invalid_index(); }
        else {
            SingleDirectionalNode<T>* current = this->_head; //где сейчас находимся (нужно для проверки следующего элемента)
            SingleDirectionalNode<T>* prev = this->_head;
            for (auto i = 0; i < current_pos - 1; i++) //находим предыдущий элемент
            {
                prev = prev->PNext; //перемещаем адрес в предыдущий элемент
            }
            for (current_pos; current_pos < list_size; current_pos++)
            {
                SingleDirectionalNode<T>* removableNode = prev->PNext; //храним адрес старого элемента на который указывал предыдущий элемент
                prev->PNext = removableNode->PNext; //соединяем предыдущий элемент с последующим
                delete removableNode;
                _size--;
            }
        }
    }

    template<class T>
    void ForwardList<T>::remove_at(SingleDirectionalNode<T>* index)
    {
        SingleDirectionalNode<T>* current = this->_head;
        while (current < index)
        {
            current = current->PNext;
        }

        if (current != nullptr) {
            SingleDirectionalNode<T>* removableNode = current; //храним адрес старого элемента на который указывал предыдущий элемент
            current->PNext = removableNode->PNext; //соединяем предыдущий элемент с последующим
            delete removableNode;
            _size--;
        }
        else {
            if (_head == _end) {
                _head = _end = nullptr;
                _size--;
            }
            else {
                remove_after(find_prev(index));
            }
        }
    }

    template<class T>
    void ForwardList<T>::remove_at(T _index)
    {
        if (_index < 0) { invalid_index(); }
        else if (_index >= _size) {
            while (_index >= _size)
            {
                _index = _size - 1;
            }
            remove(_index);
            return;
        }
        else if (_index == 0) { pop_front(); }
        else {
            remove(_index);
        }
    }

    template<class T>
    SingleDirectionalNode<T>* ForwardList<T>::find(T value)
    {
        SingleDirectionalNode<T>* ptr = this->_head;
        while (ptr != nullptr)
        {
            if (ptr->Value == value) return ptr;
            else ptr = ptr->PNext;
        }
    }

    template<class T>
    SingleDirectionalNode<T>* ForwardList<T>::find_prev(SingleDirectionalNode<T>* index)
    {
        SingleDirectionalNode<T>* prev = nullptr;
        SingleDirectionalNode<T>* current = _head;
        //добавить искл. для поиска предыдущего головы
        while (current != nullptr) {
            prev = current;
            current = current->PNext;
        }
        return prev;
    }

    template<class T>
    SingleDirectionalNode<T>* ForwardList<T>::first()
    {
        return _head;
    }

    template<class T>
    SingleDirectionalNode<T>* ForwardList<T>::last()
    {
        return _end;
    }

    template<class T>
    T& ForwardList<T>::operator[](const T index)
    {
        //начинаем с head. И если значение счётчика совпадает с индексом, который мы получили, то мы возвращаем данные
        if (index > _size - 1 || index < 0) { invalid_index(); }
        auto current_pos = 0;
        SingleDirectionalNode<T>* current = this->_head; //где сейчас находимся (нужно для проверки следующего элемента)
        while (current != nullptr) //пока указатель не станет равен null
        {
            if (current_pos == index) {
                return current->Value; //если текущая позиция совпала с входящим индексом, возвращаем данные по индексу
            }
            current = current->PNext; //присваиваем текущему эл.адрес следующего, для этого у текущего элемента спрашиваем адрес следующего
            current_pos++;
        }
    }

    template<class T>
    void ForwardList<T>::invalid_index()
    {
        string message = "Недопустимый индекс ";
        message.append(to_string((int)index));
        throw out_of_range(message);
    }

    template<class T>
    void ForwardList<T>::remove(T _index)
    {
        SingleDirectionalNode<T>* prev = this->_head;
        for (auto i = 0; i < _index - 1; i++)
        {
            prev = prev->PNext; //перемещаем адрес в предыдущий элемент
        }
        SingleDirectionalNode<T>* removableNode = prev->PNext; //храним адрес старого элемента на который указывал предыдущий элемент
        prev->PNext = removableNode->PNext; //соединяем предыдущий элемент с последующим
        delete removableNode;
        _size--;
    }
}
