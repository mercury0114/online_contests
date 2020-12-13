#include <algorithm>
#include <numeric>
#include <helpful_code/typedefs.hpp>

using std::sort;
using std::vector;

VVL Vector2D(const LL outer_size, const LL inner_size, const int init_value = 0) {
    return VVL(outer_size, VL(inner_size, init_value));
}

vector<VVL> Vector3D(const LL size1, const LL size2, const LL size3,
        const LL init_value = 0) {
    return vector<VVL>(size1, Vector2D(size2, size3, init_value));
}

LL Add(const VL& v, const LL initial = 0LL) {
    return accumulate(v.begin(), v.end(), initial);
}

template<typename T>
LL FindLastLessEqual(const vector<T>& v, const T element) {
    return upper_bound(v.begin(), v.end(), element) - v.begin() - 1;
}

template<typename T>
LL FindLastLess(const vector<T>& v, const T element) {
    return lower_bound(v.begin(), v.end(), element) - v.begin() - 1;
}

template<typename T>
vector<T> IndexSort(const vector<T>& v) {
    vector<T> indices(v.size(), 0);
    for (LL i = 0; i < indices.size(); i++) {
        indices[i] = i;
    }
    sort(indices.begin(), indices.end(), [v](const T i1, const T i2) {
        return v[i1] < v[i2];});
    return indices;
}
