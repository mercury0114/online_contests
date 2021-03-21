#pragma once

#include <map>
#include <vector>
#include <helpful_code/checks.hpp>
#include <helpful_code/io.hpp>
#include <helpful_code/typedefs.hpp>
#include <helpful_code/utilities.hpp>

using std::map;
using std::pair;
using std::prev;
using std::vector;

// TODO(add your own custom functionality)
class SegmentTree {
public:
    // time: O(N)
    // space: O(N)
    SegmentTree(const VLL& elements): elements_(elements) {
        CheckNotEmpty(elements);
    }

    // time: O(N)
    // space: O(N)
    void TrackMin() {
        min_ = elements_;
        ComputeMin(0, min_.size()-1);
    }

    // time: O(N)
    // space: O(N)
    void TrackMax() {
        max_ = elements_;
        ComputeMax(0, max_.size()-1);
    }

    // time: O(N)
    // space: O(N)
    void TrackSum() {
        sum_ = elements_;
        ComputeSum(0, sum_.size()-1);
    }

    // time: O(N)
    // space: O(N)
    void TrackMaxPrefixSum() {
        CheckNotEmpty(sum_);
        max_prefix_sum_ = elements_;
        ComputeMaxPrefixSum(0, elements_.size()-1);
    }

    // time: O(log(N))
    // space: O(log(N))
    LL Min(const UI from, const UI to) const {
        CheckNotEmpty(min_);
        CheckLessEq(from, to);
        return Min(from, to, 0, min_.size()-1);
    }

    // time: O(log(N))
    // space: O(log(N))
    LL Max(const LL from, const LL to) const {
        CheckNotEmpty(max_);
        CheckLessEq(from, to);
        return Max(from, to, 0, max_.size()-1);
    }

    // time: O(log(N))
    // space: O(log(N))
    LL Sum(const LL from, const LL to) const {
        CheckNotEmpty(sum_);
        CheckLessEq(from, to);
        return Sum(from, to, 0, sum_.size()-1);
    }

    // time: O(log(N))
    // space: O(log(N))
    LL MaxPrefixSum(const LL from, const LL to) const {
        CheckNotEmpty(sum_);
        CheckNotEmpty(max_prefix_sum_);
        return MaxPrefixSum(from, to, 0, sum_.size()-1).second;
    }

    // time: O(log(N)) * [number of things we're tracking]
    // space: O(log(N))
    void Update(const UI index, const LL value) {
        elements_[index] = value;
        if (min_.size() > 0) {
            UpdateMin(index, 0, elements_.size()-1);
        }
        if (max_.size() > 0) {
            UpdateMax(index, 0, elements_.size()-1);
        }
        if (sum_.size() > 0) {
            UpdateSum(index, 0, elements_.size()-1);
        }
        if (max_prefix_sum_.size() > 0) {
            UpdateMaxPrefixSum(index, 0, elements_.size()-1);
        }
    }

    // time: O(1)
    // space: O(1)
    LL Get(const UI index) const {
        return elements_[index];
    }

    // for debug only
    void Print() const {
        cout << "elements_: ", ::Print(elements_);
        if (min_.size()) {
            cout << "min_: ", ::Print(min_);
        }
        if (max_.size()) {
            cout << "max_: ", ::Print(max_);
        }
        if (sum_.size()) {
            cout << "sum_: ", ::Print(sum_);
        }
        if (max_prefix_sum_.size()) {
            cout << "max_prefix_sum_: ", ::Print(max_prefix_sum_);
        }
    }

private:
    LL ComputeMin(const LL begin, const LL end) {
        if (begin == end) {
            return elements_[begin];
        }
        const LL middle = (begin + end) / 2;
        min_[middle] = min(ComputeMin(begin, middle), ComputeMin(middle+1, end));
        return min_[middle];
    }

    LL ComputeMax(const LL begin, const LL end) {
        if (begin == end) {
            return elements_[begin];
        }
        const LL middle = (begin + end) / 2;
        max_[middle] = max(ComputeMax(begin, middle), ComputeMax(middle+1, end));
        return max_[middle];
    }

    LL ComputeSum(const LL begin, const LL end) {
        if (begin == end) {
            return elements_[begin];
        }
        const LL middle = (begin + end) / 2;
        sum_[middle] = ComputeSum(begin, middle) + ComputeSum(middle+1, end);
        return sum_[middle];
    }

    LL ComputeMaxPrefixSum(const LL begin, const LL end) {
        if (begin == end) {
            return max(0LL, elements_[begin]);
        }
        const LL middle = (begin + end) / 2;
        const LL left_sum = ComputeMaxPrefixSum(begin, middle);
        const LL right_sum = ComputeMaxPrefixSum(middle+1, end);
        max_prefix_sum_[middle] = max(left_sum,
                                      Sum(begin, middle, begin, middle) + right_sum);
        return max_prefix_sum_[middle];
    }

    LL Min(const LL from, const LL to, const LL begin, const LL end) const {
        if (begin == end) {
            return elements_[begin];
        }
        const LL middle = (begin + end) / 2;
        if (to <= middle) {
            return Min(from, to, begin, middle);
        }
        if (from > middle) {
            return Min(from, to, middle+1, end);
        }
        if (from == begin and end == to) {
            return min_[middle];
        }
        return min(Min(from, middle, begin, middle),
                   Min(middle+1, to, middle+1, end));
    }

    LL Max(const LL from, const LL to, const LL begin, const LL end) const {
        if (begin == end) {
            return elements_[begin];
        }
        const LL middle = (begin + end) / 2;
        if (to <= middle) {
            return Max(from, to, begin, middle);
        }
        if (from > middle) {
            return Max(from, to, middle+1, end);
        }
        if (from == begin and end == to) {
            return max_[middle];
        }
        return max(Max(from, middle, begin, middle),
                   Max(middle+1, to, middle+1, end));
    }

    LL Sum(const LL from, const LL to, const LL begin, const LL end) const {
        if (begin == end) {
            return elements_[begin];
        }
        const LL middle = (begin + end) / 2;
        if (to <= middle) {
            return Sum(from, to, begin, middle);
        }
        if (from > middle) {
            return Sum(from, to, middle+1, end);
        }
        if (from == begin and to == end) {
            return sum_[middle];
        }
        return Sum(from, middle, begin, middle) +
               Sum(middle+1, to, middle+1, end);
    }

    PLL MaxPrefixSum(const LL from, const LL to, const LL begin, const LL end) const {
        if (begin == end) {
            return make_pair(elements_[begin], max(0LL, elements_[begin]));
        }
        LL middle = (begin + end) / 2;
        if (from == begin and to == end) {
            return make_pair(sum_[middle], max_prefix_sum_[middle]);
        }
        if (from > middle) {
            return MaxPrefixSum(from, to, middle+1, end);
        }
        if (to <= middle) {
            return MaxPrefixSum(from, to, begin, middle);
        }
        const PLL left_sum_prefix = MaxPrefixSum(from, middle, begin, middle);
        const PLL right_sum_prefix = MaxPrefixSum(middle+1, to, middle+1, end);
        return make_pair(left_sum_prefix.first + right_sum_prefix.first,
                         max(left_sum_prefix.second,
                             left_sum_prefix.first + right_sum_prefix.second));
    }

    LL UpdateMin(const LL index, const LL begin, const LL end) {
        if (begin == end) {
            return elements_[begin];
        }
        const LL middle = (begin + end) / 2;
        if (index <= middle) {
            min_[middle] = min(UpdateMin(index, begin, middle), Min(middle+1, end,
                middle+1, end));
        } else {
            min_[middle] = min(UpdateMin(index, middle+1, end), Min(begin, middle,
                begin, middle));
        }
        return min_[middle];
    }

    LL UpdateMax(const LL index, const LL begin, const LL end) {
        if (begin == end) {
            return elements_[begin];
        }
        const LL middle = (begin + end) / 2;
        if (index <= middle) {
            max_[middle] = max(UpdateMax(index, begin, middle), Max(middle+1, end,
                middle+1, end));
        } else {
            max_[middle] = max(UpdateMax(index, middle+1, end), Max(begin, middle,
                begin, middle));
        }
        return max_[middle];
    }

    LL UpdateSum(const LL index, const LL begin, const LL end) {
        if (begin == end) {
            return elements_[begin];
        }
        const LL middle = (begin + end) / 2;
        if (index < begin || index > end) {
            return sum_[middle];
        }
        sum_[middle] = UpdateSum(index, begin, middle) + UpdateSum(index, middle+1, end);
        return sum_[middle];
    }

    PLL UpdateMaxPrefixSum(const LL index, const LL begin, const LL end) {
        if (begin == end) {
            return make_pair(elements_[begin], max(0LL, elements_[begin]));
        }
        const LL middle = (begin + end) / 2;
        if (begin <= index and index <= end) {
            const PLL left_sum_prefix = UpdateMaxPrefixSum(index, begin, middle);
            const PLL right_sum_prefix = UpdateMaxPrefixSum(index, middle+1, end);
            max_prefix_sum_[middle] = max(left_sum_prefix.second,
                                  left_sum_prefix.first + right_sum_prefix.second);
        }
        return make_pair(sum_[middle], max_prefix_sum_[middle]);
    }
    
    vector<LL> elements_;
    vector<LL> min_, max_;
    vector<LL> sum_, max_prefix_sum_;
};

// Class holding a union of intervals [x1, y1), [x2, y2), ..., [xn, yn)
// N = intervals.size(), see comments below.
class IntervalTree {
public:
    // time: O(log(N)) amortised
    // space: O(1)
    void Add(const LL begin, const LL end) {
        if (intervals.empty()) {
            intervals[begin] = end;
            return;
        }

        auto it_begin = intervals.upper_bound(begin);
        LL new_begin = begin;
        if (it_begin != intervals.begin() and
                prev(it_begin)->second >= begin) {
            it_begin = std::prev(it_begin);
            new_begin = min(new_begin, it_begin->first);
        }

        auto it_end = intervals.upper_bound(end);
        LL new_end = it_end == intervals.begin() ? end : 
            max(end, prev(it_end)->second);
        intervals.erase(it_begin, it_end);
        intervals[new_begin] = new_end;
    }

    // time: O(log(N)) amortised
    // space: O(1)
    void Remove(const LL begin, const LL end) {
        vector<PLL> extra;
        auto it_begin = intervals.upper_bound(begin);
        if (it_begin != intervals.begin() and
                prev(it_begin)->second >= begin) {
            it_begin = prev(it_begin);
            extra.emplace_back(it_begin->first, begin);
        }
        auto it_end = intervals.upper_bound(end);
        if (it_end != intervals.begin()) {
            extra.emplace_back(end, prev(it_end)->second);
            intervals.erase(it_begin, it_end);
        }
        for (const PLL& interval : extra) {
            if (interval.first < interval.second) {
                intervals[interval.first] = interval.second;
            }
        }
    }

    map<LL, LL> intervals;
};

class FenwickTree {
public:
    // time: O(1)
    // space: O(largest_element)
    FenwickTree(UI largest_element): tree_(largest_element + 1) {}

    // time: O(log(largest_element))
    // space: O(1)
    void Add(UI element, LL count) {
        CheckValidIndex(element, tree_);
        while (element < tree_.size()) {
            tree_[element] += count;
            element += LastBit(element);
        }
        sum_all_ += count;
    }

    // returns count[1] + count[2] + ... + count[up_to]
    // time: O(log(up_to))
    // space: O(1)
    LL SumUpTo(UI up_to) const {
        CheckValidIndex(up_to, tree_);
        LL sum = 0;
        while (up_to > 0) {
            sum += tree_[up_to];
            up_to -= LastBit(up_to);
        }
        return sum;
    }

    // time: O(log(from))
    // space: O(1)
    LL SumFrom(const UI from) const {
        if (from == 0) {
            printf("ERROR: from can't be 0\n");
            exit(EXIT_FAILURE);
        }
        return sum_all_ - SumUpTo(from-1);
    }
private:
    UI LastBit(const UI element) const {
        return element & (-element);
    }

    LL sum_all_ = 0;
    // tree_ is indexed from 1
    VLL tree_;
};

// Implemented for K = 2 dimensions
// N = points_.size(), the number of points a tree stores (see comments below)
class KDTree {
public:
    // time: O(N*log(N)*log(N))
    // space: O(N)
    // Note: to improve the time complexity to O(N), remove the "sort" in the Construct method.
    // Eliminating sort does not break the correctness! This will, however, increase the Count method
    // worst case complexity from O(sqrt(N)) to O(N), although the worst case is rarely observed.
    KDTree(const vector<PLL>& points): points_(points),
                                              min_coordinates_(points),
                                              max_coordinates_(points) {
        CheckNotEmpty(points);
        Construct(Coordinate::X, 0, points_.size()-1);    
    }

    // time: O(sqrt(N)) worst case, O(log(N)) average case
    // space: O(log(N))
    LL Count(const PLL& from) const {
        return Count(from, 0, points_.size()-1);
    }

    // For debug only
    void Print() const {
        cout << "points_:          ", ::Print(points_);
        cout << "min_coordinates_: ", ::Print(min_coordinates_);
        cout << "max_coordinates_: ", ::Print(max_coordinates_);
    }

private:
    typedef enum {
        X = 0,
        Y = 1,
    } Coordinate;

    struct Comparator {
        Comparator(Coordinate coordinate): coordinate_(coordinate) {}
        bool operator() (const PLL& p1, const PLL& p2) const {
            switch (coordinate_) {
                case X:
                    return p1.first < p2.first;
                case Y:
                    return p1.second < p2.second;
                default:
                    printf("ERROR: Comparator received incorrect enum value\n");
                    exit(1);
            }
        }
        const Coordinate coordinate_;
    };

    LL Count(const PLL& range, const UI begin, const UI end) const {
        CheckLessEq(begin, end);
        if (begin == end) {
            return (points_[begin].first >= range.first and points_[begin].second >= range.second);
        }
        const UI middle = (begin + end) / 2;
        // If the subtree has no points to include
        if (max_coordinates_[middle].first < range.first or
            max_coordinates_[middle].second < range.second) {
            return 0;
        }
        // If the subtree has all points to include
        if (min_coordinates_[middle].first >= range.first and
            min_coordinates_[middle].second >= range.second) {
            return end - begin + 1;
        }
        return Count(range, begin, middle) + Count(range, middle+1, end);
    }

    pair<PLL, PLL> Construct(Coordinate coordinate, UI begin, UI end) {
        CheckLessEq(begin, end);
        if (begin == end) {
            return make_pair(points_[begin], points_[begin]);
        }
        // NOTE: sort can be eliminated to improve the Construct time complexity
        // at the cost of degrading the Count time complexity.
        sort(&points_[begin], &points_[end+1], Comparator(coordinate));

        const Coordinate next_coordinate = (coordinate == X) ? Y : X;
        const UI middle = (begin + end) / 2;
        pair<PLL, PLL> left = Construct(next_coordinate, begin, middle);
        pair<PLL, PLL> right = Construct(next_coordinate, middle+1, end);
        min_coordinates_[middle] = MinCoordinates(left.first, right.first);
        max_coordinates_[middle] = MaxCoordinates(left.second, right.second);
        return make_pair(min_coordinates_[middle], max_coordinates_[middle]);
    }

    vector<PLL> points_;
    vector<PLL> min_coordinates_;
    vector<PLL> max_coordinates_;
};
