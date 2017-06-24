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

#include "graph.hpp"
#include <algorithm>
#include <iomanip>

using namespace Graph;

void Dijkstra ( std::ostream& output, SimpleGraph* pGraph, std::string sourceName )
{
   SimpleGraph::VertexList& pVertexList = pGraph->getVertexList();
   Vertex*  pSourceVertex = NULL;

   bool hasFound = false;
   for ( SimpleGraph::VertexList::iterator it = pVertexList.begin();
         it != pVertexList.end() || false == hasFound;
         it++)
   {
      if ( 0 == (*it)->getName().compare(sourceName) )
      {
         hasFound = true;
         pSourceVertex = (*it);
      }
   }

   output << "======================================" << std::endl;
   output << "Source: " << pSourceVertex->getName() << std::endl;

   pSourceVertex->SetData( 0 );
   pSourceVertex->SetIsVisited();

   bool  start = true;
   SimpleGraph::VertexList::iterator it = pVertexList.begin();
   SimpleGraph::VertexList::iterator ItOffset = std::find (pVertexList.begin(), pVertexList.end(), pSourceVertex );
   std::advance ( it, std::distance ( it, ItOffset )  );
   SimpleGraph::VertexList::iterator itEnd = it;

   for ( ;
         it != itEnd || start;
         it++ )
   {
      if ( pVertexList.end() == it )
      {
         it = pVertexList.begin();
         start = false;
      }
      output << (*it)->getName() << "   ";

      ///////////////////////////////////////////////////////////
      // Next block gets the shortest edge from current Vertex //
      ///////////////////////////////////////////////////////////
      int minWeight                    = INT_MAX;
      EdgeList::iterator   minWeightIt;
      for ( EdgeList::iterator itEdges = (*it)->getEdgeListPtr()->begin() ;
            itEdges != (*it)->getEdgeListPtr()->end();
            itEdges++ )
      {
         if ( (*itEdges)->getWeight() < minWeight )
         {
            minWeight   = (*itEdges)->getWeight();
            output << "Min weight: " << minWeight << std::endl;
            minWeightIt = itEdges;
         }
      }
      ///////////////////////////////////////////////////////////


      start = true;
      EdgeList::iterator itEdges = minWeightIt;
      std::advance ( itEdges, std::distance ( itEdges, minWeightIt )  );
      EdgeList::iterator itEdgesEnd = itEdges;
      for ( ;
            itEdges != itEdgesEnd || start;
            itEdges++ )
      {
         if ( (*it)->getEdgeListPtr()->end() == itEdges )
         {
            itEdges = (*it)->getEdgeListPtr()->begin();
            start   = false;
         }


         Vertex* pVertex = NULL;
         if ( (*it) != (*itEdges)->getSrcVertex() )
         {
            pVertex = (*itEdges)->getSrcVertex();
         }
         else
         {
            pVertex = (*itEdges)->getDstVertex();
         }

         if ( (*itEdges)->getWeight() + (*it)->getData() < pVertex->getData() )
         {
            pVertex->SetData( (*itEdges)->getWeight() + (*it)->getData() );
            output << "Vertex: " << pVertex->getName() << " - data: " << pVertex->getData() << std::endl;
         }
      }


      (*it)->SetIsVisited();
   }

   output << std::endl;
}

int*  createAdjacentArray ( SimpleGraph* pGraph )
{
   // Allocate a 2D array as a single block of memory
   int*   pAdjacentArray = new int[ pGraph->getVertexList().size() * pGraph->getVertexList().size() ];
   for ( int i=0; i < pGraph->getVertexList().size() * pGraph->getVertexList().size(); i++ )
   {
      pAdjacentArray[i] = INT_MAX;
   }

   // Next we will fill the 2D adjacent array with the data stored inside Graph vertices and edges
   int graphListSize = pGraph->getVertexList().size();
   for ( int row=0; row < graphListSize; row++ )
   {
      for ( int column=0; column < graphListSize; column++ )
      {
         Vertex*  pVertex = NULL;
         bool isFound = false;
         for ( SimpleGraph::VertexList::iterator it = pGraph->getVertexList().begin();
               it != pGraph->getVertexList().end() || false == isFound;
               it++ )
         {
            if ( column == (*it)->getId() )
            {
               pVertex = *it;
               isFound = true;
            }
         }

         for ( EdgeList::iterator it = pVertex->getEdgeListPtr()->begin();
               it != pVertex->getEdgeListPtr()->end();
               it++ )
         {
            if ( ( row    == (*it)->getDstVertex()->getId() &&
                   column == (*it)->getSrcVertex()->getId() ) ||
                 ( row    == (*it)->getSrcVertex()->getId() &&
                   column == (*it)->getDstVertex()->getId() )
               )
            {
               pAdjacentArray [ row * graphListSize + column ] = (*it)->getWeight();
            }
         }
      }
   }

   return pAdjacentArray;
}

void DijkstraOptimized ( std::ostream& output, SimpleGraph* pGraph, std::string sourceName )
{
   int*  pAdjacentArray = createAdjacentArray( pGraph );
   int   sourceIndex    = 0;
   int   graphListSize  = pGraph->getVertexList().size();

   // Print array output for debugging
   for ( int row=0; row < graphListSize; row++ )
   {
      for ( int column=0; column < graphListSize; column++ )
      {
         output << std::setw(10) << pAdjacentArray [ row * graphListSize + column ] << " ";
      }
      output << std::endl;
   }

   // Array to hold minimum calculated distances
   int*  pMinDistance   = new int[graphListSize];
   for ( int i=0; i < graphListSize; i++ )
   {
      pMinDistance[i] = INT_MAX;
   }

   // Array to hold vertices already visited
   bool* pVertexVisited = new bool[graphListSize];
   for ( int i=0; i < graphListSize; i++ )
   {
      pVertexVisited[i] = false;
   }

   for ( int i=0; i < graphListSize; i++ )
   {
      pMinDistance [i] = pAdjacentArray[sourceIndex * graphListSize + i ];
   }

   // Loop preparation
   pMinDistance   [ sourceIndex ] = 0;
   pVertexVisited [ sourceIndex ] = true;
   bool hasFinished = false;
   while ( false == hasFinished )
   {
      // Initialize control vars with lower/max values
      int currentVertex = -1;
      int lowerDistance = INT_MAX;

      // Identify shortest vertex connected to the current vertex being visited
      for ( int i=0; i<graphListSize; i++ )
      {
         if ( false == pVertexVisited[i] && pMinDistance[i] < lowerDistance )
         {
            currentVertex = i;
            lowerDistance = pMinDistance[i];
         }
      }
      // If did not find, then the algorithm is over
      if ( -1 == currentVertex )
      {
         hasFinished = true;
      }
      else
      {
         // Mark current vertex and save shortest path
         pVertexVisited [ currentVertex ] = true;
         pMinDistance   [ currentVertex ] = lowerDistance;

         // Check neighboors of current vertex
         for ( int i=0; i<graphListSize; i++ )
         {
            // Consider only vertices that has edges between them - other ones are marked with INT_MAX
            if ( pAdjacentArray[currentVertex * graphListSize + i] != INT_MAX )
            {
               pMinDistance [ i ] = std::min (pMinDistance[i], pMinDistance[ currentVertex ] + pAdjacentArray[currentVertex * graphListSize + i] );
            }
         }
      }
   }

   for ( int i=0; i < graphListSize; i++ )
   {
      output << (int)pMinDistance [i] << "     ";
   }
   output << std::endl;
}

struct VertexInfo
{
   int   m_id;
   int   m_valence;
   int   m_color;
};

bool orderByValence ( VertexInfo a, VertexInfo b)
{
   bool status = false;
   if ( a.m_valence > b.m_valence )
   {
      status = true;
   }
   return status;
}

void WelshPowellColoredGraph ( std::ostream& output, SimpleGraph* pGraph )
{
   int*  pAdjacentArray = createAdjacentArray( pGraph );
   int   numOfVertex    = pGraph->getVertexList().size();

   std::vector <VertexInfo> vertexList ( numOfVertex );

   for (int row=0; row < numOfVertex; row++ )
   {
      int numOfEdges = 0;
      for ( int column = 0; column < numOfVertex; column++ )
      {
         if ( pAdjacentArray [row * numOfVertex + column] != INT_MAX )
         {
            numOfEdges++;
         }
      }
      vertexList[ row ].m_id      = row;
      vertexList[ row ].m_valence = numOfEdges;
      vertexList[ row ].m_color   = 0;
   }

   std::sort(vertexList.begin(), vertexList.end(), orderByValence );

   for (std::vector<VertexInfo>::iterator it = vertexList.begin();
         it != vertexList.end();
         it++ )
   {
      output << "Id: " << it->m_id << " Valence: " << it->m_valence << std::endl;
   }

   int color = 1;

   // Set the color for first vertex (highest valence)
   vertexList[0].m_color = color;


   for ( int i=1; i < numOfVertex; i++ )
   {
      bool isConnected = true;
      for (std::vector<VertexInfo>::iterator it = vertexList.begin();
            it != vertexList.end();
            it++ )
      {
         if ( ( INT_MAX != pAdjacentArray [ i * numOfVertex + it->m_id ] && it->m_color != color ) ||
               INT_MAX == pAdjacentArray [ i * numOfVertex + it->m_id ] )
         {
            isConnected = false;
         }
      }
      if ( false == isConnected )
      {
         vertexList [ i ].m_color = color;
      }
   }

   for (std::vector<VertexInfo>::iterator it = vertexList.begin();
         it != vertexList.end();
         it++ )
   {
      output << "Id: " << it->m_id << " Valence: " << it->m_valence << " Color: " << it->m_color << std::endl;
   }

}

int main ()
{
   SimpleGraph*   pGraph = new SimpleGraph( "ValeDosSinos" );

   Vertex*  pVertex0 = new Vertex ( 0, "Novo Hamburgo" );
   Vertex*  pVertex1 = new Vertex ( 1, "Sao Leopoldo" );
   Vertex*  pVertex2 = new Vertex ( 2, "Campo Bom" );
   Vertex*  pVertex3 = new Vertex ( 3, "Ivoti" );
   Vertex*  pVertex4 = new Vertex ( 4, "Estancia Velha" );
   Vertex*  pVertex5 = new Vertex ( 5, "Dois Irmaos" );
   Vertex*  pVertex6 = new Vertex ( 6, "Presidente Lucena" );

   new Edge (0, 10, pVertex1, pVertex0 );
   new Edge (1,  5, pVertex0, pVertex2 );
   new Edge (2, 20, pVertex0, pVertex5 );
   new Edge (3,  5, pVertex2, pVertex5 );
   new Edge (4,  8, pVertex0, pVertex4 );
   new Edge (5,  8, pVertex4, pVertex3 );
   new Edge (6, 15, pVertex0, pVertex3 );
   new Edge (7,  9, pVertex3, pVertex6 );

   pGraph->AddVertex( pVertex1 );
   pGraph->AddVertex( pVertex0 );
   pGraph->AddVertex( pVertex2 );
   pGraph->AddVertex( pVertex3 );
   pGraph->AddVertex( pVertex4 );
   pGraph->AddVertex( pVertex5 );
   pGraph->AddVertex( pVertex6 );

   pGraph->Display( std::cout );

   //DijkstraOptimized( std::cout, pGraph, "Novo Hamburgo" );
   WelshPowellColoredGraph (std::cout, pGraph);

}


