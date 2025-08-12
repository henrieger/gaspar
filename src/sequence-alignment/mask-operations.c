#include "mask-operations.h"
#include "sequence-alignment.h"
#include <stddef.h>
#include <stdint.h>

#if AVX2_CHARACTERS == 1 || AVX512_CHARACTERS == 1
#include <immintrin.h>
#endif

#if AVX2_CHARACTERS == 1
void maskUnion(stateAllowedMask_t *result, stateAllowedMask_t *mask1,
               stateAllowedMask_t *mask2, uint32_t characters) {
  __m256i_u *resultAvx2 = (__m256i_u *)result;
  __m256i_u *mask1Avx2 = (__m256i_u *)mask1;
  __m256i_u *mask2Avx2 = (__m256i_u *)mask2;

  int avx2sInSequence = allowedArraySize(characters) / sizeof(__m256i_u);

  for (int i = 0; i < avx2sInSequence; i++)
    resultAvx2[i] = _mm256_or_si256(mask1Avx2[i], mask2Avx2[i]);
}

void maskIntersection(stateAllowedMask_t *result, stateAllowedMask_t *mask1,
                      stateAllowedMask_t *mask2, uint32_t characters) {
  __m256i_u *resultAvx2 = (__m256i_u *)result;
  __m256i_u *mask1Avx2 = (__m256i_u *)mask1;
  __m256i_u *mask2Avx2 = (__m256i_u *)mask2;

  int avx2sInSequence = allowedArraySize(characters) / sizeof(__m256i_u);

  for (int i = 0; i < avx2sInSequence; i++)
    resultAvx2[i] = _mm256_and_si256(mask1Avx2[i], mask2Avx2[i]);
}

void maskNot(stateAllowedMask_t *result, stateAllowedMask_t *mask,
             uint32_t characters) {
  __m256i_u *resultAvx2 = (__m256i_u *)result;
  __m256i_u *maskAvx2 = (__m256i_u *)mask;

  int avx2sInSequence = allowedArraySize(characters) / sizeof(__m256i_u);

  for (int i = 0; i < avx2sInSequence; i++)
    resultAvx2[i] = _mm256_xor_si256(maskAvx2[i], _mm256_set1_epi64x(-1LL));
}
#elif AVX512_CHARACTERS == 1
void maskUnion(stateAllowedMask_t *result, stateAllowedMask_t *mask1,
               stateAllowedMask_t *mask2, uint32_t characters) {
  __m512i_u *resultAvx512 = (__m512i_u *)result;
  __m512i_u *mask1Avx512 = (__m512i_u *)mask1;
  __m512i_u *mask2Avx512 = (__m512i_u *)mask2;

  int avx512sInSequence = allowedArraySize(characters) / sizeof(__m512i_u);

  for (int i = 0; i < avx512sInSequence; i++)
    resultAvx512[i] = _mm512_or_si512(mask1Avx512[i], mask2Avx512[i]);
}

void maskIntersection(stateAllowedMask_t *result, stateAllowedMask_t *mask1,
                      stateAllowedMask_t *mask2, uint32_t characters) {
  __m512i_u *resultAvx512 = (__m512i_u *)result;
  __m512i_u *mask1Avx512 = (__m512i_u *)mask1;
  __m512i_u *mask2Avx512 = (__m512i_u *)mask2;

  int avx512sInSequence = allowedArraySize(characters) / sizeof(__m512i_u);

  for (int i = 0; i < avx512sInSequence; i++)
    resultAvx512[i] = _mm512_and_si512(mask1Avx512[i], mask2Avx512[i]);
}

void maskNot(stateAllowedMask_t *result, stateAllowedMask_t *mask,
             uint32_t characters) {
  __m512i_u *resultAvx512 = (__m512i_u *)result;
  __m512i_u *maskAvx512 = (__m512i_u *)mask;

  int avx512sInSequence = allowedArraySize(characters) / sizeof(__m512i_u);

  for (int i = 0; i < avx512sInSequence; i++)
    resultAvx512[i] = _mm512_xor_si512(maskAvx512[i], _mm512_set1_epi64(-1LL));
}
#else
void maskUnion(stateAllowedMask_t *result, stateAllowedMask_t *mask1,
               stateAllowedMask_t *mask2, uint32_t characters) {
  uint64_t *resultLong = (uint64_t *)result;
  uint64_t *mask1Long = (uint64_t *)mask1;
  uint64_t *mask2Long = (uint64_t *)mask2;

  int longsInSequence = allowedArraySize(characters) / sizeof(uint64_t);

  for (int i = 0; i < longsInSequence; i++)
    resultLong[i] = mask1Long[i] | mask2Long[i];
}

void maskIntersection(stateAllowedMask_t *result, stateAllowedMask_t *mask1,
                      stateAllowedMask_t *mask2, uint32_t characters) {
  uint64_t *resultLong = (uint64_t *)result;
  uint64_t *mask1Long = (uint64_t *)mask1;
  uint64_t *mask2Long = (uint64_t *)mask2;

  int longsInSequence = allowedArraySize(characters) / sizeof(uint64_t);

  for (int i = 0; i < longsInSequence; i++)
    resultLong[i] = mask1Long[i] & mask2Long[i];
}

void maskNot(stateAllowedMask_t *result, stateAllowedMask_t *mask,
             uint32_t characters) {
  uint64_t *resultLong = (uint64_t *)result;
  uint64_t *maskLong = (uint64_t *)mask;

  int longsInSequence = allowedArraySize(characters) / sizeof(uint64_t);

  for (int i = 0; i < longsInSequence; i++)
    resultLong[i] = ~maskLong[i];
}
#endif
