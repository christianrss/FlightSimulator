#define ABS(X) (X<0?-X:X)
#define COS(X) cos_table[ABS(X)&255]
#define SIN(X) sin_table[ABS(X)&255]

const int NUMBER_OF_DEGREES = 256;
const int SHIFT = 9;
const int SHIFT_MULT = 1<<SHIFT;

extern long cos_table[256];
extern long sin_table[256];