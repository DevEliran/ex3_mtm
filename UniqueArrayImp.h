#ifndef EX3_MTM_UNIQUEARRAYIMP_H
#define EX3_MTM_UNIQUEARRAYIMP_H
using namespace std;


template <class Element, class Compare>
UniqueArray<Element, Compare>::UniqueArray(unsigned int size):
    data(new Element* [size]), curr_size(0), max_size(size), availability_array(new int [size]){
    for(int i = 0; i < max_size; i++){
        data[i] = nullptr;
        availability_array[i] = 0;
    }
}


template <class Element, class Compare>
UniqueArray<Element, Compare>::UniqueArray(const UniqueArray& other):
    data(new Element* [other.curr_size]), curr_size(other.curr_size), max_size(other.max_size), availability_array(new int [other.max_size]){
    for(int i = 0; i < curr_size; i++){
        if(other.availability_array[i] == 1) {
            data[i] = new Element(*other.data[i]);
        }
        else{
            data[i] = nullptr;
        }
        availability_array[i] = other.availability_array[i];
    }
}


template <class Element, class Compare>
UniqueArray<Element, Compare>::~UniqueArray(){
    for(int i = 0; i < max_size; i++){
        if(availability_array[i] == 1) {
            delete data[i];
        }
    }
    delete[] data;
    delete[] availability_array;
}


template <class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::insert(const Element& element){
    Compare compare_func;
    int len = this->getCount();
    for(int i = 0; i < max_size; i++){
        if(availability_array[i] == 1) {
            if (compare_func(*data[i], element)) {
                return i;
            }
        }
    }
    if (len >= max_size){
        throw UniqueArrayIsFullException();
    }
    for (int k = 0; k < max_size; k++){
        if(availability_array[k] == 0){
            data[k] = new Element(element);
            availability_array[k] = 1;
            curr_size ++;
            return k;
        }
    }
    return -1;
}


template <class Element, class Compare>
bool UniqueArray<Element, Compare>::getIndex(const Element& element, unsigned int& index) const {
    Compare compare_func;
    for(int i = 0; i < max_size; i++){
        if(availability_array[i] == 1) {
            if (compare_func(*data[i], element)) {
                index = i;
                return true;
            }
        }
    }
    return false;
}

template <class Element, class Compare>
bool UniqueArray<Element, Compare>::remove(const Element& element){ // inspect further
    if (this->getCount() <= 0){
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
        delete data[index];
        availability_array[index] = 0;
        return true;
    }
}


template <class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::getCount() const {
    int count = 0;
    for(int i = 0; i < max_size; i++){
        if(availability_array[i] == 1){
            count++;
        }
    }
    return count;
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
//    int len = ua.getCount();
    for(int i = 0; i < ua.max_size; i++){
        if(!f(*ua.data[i])){
            ua.remove(*ua.data[i]);
        }
    }
    return ua;
}
#endif //EX3_MTM_UNIQUEARRAYIMP_H
