#include <helpful_code/typedefs.hpp>

// N = distances.size()
// time: O(N^3)
// space: O(1)
void FloydWarshall(VVI& distances) {
    for (UI k = 0; k < distances.size(); k++) {
        for (UI i = 0; i < distances.size(); i++) {
            for (UI j = 0; j < distances.size(); j++) {
                const int sum = distances[i][k] + distances[k][j];
                if (distances[i][j] > sum) {
                    distances[i][j] = sum;
                }
            }
        }
    }
}
