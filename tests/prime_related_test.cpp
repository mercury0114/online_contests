#include <cstdio>

#include <helpful_code/checks.hpp>
#include <helpful_code/prime_related.hpp>

namespace {
    const int MILLION = 1000000;
}

void Check1Composite() {
    printf("Starting Check1Composite\n");   
    PrimeChecker checker;
    CheckEqual(checker.Prime(1), false);
    printf("Finished Check1Composite\n\n");
}

void Check2Prime() {
    printf("Starting Check2Prime\n");
    PrimeChecker checker;
    CheckEqual(checker.Prime(2), true);
    printf("Finished Check2Prime\n\n");
}

void Check101Prime() {
    printf("Starting Check101Prime\n");
    PrimeChecker checker;
    CheckEqual(checker.Prime(101), true);
    printf("Finished Check101Prime\n\n");
}

void Check121Composite() {
    printf("Starting Check121Composite\n");
    PrimeChecker checker;
    CheckEqual(checker.Prime(121), false);
    printf("Finished Check121Composite\n\n");
}

void CheckPrimesUpToMillion() {
    printf("Starting CheckPrimesUpToMillion\n");
    PrimeChecker checker;
    VB primes = Sieve(MILLION);
    for (int i = 1; i <= MILLION; i++) {
        checker.Prime(i);
        CheckEqual(checker.Prime(i), primes[i]);
    }
    printf("Finished CheckPrimesUpToMillion\n\n");
}


int main() {
    Check1Composite();
    Check2Prime();
    Check101Prime();
    Check121Composite();
    CheckPrimesUpToMillion();
    return 0;
}
