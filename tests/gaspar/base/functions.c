#include <gaspar/base/functions.h>

#include <gaspar/base/config.h>
#include <gaspar/eval/parsimony.h>
#include <gaspar/search/genetic-algorithm.h>
#include <gaspar/sequence-alignment/sequence-alignment.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>

int lineNumber = 1;

int main() {
  globalTaxa = 5;
  globalCharacters = 6;
  taxon = 0;
  character = 0;

  config_t config;
  setConfigsToDefault(&config);

  // test initializeAlignment
  initializeAlignment();
  assert(labels != NULL);
  assert(labels[0] != NULL);
  for (int i = 0; i < globalTaxa; i++) {
    assert(labels[i] == labels[0] + (i * LABEL_SIZE));
  }
  assert(alignment != NULL);

  // test addNumbersToSequence
  memcpy(token, "100110", 6);
  addNumbersToSequence();
  assert(alignment->sequenceMasks[taxon][0][0] == 0x26);
  assert(alignment->sequenceMasks[taxon][1][0] == 0x19);
  taxon++;
  character = 0;

  // test addMissingData
  addMissingData();
  printf("%d %d\n", alignment->sequenceMasks[taxon][0][0],
         alignment->sequenceMasks[taxon][1][0]);
  assert(alignment->sequenceMasks[taxon][0][0] == 0x1);
  assert(alignment->sequenceMasks[taxon][1][0] == 0x1);

  // test addMultistateChar
  memcpy(token, "01", 2);
  addMultistateChar();
  assert(alignment->sequenceMasks[taxon][0][0] == 0x3);
  assert(alignment->sequenceMasks[taxon][1][0] == 0x3);
  memcpy(token, "0", 2);
  addMultistateChar();
  assert(alignment->sequenceMasks[taxon][0][0] == 0x7);
  assert(alignment->sequenceMasks[taxon][1][0] == 0x3);

  destroyAlignment(alignment);
  free(labels[0]);
  free(labels);
}
