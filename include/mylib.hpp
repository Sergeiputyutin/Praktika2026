#pragma once

#include <cstdint>
#include <chrono>



namespace mylib {

    class Rng {
    public:
        explicit Rng(uint64_t seed = static_cast<uint64_t>(
                        std::chrono::high_resolution_clock::now().time_since_epoch().count()))
            : state(0), inc((seed ^ 0xda3e39cb94b95bdbULL) | 1)
        {
            next();
            state += seed;
            next();
        }

        uint32_t next() {
            uint64_t old = state;
            state = old * 6364136223846793005ULL + (inc | 1);
            uint32_t xorshifted = ((old >> 18u) ^ old) >> 27u;
            uint32_t rot = old >> 59u;
            return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
        }

        int nextInt(int min, int max) {
            uint32_t range = (uint32_t)(max - min + 1);
            uint32_t threshold = (-range) % range; 
            uint32_t r;
            do {
                r = next();
            } while (r < threshold);
            return min + (r % range);
        }

        char nextChar(char min = 'a', char max = 'z') {
            return (char)nextInt((int)min, (int)max);
        }

        float nextFloat(float min = 0.0f, float max = 1.0f) {
            return min + (next() * (1.0f / 4294967296.0f)) * (max - min);
        }

        double nextDouble(double min = 0.0, double max = 1.0) {
            return min + (next() * (1.0 / 4294967296.0)) * (max - min);
        }

    private:
        uint64_t state;
        uint64_t inc;
    };

}