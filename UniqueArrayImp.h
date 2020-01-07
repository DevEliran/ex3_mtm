#ifndef EX3_MTM_UNIQUEARRAYIMP_H
#define EX3_MTM_UNIQUEARRAYIMP_H
using namespace std;


template <class Element, class Compare>
UniqueArray<Element, Compare>::UniqueArray(unsigned int size):
    data(new Element* [size]), size(0), max_size(size){
    for(int i = 0; i < max_size; i++){
        data[i] = nullptr;
    }
}


template <class Element, class Compare>
UniqueArray<Element, Compare>::UniqueArray(const UniqueArray& other):
    data(new Element* [other.size]), size(other.size), max_size(other.max_size){
    for(int i = 0; i < max_size; i++){
        data[i] = new Element(*other.data[i]);
    }
}


template <class Element, class Compare>
UniqueArray<Element, Compare>::~UniqueArray(){
    delete[] data;
}


template <class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::insert(const Element& element){
    Compare compare_func;
    for(int i = 0; i < size; i++){
        if(compare_func(*data[i], element)){
            return i;
        }
    }
    if (size >= max_size){
        throw UniqueArrayIsFullException();
    }

    data[size++] = new Element(element);
    return size - 1;
}


template <class Element, class Compare>
bool UniqueArray<Element, Compare>::getIndex(const Element& element, unsigned int& index) const {
    Compare compare_func;
    for(int i = 0; i < size; i++){
        if (compare_func(*data[i], element)){
            index = i;
            return true;
        }
    }
    return false;
}

template <class Element, class Compare>
bool UniqueArray<Element, Compare>::remove(const Element& element){
    if (size <= 0){
        return false;
    }
    unsigned int idx;
    unsigned int& index = idx;
    bool found;
    found = getIndex(element, index);
    if (!found){
        return false;
    }
    else{
        delete[] data[index];
        size -- ;
        return true;
    }
}


template <class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::getCount() const {
    return size;
}


template <class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::getSize() const {
    return max_size;
}


template <class Element, class Compare>
const Element* UniqueArray<Element, Compare>::operator[](const Element& element) const{
    unsigned int idx;
    unsigned int& index = idx;
    bool found;
    found = getIndex(element, index);
    if (!found){
        return NULL;
    }
    else{
        return data[index];
    }
}


template <class Element, class Compare>
UniqueArray<Element, Compare> UniqueArray<Element, Compare>::filter(const Filter& f) const{
    UniqueArray ua (*this);
    int len = ua.size;
    for(int i = 0; i < len; i++){
        if(!f(*ua.data[i])){
            delete[] data[i];
            ua.size--;
        }
    }
    return ua;
}
#endif //EX3_MTM_UNIQUEARRAYIMP_H
