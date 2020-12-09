#include <vector>
#include <helpful_code/checks.hpp>
#include <helpful_code/typedefs.hpp>
#include <helpful_code/utilities.hpp>

using std::pair;
using std::vector;

template<typename T>
class FenwickTree {
public:
    // time: O(1)
    // space: O(largest_element)
    FenwickTree(UI largest_element): tree_(largest_element + 1) {}

    // time: O(log(largest_element))
    // space: O(1)
    void Add(UI element, T count) {
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
    T SumUpTo(UI up_to) const {
        CheckValidIndex(up_to, tree_);
        T sum = 0;
        while (up_to > 0) {
            sum += tree_[up_to];
            up_to -= LastBit(up_to);
        }
        return sum;
    }

    // time: O(log(from))
    // space: O(1)
    T SumFrom(const UI from) const {
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

    T sum_all_ = 0;
    // tree_ is indexed from 1
    vector<T> tree_;
};

// Implemented for K = 2 dimensions
// N = points_.size(), the number of points a tree stores (see comments below)
template<typename T>
class KDTree {
public:
    // time: O(N*log(N)*log(N))
    // space: O(N)
    // Note: to improve the time complexity to O(N), remove the "sort" in the Construct method.
    // Eliminating sort does not break the correctness! This will, however, increase the Count method
    // worst case complexity from O(sqrt(N)) to O(N), although the worst case is rarely observed.
    KDTree(const vector<pair<T, T>>& points): points_(points),
                                              min_coordinates_(points),
                                              max_coordinates_(points) {
        CheckNotEmpty(points);
        Construct(Coordinate::X, 0, points_.size()-1);    
    }

    // time: O(sqrt(N)) worst case, O(log(N)) average case
    // space: O(log(N))
    UI Count(const pair<T,T>& from) const {
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
        bool operator() (const pair<T,T>& p1, const pair<T,T>& p2) const {
            switch (coordinate_) {
                case X:
                    return p1.first < p2.first;
                case Y:
                    return p1.second < p2.second;
            }
        }
        const Coordinate coordinate_;
    };

    UI Count(const pair<T,T>& range, const UI begin, const UI end) const {
        CheckNotGreater(begin, end);
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

    pair<pair<T,T>, pair<T,T>> Construct(Coordinate coordinate, UI begin, UI end) {
        CheckNotGreater(begin, end);
        if (begin == end) {
            return make_pair(points_[begin], points_[begin]);
        }
        // NOTE: sort can be eliminated to improve the Construct time complexity
        // at the cost of degrading the Count time complexity.
        sort(&points_[begin], &points_[end+1], Comparator(coordinate));

        const Coordinate next_coordinate = (coordinate == X) ? Y : X;
        const UI middle = (begin + end) / 2;
        pair<pair<T,T>,pair<T,T>> left = Construct(next_coordinate, begin, middle);
        pair<pair<T,T>,pair<T,T>> right = Construct(next_coordinate, middle+1, end);
        min_coordinates_[middle] = MinCoordinates(left.first, right.first);
        max_coordinates_[middle] = MaxCoordinates(left.second, right.second);
        return make_pair(min_coordinates_[middle], max_coordinates_[middle]);
    }

    vector<pair<T,T>> points_;
    vector<pair<T,T>> min_coordinates_;
    vector<pair<T,T>> max_coordinates_;
};
