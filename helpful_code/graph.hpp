#include <helpful_code/typedefs.hpp>

// N = distances.size()
// time: O(N^3)
// space: O(1)
void FloydWarshall(VVLL& distances) {
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

bool Augment(const VVLL& bipartite, const VLL& match, VB& visited, VLL& path) {
    for (int i = 0; i < bipartite[path.back()].size(); i++) {
        LL v = bipartite[path.back()][i];
        if (not visited[v]) {
            visited[v] = true;
            path.push_back(v);
            if (match[v] == -1) {
                return true;
            }
            visited[match[v]] = true;
            path.push_back(match[v]);
            if (Augment(bipartite, match, visited, path)) {
                return true;
            }
            path.pop_back();
            path.pop_back();
        }
    }
    return false;
}

// input: bipartite is adjacency list
// output: MaxMatching[v] == -1 means that vertex v is unmatched
//         MaxMatching[v] ==  u means that vertex v is matched with u
// time: O(V * (V+E)), but not sure, could be worse
// space: O(V)
VLL MaxMatching(const VVLL& bipartite) {
    VLL match(bipartite.size(), -1);
    while (true) {
        VB visited(bipartite.size(), false);
        VLL path;
        for (int i = 0; i < bipartite.size() and path.empty(); i++) {
            if (match[i] == -1) {
                path.push_back(i);
                if (Augment(bipartite, match, visited, path)) {
                    for (int i = 1; i < path.size(); i += 2) {
                        match[path[i-1]] = path[i];
                        match[path[i]] = path[i-1];
                    }
                }
                path.pop_back();
            }
        }
        if (path.empty()) {
            break;
        }
    }
    return match;
}
