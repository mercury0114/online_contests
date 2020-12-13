#pragma once

#include <limits>
#include <helpful_code/typedefs.hpp>

using std::numeric_limits;

// time: O(up_to * log(log(up_to)))
// space: O(up_to)
VB Sieve(const LL up_to) {
    VB prime(up_to+1, true);
    prime[0] = prime[1] = false;
    for (LL i = 2; i * i <= up_to; i++) {
        if (prime[i]) {
            for (LL j = i * i; j <= up_to; j += i) {
                prime[j] = false;
            }
        }
    }
    return prime;
}

// K = repeat (see comments below)
class PrimeChecker {
public:
    PrimeChecker(LL repeat = 30, unsigned long long seed = 1): repeat_(repeat), seed_(seed) {}

    // If n is prime, the function will always return true.
    // If n is even composite, the function will always return false.
    // If n is odd composite, the function will return false with probability >= 1-2^(-K)
    // Changes seed_ each time
    // time: O(K * log(N))
    // space: O(1)
    bool Prime(const LL n) {
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
    bool MillerRabin(const LL N) {
        LL d = N-1, r = 0;
        while (!(d & 1)) {
            r++;
            d >>= 1;
        }
        // From now on: N-1 = 2^r * d.

        for (LL k = 0; k < repeat_; k++) {
            // setting seed to a new pseudo-random value
            seed_ = ((seed_ ^ 0x66778899AABBCCDD) + 23) * 17;
            LL a = seed_ % (N-3) + 2;
            LL x = PowerModN(a, d, N);
            if (x == 1 or x == N-1) continue;
            LL repeat_number = 0;
            while (repeat_number < r-1) {
                x = (x * x) % N;
                if (x == N-1) break;
                repeat_number++;
            }
            if (repeat_number == r-1) return false;
        }
        return true;
    }

    LL PowerModN(const LL a, const LL d, const LL N) const {
        LL answer = 1;
        for (LL i = numeric_limits<LL>::digits-1; i >= 0; i--) {
            answer = (answer * answer) % N;
            if ((1LL << i) & d) {
                answer = (answer * a) % N;
            }
        }
        return answer;
    }

    unsigned long long seed_;
    const LL repeat_;
};

