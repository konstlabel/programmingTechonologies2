#pragma once
#include <concepts>
#include "Element.h"
#include "Zodiac.h"

namespace Lists{

	template<typename T>
	class List {
        static_assert(!std::same_as<T, Element<T>>, "List<T> cannot store Element<T>");

		Element<T>* _head;
		Element<T>* _tail;
		int _size;

	public:

		List();
		explicit List(Element<T>* head);
		explicit List(T* head);
		List(const List<T>& other);

        ~List();

		List<T>& operator =(const List<T>& other);
		bool operator ==(const List<T>& other);

        int size() const;
        T* head() const;
        T* tail() const;

        void add(const T* obj);
        void set(int index, const T* obj);
        void remove(int index);
        void removeObject(T* obj);
        void clear();

        T* get(int index);
        int indexOf(T* obj) const;

        bool contains(T* obj) const;
        bool isEmpty() const;

        void sort(bool reverse);

        class Iterator {
            Element<T>* ptr;
        public:
            Iterator(Element<T>* ptr);

            T* operator*();
            T* operator*() const;
            Iterator& operator++();
            bool operator !=(const Iterator& other) const;
            bool operator==(const Iterator& other) const;
        };

        Iterator begin();
        Iterator end();
        Iterator begin() const;
        Iterator end() const;
	};
}

#include "List.inl"