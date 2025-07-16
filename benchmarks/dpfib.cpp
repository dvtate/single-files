#include <cmath>

int fib_dp(int n) {
    // ~800 bytes of ram
    static_assert(sizeof(int) <= 8, "int too big");
    static constexpr int max_n = 94;  // max fib term that can fit into an int
    static int cache[max_n] = {0, 1};
    static int cache_n = 1;

    // Use cache if possible
    if (cache_n >= n)
        return cache[n];

    // Prevent integer overflow
    if (n > max_n)
        return -1;
    
    // Populate cache up to n
    do {
        cache_n++;
        cache[cache_n] = cache[cache_n - 1] + cache[cache_n - 2];
    } while (cache_n < n);

    // Return calculated value from cache
    return cache[cache_n];
}

double constexpr sqrt_constexpr(double x, double curr, double prev) {
    return curr == prev
        ? curr
        : sqrt_constexpr(x, 0.5 * (curr + x / curr), curr);
}

int constexpr fib_binet(int n) {
    constexpr double phi = (1 + sqrt_constexpr(5, 5, 0)) / 2;
    double ret = (pow(phi, n) - pow(-phi, n)) * (1.0 / sqrt_constexpr(5, 5, 0));
    return (int) ret;
}

int main() {
    for (int i = 0; i < 30; i++) {
        
    }
}