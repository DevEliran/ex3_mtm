#include <cassert>
#include <functional>
#include <iostream>
#include <cmath>
#include "../UniqueArray.h"

class Point {
private:
    double x, y;
public:
    Point(double x, double y) : x(x), y(y) {}
    bool operator==(const Point& point) const {
        return (point.x == this->x) && (point.y == this->y);
    }
};

static void testPoint() {
    typedef UniqueArray<Point, std::equal_to<Point>> PointUA;
    unsigned int size = 2;
    // Test ctor on complex struct (without default ctor)
    PointUA ua(size);
    ua.insert(Point(4,5));
    ua.insert(Point(2,3));
    // Test Remove
    ua.remove(Point(2,3));
    assert(ua.getCount() == 1);
}

static void testIntP() {
    struct CompareIntP {
        bool operator() (int* p1, int* p2) const {
            return (*p1 == *p2);
        }
    };
    typedef UniqueArray<int*, CompareIntP> intPUA;
    const int size = 5;
    int* array = new int[size]{3, 25, 17, 9, 35};
    intPUA ua1(size);
    for (int i = 0; i < size; i++) {
        ua1.insert(&array[i]);
    }
    // Test Copy Ctor
    intPUA ua2(ua1);
    assert(ua2.getCount() == ua1.getCount());
    // Test getIndex
    unsigned int index1;
    unsigned int index2;
    assert(ua1.getIndex(&array[0], index1));
    assert(ua2.getIndex(&array[0], index2));
    assert(index1 == index2);
    // Test operator[]
    int* const * ptr1 = ua1[&array[0]];
    int* const * ptr2 = ua2[&array[0]];
    assert(ptr1 != nullptr && ptr2 != nullptr);
    assert(ptr1 != ptr2);
    assert((*ptr1 == *ptr2) && (*ptr1 == &array[0]));
    // Test filter
    class LessThan20 : public intPUA::Filter {
    public:
        virtual bool operator() (int* const & element) const override {
            return *element < 20;
        }
    };
    intPUA filtered = ua1.filter(LessThan20());
    assert(filtered.getCount() == 3);
    assert(!filtered.getIndex(&array[4], index1)); // & of 35
    assert(filtered.getIndex(&array[2], index1)); // & of 17
}

static void testInt() {
    typedef UniqueArray<int, std::equal_to<int>> intUA;
    // Test ctor
    unsigned int size = 4;
    intUA ua(size);
    assert(ua.getSize() == size);
    assert(ua.getCount() == 0);
    // Test insert
    ua.insert(4);
    unsigned int index = ua.insert(1);
    ua.insert(5);
    assert(ua.insert(1) == index);
    ua.insert(2);
    assert(ua.getCount() == 4);
    ua.insert(2);
    // Test UniqueArrayIsFullException
    try {
        ua.insert(3);
    }
    catch (intUA::UniqueArrayIsFullException& e) {
        return;
    }
    assert(0);
}

int main() {
    #ifndef NDEBUG
        testInt();
        testIntP();
        testPoint();
        std::cout << "All tests finished successfully!" << std::endl;
    #endif
    return 0;
}