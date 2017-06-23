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

#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>

namespace BinaryTree {

   ////////////////////////////////////////////////////////////////////////////
   ///
   ////////////////////////////////////////////////////////////////////////////
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
      int                  m_id;
      std::string          m_name;
      Node*                m_pLeft;
      Node*                m_pRight;
   };


   ////////////////////////////////////////////////////////////////////////////
   ///
   ////////////////////////////////////////////////////////////////////////////
   class Tree
   {
   public:

      Tree ()
      : m_pRoot ( NULL )
      {
      }

      void  Insert ( Node* pNode )
      {
         if ( 0 == m_pRoot )
         {
            m_pRoot = pNode;
            m_pRoot->SetLeft ( NULL );
            m_pRoot->SetRight( NULL );
         }
         else
         {
            Insert ( pNode, m_pRoot );
         }
      }

      void Print ( std::ostream& output )
      {
         Print ( output, m_pRoot, 1 );
         output << std::endl;
      }

      void PreOrder ( std::ostream& output )
      {
         PreOrder (std::cout, m_pRoot );
      }

      void InOrder ( std::ostream& output )
      {
         InOrder (std::cout, m_pRoot );
      }

      void PostOrder ( std::ostream& output )
      {
         PostOrder (std::cout, m_pRoot );
      }

   private:

      void PostOrder ( std::ostream& output, Node* pNode )
      {
         if ( NULL != pNode )
         {
            PostOrder (std::cout, pNode->getLeft()  );
            PostOrder (std::cout, pNode->getRight() );
            output << pNode->getId();
            output << "  ";
         }
      }

      void InOrder ( std::ostream& output, Node* pNode )
      {
         if ( NULL != pNode)
         {
            InOrder (std::cout, pNode->getLeft() );
            output << pNode->getId();
            output << "  ";
            InOrder (std::cout, pNode->getRight() );
         }
      }

      void PreOrder ( std::ostream& output, Node* pNode )
      {
         if ( NULL != pNode )
         {
            output << pNode->getId();
            output << "  ";

            PreOrder ( output, pNode->getLeft()  );
            PreOrder ( output, pNode->getRight() );
         }
      }

      void Print ( std::ostream& output, Node* pNode, int level )
      {
         if ( NULL != pNode )
         {
            Print ( output, pNode->getRight(), level + 1 );
            output << std::endl;
            if ( pNode == m_pRoot )
            {
               output << "Root: ";
            }
            else
            {
               for (int i=0; i < level; i++ )
               {
                  output << "     ";
               }
            }
            output << (int)pNode->getId();
            Print ( output, pNode->getLeft(), level + 1 );
         }
      }


      void Insert ( Node* pNode, Node* pLeaf )
      {
         if ( pNode->getId() < pLeaf->getId() )
         {
            if ( NULL == pLeaf->getLeft() )
            {
               pLeaf->SetLeft( pNode );
            }
            else
            {
               Insert( pNode, pLeaf->getLeft() );
            }
         }
         else
         {
            if ( NULL == pLeaf->getRight() )
            {
               pLeaf->SetRight( pNode );
            }
            else
            {
               Insert( pNode, pLeaf->getRight() );
            }
         }
      }

      Node* m_pRoot;
   };

}

#endif
