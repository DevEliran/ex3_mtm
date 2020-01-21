#ifndef EX3_MTM_UNIQUEARRAYIMP_H
#define EX3_MTM_UNIQUEARRAYIMP_H
using namespace std;


template <class Element, class Compare>
UniqueArray<Element, Compare>::UniqueArray(unsigned int size):
    data(new Element* [size]), curr_size(0), max_size(size), availability_array(new int [size]){
    for(unsigned int i = 0; i < max_size; i++){
        data[i] = nullptr;
        availability_array[i] = 0;
    }
}


template <class Element, class Compare>
UniqueArray<Element, Compare>::UniqueArray(const UniqueArray& other):
    data(new Element* [other.max_size]), curr_size(other.curr_size), max_size(other.max_size), availability_array(new int [other.max_size]){
    for(unsigned int i = 0; i < max_size; i++){
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
    for(unsigned int i = 0; i < max_size; i++){
        if(availability_array[i] == 1) {
            delete data[i];
        }
    }
    delete[] data;
    delete[] availability_array;
}


template <class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::insert(const Element& element){
//    unsigned int len = this->getCount();
    if (curr_size >= max_size){
        throw UniqueArrayIsFullException();
    }

    unsigned int idx;

    if (getIndex(element, idx)){
        return idx;
    }

    for (unsigned int k = 0; k < max_size; k++){
        if(availability_array[k] == 0){
            data[k] = new Element(element);
            availability_array[k] = 1;
            curr_size ++;
            return k;
        }
    }
    return max_size;
}


template <class Element, class Compare>
bool UniqueArray<Element, Compare>::getIndex(const Element& element, unsigned int& index) const {
    auto compare_func = Compare();
    for(unsigned int i = 0; i < max_size; i++){
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
bool UniqueArray<Element, Compare>::remove(const Element& element){
    if (this->getCount() <= 0){
        return false;
    }
    unsigned int idx;
    if (!getIndex(element, idx)){
        return false;
    }
    delete data[idx];
    availability_array[idx] = 0;
    curr_size--;
    return true;

}


template <class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::getCount() const {
    int count = 0;
    for(unsigned int i = 0; i < max_size; i++){
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

    if (!getIndex(element, idx)){
        return NULL;
    } else{
        return data[idx];
    }
}


template <class Element, class Compare>
UniqueArray<Element, Compare> UniqueArray<Element, Compare>::filter(const Filter& f) const{
    UniqueArray ua (*this);
    for(unsigned int i = 0; i < ua.max_size; i++){
        if(!f(*ua.data[i])){
            ua.remove(*ua.data[i]);
        }
    }
    return ua;
}


template <class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::getFirstEmptyLocation() {
    for(unsigned int i = 0; i < max_size; i++){
        if(availability_array[i] == 0){
            return i;
        }
    }
    return max_size;
}


template <class Element, class Compare>
const Element* UniqueArray<Element, Compare>::getElementByIndex(
        unsigned int index) const {
    return data[index];
}



template <class Element, class Compare>
UniqueArray<Element, Compare>::UniqueArray(const UniqueArray& ua1, const UniqueArray& ua2, const UniqueArray& ua3):
data(new Element*[ua1.max_size + ua2.max_size + ua3.max_size]), curr_size(ua1.curr_size + ua2.curr_size + ua3.curr_size), max_size(ua1.max_size + ua2.max_size + ua3.max_size), availability_array(new int[ua1.max_size + ua2.max_size + ua3.max_size]){
    for(unsigned int i = 0; i < ua1.max_size; i++){
        if(ua1.availability_array[i] == 1) {
            data[i] = new Element(*ua1.data[i]);
        }
        else{
            data[i] = nullptr;
        }
        availability_array[i] = ua1.availability_array[i];
    }
    for(unsigned int j = ua1.max_size; j < ua1.max_size + ua2.max_size; j++){
        if(ua2.availability_array[j - ua1.max_size] == 1) {
            data[j] = new Element(*ua1.data[j - ua1.max_size]);
        }
        else{
            data[j] = nullptr;
        }
        availability_array[j] = ua1.availability_array[j - ua1.max_size];
    }
    for(unsigned int k = ua1.max_size + ua2.max_size; k < ua1.max_size + ua2.max_size + ua3.max_size; k++){
        if(ua1.availability_array[k - (ua1.max_size + ua2.max_size)] == 1) {
            data[k] = new Element(*ua1.data[k - (ua1.max_size + ua2.max_size)]);
        }
        else{
            data[k] = nullptr;
        }
        availability_array[k] = ua1.availability_array[k - (ua1.max_size + ua2.max_size)];
    }
}
#endif //EX3_MTM_UNIQUEARRAYIMP_H
