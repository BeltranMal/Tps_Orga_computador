/*
 * CS:APP Data Lab
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
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


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
// 1
/*
 * bitAnd - x&y using only ~ and |
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y)
{
  int resultado = ~(~x | ~y);
  return resultado;
}
/*
 * bitMatch - Create mask indicating which bits in x match those in y
 *            using only ~ and &
 *   Example: bitMatch(0x7, 0xE) = 0x6
 *   Legal ops: ~ & |
 *   Max ops: 14
 *   Rating: 1
 */
int bitMatch(int x, int y)
{
  return ((~x) & (~y)) | (x & y);
}
/*
 * bitNor - ~(x|y) using only ~ and &
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitNor(int x, int y)
{
  return (~x & ~y);
}
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y)
{
  return (~(x & y)) & (~((~x & ~y)));
}
// 2
/*
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x)
{

  int mascara = 170;
  int mascara_32 = (mascara << 24) | (mascara << 16) | (mascara << 8) | mascara;
  return !(~(x & mascara_32) & mascara_32);
}
/*
 * anyEvenBit - return 1 if any even-numbered bit in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples anyEvenBit(0xA) = 0, anyEvenBit(0xE) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyEvenBit(int x)
{
  int mascara = 85;
  int mascara_32 = (mascara << 24) | (mascara << 16) | (mascara << 8) | mascara;
  return !!(x & mascara_32);
}
/*
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m)
{
  int mascara = 255;
  int desplazamiento_n = n << 3;
  int desplazamiento_m = m << 3;
  int byte_n = (mascara << desplazamiento_n);
  int byte_m = (mascara << desplazamiento_m);
  int x_filtrado = x & (~(byte_n | byte_m));
  int swap_n = ((x >> desplazamiento_n) & mascara) << desplazamiento_m;
  int swap_m = ((x >> desplazamiento_m) & mascara) << desplazamiento_n;

  return x_filtrado | (swap_n | swap_m);
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
int fitsBits(int x, int n)
{

  int shift = x << (32 + (~n + 1)); 
  int reestablecemos = shift >> (32 + (~n + 1));
  int resultado = !(reestablecemos ^ x);
  return resultado;
}
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x)
{
  return (~x) + 1;
}
/*
 * sign - return 1 if positive, 0 if zero, and -1 if negative
 *  Examples: sign(130) = 1
 *            sign(-23) = -1
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 2
 */
int sign(int x)
{
  /* al hacer x >> 31 nos traemos el msb a la posicion del lsb
    + caso que msb = 0 => 0000 0000 = 0 ()
    + caso que msb = 1 => 1111 1111 = -1
  - siendo x positivo distinto de 0, x = 0100 0000, de modo que el msb = 0
    -> terminaria retornando 0, entonces habria que hacerlo 1
    -> pero solo lo hacemos 1 cuando el nro es positivo
    -> si el nro es 0 entonces no lo modificamos
  - si x fuera negativo caemos en el caso de msb = 1
    -> obteniendo 1111 1111 y a este no le afectaria sumarle (OR) 0 o 1
  */

  return ((!(!x)) | (x >> 31));
}
// 3
/*
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y)
{
  int mascara = 128;
  int mascara_32 = mascara << 24;
  int signo_x = x & mascara_32;
  int signo_y = y & mascara_32;
  int signo_sum = (x + y) & mascara_32;

  return !((signo_sum ^ signo_x) & (signo_sum ^ signo_y));
}
/*
 * bitMask - Generate a mask consisting of all 1's
 *   lowbit and highbit
 *   Examples: bitMask(5,3) = 0x38
 *   Assume 0 <= lowbit <= 31, and 0 <= highbit <= 31
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int bitMask(int highbit, int lowbit)
{
  int mascara = 255;
  int mascara_32 = mascara << 24 | mascara << 16 | mascara << 8 | mascara;
  int filtro_highbit = mascara_32 << highbit;
  int filtro_lowbit = mascara_32 << lowbit;
  int filtro = (filtro_highbit << 1) ^ (filtro_lowbit);
  int resta = highbit + (~lowbit + 1);
  int signo_resta = (resta >> 31);
  return (~(signo_resta)) & filtro;
}
/*
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z)
{
  int es_true = !!(x);
  int situacion = ((es_true << 31) >> 31);
  int resultado = ((situacion ^ z) & z)| (situacion & y);
  return resultado;
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
int isAsciiDigit(int x)
{
  int minimo = 48;
  int maximo = 57;
  int mayor_a_minimo = x + (~minimo + 1); 
  int signo_menor = !(mayor_a_minimo >> 31); 
  int menor_a_maximo = maximo + (~x + 1); 
  int signo_mayor = !(menor_a_maximo >> 31);  
  int resultado = (signo_mayor & signo_menor);

  return resultado;
}
/*
 * isGreater - if x > y  then return 1, else return 0
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y)
{
  int signo_x = x>>31;
  int signo_y = y>>31;
  return (!(signo_x & ~signo_y))&(!((!(signo_x ^ signo_y)) & (x+~y)>>31));
  
}

/*
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c)
{
  int mascara = 255;
  int x_filtrado = x & (~(mascara << (n << 3)));
  int c_posicionado = c << ((n << 3));
  return x_filtrado | c_posicionado;
}
// 4
/*
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x)
{
  int signo_x = x >> 31;
  return (x ^ signo_x) + (~signo_x + 1);
}
/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int bang(int x)
{
  return (~(x | (~x + 1)) >> 31) & 1;
}
/*
 * isNonZero - Check whether x is nonzero using
 *              the legal operators except !
 *   Examples: isNonZero(3) = 1, isNonZero(0) = 0
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int isNonZero(int x)
{
  return ((x | (~x + 1)) >> 31) & 1;
}
/*
 * logicalNeg - implement the ! operator, using all of
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int logicalNeg(int x)
{
  return (~(x | (~x + 1)) >> 31) & 1;
}
// float
/*
 * floatAbsVal - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatAbsVal(unsigned uf)
{
  unsigned infinito = 255 << 23;
  unsigned mascara = 1 << 31;
  unsigned abs = uf & ~mascara;
  if (abs  >  infinito)
  {
    return uf;
  }
  return uf & ~(1 << 31);
}
/*
 * floatIsEqual - Compute f == g for floating point arguments f and g.
 *   Both the arguments are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   If either argument is NaN, return 0.
 *   +0 and -0 are considered equal.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 25
 *   Rating: 2
 */
int floatIsEqual(unsigned uf, unsigned ug)
{
 
  unsigned infinito = 255 << 23;
  unsigned mascara = 1 << 31;
  unsigned abs_uf = uf & ~mascara;
  unsigned abs_ug = ug & ~mascara;

  if ((abs_uf  >  infinito))
  {
    return 0;
  }

  if (abs_ug > infinito)
  {
    return 0;
  }

  if (((!(abs_uf ^ 0) && !(abs_ug ^ 0))))
  {
    return 1;
  }

  return  !((uf) ^ (ug));
}
/*
 * floatNegate - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatNegate(unsigned uf)
{
  unsigned infinito = 255 << 23;
  unsigned mascara = 1 << 31;
  unsigned abs = uf & ~mascara;
  if (abs > infinito)
  {
    return uf;
  }

  return uf + (1 << 31);
}
/*
 * floatIsLess - Compute f < g for floating point arguments f and g.
 *   Both the arguments are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   If either argument is NaN, return 0.
 *   +0 and -0 are considered equal.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 3
 */
int floatIsLess(unsigned uf, unsigned ug)
{
  int mascara = 1;
  int mascara_32 = mascara << 31;
  unsigned infinito = 255 << 23;
  int parte_fraccionaria = ~(infinito + mascara_32);
  unsigned abs_uf = uf & ~mascara_32;
  unsigned abs_ug = ug & ~mascara_32;
  int signo_uf = (uf >> 31) & mascara;
  int signo_ug = (ug >> 31) & mascara;
  int frac_uf = parte_fraccionaria & uf;
  int frac_ug = parte_fraccionaria & ug;
  int exp_uf = (uf & infinito) ;
  int exp_ug = (ug & infinito) ;

  if ((abs_uf  >  infinito) )
  { 
    return 0;
  }
  if (abs_ug  >  infinito)
  {
    return 0;
  }

  if ((abs_uf == 0) && (abs_ug == 0))
  {
    return 0;
  }

  if (signo_uf != signo_ug) 
  {
    return (signo_uf > signo_ug);
  }
  
  if(exp_uf != exp_ug)
  {
    return (exp_uf< exp_ug) ^ (signo_uf); 
  } 

  if( frac_uf != frac_ug)
  {
    return (frac_uf < frac_ug) ^ (signo_uf);
  }

  return 0;
}
/*
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf)
{
  int bit_signo = 1 << 31;
  int bias = 127;
  int infinito = 255 << 23;
  
  // sabemos que E = exp - bias / E = es la cantidad de bits luego del punto
  int exp_uf = (uf & infinito) >> 23;
  int signo_uf = !!(uf & bit_signo);
  int frac_uf = uf & (~(infinito + bit_signo)); // la parte frac debe tener 23 bits
  
  int e_uf = exp_uf - bias;
  unsigned abs_uf = uf & ~bit_signo;
  unsigned fuera_de_rango = 128 << 24; //10000000 0000000 0000000 00000000
  int e_max = 30;
  int resultado;
  
  // Caso de si es Nan o Infinito
  // o Caso de que se me haya pasado de rango
  if (abs_uf > infinito || e_uf > e_max)
  {
    return fuera_de_rango;
  }
  // Valor desnormalizado cuando el exp_uf = 00...0 => valores mas cercanos al 0,0
  // si la frac_u = 00...0 entonces representa el valor 0 
  if(exp_uf == 0)
  {
    return 0;
  }

  if (e_uf < 0)
  {
    return 0;
  }
  if (e_uf > e_max){
    return fuera_de_rango;
  }


  // Caso de Valor normalizado!
  // le agregamos el 1
  resultado = frac_uf | (128 << 16);

  // Segun si E es menor a 23 entonces shifteamos a la derecha
  // Caso inverso a la izquierda, para reconstruir el nro
  if (e_uf < 23)
  {
    resultado = resultado >> (23 - e_uf);
  } else
  {
    resultado = resultado << (e_uf - 23);
  }

  // si el signo_uf != 0 => hacemos negativo el numero
  if (signo_uf)
  {
    return ~resultado + 1;
  }
  // en el otro caso retornamos el numero normal
  return resultado;
}
/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatPower2(int x)
{
  int bias =127;
  int exp_x = x+bias; 
  int frac = 23;
  int exp_max =255;
  unsigned infinito = exp_max << frac;

  if(exp_x>=exp_max)//fuerad del rango
  {
    return infinito;
  }

  if(!((x>>31) &1) && exp_x <exp_max )//cuando estamos adentro del rango
  {
    return exp_x<<frac;
  }


  return 0;//cuando el resultado es muy cerca a 0 pero no es 0


}
