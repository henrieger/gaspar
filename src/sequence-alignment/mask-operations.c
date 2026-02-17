#include "mask-operations.h"
#include "sequence-alignment.h"
#include <stddef.h>
#include <stdint.h>
#include <utils/math.h>

#if AVX2_CHARACTERS || AVX512_CHARACTERS
#include <immintrin.h>
#endif

uint32_t calculateSize_64(uint32_t characters) {
  return ceilDiv(allowedArraySize(characters), sizeof(uint64_t));
}

void maskUnion_64(stateAllowedMask_t *result, stateAllowedMask_t *mask1,
                  stateAllowedMask_t *mask2, uint32_t size) {
  uint64_t *resultLong = (uint64_t *)result;
  uint64_t *mask1Long = (uint64_t *)mask1;
  uint64_t *mask2Long = (uint64_t *)mask2;

  for (int i = 0; i < size; i++)
    resultLong[i] = mask1Long[i] | mask2Long[i];
}

void maskIntersection_64(stateAllowedMask_t *result, stateAllowedMask_t *mask1,
                         stateAllowedMask_t *mask2, uint32_t size) {
  uint64_t *resultLong = (uint64_t *)result;
  uint64_t *mask1Long = (uint64_t *)mask1;
  uint64_t *mask2Long = (uint64_t *)mask2;

  for (int i = 0; i < size; i++)
    resultLong[i] = mask1Long[i] & mask2Long[i];
}

void maskNot_64(stateAllowedMask_t *result, stateAllowedMask_t *mask,
                uint32_t size) {
  uint64_t *resultLong = (uint64_t *)result;
  uint64_t *maskLong = (uint64_t *)mask;

  for (int i = 0; i < size; i++)
    resultLong[i] = ~maskLong[i];
}

#ifdef AVX2_CHARACTERS
inline uint32_t calculateSize_256(uint32_t characters) {
  return ceilDiv(allowedArraySize(characters), sizeof(__m256i_u));
}

void maskUnion_256(stateAllowedMask_t *result, stateAllowedMask_t *mask1,
                   stateAllowedMask_t *mask2, uint32_t size) {
  __m256i_u *resultAvx2 = (__m256i_u *)result;
  __m256i_u *mask1Avx2 = (__m256i_u *)mask1;
  __m256i_u *mask2Avx2 = (__m256i_u *)mask2;

  for (int i = 0; i < size; i++)
    resultAvx2[i] = _mm256_or_si256(mask1Avx2[i], mask2Avx2[i]);
}

void maskIntersection_256(stateAllowedMask_t *result, stateAllowedMask_t *mask1,
                          stateAllowedMask_t *mask2, uint32_t size) {
  __m256i_u *resultAvx2 = (__m256i_u *)result;
  __m256i_u *mask1Avx2 = (__m256i_u *)mask1;
  __m256i_u *mask2Avx2 = (__m256i_u *)mask2;

  for (int i = 0; i < size; i++)
    resultAvx2[i] = _mm256_and_si256(mask1Avx2[i], mask2Avx2[i]);
}

void maskNot_256(stateAllowedMask_t *result, stateAllowedMask_t *mask,
                 uint32_t size) {
  __m256i_u *resultAvx2 = (__m256i_u *)result;
  __m256i_u *maskAvx2 = (__m256i_u *)mask;

  for (int i = 0; i < size; i++)
    resultAvx2[i] = _mm256_xor_si256(maskAvx2[i], _mm256_set1_epi64x(-1LL));
}
#endif

#ifdef AVX512_CHARACTERS
inline uint32_t calculateSize_512(uint32_t characters) {
  return ceilDiv(allowedArraySize(characters), sizeof(__m512i_u));
}

void maskUnion_512(stateAllowedMask_t *result, stateAllowedMask_t *mask1,
                   stateAllowedMask_t *mask2, uint32_t size) {
  __m512i_u *resultAvx512 = (__m512i_u *)result;
  __m512i_u *mask1Avx512 = (__m512i_u *)mask1;
  __m512i_u *mask2Avx512 = (__m512i_u *)mask2;

  for (int i = 0; i < size; i++)
    resultAvx512[i] = _mm512_or_si512(mask1Avx512[i], mask2Avx512[i]);
}

void maskIntersection_512(stateAllowedMask_t *result, stateAllowedMask_t *mask1,
                          stateAllowedMask_t *mask2, uint32_t size) {
  __m512i_u *resultAvx512 = (__m512i_u *)result;
  __m512i_u *mask1Avx512 = (__m512i_u *)mask1;
  __m512i_u *mask2Avx512 = (__m512i_u *)mask2;

  for (int i = 0; i < size; i++)
    resultAvx512[i] = _mm512_and_si512(mask1Avx512[i], mask2Avx512[i]);
}

void maskNot_512(stateAllowedMask_t *result, stateAllowedMask_t *mask,
                 uint32_t size) {
  __m512i_u *resultAvx512 = (__m512i_u *)result;
  __m512i_u *maskAvx512 = (__m512i_u *)mask;

  for (int i = 0; i < size; i++)
    resultAvx512[i] = _mm512_xor_si512(maskAvx512[i], _mm512_set1_epi64(-1LL));
}
#endif

#if AVX2_CHARACTERS == 1
inline uint32_t calculateSize(uint32_t characters) {
  return calculateSize_256(characters);
}

void maskUnion(stateAllowedMask_t *result, stateAllowedMask_t *mask1,
               stateAllowedMask_t *mask2, uint32_t size) {
  return maskUnion_256(result, mask1, mask2, size);
}

void maskIntersection(stateAllowedMask_t *result, stateAllowedMask_t *mask1,
                      stateAllowedMask_t *mask2, uint32_t size) {
  return maskIntersection_256(result, mask1, mask2, size);
}

void maskNot(stateAllowedMask_t *result, stateAllowedMask_t *mask,
             uint32_t size) {
  return maskNot_256(result, mask, size);
}
#elif AVX512_CHARACTERS == 1
inline uint32_t calculateSize(uint32_t characters) {
  return calculateSize_512(characters);
}

void maskUnion(stateAllowedMask_t *result, stateAllowedMask_t *mask1,
               stateAllowedMask_t *mask2, uint32_t size) {
  return maskUnion_512(result, mask1, mask2, size);
}

void maskIntersection(stateAllowedMask_t *result, stateAllowedMask_t *mask1,
                      stateAllowedMask_t *mask2, uint32_t size) {
  return maskIntersection_512(result, mask1, mask2, size);
}

void maskNot(stateAllowedMask_t *result, stateAllowedMask_t *mask,
             uint32_t size) {
  return maskNot_512(result, mask, size);
}
#else
inline uint32_t calculateSize(uint32_t characters) {
  return calculateSize_64(characters);
}

void maskUnion(stateAllowedMask_t *result, stateAllowedMask_t *mask1,
               stateAllowedMask_t *mask2, uint32_t size) {
  return maskUnion_64(result, mask1, mask2, size);
}

void maskIntersection(stateAllowedMask_t *result, stateAllowedMask_t *mask1,
                      stateAllowedMask_t *mask2, uint32_t size) {
  return maskIntersection_64(result, mask1, mask2, size);
}

void maskNot(stateAllowedMask_t *result, stateAllowedMask_t *mask,
             uint32_t size) {
  return maskNot_64(result, mask, size);
}
#endif
