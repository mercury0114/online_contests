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

namespace {
    constexpr LL MAX_STRING_LENGTH = 200000;
}

void Print(const VLL& v) {
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

void AnswerVector(LL Case, const VLL& v) {
    printf("Case #%lld:", Case);
    for (const LL e : v) {
        printf(" %lld", e);
    }
    printf("\n");
}

void ScanElement(LL* const N) {
    scanf("%lld", N);
}

void ScanElement(string* const s) {
    char buffer[MAX_STRING_LENGTH];
    scanf("%s", buffer);
    *s = buffer;
}

void ScanElement(PLL* const p) {
    scanf("%lld %lld", &p->first, &p->second);
}

PLL ScanPLL() {
    PLL p;
    ScanElement(&p);
    return p;
}

LL ScanLL() {
    LL element;
    scanf("%lld", &element);
    return element;
}

string ScanString(const LL max_length = MAX_STRING_LENGTH) {
    char buffer[max_length];
    scanf("%s", buffer);
    return string(buffer);
}

template <typename T>
vector<T> ScanVector(const LL size) {
    vector<T> v(size);
    for (LL i = 0; i < size; i++) {
        ScanElement(&v[i]);
    }
    return v;
}

template<typename T>
vector<T> ScanVector(void) {
    LL N = ScanLL();
    return ScanVector<T>(N);
}
