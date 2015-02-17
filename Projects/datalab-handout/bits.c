/* 
 * CS:APP Data Lab 
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

#include "btest.h"
#include <limits.h>

/*
 * Instructions to Students:
 *
 * STEP 1: Fill in the following struct with your identifying info.
 */
team_struct team =
{
  /* First Group memeber ID/ My ID */
    "100576939", 
   /* First group member name/ My name. */
   "Adam Ross",
   /* First group memeber login/ My Login. */
   "adro4510",

   /* The following should only be changed if there are two team members */
   /* Student name 2: Full name of the second team member */
   "Mathew Maskowitz",
   /* Login ID 2: Login ID of the second team member */
   "moskowmh"
};

#if 0
/*
 * STEP 2: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

CODING RULES:
 
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
 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

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


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.
#endif

/*
 * STEP 3: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the btest test harness to check that your solutions produce 
 *      the correct answers. Watch out for corner cases around Tmin and Tmax.
 */
/*
 * isZero - returns 1 if x == 0, and 0 otherwise 
 *   Examples: isZero(5) = 0, isZero(0) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int isZero(int x) {
       /* pretty simple, it does what is required. 
	  If x is 0 it returns true or 1. */
       
   return !x;
   }
/* 
 * TMax - return maximum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmax(void) {
  /* Also pretty simple, it creates the largest negative 
     tc number by logical shifting 1 all the way to the 
     highest power and then (not)s it. Flipping all 
     1s to 0s and 0s to 1s making the largest tc number. */
  
  return ~(1 << 31);
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  /* It masks x to all 0s if positive or 1s if negative with an 
    arithmatic right shift 31 bits. It then applies the mask to 
    negated x and a negated mask to x and adds them. This ensures 
    no matter what value, positive or negative, that if there is a 
    bit larger than can be represented in n bits then 
    it will show up as a 1 when shifting n-1 bits. If there 
    is such a bit then it would show up as a positive value 
    and when it is !'d evaluate to false or 0. */
  
  int mask = x >> 31; /* all 0s if positive, all 1s if negative */
  
  return !(((~x & mask) + (x & ~mask)) >> (n + ~0)); /* (~x & mask) will negate negative values for positive bits after n-1 shift. */
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  /* fairly simple... litterally negate x and add 1. */
  
  int a = ~x + 1;
  
  return a;
}
/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
  /* Add x + y to equal s, if s overflowed negatively 
     then s will have a leading 0 making s being all 0s 
     when right shifting. If it overflowed positively 
     then s will have a 1 leading to s having all 1s 
     when right shifting. The statement (x^y) will 
     evaluate to all 1s if one x or y is negative and 
     the other is positive, this case will never overflow 
     and evaluate to 1 later in the function. If a=(x^y) 
     does equal all 1s then when you ~ it and & it with 
     (x^s) then this statement will evaluate to all 0s. 
     then in the final statement it will evaluate to 1 
     meaning it overflowed. If the opposite it true and it 
     did not overflow then it will evaluate to 0. */
  
  int s = x + y;
  int a;
  
  x = x >> 31;
  y = y >> 31;
  s = s >> 31;
  a = (x^y); /* checking for same sign x and y */
  a = (a & 0) | (~a & (x^s)); /* if did have same sign this will return in 1s meaning it has overflowed */
  
  return (a & 0) | (~a & 1); /* statement will return 0 if did overflow ~a = all 0s */
}
/* 
 * reverseBytes - reverse the bytes of x
 *   Example: reverseBytes(0x01020304) = 0x04030201
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 3
 */
int reverseBytes(int x) {
  /* I break it into 4 parts of 8 bits each by masking 
     each 8 bit segment with 8 bits of all 1s and store 
     the value as 1 of 4 parts. Then shift it to the 
     right 8 bits and repeat. Then shift each part 
     back in reverse order in the return. */ 
 
  int p1 = x  & 0xFF;
  int p2 = (x >> 8) & 0xFF;
  int p3 = (x >> 16) & 0xFF;
  int p4 = (x >> 24) & 0xFF;

  return (p1 << 24) | ( p2 << 16) | (p3 << 8) | p4;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 1 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  /* first I shift 1 all the way to the left to make largest 
     negative number. Then arithmatic right shift x n bits. 
     Then create a mask of n 0 bits starting from the right, 
     the rest of the bits in the mask are 1s. then apply the 
     mask to make how ever many bits we shifted to 0s 
     effectivly making a logical right shift. */

  int b;
  int d;
  
  int a = 0x1 << 31; 
  x = x >> n; /* arithmetic right will copy all 0s or 1s from rightmost */
  b = a >> n; /* makes a mask of n 1s starting from right */
  d = ~(b << 1); /* shifts b left by 1 to maintain x value and ~ it to make right most bits shifted all 0s */
 
  return x & d; /* returns 000001111... & number effectivly logicaly right shifting */
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  /* If x is 0 then the redefined x will be all 1s and if 
     you add 1 it will be come all 0s and apply a all ~0s(1s) 
     mask to z, effectivly returning z. Or if x is not 0 
     then the result of new x will be all 1s and the right 
     most character being a 0, then if you add 1 it will 
     be all ones which then effectivly &s to y and returns y. */

  x = ~(!!x) + 1; /* checks for value non-zero in x. Will return 11111.... if x==0. Will retun 000000... if x=/=0. */

  return (x & y) | (~x & z);  /* if new x was 0 then all 1s masked with y will return y. if not 0 ~x masked with z will return z */
}
/* 
 * sm2tc - Convert from sign-magnitude to two's complement
 *   where the MSB is the sign bit
 *   Example: sm2tc(0x80000005) = -5.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 */
int sm2tc(int x) {
  /* First we make a mask of 1 followed by 31 0s. Then we 
     make two masks one of all 0s and the other of all 1s, 
     later on depending on the number entered one will 
     capture the positive portion of the number, if any, 
     and the other will capture the negative portion. if 
     the number is negative we will convert it to it's 
     positive counter part by subtracting one and negating 
     the number. We then and that with x to capture if the 
     number is positive or negative in int sign. If the 
     number was negative then we subtract 1 from it and 
     negate the whole thing, which is the process of 
     switching signs on a number. We add all the number 
     portions and sign portion. */

  int mask = 1 << 31; /* simply 10000000... */
  int neg = (mask & x) >> 31; /* if x is negative this will capture all 1s. if positive all 0s */
  int pos = ~neg; /* captures the reverse. if x is negative pos is all 0s. if positive all 1s */
  int sign = mask & x; /* captures the sm sign of the number either being 0 for pos or 1 for neg */

  pos = pos & x;
  neg = neg & x;

  neg = ~(neg + ~0); /* if the number was negative we will make it's tc counter part here */

  return (neg + pos + sign);
}
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
  /* Basicly this keeps sorting our 32bit number in half. 
     For every pair of same bits it finds it will eliminate 
     the pair in the next sort, for every two 1s or 0s it 
     finds it replaces it with a 0 or 1, respectivly, and throws it to 
     the left. eventually you are left to shift one bit, 
     if there was an odd number of zeros this bit will 
     be a 1 after you xor it with the previous half. 
     Then we & it with 1, we obtain 1 mean odd number of zeros.*/

  x = ( x >> 16 ) ^ x;
  x = ( x >> 8 ) ^ x;
  x = ( x >> 4 ) ^ x;
  x = ( x >> 2 ) ^ x;
  x = ( x >> 1) ^ x;

  return (x & 1);
}
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 60
 *   Rating: 4
 */
int isPower2(int x) {
  /* if x is positive then sign ^ mask will be all 1s. If x is 
     a power of two then there will only be one 1 bit in the 
     number, when you subtract 1 from that it turns all the 
     bits to the right of it to 1s. Then you & that with x, 
     which if your number is a power of x will result in all 0s. 
     Bang that and you get 1. The +!x statement will compensate 
     if x = 0. */

  int mask = ~0; /* makes mask of 11111111111... */
  int sign = x >> 31; /* if x is pos then 0000... if neg 1111... */
  int minus = (mask ^ sign); /* will return 1111... if x was positive or 0000... if negative */

  return !((x & (x + minus)) + !x); /* subtract 1111...(-1) from x and & it with old x. if there was only one 1 value then it will return all 0s and ! to 1. if not it will return a value and ! to 0. */
}

/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  /* This is acctually pretty simple. If there are any 1s in 
     our binary number then we carry it/them down in a sense. 
     Each right shift and OR statement carries any 1s down till 
     we just have 1 bit left. If there was a 1 in any part of 
     our binary number then the final x will equal 1. Then 
     when we negate x it will have a 0 on the left most bit 
     if there are any any 1 bits from our original number. 
     & it with 1 and we return 0. the only case that it 
     will work is if all bits are 0. */
  
  x = ( x >> 16 ) | x;
  x = ( x >> 8 ) | x;
  x = ( x >> 4 ) | x;
  x = ( x >> 2 ) | x;
  x = ( x >> 1 ) | x;
  
  return ~x & 1;
}
/*
 * classLog2 - return floor(log base 2 of x), where x > 0
 *   Example: classLog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int classLog2(int x) {
  /* W first test if the leading 1 bit is in the left most 16 bits. 
     It should return 1 if n>= 16. If A did return 1 then we add 16 
     to the t. Then if A did return 1 then we would shift all 
     bits in xc to the right by 16, cutting the data we are 
     looking at in half. We then repeat the proccess cutting each 
     segment in half until we are left with the leading bit and 
     the count of its position. We then return t which is our 
     leading bit position and the value of our floor log base 2 of x.*/
        
  int a = !(!(x >> 16)); /* checks for most any bits in first 16 bits, ie most significant bits. if bit is in first 16 then will return 1, otherwise 0. */
  int t = 0; /* a counter for position of leading bit */
  int xc = x; /* a copy of x for which to shift and search */
  
  t = t + (a << 4); /* if a was 1 then add 16 to t because the most significant bit was in the first 16, hence a was 1. */
  xc = (((~a + 1) & (x >> 16)) + (~(~a + 1) & x)); /* if a did return 1 it shifts x's copy over 16 bits to do the next fold-search. */
  
  a = !(!(xc >> 8)); /* rinse and repeat */
  t = t + (a << 3);
  xc = (((~a + 1) & (xc >> 8)) + (~(~a + 1) & xc));
	
  a = !(!(xc >> 4));
  t = t + (a << 2);
  xc = (((~a + 1) & (xc >> 4)) + (~(~a + 1) & xc));
  
  a = !(!(xc >> 2));
  t = t + (a << 1);
  xc = (((~a + 1) & (xc >> 2)) + (~(~a + 1) & xc));
  
  a = !(!(xc >> 1));
  t = t + a;
  
  return t;
}
