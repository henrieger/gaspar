#include <stdio.h>
#include <sequence-alignment/sequence-alignment.h>

int main() {
  setSequenceSize(6);
  setAlignmentSize(5);
  createCharacterWeights();

  printCharacterWeights();

  static const char alpha[] = "Alpha\t";
  static const char beta[] = "Beta\t";
  static const char gamma[] = "Gamma\t";
  static const char delta[] = "Delta\t";
  static const char epsilon[] = "Epsilon\t";

  static const char *labels[5] = {alpha, beta, gamma, delta, epsilon};
  
  alignment_t *alignment = newAlignment(getAlignmentSize(), labels);

  printf("Labels: { ");
  for (int i = 0; i < getAlignmentSize(); i++) {
    printf("%s, ", labels[i]);
  }
  printf("}\n");

  printf("Allowed states array size: %ld\n", allowedArraySize());
  printf("Sizeof allowed_t: %ld\n", sizeof(allowed_t));
  printf("Sizeof sequence_t: %ld\n", sizeof(sequence_t));
  printf("Sizeof alignment_t: %ld\n", sizeof(alignment_t));

  // Alpha: 100110
  alignment->sequences[0].allowed[0][0] = (allowed_t) 0b00100110;
  alignment->sequences[0].allowed[1][0] = (allowed_t) 0b00011001;
  alignment->sequences[0].allowed[2][0] = (allowed_t) 0b00000000;
  alignment->sequences[0].allowed[3][0] = (allowed_t) 0b00000000;
  alignment->sequences[0].allowed[4][0] = (allowed_t) 0b00000000;
  alignment->sequences[0].allowed[5][0] = (allowed_t) 0b00000000;
  alignment->sequences[0].allowed[6][0] = (allowed_t) 0b00000000;
  alignment->sequences[0].allowed[7][0] = (allowed_t) 0b00000000;

  // Beta: 001000
  alignment->sequences[1].allowed[0][0] = (allowed_t) 0b00111011;
  alignment->sequences[1].allowed[1][0] = (allowed_t) 0b00000100;
  alignment->sequences[1].allowed[2][0] = (allowed_t) 0b00000000;
  alignment->sequences[1].allowed[3][0] = (allowed_t) 0b00000000;
  alignment->sequences[1].allowed[4][0] = (allowed_t) 0b00000000;
  alignment->sequences[1].allowed[5][0] = (allowed_t) 0b00000000;
  alignment->sequences[1].allowed[6][0] = (allowed_t) 0b00000000;
  alignment->sequences[1].allowed[7][0] = (allowed_t) 0b00000000;

  // Gamma: 110000
  alignment->sequences[2].allowed[0][0] = (allowed_t) 0b00111100;
  alignment->sequences[2].allowed[1][0] = (allowed_t) 0b00000011;
  alignment->sequences[2].allowed[2][0] = (allowed_t) 0b00000000;
  alignment->sequences[2].allowed[3][0] = (allowed_t) 0b00000000;
  alignment->sequences[2].allowed[4][0] = (allowed_t) 0b00000000;
  alignment->sequences[2].allowed[5][0] = (allowed_t) 0b00000000;
  alignment->sequences[2].allowed[6][0] = (allowed_t) 0b00000000;
  alignment->sequences[2].allowed[7][0] = (allowed_t) 0b00000000;

  // Delta: 110111
  alignment->sequences[3].allowed[0][0] = (allowed_t) 0b00000100;
  alignment->sequences[3].allowed[1][0] = (allowed_t) 0b00111011;
  alignment->sequences[3].allowed[2][0] = (allowed_t) 0b00000000;
  alignment->sequences[3].allowed[3][0] = (allowed_t) 0b00000000;
  alignment->sequences[3].allowed[4][0] = (allowed_t) 0b00000000;
  alignment->sequences[3].allowed[5][0] = (allowed_t) 0b00000000;
  alignment->sequences[3].allowed[6][0] = (allowed_t) 0b00000000;
  alignment->sequences[3].allowed[7][0] = (allowed_t) 0b00000000;

  // Epsilon: 001110
  alignment->sequences[4].allowed[0][0] = (allowed_t) 0b00100011;
  alignment->sequences[4].allowed[1][0] = (allowed_t) 0b00011100;
  alignment->sequences[4].allowed[2][0] = (allowed_t) 0b00000000;
  alignment->sequences[4].allowed[3][0] = (allowed_t) 0b00000000;
  alignment->sequences[4].allowed[4][0] = (allowed_t) 0b00000000;
  alignment->sequences[4].allowed[5][0] = (allowed_t) 0b00000000;
  alignment->sequences[4].allowed[6][0] = (allowed_t) 0b00000000;
  alignment->sequences[4].allowed[7][0] = (allowed_t) 0b00000000;

  printAlignment(alignment);

  alignment_t *copy = copyAlignment(alignment);
  printAlignment(copy);

  alignment_t *multiState = newAlignment(5, labels);

  // Alpha: 100110
  multiState->sequences[0].allowed[0][0] = (allowed_t) 0b00100110;
  multiState->sequences[0].allowed[1][0] = (allowed_t) 0b00011001;
  multiState->sequences[0].allowed[2][0] = (allowed_t) 0b00000000;
  multiState->sequences[0].allowed[3][0] = (allowed_t) 0b00000000;
  multiState->sequences[0].allowed[4][0] = (allowed_t) 0b00000000;
  multiState->sequences[0].allowed[5][0] = (allowed_t) 0b00000000;
  multiState->sequences[0].allowed[6][0] = (allowed_t) 0b00000000;
  multiState->sequences[0].allowed[7][0] = (allowed_t) 0b00000000;

  // Beta: 00[01][012]00
  multiState->sequences[1].allowed[0][0] = (allowed_t) 0b00111111;
  multiState->sequences[1].allowed[1][0] = (allowed_t) 0b00001100;
  multiState->sequences[1].allowed[2][0] = (allowed_t) 0b00001000;
  multiState->sequences[1].allowed[3][0] = (allowed_t) 0b00000000;
  multiState->sequences[1].allowed[4][0] = (allowed_t) 0b00000000;
  multiState->sequences[1].allowed[5][0] = (allowed_t) 0b00000000;
  multiState->sequences[1].allowed[6][0] = (allowed_t) 0b00000000;
  multiState->sequences[1].allowed[7][0] = (allowed_t) 0b00000000;

  // Gamma: 110000
  multiState->sequences[2].allowed[0][0] = (allowed_t) 0b00111100;
  multiState->sequences[2].allowed[1][0] = (allowed_t) 0b00000011;
  multiState->sequences[2].allowed[2][0] = (allowed_t) 0b00000000;
  multiState->sequences[2].allowed[3][0] = (allowed_t) 0b00000000;
  multiState->sequences[2].allowed[4][0] = (allowed_t) 0b00000000;
  multiState->sequences[2].allowed[5][0] = (allowed_t) 0b00000000;
  multiState->sequences[2].allowed[6][0] = (allowed_t) 0b00000000;
  multiState->sequences[2].allowed[7][0] = (allowed_t) 0b00000000;

  // Delta: ?101?1
  multiState->sequences[3].allowed[0][0] = (allowed_t) 0b00010101;
  multiState->sequences[3].allowed[1][0] = (allowed_t) 0b00111011;
  multiState->sequences[3].allowed[2][0] = (allowed_t) 0b00010001;
  multiState->sequences[3].allowed[3][0] = (allowed_t) 0b00010001;
  multiState->sequences[3].allowed[4][0] = (allowed_t) 0b00010001;
  multiState->sequences[3].allowed[5][0] = (allowed_t) 0b00010001;
  multiState->sequences[3].allowed[6][0] = (allowed_t) 0b00010001;
  multiState->sequences[3].allowed[7][0] = (allowed_t) 0b00010001;

  // Epsilon: 001110
  multiState->sequences[4].allowed[0][0] = (allowed_t) 0b00100011;
  multiState->sequences[4].allowed[1][0] = (allowed_t) 0b00011100;
  multiState->sequences[4].allowed[2][0] = (allowed_t) 0b00000000;
  multiState->sequences[4].allowed[3][0] = (allowed_t) 0b00000000;
  multiState->sequences[4].allowed[4][0] = (allowed_t) 0b00000000;
  multiState->sequences[4].allowed[5][0] = (allowed_t) 0b00000000;
  multiState->sequences[4].allowed[6][0] = (allowed_t) 0b00000000;
  multiState->sequences[4].allowed[7][0] = (allowed_t) 0b00000000;

  printAlignment(multiState);

  destroyAlignment(alignment);
  destroyAlignment(copy);
  destroyAlignment(multiState);
  destroyCharacterWeights();
}
