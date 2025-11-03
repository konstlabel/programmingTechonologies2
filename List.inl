#include <iostream>

namespace Lists {

    template<typename T>
    List<T>::List() : _size(0), _head(nullptr), _tail(nullptr) {}

    template<typename T>
    List<T>::List(Element<T>* head) : size(1), _head(head), _tail(head) {
        
        while (_tail->_next != nullptr) {
            _tail = _tail->_next;
            _size++;
        }
    }

    template<typename T>
    List<T>::List(T* head) : _size(1) {

        _head = new Element(head);
        _tail = _head;
    }

    template<typename T>
    List<T>::List(const List<T>& other) {

        if (!other.isEmpty()) {
            Element<T>* current = other._head;
            for (int i = 0; i < other._size; i++) {
                add(current->_data);
                current = current->_next;
            }
        }
    }

    template<typename T>
    List<T>::~List() {

        clear();
    }

    template<typename T>
    List<T>& List<T>::operator =(const List<T>& other) {

        if (this == &other)
            return *this;

        clear();

        if (other.isEmpty())
            return *this;

        Element<T>* current = other._head;
        while (current != nullptr) {
            add(current->_data);
            current = current->_next;
        }

        return *this;
    }

    template<typename T>
    bool List<T>::operator ==(const List<T>& other) {

        if (_size != other._size || _head != other._head || _tail != other._tail)
            return false;

        return true;
    }

    template<typename T>
    int List<T>::size() const {

        return _size;
    }

    template<typename T>
    T* List<T>::head() const {

        return _head->_data;
    }

    template<typename T>
    T* List<T>::tail() const {

        return _tail->_data;
    }

    template<typename T>
    void List<T>::add(const T* obj) {

        if (obj == nullptr)
            throw std::invalid_argument("Cannot add null object");

        Element<T>* element = new Element<T>(new T(*obj));
        if (_head == nullptr)
            _head = _tail = element;
        else {
            _tail->_next = element;
            _tail = element;
        }
        _size++;
    }

    template<typename T>
    void List<T>::set(int index, const T* obj) {

        if (index < 0 || index >= _size)
            throw std::out_of_range("Index out of range");

        if (obj == nullptr)
            throw std::invalid_argument("Cannot set null object");

        Element<T>* ne = new Element<T>(*obj);

        Element<T>* element = _head;
        if (index == 0) {
            ne->_next = _head->_next;
            _head = ne;
            delete element;
        }
        else {
            for (int i = 1; i < index; i++)
                element = element->_next;
            Element<T>* temp = element->_next;
            element->_next = ne;
            ne->_next = temp->_next;
            delete temp;
        }

        if (ne->_next == nullptr)
            _tail = ne;
    }
    
    template<typename T>
    void List<T>::remove(int index) {

        if (index < 0 || index >= _size)
            throw std::out_of_range("Index out of range");

        Element<T>* element = _head;
        if (index == 0) {
            _head = _head->_next;
            delete element;
        }
        else {
            for (int i = 1; i < index; i++)
                element = element->_next;
            Element<T>* temp = element->_next;
            element->_next = temp->_next;
            delete temp;
        }

        if (element->_next == nullptr)
            _tail = element;

        _size--;
    }

    template<typename T>
    void List<T>::removeObject(T* obj) {

        if (obj == nullptr)
            throw std::invalid_argument("Cannot delete null object");

        int index = indexOf(obj);
        if (index == -1)
            throw std::invalid_argument("Object not found in vector");

        remove(index);
    }

    template<typename T>
    void List<T>::clear() {

        while (_head != nullptr) {
            Element<T>* temp = _head->next();
            delete _head;
            _head = temp;
        }
        _tail = nullptr;
        _size = 0;
    }

    template<typename T>
    T* List<T>::get(int index) {

        if (index < 0 || index >= _size)
            throw std::out_of_range("Index out of range");

        Element<T>* element = _head;
        for (int i = 0; i < index; i++)
            element = element->_next;
        return element->_data;
    }

    template<typename T>
    int List<T>::indexOf(T* obj) const {

        Element<T>* element = _head;
        for (int i = 0; i < _size; i++) {
            if (element->_data != nullptr && *element->_data == *obj) {
                return i;
            }
            element = element->next();
        }

        return -1;
    }

    template<typename T>
    bool List<T>::contains(T* obj) const {

        return indexOf(obj) >= 0;
    }

    template<typename T>
    bool List<T>::isEmpty() const {

        return _size == 0;
    }

    template<typename T>
    List<T>::Iterator List<T>::begin() {

        return Iterator(_head);
    }

    template<typename T>
    List<T>::Iterator List<T>::end() {

        return Iterator(nullptr);
    }

    template<typename T>
    List<T>::Iterator List<T>::begin() const {

        return Iterator(_head);
    }

    template<typename T>
    List<T>::Iterator List<T>::end() const {

        return Iterator(nullptr);
    }

    template<typename T>
    List<T>::Iterator::Iterator(Element<T>* ptr) :ptr(ptr) {}

    template<typename T>
    T* List<T>::Iterator::operator*() {

        return ptr->_data;
    }

    template<typename T>
    T* List<T>::Iterator::operator*() const {

        return ptr->_data;
    }

    template<typename T>
    List<T>::Iterator& List<T>::Iterator::operator++() {

        ptr = ptr->_next;
        return *this;
    }

    template<typename T>
    bool List<T>::Iterator::operator !=(const Iterator& other) const {

        return ptr != other.ptr;
    }

    template<typename T>
    bool List<T>::Iterator::operator==(const Iterator& other) const {

        return ptr == other.ptr;
    }
    
    template<typename T>
    void List<T>::sort(bool reverse) {

        if (!_head || !_head->next()) 
            return;

        bool swapped;
        do {
            swapped = false;
            Element<T>* current = _head;

            while (current->next()) {
                if ((!reverse && *(current->data()) > *(current->next()->data())) ||
                    (reverse && *(current->data()) < *(current->next()->data()))) {
                    std::swap(current->_data, current->next()->_data);
                    swapped = true;
                }
            
                current = current->next();
            }

        } while (swapped);
    }
}