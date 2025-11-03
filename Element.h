#pragma once

namespace Lists {
	template<typename T>
	class Element {
		T* _data;
		Element<T>* _next;

		Element(T* data);
		Element(T* data, Element<T>* next);
		Element(const Element<T>& other);

		~Element();

		Element<T>& operator =(const Element<T>& other);
		bool operator ==(const Element<T>& other);

		T* data() const;
		Element<T>* next() const;

		void data(T* data);
		void next(Element<T>* next);
	public:
		template<typename>
		friend class List;
	};
}

#include "Element.inl"