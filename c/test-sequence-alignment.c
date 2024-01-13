#include "sequence-alignment.h"

int main() {
  setSequenceSize(6);
  setAlignmentSize(5);
  createCharacterWeights();
  
  alignment_t alignment = newAlignment();

  alignment[0].name = "Alpha";
  alignment[0].charset[0] = 0b00000010;
  alignment[0].charset[1] = 0b00000001;
  alignment[0].charset[2] = 0b00000001;
  alignment[0].charset[3] = 0b00000010;
  alignment[0].charset[4] = 0b00000010;
  alignment[0].charset[5] = 0b00000001;

  alignment[1].name = "Beta";
  alignment[1].charset[0] = 0b00000001;
  alignment[1].charset[1] = 0b00000001;
  alignment[1].charset[2] = 0b00000010;
  alignment[1].charset[3] = 0b00000001;
  alignment[1].charset[4] = 0b00000001;
  alignment[1].charset[5] = 0b00000001;

  alignment[2].name = "Gamma";
  alignment[2].charset[0] = 0b00000010;
  alignment[2].charset[1] = 0b00000010;
  alignment[2].charset[2] = 0b00000001;
  alignment[2].charset[3] = 0b00000001;
  alignment[2].charset[4] = 0b00000001;
  alignment[2].charset[5] = 0b00000001;

  alignment[3].name = "Delta";
  alignment[3].charset[0] = 0b00000010;
  alignment[3].charset[1] = 0b00000010;
  alignment[3].charset[2] = 0b00000001;
  alignment[3].charset[3] = 0b00000010;
  alignment[3].charset[4] = 0b00000010;
  alignment[3].charset[5] = 0b00000010;

  alignment[4].name = "Epsilon";
  alignment[4].charset[0] = 0b00000001;
  alignment[4].charset[1] = 0b00000001;
  alignment[4].charset[2] = 0b00000010;
  alignment[4].charset[3] = 0b00000010;
  alignment[4].charset[4] = 0b00000010;
  alignment[4].charset[5] = 0b00000001;

  printAlignment(alignment);
  printCharacterWeights();

  destroyAlignment(alignment);
  destroyCharacterWeights();
}
