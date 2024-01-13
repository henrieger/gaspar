#include "sequence-alignment.h"

int main() {
  setSequenceSize(6);
  setAlignmentSize(5);
  createCharacterWeights();
  
  alignment_t alignment = newAlignment();

  alignment[0].name = "Alpha";
  alignment[0].charsets[0] = 0b00000010;
  alignment[0].charsets[1] = 0b00000001;
  alignment[0].charsets[2] = 0b00000001;
  alignment[0].charsets[3] = 0b00000010;
  alignment[0].charsets[4] = 0b00000010;
  alignment[0].charsets[5] = 0b00000001;

  alignment[1].name = "Beta";
  alignment[1].charsets[0] = 0b00000001;
  alignment[1].charsets[1] = 0b00000001;
  alignment[1].charsets[2] = 0b00000010;
  alignment[1].charsets[3] = 0b00000001;
  alignment[1].charsets[4] = 0b00000001;
  alignment[1].charsets[5] = 0b00000001;

  alignment[2].name = "Gamma";
  alignment[2].charsets[0] = 0b00000010;
  alignment[2].charsets[1] = 0b00000010;
  alignment[2].charsets[2] = 0b00000001;
  alignment[2].charsets[3] = 0b00000001;
  alignment[2].charsets[4] = 0b00000001;
  alignment[2].charsets[5] = 0b00000001;

  alignment[3].name = "Delta";
  alignment[3].charsets[0] = 0b00000010;
  alignment[3].charsets[1] = 0b00000010;
  alignment[3].charsets[2] = 0b00000001;
  alignment[3].charsets[3] = 0b00000010;
  alignment[3].charsets[4] = 0b00000010;
  alignment[3].charsets[5] = 0b00000010;

  alignment[4].name = "Epsilon";
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
