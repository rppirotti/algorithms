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
#include <utility>
#include <list>
#include <vector>

typedef std::vector<std::list<int>* > MatrixType;

void Dfs ( MatrixType& matrix, int* pVisited, long long numOfVertex, long long n, long long* pNumOfCities )
{
   if ( 0 == pVisited[n] )
   {
      pVisited[n] = 1;
      *pNumOfCities = *pNumOfCities + 1;

      int i = 0;
      for ( std::list<int>::iterator it = matrix[n]->begin();
            it != matrix[n]->end();
            it++ )
      {
         Dfs ( matrix, pVisited, numOfVertex, *it, pNumOfCities );
         i++;
      }
   }
}


int main ()
{
   int q = 0;
   long long n, m, clib, croad;
   MatrixType  matrix;
   int*  pVisited = NULL;

   // Input handle
   std::cout << "Queries: ";
   std::cin >> q;

   for ( int a=0; a < q; a++ )
   {
      for (int i=0; i < q; i++ )
      {
         std::cout << "Cities, roads, library cost, road cost: ";
         std::cin >> n >> m >> clib >> croad;

         std::cout << "Cities: " << n << std::endl;
         std::cout << "Roads: "  << m << std::endl;
         std::cout << "Library Cost: " << clib << std::endl;
         std::cout << "Road cost: " << croad << std::endl;

         // Create adjacent matrix for cities
         matrix.clear();
         matrix.resize(n);     // Allocate matrix for all cities

         pVisited        = new int[n]();
         for (long long i=0; i < n; i ++ )
         {
            matrix[i] = new std::list<int>;
         }

         for (long long i=0; i < m; i++ )
         {
            int u, v;
            std::cin >> u >> v;
            matrix[u-1]->push_back(v-1);
            matrix[v-1]->push_back(u-1);
         }
      }

      // Algorithm

      // If libraries are cheaper than roads, create one library at each city
      if ( clib < croad )
      {
         std::cout << clib * n;
      }
      else
      {
         // If libraries are the same cost or more expensive than roads, create one library and (cities - 1) roads for
         // each connected graph. So let's use a DFS to find how many graphs we have.

         std::list < long long > graphList;

         for (long long i = 0; i < n; i++ )
         {
            long long numOfCities = 0;
            Dfs (matrix, pVisited, n, i, &numOfCities );
            if ( numOfCities > 0 )
            {
               graphList.push_back( numOfCities );
            }
         }

         long long totalCost = 0;
         for ( std::list < long long >::iterator it = graphList.begin();
               it != graphList.end();
               it++ )
         {
            std::cout << "Num: " << *it << std::endl;
            totalCost += (*it - 1) * croad + clib;
         }
         std::cout << "Total: " << totalCost << std::endl;
         std::cout << totalCost << std::endl;
      }

   }

}

