#include <cstdio>
#include <vector>
#include <helpful_code/checks.hpp>
#include <helpful_code/trees.hpp>
#include <helpful_code/typedefs.hpp>

using std::vector;

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

int main() {
    CheckFenwickTreeUpTo();
    CheckFenwickTreeFrom();
    CheckKDTree();
    return 0;
}
