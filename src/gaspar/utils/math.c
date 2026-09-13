#include <gaspar/utils/math.h>

// Returns ceil(n / q)
inline uint64_t ceilDiv(uint64_t n, uint64_t q) { return (n + q - 1) / q; }
