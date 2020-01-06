//
// Created by Eliran on 1/3/2020.
//

#ifndef EX3_MTM_UNIQUEARRAYIMP_H
#define EX3_MTM_UNIQUEARRAYIMP_H
using namespace std;


template <class Element, class Compare>//think how to properly initialize Element type
UniqueArray<Element, Compare>::UniqueArray(unsigned int size):
    data(new Element), size(0), max_size(size){
}


template <class Element, class Compare>//implement exceptions
UniqueArray<Element, Compare>::UniqueArray(const UniqueArray& other):
    data(new Element[]), size(other.size), max_size(other.max_size){
    for(int i = 0; i < size; i++){
        try {
            data[i] = other.data[i];
        }
        catch (...){
             
        }
    }
}


template <class Element, class Compare>
UniqueArray<Element, Compare>::~UniqueArray(){
    delete[] data;
}


template <class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::insert(const Element& element){
    if (size >= max_size){
        throw UniqueArrayIsFullException();
    }
    for(int i = 0; i < size; i++){
        if(data[i] == element){
            throw UniqueArrayElementAlreadyExists();
        }
    }
    data[size++] = element;
}


template <class Element, class Compare>
bool UniqueArray<Element, Compare>::getIndex(const Element& element, unsigned int& index) const :{
    for(int i = 0; i < size; i++){
        if (data[i] == element){
            index = i;
            return true;
        }
    }
    return false;
}

template <class Element, class Compare>
bool UniqueArray<Element, Compare>::remove(const Element& element){
    if (size <= 0){
        throw UniqueArrayEmpty();
    }
    unsigned int& index = max_size+1;
    bool found = false;
    found = getIndex(element, index);
    if (!found){
        throw UniqueArrayElementNotFound();
    }
}
#endif //EX3_MTM_UNIQUEARRAYIMP_H
