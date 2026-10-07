/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the t amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1 << 31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
  return ~(~x & ~y) & ~(x & y);
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  int mask = x >> 31;      // 符号掩码：负数为1，非负为0
  return (~x + 1) & mask;  // -x 与掩码&，负数取-x，非负取0
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  int byte = (x >> (src << 3)) & 0xFF;       // 提取src位置字符
  int mask = ~(0xFF << (dst << 3));          // 掩码记录待删除的位置
  return (x & mask) | (byte << (dst << 3));  
}

// P5
/* 
 * logicalShift - t x to the right by n bits, using a logical t
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  int a = x >> n;            // 算术右移（但会补符号位1）
  int b  = (1 << 31) >> n;     
  int mask  = ~(b << 1);     // 不使用-，先右移n再左移1，然后取反
  return a & mask;           
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int m = 0x0F | (0x0F << 8);      // 0x0F0F
  m = m | (m << 16);               // 0x0F0F0F0F
  int low  = (x & m) << 4;         // 低半字节移到高位
  int high = (x >> 4) & m;         // 高半字节移到低位
  return low | high;               // 合并 
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  int low0 = ~x & (x + 1);    // 找最低的0位
  int x2   = x | low0;        // 把最低0位变为1
  return ~x2 & (x2 + 1);      // 再找现在的最低0位，即原本的第二低0位
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  x = x ^ (x >> 16);
  x = x ^ (x >> 8);
  x = x ^ (x >> 4);
  x = x ^ (x >> 2);
  x = x ^ (x >> 1);
  return !(x & 1);
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  int m = n & 31;                // 取模
  int y = (~m + 1) & 31;         // 左移对应的位数
  int left  = x << y;            
  int mask  = ~(~0 << y);        // 顶部m位为0的掩码，用于处理right
  int right = (x >> m) & mask;   // 与mask作&，去掉高位可能补的1

  return left | right;
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  int m   = 1 << n;                   // 2^n
  int t = (x >> n) & 1;               // 奇偶判据（偶数商=0，奇数商=1）
  int bias = (m >> 1) + ~0;           // m/2 - 1
  return ((x + bias + t) >> n) << n;  //加偏移后四舍五入
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  int t = (x & y) + ((x ^ y) >> 1);       // 向下取整
  int odd = (x ^ y) & 1;                  // 奇数判断
  int sx = x >> 31;                       // x的符号(0为正, -1为负)
  int sy = y >> 31;                       // y的符号
  int d  = x + ~y + 1;                    // x - y
  int sd = d >> 31;                       // x-y的符号
  int same = !(sx ^ sy);                  // 是否同号
  int gt = (same & !sd) | (!same & !sx);  
  return t + (odd & gt);
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  int sx = x >> 31, sa = a >> 31, sb = b >> 31;   // 符号位(0为正, -1为负)
  int sameA = !(sx ^ sa), sameB = !(sx ^ sb);     // 判断是否同号
  // 判断x>=a，同号看x-a符号，异号看x符号
  int da  = x + ~a + 1;
  int geA = (sameA & !(da >> 31)) | (!sameA & !sx);
  // 同理判断x>=b
  int db  = x + ~b + 1;
  int geB = (sameB & !(db >> 31)) | (!sameB & !sx);
  // (x>=a)^(x>=b)，再补端点
  return (geA ^ geB) | !da | !db;
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  int a = x << 2;                     // 4x
  int y = a + x;                      // 5x
  int sh = (x >> 29) ^ (x >> 31);     // 移位溢出：非0表示4x超出
  int shmask = (~sh + 1) >> 31;       // sh为0时为0，非0时为-1，非0表示溢出
  int admask = (y ^ x) >> 31;         // 加法溢出
  int ovf = shmask | admask;          
  int sx = x >> 31;                   // x的符号
  int min = 1 << 31;
  int max = ~min;
  return (y & ~ovf) | ((ovf & ~sx) & max) | ((ovf & sx) & min);
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  int sx = x >> 31, sy = y >> 31, sz = z >> 31;
  int t = x + y;                          // x+y
  int st = t >> 31;
  int ovf1 = ~(sx ^ sy) & (st ^ sx);      // 溢出判断
  int pos1 = ovf1 & ~sx;
  int neg1 = ovf1 & sx;
  int d1 = ~pos1 + 1 + neg1;
  int s = t + z;                          // t+z
  int ss = s >> 31;
  int ovf2 = ~(st ^ sz) & (ss ^ st);
  int pos2 = ovf2 & ~st;
  int neg2 = ovf2 & st;
  int d2 = ~pos2 + 1 + neg2;
  return d1 + d2;
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  unsigned sign = uf & 0x80000000;                  // 符号位
  unsigned exp  = (uf >> 23) & 0xFF;                // 指数位
  unsigned frac = uf & 0x7FFFFF;                    // 尾数位
  if (exp == 0xFF) return uf;
  unsigned M = (exp == 0) ? frac : (frac + 0x800000);
  unsigned M3 = M + (M << 1);                        // 3M
  unsigned r  = (M3 + ((M3 >> 1) & 1)) >> 1;         // 3M/2向偶数舍入
  unsigned newexp = exp;
  if (r >= 0x1000000) {
    r = (r + ((r >> 1) & 1)) >> 1;                   
    newexp = exp + 1;
  }
  unsigned newfrac;
  if (r >= 0x800000) {
    newfrac = r - 0x800000;
    if (newexp == 0) newexp = 1;
  } else {
    newfrac = r;
    newexp = 0;
  }
  if (newexp >= 0xFF) return sign | 0x7F800000;
  return sign | (newexp << 23) | newfrac;
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  unsigned sign = uf & 0x80000000;
  unsigned exp  = (uf >> 23) & 0xFF;
  unsigned frac = uf & 0x7FFFFF;
  if (exp >= 0xFF) return uf;                     // 无穷
  if (exp >= 150) return uf;                      // 整数
  if (exp < 127) {
    if (exp == 126 && frac != 0)
      return sign | 0x3F800000;
    return sign;
  }
  int t = 150 - exp;
  unsigned M = frac + 0x800000;
  unsigned bias = (1 << (t - 1)) - 1;            // 2^(t-1) - 1
  unsigned par  = (M >> t) & 1;
  unsigned Mr   = ((M + bias + par) >> t) << t;  // 舍入到 2^t 倍数
  unsigned newexp = exp;
  if (Mr >= 0x1000000) {
    Mr >>= 1;
    newexp = exp + 1;
  }
  return sign | (newexp << 23) | (Mr - 0x800000);
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  unsigned sign = x & 0x80000000;
  unsigned absx = x;
  if (x < 0) absx = ~x + 1;
  if (x == 0) return 0;
  unsigned p = 31;                  // 找最高位
  while (!((absx >> p) & 1)) p--;
  unsigned exp = p + 127;
  unsigned frac;
  if (p <= 23) {                    // 无需舍入直接左移
    frac = (absx << (23 - p)) & 0x7FFFFF;
  } else {                          // p>23，向偶数舍入
    unsigned t = p - 23;
    unsigned bias  = (1 << (t - 1)) - 1;
    unsigned par   = (absx >> t) & 1;
    unsigned mant  = (absx + bias + par) >> t;
    if (mant >= 0x1000000) {
      mant >>= 1;
      exp++;
    }
    frac = mant - 0x800000;
  }
  return sign | (exp << 23) | frac;
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  int m1 = 0x55 | (0x55 << 8);   m1 = m1 | (m1 << 16);
  int m2 = 0x33 | (0x33 << 8);   m2 = m2 | (m2 << 16);
  int m3 = 0x0F | (0x0F << 8);   m3 = m3 | (m3 << 16);

  x = (x & m1) + ((x >> 1) & m1);
  x = (x & m2) + ((x >> 2) & m2);
  x = (x + (x >> 4)) & m3;
  x = x + (x >> 8);
  x = x + (x >> 16);
  return x & 0x3F;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x)
{
  int mask;
  mask = (0xFF << 8) | 0xFF;
  x = ((x >> 16) & mask) | (x << 16);
  mask = mask ^ (mask << 8);
  x = ((x >> 8) & mask) | ((x & mask) << 8);
  mask = mask ^ (mask << 4);
  x = ((x >> 4) & mask) | ((x & mask) << 4);
  mask = mask ^ (mask << 2);
  x = ((x >> 2) & mask) | ((x & mask) << 2);
  mask = mask ^ (mask << 1);
  x = ((x >> 1) & mask) | ((x & mask) << 1);
  return x;
}
