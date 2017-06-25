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
#include <queue>
#include <algorithm>

typedef std::vector < std::list<int>* > ListVector;

int main ()
{
   int q = 0;

   std::cout << "Queries: ";
   std::cin >> q;
   std::cout << q << std::endl;

   for (int query=0; query < q; query++ )
   {
      int      nodes  = 0;
      long int edges  = 0;     // All edges has weight of 6
      int      source = 0;

      std::cout << "Nodes, Edges: ";
      std::cin >> nodes >> edges;
      std::cout << nodes << "  " << edges << std::endl;

      // Our list of nodes
      ListVector  matrix;
      matrix.resize(nodes);
      int      visited  [ nodes ];
      long int distance [ nodes ];
      for ( int i=0; i < nodes; i++ )
      {
         matrix  [ i ] = new std::list<int>;
         visited [ i ] = 0;
         distance[ i ] = 0;
      }

      // Read input and create an incidence list
      for (long int i=0; i < edges; i++ )
      {
         int u, v;
         std::cin >> u >> v;
         if ( std::find ( matrix[u-1]->begin(), matrix[u-1]->end(), (v-1) ) == matrix[u-1]->end() )
         {
            matrix[u-1]->push_back(v-1);
            matrix[v-1]->push_back(u-1);
         }
      }

      std::cout << "Source: ";
      std::cin >> source;
      std::cout << source << std::endl;

      // Run BFS
      bool  hasFinished = false;
      int   currentNode = source - 1;
      int   level       = 0;
      std::queue<int>   queue;
      while ( false == hasFinished )
      {
         level++;
         visited [ currentNode ] = 1;

         for ( std::list<int>::iterator it = matrix[currentNode]->begin();
               it != matrix[currentNode]->end();
               it ++ )
         {
            if ( 0 == visited [ *it ] )
            {
               queue.push(*it );
               visited [ *it ] = 1;
               distance[ *it ] = (long int)level * (long int)6;
            }
         }
         if ( false == queue.empty() )
         {
            currentNode = queue.front();
            queue.pop();
         }
         else
         {
            hasFinished = true;
         }
      }

      // Output
      for ( int i=0; i < nodes; i++ )
      {
         if ( (source - 1) != i )
         {
            std::cout << (( 0 == distance [ i ] ) ? -1 : distance [ i ]) ;
            std::cout << " ";
         }
      }
   }
}

