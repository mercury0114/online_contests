#include <iostream>
#include <vector>
#include <utility>
#include <helpful_code/typedefs.hpp>

using std::cout;
using std::endl;
using std::vector;
using std::pair;

template<typename T>
void Print(const vector<T>& v) {
    for (const T element : v) {
        cout << element << " ";
    }
    cout << endl;
}

template<typename T>
void Print(const pair<T, T>& p) {
    cout << "(" << p.first << "," << p.second << ")" << endl;
}

template<typename T>
void Print(const vector<pair<T, T>>& v) {
    for (const pair<T, T>& p : v) {
        cout << "(" << p.first << "," << p.second << ") ";
    }
    cout << endl;
}
