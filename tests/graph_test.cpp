#include <cstdio>

#include <helpful_code/checks.hpp>
#include <helpful_code/graph.hpp>

void CheckMatchFound() {
    printf("Starting CheckMatchFound\n");
    VVLL bipartite = {{1,3}, {0, 2}, {1, 3}, {0, 2}};
    VLL matching = MaxMatching(bipartite);
    LL unmatched = count(matching.begin(), matching.end(), -1);
    CheckEqual(unmatched, 0);
    printf("Finished CheckMatchFound\n\n");
}

int main() {
    CheckMatchFound();
    return 0;
}
