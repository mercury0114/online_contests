#pragma once

#include <cstdio>
#include <iostream>
#include <vector>
#include <helpful_code/typedefs.hpp>

using std::cout;
using std::endl;
using std::vector;

void CheckLess(const LL a, const LL b) {
    if (a >= b) {
        cout << "ERROR: not " << a << " < " << b << endl;
        exit(EXIT_FAILURE);
    }
}

void CheckLessEq(const LL a, const LL b) {
    if (a > b) {
        cout << "ERROR: not " << a << " <= " << b << endl;
        exit(EXIT_FAILURE);
    }
}

void CheckValidIndex(const LL index, const VLL& v) {
    if (index >= v.size() || index < 0) {
        cout << "ERROR: " << index << " out of range [0, " << v.size()-1 << "]" << endl;
        exit(EXIT_FAILURE);
    }
}

void CheckNotZero(const LL number) {
    if (number == 0) {
        cout << "ERROR: number is 0" << endl;
        exit(EXIT_FAILURE);
    }
}

void CheckEqual(const LL actual, const LL expected) {
    if (actual != expected) {
        cout << "ERROR: " << actual << " != " << expected << endl;
        exit(EXIT_FAILURE);
    }
}

template<typename T>
void CheckNotEmpty(const vector<T>& v) {
    if (v.size() == 0) {
        printf("ERROR: vector should not be empty\n");
        exit(EXIT_FAILURE);
    }
}
