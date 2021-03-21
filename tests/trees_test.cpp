#include <cstdio>
#include <map>
#include <vector>
#include <helpful_code/checks.hpp>
#include <helpful_code/trees.hpp>
#include <helpful_code/typedefs.hpp>

using std::map;
using std::vector;

void CheckEmptyIntervalTree() {
    printf("Starting CheckEmptyIntervalTree\n");
    IntervalTree tree;
    tree.Add(101, 102);
    tree.Remove(100, 102);
    CheckEqual(tree.intervals.size(), 0);
    tree.Remove(100, 103);
    CheckEqual(tree.intervals.size(), 0);
    printf("Finished CheckEmptyIntervalTree\n\n");
}

void CheckIntervalTree() {
    printf("Starting CheckIntervalTree\n");
    IntervalTree tree;
    tree.Add(0, 10);
    tree.Add(20, 30);
    tree.Remove(25, 28);
    tree.Add(25, 28);
    tree.Add(40, 50);
    tree.Add(60, 70);
    tree.Add(80, 90);
    tree.Remove(40, 65);
    vector<PLL> remaining = {{0, 10}, {20, 30}, {65, 70}, {80, 90}};
    LL i = 0;
    for (const PLL& interval : tree.intervals) {
        CheckEqual(interval.first, remaining[i].first);
        CheckEqual(interval.second, remaining[i].second);
        i++;
    }
    printf("Finished CheckIntervalTree\n\n");
}

void CheckFenwickTreeUpTo() {
    printf("Starting CheckFenwickTreeUpTo\n");
    FenwickTree tree(10);
    tree.Add(1, 1);
    tree.Add(2, 1);
    CheckEqual(tree.SumUpTo(1), 1);
    CheckEqual(tree.SumUpTo(2), 2);
    printf("Finished CheckFenwickTreeUpTo\n\n");
}

void CheckFenwickTreeFrom() {
    printf("Starting CheckFenwickTreeFrom\n");
    FenwickTree tree(10);
    tree.Add(1, 1);
    tree.Add(10, 10);
    CheckEqual(tree.SumFrom(1), 11);
    CheckEqual(tree.SumFrom(2), 10);
    printf("Finished CheckFenwickTreeFrom\n\n");
}

void CheckKDTree() {
    printf("Starting CheckKDTree\n");
    vector<PLL> points = {make_pair(0, 0), make_pair(10, 10)};
    KDTree tree(points);
    CheckEqual(tree.Count(points[0]), 2);
    CheckEqual(tree.Count(points[1]), 1);
    printf("Finished CheckKDTree\n\n");
}

void CheckSegmentTreeMax() {
    printf("Starting CheckSegmentTreeMax\n");
    VLL elements = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    SegmentTree tree(elements);
    tree.TrackMax();
    CheckEqual(tree.Max(0, 3), 3);
    CheckEqual(tree.Max(2, 5), 5);
    tree.Update(4, 10);
    CheckEqual(tree.Max(0, 8), 10);
    tree.Update(4, 1);
    CheckEqual(tree.Max(0, 4), 3);
    printf("Finished CheckSegmentTreeMax\n\n");
}

void CheckSegmentTreeMin() {
    printf("Starting CheckSegmentTreeMin\n");
    VLL elements = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    SegmentTree tree(elements);
    tree.TrackMin();
    CheckEqual(tree.Min(2, 5), 2);
    CheckEqual(tree.Min(0, 4), 0);
    tree.Update(0, 3);
    CheckEqual(tree.Min(0, 4), 1);
    tree.Update(7, -1);
    CheckEqual(tree.Min(2, 7), -1);
    printf("Finished CheckSegmentTreeMin\n\n");
}

void CheckSegmentTreeSum() {
    printf("Starting CheckSegmentTreeSum\n");
    VLL elements = {1, 1, 1, 1, 1, 1};
    SegmentTree tree(elements);
    tree.TrackSum();
    CheckEqual(tree.Sum(2, 4), 3);
    CheckEqual(tree.Sum(0, 5), 6);
    tree.Update(1, 0);
    CheckEqual(tree.Sum(0, 5), 5);
    CheckEqual(tree.Sum(1, 1), 0);
    tree.Update(3, -1);
    CheckEqual(tree.Sum(1, 3), 0);
    printf("Finished CheckSegmentTreeSum\n\n");
}

void CheckSegmentTreeMaxPrefixSum() {
    printf("Starting CheckSegmentTreeMaxPrefixSum\n");
    VLL elements = {1, -1, 1, -1, 1, -1, 1};
    SegmentTree tree(elements);
    tree.TrackSum();
    tree.TrackMaxPrefixSum();
    CheckEqual(tree.MaxPrefixSum(0, 2), 1);
    CheckEqual(tree.MaxPrefixSum(0, 6), 1);
    CheckEqual(tree.MaxPrefixSum(1, 1), 0);
    CheckEqual(tree.MaxPrefixSum(2, 5), 1);
    tree.Update(4, 4);
    CheckEqual(tree.MaxPrefixSum(0, 5), 4); 
    tree.Update(5, 0);
    CheckEqual(tree.MaxPrefixSum(0, 6), 5);
    printf("Finished CheckSegmentTreeMaxPrefixSum\n\n");
}

int main() {
    CheckEmptyIntervalTree();
    CheckIntervalTree();
    CheckFenwickTreeUpTo();
    CheckFenwickTreeFrom();
    CheckKDTree();
    CheckSegmentTreeMax();
    CheckSegmentTreeMin();
    CheckSegmentTreeSum();
    CheckSegmentTreeMaxPrefixSum();
    return 0;
}
