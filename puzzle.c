#include <stdio.h>


int bitAnd(int x, int y) {
    
    return ~(~x | ~y);
}


int getByte(int x, int n) {
    return (x >> (n << 3))&0xFF;
}


int logicalShift(int x, int n) {
    
    return 0;
}


int bitCount(int x) {
   
    return 0;
}


int bang(int x) {
    
    return 0;
}


int tmin(void) {
    
    return 0;
}


int fitsBits(int x, int n) {
    
    return 0;
}


int divpwr2(int x, int n) {
    
    return 0;
}


int negate(int x) {
    
    return 0;
}


int isPositive(int x) {
    
    return 0;
}


int isLessOrEqual(int x, int y) {
    
    return 0;
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
