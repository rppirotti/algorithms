/*
 *   Copyright 2017 Rodolfo P
 *
 *   Permission is hereby granted, free of charge, to any person obtaining a
 *   copy of this software and associated documentation files (the "Software"),
 *   to deal in the Software without restriction, including without limitation
 *   the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *   and/or sell copies of the Software, and to permit persons to whom the
 *   Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included
 *   in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 *   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 *   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *   OTHER DEALINGS IN THE SOFTWARE.
 */


#include <iostream>

int factorial ( int number )
{
   int result = 1;

   if ( 0 != number )
   {
      result = number * factorial(number - 1);
   }

   return result;
}


#define ARRAY_SIZE 50

int* multTwoArrays ( int* p1, int* p2)
{
   int* pResult = new int [ ARRAY_SIZE ]();

   int carry     = 0;
   int carrySum  = 0;
   int dstOffset = 0;

   for (int p1Index=0; p1Index < ARRAY_SIZE; p1Index++ )
   {
      for ( int p2Index=0; p2Index < ARRAY_SIZE; p2Index++ )
      {
         int value = p1[p1Index] * p2[p2Index] + carry;
         if ( value >= 10 )
         {
            carry = value - 9;
            value = 0;
         }
         if ( pResult [ dstOffset + p2Index ] + value + carrySum >= 10 )
         {
            carrySum = pResult [ dstOffset + p2Index ] + value + carrySum- 9;
            pResult [ dstOffset + p2Index ] = 0;
         }
         else
         {
            pResult [ dstOffset + p2Index ] += value + carrySum;
         }
      }
   }

   return pResult;
}

int* subtractOneFromArray ( int* pArray )
{
   int* pResult = new int[ARRAY_SIZE]();

   int carry = 0;
   for (int i=0; i<ARRAY_SIZE; i++ )
   {
      if(  pArray [i] - 1 < 0 )
      {
      }
   }

}


int* factorial ( int* pArray )
{
   int* pResult = new int [ ARRAY_SIZE ]();
   pResult [0] = 1;

   // Check if array all zeroes - if yes, return 1 (0! = 1)
   bool areAllZeroes = true;
   for (int i=0; i < ARRAY_SIZE; i++ )
   {
      if ( pArray [ i ] != 0 )
      {
         areAllZeroes = false;
      }
   }

   if ( true == areAllZeroes )
   {
      pResult = multTwoArrays( pArray,  factorial ( pArray - 1 ) );




      //result = number * factorial(number - 1);
   }

   return pResult;
}


int multiplyArrayX (int* pArray, int x, int numSize)
{
   int carry = 0;
   int localNumSize = numSize;

   for (int i=0; i<numSize; i++ )
   {
      int value = pArray[i] * x + carry;
      pArray [i] = value % 10;            //Store last digit
      carry = value / 10;
   }

   while ( carry )
   {
      pArray[localNumSize] = carry %10;
      carry = carry / 10;
      localNumSize++;
   }
   return localNumSize;
}

//int main ()
//{
//   int number = 0;
//
//   std::cin >> number;
//
//   std::cout << "number: " << number << std::endl;
//   std::cout << "factorial: " << factorial( number ) << std::endl;
//
//   int*  pArray  = new int[ ARRAY_SIZE ]();
//   int   numSize = 1;
//
//   pArray [ 0 ] = 1;   // Initialize with 1 (most-right aligned)
//
//   for (int i=2; i<= number; i++ )
//   {
//      numSize = multiplyArrayX(pArray, i, numSize);
//   }
//
//   for (int i=numSize-1; i >= 0; i-- )
//   {
//      std::cout << pArray[i];
//   }
//
//   std::cout << std::endl;
//
//}



