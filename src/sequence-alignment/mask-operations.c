#include "mask-operations.h"
#include "sequence-alignment.h"
#include <stddef.h>
#include <stdint.h>

size_t ceilDiv(size_t n, size_t q) { return (n + q - 1) / q; }

#if AVX2_CHARACTERS == 1 || AVX512_CHARACTERS == 1
#include <immintrin.h>
#endif

#if AVX2_CHARACTERS == 1
void maskUnion(uint8_t *result, uint8_t *mask1, uint8_t *mask2) {
  __m256i_u *resultAvx2 = (__m256i_u *)result;
  __m256i_u *mask1Avx2 = (__m256i_u *)mask1;
  __m256i_u *mask2Avx2 = (__m256i_u *)mask2;

  int avx2sInSequence = ceilDiv(getSequenceSize(), (8 * sizeof(__m256i_u)));

  for (int i = 0; i < avx2sInSequence; i++)
    resultAvx2[i] = _mm256_or_si256(mask1Avx2[i], mask2Avx2[i]);
}

void maskIntersection(uint8_t *result, uint8_t *mask1, uint8_t *mask2) {
  __m256i_u *resultAvx2 = (__m256i_u *)result;
  __m256i_u *mask1Avx2 = (__m256i_u *)mask1;
  __m256i_u *mask2Avx2 = (__m256i_u *)mask2;

  int avx2sInSequence = ceilDiv(getSequenceSize(), (8 * sizeof(__m256i_u)));

  for (int i = 0; i < avx2sInSequence; i++)
    resultAvx2[i] = _mm256_and_si256(mask1Avx2[i], mask2Avx2[i]);
}

void maskNot(uint8_t *result, uint8_t *mask) {
  __m256i_u *resultAvx2 = (__m256i_u *)result;
  __m256i_u *maskAvx2 = (__m256i_u *)mask;

  int avx2sInSequence = ceilDiv(getSequenceSize(), (8 * sizeof(__m256i_u)));

  for (int i = 0; i < avx2sInSequence; i++)
    resultAvx2[i] = _mm256_xor_si256(maskAvx2[i], _mm256_set1_epi64x(-1LL));
}
#elif AVX512_CHARACTERS == 1
void maskUnion(uint8_t *result, uint8_t *mask1, uint8_t *mask2) {
  __m512i_u *resultAvx512 = (__m512i_u *)result;
  __m512i_u *mask1Avx512 = (__m512i_u *)mask1;
  __m512i_u *mask2Avx512 = (__m512i_u *)mask2;

  int avx512sInSequence = ceilDiv(getSequenceSize(), (8 * sizeof(__m512i_u)));

  for (int i = 0; i < avx512sInSequence; i++)
    resultAvx512[i] = _mm512_or_si512(mask1Avx512[i], mask2Avx512[i]);
}

void maskIntersection(uint8_t *result, uint8_t *mask1, uint8_t *mask2) {
  __m512i_u *resultAvx512 = (__m512i_u *)result;
  __m512i_u *mask1Avx512 = (__m512i_u *)mask1;
  __m512i_u *mask2Avx512 = (__m512i_u *)mask2;

  int avx512sInSequence = ceilDiv(getSequenceSize(), (8 * sizeof(__m512i_u)));

  for (int i = 0; i < avx512sInSequence; i++)
    resultAvx512[i] = _mm512_and_si512(mask1Avx512[i], mask2Avx512[i]);
}

void maskNot(uint8_t *result, uint8_t *mask) {
  __m512i_u *resultAvx512 = (__m512i_u *)result;
  __m512i_u *maskAvx512 = (__m512i_u *)mask;

  int avx512sInSequence = ceilDiv(getSequenceSize(), (8 * sizeof(__m512i_u)));

  for (int i = 0; i < avx512sInSequence; i++)
    resultAvx512[i] = _mm512_xor_si512(maskAvx512[i], _mm512_set1_epi64(-1LL));
}
#else
void maskUnion(allowedStateMask_t *result, allowedStateMask_t *mask1,
               allowedStateMask_t *mask2) {
  uint64_t *resultLong = (uint64_t *)result;
  uint64_t *mask1Long = (uint64_t *)mask1;
  uint64_t *mask2Long = (uint64_t *)mask2;

  int longsInSequence = ceilDiv(getSequenceSize(), (8 * sizeof(uint64_t)));

  for (int i = 0; i < longsInSequence; i++)
    resultLong[i] = mask1Long[i] | mask2Long[i];
}

void maskIntersection(uint8_t *result, uint8_t *mask1, uint8_t *mask2) {
  uint64_t *resultLong = (uint64_t *)result;
  uint64_t *mask1Long = (uint64_t *)mask1;
  uint64_t *mask2Long = (uint64_t *)mask2;

  int longsInSequence = ceilDiv(getSequenceSize(), (8 * sizeof(uint64_t)));

  for (int i = 0; i < longsInSequence; i++)
    resultLong[i] = mask1Long[i] & mask2Long[i];
}

void maskNot(uint8_t *result, uint8_t *mask) {
  uint64_t *resultLong = (uint64_t *)result;
  uint64_t *maskLong = (uint64_t *)mask;

  int longsInSequence = ceilDiv(getSequenceSize(), (8 * sizeof(uint64_t)));

  for (int i = 0; i < longsInSequence; i++)
    resultLong[i] = ~maskLong[i];
}
#endif
