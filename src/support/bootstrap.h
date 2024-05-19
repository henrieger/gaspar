#ifndef __BOOTSTRAP_H__

#include <answer/answer.h>
#include <sequence-alignment/sequence-alignment.h>
#include <tree/tree.h>
#include <config.h>

// Perform bootstrap analysis by the giving method and number of replicates.
void bootstrap(alignment_t *alignment, config_t *config);

#endif // !__BOOTSTRAP_H__
