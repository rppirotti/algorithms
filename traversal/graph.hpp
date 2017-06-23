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

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <list>
#include <string>
#include <vector>
#include <iostream>

namespace Graph {

   class Edge;

   ////////////////////////////////////////////////////////////////////////////
   ///
   ////////////////////////////////////////////////////////////////////////////
   class Vertex
   {
   public:
      Vertex ( int id, std::string name )
      : m_id      ( id )
      , m_name    ( name )
      , m_isVisited ( false )
      { }

      void AddEdge ( Edge* pEdge )
      {
         m_edgesList.push_back( pEdge );
      }

      std::list<Edge*>* getEdgeListPtr ()
      {
         return &m_edgesList;
      }

      std::string getName ()
      {
         return m_name;
      }

   private:
      int                  m_id;
      std::string          m_name;
      std::list < Edge* >  m_edgesList;
      bool                 m_isVisited;
   };


   ////////////////////////////////////////////////////////////////////////////
   ///
   ////////////////////////////////////////////////////////////////////////////
   class Edge
   {
   public:
      Edge ( int id, int weight, Vertex* pSrc, Vertex* pDst )
   : m_id ( id )
   , m_weight ( weight )
   , m_pSrcVertex ( pSrc )
   , m_pDstVertex ( pDst )
   , m_isVisited  ( false )
   {
         m_pSrcVertex->AddEdge( this );
         m_pDstVertex->AddEdge( this );
   }

   Vertex*  getSrcVertex ()
   {
      return m_pSrcVertex;
   }

   Vertex*  getDstVertex ()
   {
      return m_pDstVertex;
   }

   int getWeight ()
   {
      return m_weight;
   }
   private:
      int      m_id;
      int      m_weight;
      Vertex*  m_pSrcVertex;
      Vertex*  m_pDstVertex;
      bool     m_isVisited;
   };


   ////////////////////////////////////////////////////////////////////////////
   ///
   ////////////////////////////////////////////////////////////////////////////
   class SimpleGraph
   {
   public:
      SimpleGraph ( std::string name )
      : m_name ( name )
      {
      }

      void AddVertex ( Vertex* pVertex )
      {
         m_vertexList.push_back( pVertex );
      }

      void Display ( std::ostream& output )
      {
         output << "Graph: " << m_name << std::endl;
         for ( std::vector<Vertex*>::iterator it = m_vertexList.begin() ;
               it != m_vertexList.end() ;
               it++ )
         {
            output << "Vertex: " << (*it)->getName() << std::endl;
            std::list<Edge*>* pEdgeList = (*it)->getEdgeListPtr();
            for ( std::list<Edge*>::iterator it2 = pEdgeList->begin();
                  it2 != pEdgeList->end();
                  it2++ )
            {
               if ( (*it) != (*it2)->getSrcVertex() )
               {
                  output << "   Connected to: " << (*it2)->getSrcVertex()->getName() << "(" << (*it2)->getWeight() << " km)";
               }
               else
               {
                  output << "   Connected to: " << (*it2)->getDstVertex()->getName() << "(" << (*it2)->getWeight() << " km)";
               }
            }
            output << std::endl;
         }
      }

   private:
      std::string          m_name;
      std::vector<Vertex*> m_vertexList;

   };

}

#endif
