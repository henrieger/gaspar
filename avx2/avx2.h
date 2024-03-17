#ifndef __AVX2_H__
#define __AVX2_H__

#include <immintrin.h>

#define avx_t __m256i

#define vectorized_8(vector, i)                                                \
  vector[i], vector[i + 1], vector[i + 2], vector[i + 3], vector[i + 4],       \
      vector[i + 5], vector[i + 6], vector[i + 7], vector[i + 8],              \
      vector[i + 9], vector[i + 10], vector[i + 11], vector[i + 12],           \
      vector[i + 13], vector[i + 14], vector[i + 15], vector[i + 16],          \
      vector[i + 17], vector[i + 18], vector[i + 19], vector[i + 20],          \
      vector[i + 21], vector[i + 22], vector[i + 23], vector[i + 24],          \
      vector[i + 25], vector[i + 26], vector[i + 27], vector[i + 28],          \
      vector[i + 29], vector[i + 30], vector[i + 31]

#define avx_load(vector, i) _mm256_load_si256((avx_t *)(vector + i))
#define avx_store(dest, src, i) _mm256_store_si256((avx_t *)(dest + i), src)

#define avx_minusOne _mm256_set1_epi8(-1)

#define avx_sum(a, b) _mm256_add_epi8(a, b)

#define avx_setMask(a) _mm256_cmpeq_epi8(a, _mm256_setzero_si256())

#define avx_and(a, b) _mm256_and_si256(a, b)
#define avx_or(a, b) _mm256_or_si256(a, b)
#define avx_xor(a, b) _mm256_xor_si256(a, b)

#endif // !__AVX2_H__
