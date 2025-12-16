#include <stdio.h>


int bitAnd(int x, int y) {
    
    return ~(~x | ~y);
}


int getByte(int x, int n) {
    return (x >> (n << 3)) &0xFF;
}


int logicalShift(int x, int n) {
    
    return  (1 << (32 - n)) - 1;
}


int bitCount(int x) {
   
    return x & 0x3f;
}


int bang(int x) {
    
    return ((x | -x) >> 31) + 1 ;
}


int tmin(void) {
    
    return 1 << 31;
}


int fitsBits(int x, int n) {
    
    return (x << (32 - n)) >> (32 - n) == x;
}


int divpwr2(int x, int n) {
    
    return (x + ((x >> 31) & ((1 << n) - 1))) >> n;
}


int negate(int x) {
    
    return ~x + 1;
}


int isPositive(int x) {
    
    return !(x << 31) & !!x;
}


int isLessOrEqual(int x, int y) {
    
    return x <= y ;
}


int ilog2(int x) {
  
    return 0;
}

/******** FLOATING POINT PUZZLES *********/

unsigned float_neg(unsigned uf) {
   
    return 0;
}


unsigned float_i2f(int x) {
   
    return 0;
}


unsigned float_twice(unsigned uf) {
    
    return 0;
}
