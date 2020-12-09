#include <cstdio>
#include <string>
#include <vector>
#include <helpful_code/typedefs.hpp>

using std::vector;

void ScanElement(int* const N) {
    scanf("%d", N);
}

void ScanElement(LL* const N) {
    scanf("%lld", N);
}

void ScanElement(string* const s) {
    char buffer[1000];
    scanf("%s", buffer);
    *s = buffer;
}

void ScanElement(PII* const pii) {
    scanf("%d %d", &pii->first, &pii->second);
}

template <typename T>
vector<T> Scan(const UI size) {
    vector<T> v(size);
    for (UI i = 0; i < size; i++) {
        ScanElement(&v[i]);
    }
    return v;
}

template<typename T>
vector<T> Scan(void) {
    UI N;
    scanf("%u", &N);
    return Scan<T>(N);
}
