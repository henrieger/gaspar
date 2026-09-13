#ifndef __BOOTSTRAP_H__

#include <gaspar/answer/answer.h>
#include <gaspar/base/config.h>
#include <gaspar/sequence-alignment/sequence-alignment.h>
#include <gaspar/tree/tree.h>

// Perform bootstrap analysis by the giving method and number of replicates.
void bootstrap(alignment_t *alignment, config_t *config);

#endif // !__BOOTSTRAP_H__
