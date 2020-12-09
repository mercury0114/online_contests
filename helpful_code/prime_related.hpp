#include <limits>
#include <helpful_code/typedefs.hpp>

using std::numeric_limits;

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

