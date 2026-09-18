#ifndef __LIBGASPAR_SUPPORT_H__

#include <gaspar/answer.h>
#include <gaspar/config.h>
#include <gaspar/sequence-alignment.h>
#include <gaspar/tree.h>

// Perform bootstrap analysis by the giving method and number of replicates.
void bootstrap(alignment_t *alignment, config_t *config);

#endif // !__LIBGASPAR_SUPPORT_H__
