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

using namespace Graph;

int main ()
{
   SimpleGraph*   pGraph = new SimpleGraph( "ValeDosSinos" );

   Vertex*  pVertex0 = new Vertex ( 0, "Novo Hamburgo" );
   Vertex*  pVertex1 = new Vertex ( 1, "São Leopoldo" );
   Vertex*  pVertex2 = new Vertex ( 2, "Campo Bom" );
   Vertex*  pVertex3 = new Vertex ( 3, "Ivoti" );
   Vertex*  pVertex4 = new Vertex ( 4, "Estância Velha" );
   Vertex*  pVertex5 = new Vertex ( 5, "Dois Irmãos" );

   new Edge (0, 10, pVertex1, pVertex0 );
   new Edge (1,  5, pVertex0, pVertex2 );
   new Edge (2, 20, pVertex0, pVertex5 );
   new Edge (3,  5, pVertex2, pVertex5 );
   new Edge (4,  8, pVertex0, pVertex4 );
   new Edge (5,  8, pVertex4, pVertex3 );
   new Edge (6, 15, pVertex0, pVertex3 );

   pGraph->AddVertex( pVertex0 );
   pGraph->AddVertex( pVertex1 );
   pGraph->AddVertex( pVertex2 );
   pGraph->AddVertex( pVertex3 );
   pGraph->AddVertex( pVertex4 );
   pGraph->AddVertex( pVertex5 );

   pGraph->Display( std::cout );

}
