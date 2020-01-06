//
// Created by Eliran on 1/3/2020.
//

#include "UniqueArray.h"

template <class Element, class Compare>
class UniqueArray {
    Element element;
    static int size;
    static int max_size;
public:
    UniqueArray(unsigned int size);
    UniqueArray(const UniqueArray& other);
    ~UniqueArray()
    unsigned int insert(const Element& element);
    bool getIndex(const Element& element, unsigned int& index) const;
    const Element* operator[](const Element element) const;
    bool remove(const Element& element);
    unsigned int count() const;//returns current size
    unsigned int size() const;//returns max size
    UniqueArray<Element, Compare> filter(const Filter& f) const;
    class UniqueArrayIsFullException{};
    class Filter{};
};

template <class Element, class Compare>
UniqueArray<Element, Compare>::UniqueArray(unsigned int size):
    element(new Element), max_size(size), size(0){
    }

template <class Element, class Compare>
