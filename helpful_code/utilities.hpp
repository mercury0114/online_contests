#pragma once

#include <algorithm>
#include <numeric>
#include <limits>
#include <stack>
#include <utility>
#include <vector>

#include <helpful_code/checks.hpp>
#include <helpful_code/typedefs.hpp>

using std::accumulate;
using std::max;
using std::min;
using std::make_pair;
using std::numeric_limits;
using std::pair;
using std::stack;
using std::vector;

LL Min(LL a, LL b, LL c) {
    return min(a, min(b, c));
}

LL Max(LL a, LL b, LL c) {
    return max(a, max(b, c));
}

LL Min(LL a, LL b, LL c, LL d) {
    return min(Min(a, b, c), d);
}

LL Max(LL a, LL b, LL c, LL d) {
    return max(Max(a, b, c), d);
}

LL ModN(const LL number, const LL N) {
    CheckNotZero(N);
    if (number >= 0) {
        return number % N;
    }
    return (N - (-number % N)) % N;
}

template<typename T>
constexpr pair<T, T> MinPair() {
    return make_pair(numeric_limits<T>::min(), numeric_limits<T>::min());
}

template<typename T>
constexpr pair<T, T> MaxPair() {
    return make_pair(numeric_limits<T>::max(), numeric_limits<T>::max());
}

template<typename T>
pair<T,T> MinCoordinates(const pair<T,T>& p1, const pair<T,T>& p2) {
    return make_pair(min<T>(p1.first, p2.first), min<T>(p1.second, p2.second));
}

template<typename T>
pair<T,T> MaxCoordinates(const pair<T,T>& p1, const pair<T,T>& p2) {
    return make_pair(max<T>(p1.first, p2.first), max<T>(p1.second, p2.second));
}

VLL LPS(const string& s) {
    VLL prefix(s.size(), 0);
    for (LL i = 1; i < s.size(); i++) {
        LL j = prefix[i-1];
        while (j > 0 and s[j] != s[i]) {
            j = prefix[j-1];
        }
        prefix[i] = j + (s[j] == s[i]);
    }
    return prefix;
}

// histrogram entries have to be non-negative
// time: O(N)
// space: O(N)
LL LargestHistogramArea(const VLL& histogram) {
    VLL extended(histogram.size()+2);
    extended[0] = -2;
    for (LL h = 0; h < histogram.size(); h++) {
        extended[h+1] = histogram[h];
    }
    extended[histogram.size()+1] = -1;

    LL largest = 0;
    stack<LL> s;
    s.push(0);
    for (LL e = 1; e < extended.size(); e++) {
        while (extended[s.top()] >= extended[e]) {
            LL height = extended[s.top()];
            s.pop();
            largest = max(largest, height * (e-1 - s.top()));
        }
        s.push(e);
    }
    return largest;
}

