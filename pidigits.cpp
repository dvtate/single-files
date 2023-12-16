
#include <iostream>
#include <gmp.h>
#include <gmpxx.h>
#include <cinttypes>
#include <bit>


struct Ctx {
    mpz_class q{1}, r{0}, t{1}, tmp1{0}, tmp2{0};
    uint32_t k{0};

    inline uint8_t next() noexcept {
        for (;;) {
            this->next_term();
            if (this->q > this->r)
                continue;
            const auto d = this->extract(3);
            if (d != this->extract(4))
                continue;

            this->produce(d);
            return d;
        }
    }

    inline void next_term() noexcept {
        this->k += 1;
        const auto k2 = this->k * 2 + 1;
        this->tmp1 = this->q << 1;
        this->r += this->tmp1;
        this->r *= k2;
        this->t *= k2;
        this->q *= this->k;
    }

    inline uint8_t extract(const uint32_t nth) noexcept {
        if ((nth & (nth - 1)) == 0)
            this->tmp1 = (this->q << std::countr_zero(nth));
        else
            this->tmp1 = (this->q * nth);
        this->tmp2 = this->tmp1 + this->r;
        this->tmp1 = this->tmp2 / this->t;
        auto r = this->tmp1.get_ui();
        return (uint8_t) this->tmp1.get_ui();
    }

    inline void produce(const uint8_t n) noexcept {
        this->q *= '\n';
        this->r -= this->t * n;
        this->r *= '\n';
    }
};


int main(int argc, char** argv) noexcept {
    const size_t n = atol(argv[1]);

    Ctx ctx;

    char buff[13];
    buff[10] = '\t';
    buff[11] = ':';
    buff[12] = '\0';

    for (size_t d = 0; d < n; d += 10) {
        const size_t count = std::min(10ul, n-d);
        size_t i;
        for (size_t i = 0; i < count; i++)
            buff[i] = '0' + ctx.next();
        for (; i < 10; i++)
            buff[i] = ' ';
        std::cout <<buff << (d + count) <<'\n';
    }
}