#pragma once

#include <iostream>
#include <cstdio>
#include <string>
#include <utility>
#include <vector>
#include <helpful_code/typedefs.hpp>

using std::cout;
using std::endl;
using std::pair;
using std::vector;

void Print(const VL& v) {
    for (const LL element : v) {
        printf("%lld ", element);
    }
    printf("\n");
}

void Print(const PLL& p, bool endline = true) {
    printf("(%lld,%lld)", p.first, p.second);
    if (endline) {
        printf("\n");
    }

}

void Print(const vector<PLL>& v) {
    for (const PLL& p : v) {
        Print(p, false);
    }
    printf("\n");
}

void AnswerVector(LL Case, const VL& v) {
    printf("Case #%lld:", Case);
    for (const LL e : v) {
        printf(" %lld", e);
    }
    printf("\n");
}

LL ScanLL() {
    LL element;
    scanf("%lld", &element);
    return element;
}

void ScanElement(LL* const N) {
    scanf("%lld", N);
}

void ScanElement(string* const s) {
    char buffer[1000];
    scanf("%s", buffer);
    *s = buffer;
}

void ScanElement(PLL* const p) {
    scanf("%lld %lld", &p->first, &p->second);
}

template <typename T>
vector<T> Scan(const LL size) {
    vector<T> v(size);
    for (LL i = 0; i < size; i++) {
        ScanElement(&v[i]);
    }
    return v;
}

template<typename T>
vector<T> Scan(void) {
    LL N;
    scanf("%u", &N);
    return Scan<T>(N);
}
