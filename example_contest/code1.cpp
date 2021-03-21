// Solution to the 1st problem of the Google KickStart 2021 round A

#include <helpful_code/io.hpp>

int main() {
    LL T = ScanLL();
    for (LL Case = 1; Case <= T; Case++) {
        LL N = ScanLL(), K = ScanLL();
        string s = ScanString();
        LL score = 0;
        for (int i = 0; i < s.size() / 2; i++) {
            score += (s[i] != s[s.size()-1-i]);
        }
        printf("Case #%lld: %lld\n", Case, llabs(K - score));
    }

}
