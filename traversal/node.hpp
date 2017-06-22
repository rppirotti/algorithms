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

#ifndef TRAVERSAL_NODE_HPP_
#define TRAVERSAL_NODE_HPP_

#include <list>
#include <string>

namespace Graph {

   class Node
   {
   public:
      Node ( int id )
      : m_id      ( id )
      , m_pParent ( NULL  )
      { }

      void  SetParent ( Node* pParent)
      {
         m_pParent = pParent;
      }
      void  AddChild ( Node* pChild )
      {
         m_childs.push_back ( pChild );
         pChild->SetParent  ( this );
      }
      void  RemoveChild ( Node* pChild )
      {
         m_childs.remove ( pChild );
      }

   private:
      std::list < Node* >  m_childs;
      Node*                m_pParent;
      int                  m_id;
      std::string          m_name;
   };

}

namespace BinaryTree {

   class Node
   {
   public:
      Node ( int id, std::string name = "" )
      : m_id   ( id )
      , m_name ( name  )
      , m_pLeft  ( NULL )
      , m_pRight ( NULL )
      { }

      Node* getLeft ()
      {
         return m_pLeft;
      }
      Node* getRight ()
      {
         return m_pRight;
      }
      std::string getName ()
      {
         return m_name;
      }
      int   getId ()
      {
         return m_id;
      }

      void SetLeft ( Node* pLeft )
      {
         m_pLeft = pLeft;
      }
      void SetRight ( Node* pRight )
      {
         m_pRight = pRight;
      }

   private:
      Node*                m_pLeft;
      Node*                m_pRight;
      int                  m_id;
      std::string          m_name;
   };

}

#endif /* TRAVERSAL_NODE_HPP_ */
