#include <iostream>
#include <cinttypes>
#include <bit>
#include <limits>

inline bool mul_safe(unsigned int& a, unsigned int b) {
    if (std::countl_zero(a) + std::countl_zero(b) < 32)
        return false;
    a *= b;
    return true;
}
inline bool add_safe(unsigned int& a, unsigned int b) {
    if (std::countl_zero(a) == 0 || std::countl_zero(b) == 0)
        return false;
    a += b;
    return true;
}

int reverse(int x) {
    bool sign = x < 0;
    if (x == std::numeric_limits<int>::min())
        return 0;
    unsigned int in = sign ? -x : x;
    unsigned int ret = in % 10;
    in /= 10;
    unsigned int i = 0;
    while (in != 0) {
        if (i > 7) {
            if (!mul_safe(ret, 10))
                return 0;
            if (!add_safe(ret, in % 10))
                return 0;
        } else {
            ret *= 10;
            ret += in % 10;
        }
        in /= 10;
        i++;
    }

    return sign ? (-(int)ret) : ret;
}

int main() {
    int n;
  	std::cin >>n;
  	std::cout <<reverse(n) <<std::endl;
}
