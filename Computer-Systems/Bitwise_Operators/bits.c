/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
  // This is equivalent to x | y when working out the logic table
  return ~(~x & ~y);
}



/*
 * isZero - returns 1 if x == 0, and 0 otherwise 
 *   Examples: isZero(5) = 0, isZero(0) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int isZero(int x) {
  // If x is 0, this will return its opposite (1)
  // Else, x will be true, so its opposite will be (0)
  return !x;
}



/* 
 * minusOne - return a value of -1 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void) {
  // As per the complement operator's axioms, 1 is first added to the number.
  // Then, the additive inverse of the number is taken.
  // For 0, we will first get 1 as (0 + 1 = 1)
  // Then, the additive inverse of 1 is -1, so we will get -1.
  return ~0;
}



/* 
 * anyOddBit - return 1 if any odd-numbered bit in word set to 1
 *   Examples anyOddBit(0x5) = 0, anyOddBit(0x7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyOddBit(int x) {
  // A comparison bit of 0 is first provided that represents 0xAAAAAAAA (all 1010...)
  int cmp = 0xAA, ans;
  cmp <<= 8;
  cmp += 0xAA;
  cmp <<= 8;
  cmp += 0xAA;
  cmp <<= 8;
  cmp += 0xAA; //cmp = 0xAAAAAAAA

  // This set ans as only consisting of the bits in the odd places.
  ans = x & cmp;

  // If ans is 0, then there were no bits in the odd places.
  // Else, then there were and the return statement will return the boolean representing this
  return !!ans;
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
  // Extracts the signs by checking whether the first bit in the string is 0 or 1.
    // 0 = negative and 1 = positive
  int signx = !(x >> 31), signy = !(y >> 31);

  // test1 checks if the signs differ.
    // if signx != signy, then no overflow can possibly occur
  int test1 = signx ^ signy;

  // test2 checks if the sign of x differs from the sign of x + y
    // 0 = the signs differ and 1 = the signs are synonmous
  int test2 = !(signx ^ !((x + y) >> 31));

  // if either or both tests are 1, then these numbers can be added without overflow
  // else if both tests are 0, then these numbers will overflow
  return test1 | test2;
}



/* 
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2 
 */
int leastBitPos(int x) {
  // first, it finds the complement of x, but adding 1 will cause a ripple until a 0 is reached,
  // which will be where the least significant bit is inside of the original string
  // since that is where it was first 1.
  // Then, we AND it by its original value to return the bit position where the least
  // significant bit in x is, and since we took the complement of x, all other bits of (~x + 1) and x will be
  // opposites, so this will always return the least significant bit. 
  return (~x + 1) & x;
}



/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  // test_less checks to see if x is less than 0x30 exclusive by adding the complement of 0x2F.
  // if x < 0x30, then this value will be negative.
  int test_less = x + ~0x2F;

  // test_greater checks to see if x is greater than 0x3A in a similar to method to checking if it was less than 0x30.
  // if the complement of x is greater than 0x3A, then will return negative.
  int test_greater = ~x + 0x3A;

  // if either of these tests return negative (i.e., 1) then this is not an ascii digit
  // else, then the 32nd bit will be positive and both tests will have been passed.
  return !((test_less | test_greater) >> 31);
}



/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  // This checks if x is 0 or not.
    // if x is 0, then its inverse boolean val will be 0x1 and, after bit shifting, will be 0xFFFFFFFF
      // this is to show that x is true
    // else x is not 0, then its inverse boolean val will be 0x0 and, after bit shifting, will be 0x00000000
      // this is to show that x is false
  int cmp = ((!x) << 31) >> 31;

  // If x is false, then z will & to 0x0
  // Else, then ~cmp will & to 0
  // thus eliminating either the left or right side of the OR statement
  // Which resembles a makeshift conditional
  return (cmp & z) | (~cmp & y);

}



/* 
 * reverseBytes - reverse the bytes of x
 *   Example: reverseBytes(0x01020304) = 0x04030201
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 3
 */
int reverseBytes(int x) {
  // gets the last byte by itself
  int byte1 = (x >> 24) & 0xff;

  // gets the third byte by itself
  int byte2 = (x >> 16) & 0xff;

  // gets the second byte by itself
  int byte3 = (x >> 8) & 0xff;

  // gets the first byte by itself 
  int byte4 = x & 0xff;

  // This now shifts all of the bytes into their opposite locations
  // and combines them with OR statements to return the reverse byte string
  return (byte1) | (byte2 << 8) | (byte3 << 16) | (byte4 << 24);
}



/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  // starts by creating the mask of 1000100010001000... and the mask 00...0000111100001111
  int m = 0x11 ^ (0x11 << 8) ^ (0x11 << 16) ^ (0x11 << 24), m2 = 0xf ^ (0xf << 8);

  // creates an answer variable and adds the AND value of the 0-3 bit shifted x value with our first mask
    // this is performed four times to represent the total number of bits in our original string.
  // we are left the combined number of all of the bits within our original integer
  int ans = x & m;
  ans += (x >> 1) & m;
  ans += (x >> 2) & m;
  ans += (x >> 3) & m;

  // we wend by returning the answer. 
  return ans;
}



/*
 * satAdd - adds two numbers but when positive overflow occurs, returns
 *          maximum possible value (Tmax), and when negative overflow occurs,
 *          it returns minimum negative value (Tmin)
 *   Examples: satAdd(0x40000000,0x40000000) = 0x7fffffff
 *             satAdd(0x80000000,0xffffffff) = 0x80000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 4
 */
int satAdd(int x, int y) {
  // this test checks whether the sign of the sum matches both x and y
  // if the overflow is 0, then no overflow occurred
    // explanation: if the sum and x are the same, the xor will be 0.
  // if the signs are different, for both of them, then overflow will have happened
  int test_overflow = (((x + y) ^ x) & ((x + y) ^ y)) >> 31;

  // LHS of XOR: if there is no overflow, then only the sum is on the LHS
  // LHS of XOR: else, then it will bitshift to the right by 1 to represent either TMAX or TMIN depending on the LHS.
  // RHS of XOR: if there is no overflow, then no sign change is necessary.
  // RHS of XOR: if there is overflow, then a sign change will be present to adjust the sign to be either TMAX or TMIN
    // depending on if the sign of the sum and the overflow. (this is basically just a correction factor)
  return ((x + y) >> test_overflow) ^ (test_overflow << 31);
}



/*
 * trueFiveEighths - multiplies by 5/8 rounding toward 0,
 *  avoiding errors due to overflow
 *  Examples: trueFiveEighths(11) = 6
 *            trueFiveEighths(-9) = -5
 *            trueFiveEighths(0x30000000) = 0x1E000000 (no overflow)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 4
 */
int trueFiveEighths(int x)
{
  // By using the power of 2 division principle from the textbook, this statement is equivalent
  // to dividing the given integer by 8.
  int div = x >> 3;

  // This statement will return the remainder of dividing the integer by 8 (if there is one)
  int rem = x & 7;

  // This statement creates a bit mask for 
  int m = x >> 31 & 7;

  // ~Progressing from left to right~
  // 1. the quotient is first added to itself multiplied by 5
  // 2. the remainder is then added to itself multiplied by 5
  // 3. then, the sign of the original value is taken
    // 111... is -; 000... is +
  // 4. the sign is then taken and then taken mod 8 to get either 111 (7) or 000 (0) 
    // this mask is used to account for negative numbers
  // 5. then, the mod 8 value and the negative mask are added and divided by 8 to compensate for our original division process.
  // 6. finally, the quotient and divided remainder + negative mask are added. 
  return (div + (div << 2)) + (rem + (rem << 2) + (x >> 31 & 7) >> 3);
}



/*
 * Extra credit
 */
/* 
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {
  //Removes the sign
  unsigned abs_val = 0x7FFFFFFF & uf;
  
  //Checks if abs_val is above min nan NaN
    // if it is, then return the original
    // else, then return the abs_val
  if (abs_val > 0x7F800000) return uf;
  else return abs_val;
}



/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  // declares the sign, exponent, and fraction value
  unsigned s = uf & 0x80000000, e = uf & 0x7F800000, f = uf & 0x7FFFFF;

  // Checks if the exponent is NaN
  if (e == 0x7F800000) return uf;

  // if the exponent is 0, just return the signed fraction multiplied by 2
  if (e == 0x0) return (s ^ (f << 1));

  // recombines everything and multiplies exponent by 2
  return (s ^ (e + (1 << 23)) ^ f);
}
