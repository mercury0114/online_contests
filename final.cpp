#include <limits>
#include <string>
#include <utility>
#include <vector>
using std::numeric_limits;
using std::pair;
using std::string;
using std::vector;


typedef unsigned int UI;
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<LL, LL> PLL;
typedef vector<bool> VB;
typedef vector<int> VI;
typedef vector<LL> VLL;
typedef vector<std::string> VS;
typedef vector<VI> VVI;


// time: O(up_to * log(log(up_to)))
// space: O(up_to)
VB Sieve(const UI up_to) {
    VB prime(up_to+1, true);
    prime[0] = prime[1] = false;
    for (UI i = 2; i * i <= up_to; i++) {
        if (prime[i]) {
            for (UI j = i * i; j <= up_to; j += i) {
                prime[j] = false;
            }
        }
    }
    return prime;
}

// K = repeat (see comments below)
class PrimeChecker {
public:
    PrimeChecker(const UI repeat = 20, const UI seed = 1): repeat_(repeat), seed_(seed) {}

    // If n is prime, the function will always return true.
    // If n is even composite, the function will always return false.
    // If n is odd composite, the function will return false with probability >= 1-2^(-K)
    // Changes seed_ each time
    // time: O(K * log(N))
    // space: O(1)
    bool Prime(const UI n) {
        switch (n) {
            case 0: return false;
            case 1: return false;
            case 2: return true;
            case 3: return true;
            default: return n % 2 == 1 and MillerRabin(n);
        }
    }

private:
    // variable names copied from Wikipedia's article:
    // https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test
    bool MillerRabin(const UI N) {
        UI d = N-1, r = 0;
        while (!(d & 1)) {
            r++;
            d >>= 1;
        }
        // From now on: N-1 = 2^r * d.

        for (int k = 0; k < repeat_; k++) {
            // setting seed to a new pseudo-random value
            seed_ = ((seed_ ^ 0x66778899AABBCCDD) + 23) * 17;
            UI a = seed_ % (N-3) + 2;
            LL x = PowerModN(a, d, N);
            if (x == 1 or x == N-1) continue;
            UI repeat_number = 0;
            while (repeat_number < r-1) {
                x = (x * x) % N;
                if (x == N-1) break;
                repeat_number++;
            }
            if (repeat_number == r-1) return false;
        }
        return true;
    }

    LL PowerModN(const UI a, const UI d, const UI N) const {
        LL answer = 1;
        for (int i = numeric_limits<LL>::digits-1; i >= 0; i--) {
            answer = (answer * answer) % N;
            if ((1LL << i) & d) {
                answer = (answer * a) % N;
            }
        }
        return answer;
    }

    UI seed_;
    const UI repeat_;
};


bool Interesting(const int X, PrimeChecker& checker) {
    if (X == 1 || X == 4) {
        return true;
    }
    if (checker.Prime(X)) {
        return true;
    }
    if (X % 2 == 0 and X % 4 != 0) {
        return true;
    }
    if (X % 4 == 0 and checker.Prime(X/4)) {
        return true;
    }
    return false;
}

int main() {
    PrimeChecker checker(20);

    int T;
    scanf("%d", &T);
    for (int Case = 1; Case <= T; Case++) {
        int L, R;
        scanf("%d %d", &L, &R);
        int count = 0;
        for (int X = L; X <= R; X++) {
            if (Interesting(X, checker)) {
                count++;
            }
        }
        printf("Case #%d: %d\n", Case, count);
    }

    return 0;
}
