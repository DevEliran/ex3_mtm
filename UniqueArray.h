#ifndef MTMPARKINGLOT_UNIQUEARRAY_H
#define MTMPARKINGLOT_UNIQUEARRAY_H


#include <functional>

using namespace std;
template <class Element, class Compare = std::equal_to<Element>>
class UniqueArray {

public:
    Element** data;
    unsigned int curr_size;
    unsigned int max_size;
    int* availability_array;

    explicit UniqueArray(unsigned int size);
    UniqueArray(const UniqueArray& other);
    ~UniqueArray();
    UniqueArray& operator=(const UniqueArray&) = delete;
    unsigned int insert(const Element& element);
    bool getIndex(const Element& element, unsigned int& index) const;
    const Element* operator[] (const Element& element) const;
    bool remove(const Element& element);
    unsigned int getCount() const;
    unsigned int getSize() const;

    /**
     * @return the index of the first empty spot in the array.
     */
    unsigned int getFirstEmptyLocation();

    /**
     * @param index
     * @return an Element pointer in the index spot inside 'data' array.
     */
    const Element* getElementByIndex(unsigned int index) const;

    class Filter {
    public:
        virtual bool operator() (const Element&) const = 0;
    };
    UniqueArray filter(const Filter& f) const;

    class UniqueArrayIsFullException{};

    typedef Element** iterator;
    typedef const Element** const_iterator;

    iterator begin(){
        return data;
    }
    const_iterator begin() const{
        return data;
    }
    iterator end(){
        return data + max_size;
    }
    const_iterator end() const{
        return data + max_size;
    }
};

#include "UniqueArrayImp.h"


#endif //MTMPARKINGLOT_UNIQUEARRAY_H
