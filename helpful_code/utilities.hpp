#include <algorithm>
#include <numeric>
#include <limits>
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
using std::vector;

template<typename T>
constexpr pair<T, T> MinPair() {
    return make_pair(numeric_limits<T>::min(), numeric_limits<T>::min());
}

template<typename T>
constexpr pair<T, T> MaxPair() {
    return make_pair(numeric_limits<T>::max(), numeric_limits<T>::max());
}

template<typename T>
T Min(const vector<T>& v) {
    CheckNotEmpty(v);
    T answer = v[0];
    for (const T& t : v) {
        answer = min(answer, t);
    }
    return answer;
}
template<typename T>
T Max(const vector<T>& v) {
    CheckNotEmpty(v);
    T answer = v[0];
    for (const T& t : v) {
        answer = max(answer, t);
    }
    return answer;
}

template<typename T>
pair<T,T> MinCoordinates(const pair<T,T>& p1, const pair<T,T>& p2) {
    return make_pair(min<T>(p1.first, p2.first), min<T>(p1.second, p2.second));
}

template<typename T>
pair<T,T> MaxCoordinates(const pair<T,T>& p1, const pair<T,T>& p2) {
    return make_pair(max<T>(p1.first, p2.first), max<T>(p1.second, p2.second));
}

VVI Vector2D(const UI outer_size, const UI inner_size, const int init_value = 0) {
    return VVI(outer_size, VI(inner_size, init_value));
}

vector<VVI> Vector3D(const UI size1, const UI size2, const UI size3,
        const int init_value = 0) {
    return vector<VVI>(size1, Vector2D(size2, size3, init_value));
}

template<typename T>
T Add(const vector<T>& v, const T initial = 0) {
    return accumulate(v.begin(), v.end(), initial);
}
