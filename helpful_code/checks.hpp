#include <cstdio>
#include <iostream>
#include <vector>
#include <helpful_code/typedefs.hpp>

using std::cout;
using std::endl;
using std::vector;

template<typename T>
void CheckNotEmpty(const vector<T>& v) {
    if (v.size() == 0) {
        printf("ERROR: vector should not be empty\n");
        exit(EXIT_FAILURE);
    }
}

template<typename T>
void CheckNotGreater(const T a, const T b) {
    if (a > b) {
        cout << "ERROR: " << a << " > " << b << endl;
        exit(EXIT_FAILURE);
    }
}

template<typename T>
void CheckValidIndex(const UI index, const vector<T>& v) {
    if (index >= v.size()) {
        cout << "ERROR: " << index << " out of range [0, " << v.size()-1 << "]" << endl;
        exit(EXIT_FAILURE);
    }
}
