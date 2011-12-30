/* Copyright (c) 1997-2010
   Ewgenij Gawrilow, Michael Joswig (Technische Universitaet Darmstadt, Germany)
   http://www.polymake.de

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; either version 2, or (at your option) any
   later version: http://www.gnu.org/licenses/gpl.txt.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
--------------------------------------------------------------------------------
   $Project: polymake $$Id: bindings.cc 9691 2010-05-28 23:47:18Z gawrilow $
*/

namespace polymake { namespace tom {
///==== Automatically generated contents follow.    Please do not delete this line. ====
   FunctionWrapper4perl( pm::Array<pm::Set<int, pm::operations::cmp>, void> (pm::Set<int, pm::operations::cmp> const&) ) {
      perl::Value arg0(stack[0]);
      IndirectWrapperReturn( arg0.get< perl::TryCanned< const Set< int > > >() );
   }
   FunctionWrapperInstance4perl( pm::Array<pm::Set<int, pm::operations::cmp>, void> (pm::Set<int, pm::operations::cmp> const&) );

   FunctionWrapper4perl( std::list<pm::Array<pm::Set<int, pm::operations::cmp>, void>, std::allocator<pm::Array<pm::Set<int, pm::operations::cmp>, void> > > (pm::Array<pm::Set<int, pm::operations::cmp>, void>) ) {
      perl::Value arg0(stack[0]);
      IndirectWrapperReturn( arg0.get< perl::TryCanned< const Array< Set< int > > > >() );
   }
   FunctionWrapperInstance4perl( std::list<pm::Array<pm::Set<int, pm::operations::cmp>, void>, std::allocator<pm::Array<pm::Set<int, pm::operations::cmp>, void> > > (pm::Array<pm::Set<int, pm::operations::cmp>, void>) );

   FunctionWrapper4perl( pm::Array<pm::Array<pm::Set<int, pm::operations::cmp>, void>, void> (pm::Array<pm::Set<int, pm::operations::cmp>, void>) ) {
      perl::Value arg0(stack[0]);
      IndirectWrapperReturn( arg0.get< perl::TryCanned< const Array< Set< int > > > >() );
   }
   FunctionWrapperInstance4perl( pm::Array<pm::Array<pm::Set<int, pm::operations::cmp>, void>, void> (pm::Array<pm::Set<int, pm::operations::cmp>, void>) );

///==== Automatically generated contents end here.  Please do not delete this line. ====
} }
