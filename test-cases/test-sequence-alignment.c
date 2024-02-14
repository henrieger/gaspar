#include <string.h>
#include <sequence-alignment/sequence-alignment.h>

int main() {
  setSequenceSize(6);
  setAlignmentSize(5);
  createCharacterWeights();
  
  alignment_t alignment = newAlignment();

  strncpy(alignment[0].label, "Alpha", LABEL_SIZE);
  alignment[0].charsets[0] = 0b00000010;
  alignment[0].charsets[1] = 0b00000001;
  alignment[0].charsets[2] = 0b00000001;
  alignment[0].charsets[3] = 0b00000010;
  alignment[0].charsets[4] = 0b00000010;
  alignment[0].charsets[5] = 0b00000001;

  strncpy(alignment[1].label, "Beta", LABEL_SIZE);
  alignment[1].charsets[0] = 0b00000001;
  alignment[1].charsets[1] = 0b00000001;
  alignment[1].charsets[2] = 0b00000010;
  alignment[1].charsets[3] = 0b00000001;
  alignment[1].charsets[4] = 0b00000001;
  alignment[1].charsets[5] = 0b00000001;

  strncpy(alignment[2].label, "Gamma", LABEL_SIZE);
  alignment[2].charsets[0] = 0b00000010;
  alignment[2].charsets[1] = 0b00000010;
  alignment[2].charsets[2] = 0b00000001;
  alignment[2].charsets[3] = 0b00000001;
  alignment[2].charsets[4] = 0b00000001;
  alignment[2].charsets[5] = 0b00000001;

  strncpy(alignment[3].label, "Delta", LABEL_SIZE);
  alignment[3].charsets[0] = 0b00000010;
  alignment[3].charsets[1] = 0b00000010;
  alignment[3].charsets[2] = 0b00000001;
  alignment[3].charsets[3] = 0b00000010;
  alignment[3].charsets[4] = 0b00000010;
  alignment[3].charsets[5] = 0b00000010;

  strncpy(alignment[4].label, "Epsilon", LABEL_SIZE);
  alignment[4].charsets[0] = 0b00000001;
  alignment[4].charsets[1] = 0b00000001;
  alignment[4].charsets[2] = 0b00000010;
  alignment[4].charsets[3] = 0b00000010;
  alignment[4].charsets[4] = 0b00000010;
  alignment[4].charsets[5] = 0b00000001;

  printAlignment(alignment);
  printCharacterWeights();

  destroyAlignment(alignment);
  destroyCharacterWeights();
}
