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
#include <limits.h>

namespace Graph {

   class Edge;

   typedef  std::list < Edge* > EdgeList;

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
      , m_data    ( INT_MAX )
      { }

      void AddEdge ( Edge* pEdge )
      {
         m_edgesList.push_back( pEdge );
      }

      EdgeList* getEdgeListPtr ()
      {
         return &m_edgesList;
      }

      std::string getName ()
      {
         return m_name;
      }

      bool getIsVisited () const
      {
         return m_isVisited;
      }

      void SetIsVisited ()
      {
         m_isVisited = true;
      }

      int getData ()
      {
         return m_data;
      }

      void SetData ( int data )
      {
         m_data = data;
      }

      int getId ()
      {
         return m_id;
      }

   private:
      int                  m_id;
      int                  m_data;
      std::string          m_name;
      EdgeList             m_edgesList;
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

      typedef std::vector<Vertex*>  VertexList;

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
         for ( VertexList::iterator it = m_vertexList.begin() ;
               it != m_vertexList.end() ;
               it++ )
         {
            output << "Vertex: " << (*it)->getName() << std::endl;
            EdgeList* pEdgeList = (*it)->getEdgeListPtr();
            for ( EdgeList::iterator it2 = pEdgeList->begin();
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

      VertexList&   getVertexList ()
      {
         return m_vertexList;
      }

   private:
      std::string    m_name;
      VertexList     m_vertexList;

   };

}

#endif
