#include <helpful_code/typedefs.hpp>

// N = distances.size()
// time: O(N^3)
// space: O(1)
void FloydWarshall(VVL& distances) {
    for (LL k = 0; k < distances.size(); k++) {
        for (LL i = 0; i < distances.size(); i++) {
            for (LL j = 0; j < distances.size(); j++) {
                const LL sum = distances[i][k] + distances[k][j];
                if (distances[i][j] > sum) {
                    distances[i][j] = sum;
                }
            }
        }
    }
}
