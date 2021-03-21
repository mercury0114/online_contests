#include <cstdio>

#include <helpful_code/utilities.hpp>

void CheckModNegative() {
    printf("Starting CheckModNegative\n");
    CheckEqual(ModN(-7, 8), 1);
    CheckEqual(ModN(-16, 8), 0);
    printf("Finished CheckModNegative\n\n");
}

void CheckIncreasingHistogram() {
    printf("Starting CheckHistogram\n");
    VLL histogram = {1, 2, 3, 4, 5};
    CheckEqual(LargestHistogramArea(histogram), 9);
    printf("Finished CheckHistogram\n\n");
}

void CheckDecreasingHistogram() {
    printf("Starting CheckDecreasingHistogram\n");
    VLL histogram = {5, 4, 3, 2, 1, 0};
    CheckEqual(LargestHistogramArea(histogram), 9);
    printf("Finished CheckDecreasingHistogram\n\n");
}

void CheckConvexHistogram() {
    printf("Starting CheckConvexHistogram\n");
    VLL histogram = {5, 4, 3, 2, 3, 4, 5};
    CheckEqual(LargestHistogramArea(histogram), 14);
    printf("Finished CheckConvexHistogram\n\n");
}

void CheckConcaveHistogram() {
    printf("Starting CheckConcaveHistogram\n");
    VLL histogram = {0, 1, 2, 3, 4, 5, 4, 3, 2, 1, 0};
    CheckEqual(LargestHistogramArea(histogram), 15);
    printf("Finished CheckConcaveHistogram\n\n");

}

int main() {
    CheckModNegative();
    CheckIncreasingHistogram();
    CheckDecreasingHistogram();
    CheckConvexHistogram();
    CheckConcaveHistogram();
    return 0;
}
